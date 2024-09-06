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

function createLayout(device, props) {
    const entries = [];
    const shaderParts = [];
    const nameToBinding = {};
    Object.entries(props).forEach(([name, entry], i) => {
        const { type, visibility = ALL_STAGES, props = {}, shaderType } = entry;
        entries.push({
            binding: i,
            visibility,
            [type]: props
        });
        nameToBinding[name] = i;

        let shaderDeclaration;

        switch (type) {
            case "buffer": 
                shaderDeclaration = `@binding(${i}) var<uniform> ${name}: ${shaderType};`;
                break;
            case "sampler":
                shaderDeclaration = `@binding(${i}) var ${name}: sampler;`;
                break;
            case "texture":
                shaderDeclaration = `@binding(${i}) var ${name}: texture_2d<f32>;`;
                break;
        }

        shaderParts.push(shaderDeclaration)
        nameToBinding[name] = i;
    })

    const handle = device.createBindGroupLayout({
        entries
    });

    return { handle, shaderParts, nameToBinding };
}
