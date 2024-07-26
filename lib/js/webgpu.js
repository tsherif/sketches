
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

const FORMAT_STRIDES = {
    float32x2: 8,
    unorm8x4: 4
}

export function createRenderPipeline(device, props) {
    const {code, vertexEntry, fragmentEntry, buffers: bufferCfg, presentationFormat, topology} = props;

    // const shaderModule = device.createShaderModule({
    //     code
    // });

    // const buffers = bufferCfg.map((format, i) => ({
    //     arrayStride: FORMAT_STRIDES[format],
    //     attributes: [{
    //         shaderLocation: i,
    //         format,
    //         offset: 0
    //     }]
    // }))

    // const pipeline = device.createRenderPipeline({
    //     layout: 'auto',
    //     vertex: {
    //         module: shaderModule,
    //         entryPoint: vertexEntry,
    //         buffers,
    //     },
    //     fragment: {
    //         module: shaderModule,
    //         entryPoint: fragmentEntry,
    //         targets: [{
    //             format: presentationFormat
    //         }]
    //     },
    //     primitive: {
    //         topology
    //     }
    // });

    const shaderModule = device.createShaderModule({
        code: `
            struct VSOut {
                @builtin(position) position: vec4f,
                @location(0) color: vec4f
            };

            @vertex
            fn vs(
                @location(0) position: vec4f,
                @location(1) color: vec4f
            ) -> VSOut {
                return VSOut(position, color);
            }

            @fragment
            fn fs(
                @location(0) color: vec4f
            ) -> @location(0) vec4f {
                return color;
            }
        `
    });

    const pipeline = device.createRenderPipeline({
        layout: 'auto',
        vertex: {
            module: shaderModule,
            entryPoint: "vs",
            buffers: [
                {
                    arrayStride: 8,
                    attributes: [{
                        shaderLocation: 0,
                        format: "float32x2",
                        offset: 0
                    }]
                },
                {
                    arrayStride: 4,
                    attributes: [{
                        shaderLocation: 1,
                        format: "unorm8x4",
                        offset: 0
                    }]
                }
            ]
        },
        fragment: {
            module: shaderModule,
            entryPoint: "fs",
            targets: [{
                format: presentationFormat
            }]
        },
        primitive: {
            topology: "triangle-list"
        }
    });

    return pipeline;
}