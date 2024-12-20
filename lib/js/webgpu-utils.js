
export async function initWebGPU() {
    const adapter = await navigator.gpu.requestAdapter();
    const [adapterInfo, device] = await Promise.all([
        adapter.requestAdapterInfo(),
        adapter.requestDevice()
    ]);
    const presentationFormat = navigator.gpu.getPreferredCanvasFormat();

    return {
        device,
        adapterInfo,
        presentationFormat
    }
}

export function createVertexBuffer(device, data) {
    const buffer = device.createBuffer({
        size: data.byteLength,
        usage: GPUBufferUsage.VERTEX | GPUBufferUsage.COPY_DST
    });
    device.queue.writeBuffer(buffer, 0, data);

    return buffer;
}

export function createIndexBuffer(device, data) {
    const buffer = device.createBuffer({
        size: data.byteLength,
        usage: GPUBufferUsage.INDEX | GPUBufferUsage.COPY_DST
    });
    device.queue.writeBuffer(buffer, 0, data);

    const type = data.BYTES_PER_ELEMENT === 16 ? "uint16" : "uint32";

    return { buffer, type };
}

const TYPE_SIZES = {
    mat4x4f: 64,
    vec4f: 16
}

export function createUniformBuffer(device, props) {
    let size = 0;
    const offsets = {};
    let shaderParts = [];
    Object.entries(props).forEach(([name, type]) => {
        offsets[name] = size;
        size += TYPE_SIZES[type];
        shaderParts.push(`${name}: ${type}`);
    });

    const buffer = device.createBuffer({
        size,
        usage: GPUBufferUsage.UNIFORM | GPUBufferUsage.COPY_DST
    });

    return {
        buffer,
        size,
        offsets,
        shaderString: shaderParts.join(',\n')
    }
}

export function updateUniformBuffer(device, buffer, props) {
    Object.entries(props).forEach(([key, value]) => 
        device.queue.writeBuffer(buffer.buffer, buffer.offsets[key], value)
    );
}

export function createTextureFromImage(device, image, props = {}) {
    const texture = device.createTexture({
        size: [image.width, image.height],
        format: props.format ?? "rgba8unorm",
        mipLevelCount: getMipLevelCount(image.width, image.height),
        usage: GPUTextureUsage.TEXTURE_BINDING | GPUTextureUsage.COPY_DST | GPUTextureUsage.RENDER_ATTACHMENT
    });

    device.queue.copyExternalImageToTexture(
        { source: image, flipY: props.flipY ?? true },
        { texture },
        {
            width: image.width,
            height: image.height
        }
    );

    generate2DMipmap(device, texture);

    return texture
}

const FORMAT_STRIDES = {
    float32x2: 8,
    float32x3: 12,
    unorm8x4: 4
}

export function createRenderPipeline(device, props) {
    const {
        code,
        vertexEntry,
        fragmentEntry,
        vertexBuffers: vertexBufferCfg,
        renderTargets,
        topology,
        cull,
        multisample,
        depth
    } = props;

    const shaderModule = device.createShaderModule({
        code
    });

    const buffers = vertexBufferCfg.map((cfgOrFormat, i) => {
        const cfg = typeof cfgOrFormat === "string" ? { 
            format: cfgOrFormat,
            stride: FORMAT_STRIDES[cfgOrFormat]
        } : cfgOrFormat;
        const { format, stride, step} = cfg;
        return {
            arrayStride: stride,
            stepMode: step,
            attributes: [{
                shaderLocation: i,
                format,
                offset: 0
            }]
        }
    })

    const pipeline = device.createRenderPipeline({
        layout: 'auto',
        vertex: {
            module: shaderModule,
            entryPoint: vertexEntry,
            buffers,
        },
        fragment: {
            module: shaderModule,
            entryPoint: fragmentEntry,
            targets: renderTargets.map(t => ({ format: t }))
        },
        primitive: {
            topology,
            cullMode: cull
        },
        multisample: multisample ? { count: 4 } : undefined,
        depthStencil: depth ? {
            format: "depth24plus",
            depthWriteEnabled: true,
            depthCompare: "less"
        } : undefined
    });

    return pipeline;
}

export function createUniformSet(device, layout, entries) {
    return device.createBindGroup({
        layout: layout,
        entries: entries.map((e, i) => {
            if (e.buffer) {
                return {
                    binding: i,
                    resource: {
                        buffer: e.buffer?.buffer ?? e.buffer
                    }
                };
            }

            if (e.texture) {
                return {
                    binding: i,
                    resource: e.texture.createView()
                };
            }

            if (e.sampler) {
                return {
                    binding: i,
                    resource: e.sampler
                };
            }
        })
    });
}

export function createRenderPassConfig(props) {
    return {
        commands: props.commands,
        canvasTargets: props.color?.map(c => c.context),
        descriptor: {
            colorAttachments: props.color?.map(c => ({
                view: c.texture?.createView(),
                resolveTarget: undefined,
                loadOp: c.clear ? 'clear' : 'load',
                storeOp: 'store',
                clearValue: c.clear
            })),
            depthStencilAttachment: props.depth ? 
                {
                    view: props.depth.texture.createView(),
                    depthClearValue: props.depth.clear,
                    depthLoadOp: props.depth.clear ? 'clear' : 'load',
                    depthStoreOp: "store"
                } : undefined,
        }
    }
}

export function updateRenderPassConfigTextures(config, props) {
    const { descriptor } = config;
    if (props.color) {
        props.color.forEach((c, i) => {
            if (c && descriptor.colorAttachments?.[i]) {
                descriptor.colorAttachments[i].view = c.createView();
            }
        })
    }

    if (props.depth && descriptor.depthStencilAttachment) {
        descriptor.depthStencilAttachment.view = props.depth.createView();
    }
}

export function encodeRenderPass(commandEncoder, config) {
    const { 
        descriptor,
        canvasTargets,
        commands
    } = config;


    descriptor.colorAttachments.forEach((c, i) => {
        const context = canvasTargets[i];
        
        if (context) {
            if (c.view) {
                c.resolveTarget = context.getCurrentTexture().createView();
            } else {
                c.view = context.getCurrentTexture().createView();
            }
        }   
    });

    const renderPass = commandEncoder.beginRenderPass(descriptor);

    let indexedDraw = false;
    commands.forEach(d => {
        const { pipeline, mesh, uniforms, draw } = d;

        if (pipeline) {
            renderPass.setPipeline(pipeline);
        }

        if (mesh) {
            const { vertices, indices } = mesh;
            vertices.forEach((b, i) => renderPass.setVertexBuffer(i, b));
            if (indices) {
                renderPass.setIndexBuffer(indices.buffer, indices.type);
                indexedDraw = true;
            } else {
                indexedDraw = false;
            }
        }

        if (uniforms) {
            uniforms.forEach((u, i) => renderPass.setBindGroup(i, u));
        }

        if (draw) {
            const { vertices, instances = 1 } = draw;
            if (indexedDraw) {
                renderPass.drawIndexed(vertices, instances);
            } else if (vertices) {
                renderPass.draw(vertices, instances);
            }
        }
    })
    
    renderPass.end();
}

function getMipLevelCount(width, height = 0, depth = 0) {
    return 1 + Math.floor(Math.log2(Math.max(width, height, depth)));
}

// From: https://webgpufundamentals.org/webgpu/lessons/webgpu-importing-textures.html
const generate2DMipmap = (() => {
    let sampler;
    let module;

    const pipelines = {};

    return function generate2DMipmap(device, texture) {
        module ??= device.createShaderModule({
            label: "generateMipmap shader module",
            code: `
                struct VSOut {
                    @builtin(position) position: vec4f,
                    @location(0) uv: vec2f
                }

                @vertex 
                fn vs(@builtin(vertex_index) index: u32) -> VSOut {
                    let positions = array(
                        vec2f(-1, -1),
                        vec2f(1, -1),
                        vec2f(-1, 1),
                        vec2f(1, 1)
                    );

                    let pos = positions[index];
                    let uv = pos * 0.5 + 0.5;

                    var vsOut: VSOut;
                    vsOut.position = vec4f(pos, 0.0, 1.0);
                    vsOut.uv = vec2f(uv.x, 1.0 - uv.y);

                    return vsOut;
                }

                @group(0) @binding(0) var mipmapSampler: sampler;
                @group(0) @binding(1) var mipmapTexture: texture_2d<f32>;
            
            
                @fragment
                fn fs(fsIn: VSOut) -> @location(0) vec4f {
                    return textureSample(mipmapTexture, mipmapSampler, fsIn.uv);
                }
            `
        });

        sampler ??= device.createSampler({
            minFilter: "linear"
        })

        pipelines[texture.format] ??= device.createRenderPipeline({
            label: `mipmap pipeline`,
            layout: 'auto',
            vertex: {
                module,
                entryPoint: "vs"
            },
            fragment: {
                module,
                entryPoint: "fs",
                targets: [{
                    format: texture.format
                }]
            },
            primitive: {
                topology: "triangle-strip"
            }
        })

        const pipeline = pipelines[texture.format];

        const encoder = device.createCommandEncoder({
            label: "mipmap command encoder"
        });

        let { width, height } = texture;
        let mipLevel = 0;
        
        while (width > 1 || height > 1) {
            width = Math.max(1, Math.floor(width / 2));
            height = Math.max(1, Math.floor(height / 2));

            const bindGroup = device.createBindGroup({
                layout: pipeline.getBindGroupLayout(0),
                entries: [
                    { 
                        binding: 0, 
                        resource: sampler
                    },
                    { 
                        binding: 1, 
                        resource: texture.createView({
                            baseMipLevel: mipLevel,
                            mipLevelCount: 1
                        })
                    },
                ]
            })

            const pass = encoder.beginRenderPass({
                label: `mipmap level ${mipLevel} render pass`,
                colorAttachments: [
                    {
                        view: texture.createView({
                            baseMipLevel: mipLevel + 1,
                            mipLevelCount: 1
                        }),
                        loadOp: "load",
                        storeOp: "store"
                    }
                ]
            });

            pass.setPipeline(pipeline);
            pass.setBindGroup(0, bindGroup);
            pass.draw(4);
            pass.end();

            ++mipLevel;
        }

        device.queue.submit([encoder.finish()])
    };
})()