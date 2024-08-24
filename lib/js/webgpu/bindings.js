export const Bindings = {
    init,
};

function init(device) {
    return {
        create: (layout, entries) => create(device, layout, entries),
        createLayout: (entries) => createLayout(device, entries)
    };
}

function create(device, layout, entries) {
    return device.createBindGroup({
        layout: layout?.handle,
        entries: entries.map((e, i) => {
            if (e.buffer) {
                return {
                    binding: i,
                    resource: {
                        buffer: e.buffer?.handle
                    }
                };
            }

            if (e.texture) {
                return {
                    binding: i,
                    resource: e.texture.handle.createView()
                };
            }

            if (e.sampler) {
                return {
                    binding: i,
                    resource: e.sampler.handle
                };
            }
        })
    });
}

const ALL_STAGES = GPUShaderStage.VERTEX | GPUShaderStage.FRAGMENT | GPUShaderStage.COMPUTE;

const STAGE_NAME_TO_FLAG = {
    vertex: GPUShaderStage.VERTEX,
    fragment: GPUShaderStage.FRAGMENT,
    compute: GPUShaderStage.COMPUTE 
};

function createLayout(device, entries) {
    const handle = device.createBindGroupLayout({
        entries: entries.map((e, i) => {
            let type, props;
            if (typeof e === "string") {
                type = e;
                props = {};
            } else {
                type = e[0];
                props = e[1];
            }

            return {
                binding: i,
                visibility: ALL_STAGES,
                [type]: props
            }
        })
    });

    return { handle };
}
