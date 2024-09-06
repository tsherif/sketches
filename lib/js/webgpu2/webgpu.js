import { Buffers } from "./buffers.js";
import { Commands } from "./commands.js";
import { Render } from "./render.js";
import { Bindings } from "./bindings.js";
import { Textures } from "./textures.js";

export const WebGPU = {
    init,
}

async function init() {
    const adapter = await navigator.gpu.requestAdapter();
    const [adapterInfo, device] = await Promise.all([
        adapter.requestAdapterInfo(),
        adapter.requestDevice()
    ]);
    const presentationFormat = navigator.gpu.getPreferredCanvasFormat();

    const webgpu = {
        INFO: adapterInfo,
        CANVAS_FORMAT: presentationFormat,
        adapter,
        device,
        configureContext: (context) =>  context.configure({ device, format: presentationFormat }),
        buffers: Buffers.init(device),
        render: Render.init(device),
        commands: Commands.init(device),
        bindings: Bindings.init(device),
        textures: Textures.init(device)
    };

    return webgpu;
}

function configureContext(device, format, context) {
    context.configure({
        device,
        format
    });
}