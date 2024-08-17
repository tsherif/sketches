export const Bindings = {
    init,
};

function init(device) {
    return {
        createLayout: (entries) => createLayout(device, entries)
    }
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
            if (typeof e === "string") {
                return {
                    binding: i,
                    visibility: ALL_STAGES,
                    [e]: {}
                }
            }
        })
    });

    return { handle };
}
