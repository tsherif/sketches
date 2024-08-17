export const Render = {
    init,
};

function init(device) {
    return {
        createPipeline: (props) => createPipeline(device, props)   
    };
}

const FORMAT_STRIDES = {
    uint8x2: 2,
    uint8x4: 4,
    sint8x2: 2,
    sint8x4: 4,
    unorm8x2: 2,
    unorm8x4: 4,
    snorm8x2: 2,
    snorm8x4: 4,
    uint16x2: 4,
    uint16x4: 8,
    sint16x2: 4,
    sint16x4: 8,
    unorm16x2: 4,
    unorm16x4: 8,
    snorm16x2: 4,
    snorm16x4: 8,
    float16x2: 4,
    float16x4: 8,
    float32: 4,
    float32x2: 8,
    float32x3: 12,
    float32x4: 16,
    uint32: 4,
    uint32x2: 8,
    uint32x3: 12,
    uint32x4: 16,
    sint32: 4,
    sint32x2: 8,
    sint32x3: 12,
    sint32x4: 16,
    "unorm10-10-10-2": 4
};



export function createPipeline(device, props) {
    const {
        code,
        vertexEntry,
        fragmentEntry,
        vertexBuffers: vertexBufferCfg,
        renderTargets,
        topology,
        cull,
        multisample,
        depth,
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

    const handle = device.createRenderPipeline({
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

    return { handle };
}