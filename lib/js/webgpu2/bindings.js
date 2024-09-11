
export const Bindings = {
    init,
};

function init(device) {
    return {
        create: (layout, entries) => create(device, layout, entries),
        createLayout: (entries) => createLayout(device, entries),
    };
}

function create(device, layout, entries) {
    return device.createBindGroup({
        layout: layout.handle,
        entries: Object.entries(entries).map(([name, resource]) => {
            const { binding, type } = layout.entryByName[name];
            if (type === "buffer") {
                return {
                    binding,
                    resource: {
                        buffer: resource.handle
                    }
                };
            }

            if (type === "texture") {
                return {
                    binding,
                    resource: resource.handle.createView()
                };
            }

            if (type === "sampler") {
                return {
                    binding,
                    resource: resource.handle
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

function createLayout(device, props) {
    const entries = [];
    const entryByName = {};
    Object.entries(props).forEach(([name, entry], i) => {
        const { type, visibility = ALL_STAGES, props = {}, shaderType } = entry;
        entries.push({
            binding: i,
            visibility,
            [type]: props
        });

        entryByName[name] = {
            binding: i,
            type,
            struct: entry.struct ?? null
        };
    })

    const handle = device.createBindGroupLayout({
        entries
    });

    return { handle, entryByName };
}

