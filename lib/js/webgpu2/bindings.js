import { TYPE_SIZES } from "./constants.js";

export const Bindings = {
    init,
};

function init(device) {
    return {
        create: (layout, entries) => create(device, layout, entries),
        createLayout: (entries) => createLayout(device, entries),
        createStruct
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
    const shaderParts = [];
    const entryByName = {};
    Object.entries(props).forEach(([name, entry], i) => {
        const { type, visibility = ALL_STAGES, props = {}, shaderType } = entry;
        entries.push({
            binding: i,
            visibility,
            [type]: props
        });

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
        entryByName[name] = {
            binding: i,
            type
        };
    })

    const handle = device.createBindGroupLayout({
        entries
    });

    return { handle, shaderParts, entryByName };
}

function createStruct(props) {
    let size = 0;
    const offsets = {};
    let shaderParts = [];
    Object.entries(props).forEach(([name, type]) => {
        offsets[name] = size;
        size += TYPE_SIZES[type];
        shaderParts.push(`${name}: ${type}`);
    });

    return {
        size,
        offsets,
        shaderString: shaderParts.join(',\n')
    }
}