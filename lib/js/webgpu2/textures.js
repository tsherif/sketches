export const Textures = {
    init,
};

function init(device) {
    return {
        create: (props) => create(device, props),
        createFromImage: (image, props = {}) => createFromImage(device, image, props),
        createSampler: (props) => createSampler(device, props)
    };
};

const FLAG_NAMES_TO_BIT = {
    "texture": GPUTextureUsage.TEXTURE_BINDING,
    "storage": GPUTextureUsage.STORAGE_BINDING,
    "render": GPUTextureUsage.RENDER_ATTACHMENT,
    "copy-src": GPUTextureUsage.COPY_SRC,
    "copy-dst": GPUTextureUsage.COPY_DST
};

function create(device, props) {
    const handle = device.createTexture({
        ...props,
        usage: props.usage.reduce((bits, name) => bits | FLAG_NAMES_TO_BIT[name], 0),
        sampleCount: props.multisample ? 4 : 1
    });

    return {
        handle,
        ...props
    }
}

function createFromImage(device, image, props) {
    const handle = device.createTexture({
        size: [image.width, image.height],
        format: props.format ?? "rgba8unorm",
        mipLevelCount: getMipLevelCount(image.width, image.height),
        usage: GPUTextureUsage.TEXTURE_BINDING | GPUTextureUsage.COPY_DST | GPUTextureUsage.RENDER_ATTACHMENT
    });

    device.queue.copyExternalImageToTexture(
        { source: image, flipY: props.flipY ?? true },
        { texture: handle },
        {
            width: image.width,
            height: image.height
        }
    );

    generate2DMipmap(device, handle);

    return { handle };
}

function createSampler(device, props) {
    return {
        handle: device.createSampler(props),
        ...props
    };
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