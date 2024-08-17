import { Buffers } from "./buffers.js";

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
        adapter,
        device,
        info: adapterInfo,
        presentationFormat,
        configureContext: (context) => configureContext(device, presentationFormat, context),
        buffers: Buffers.init(device)
    };

    return webgpu;
}

function configureContext(device, format, context) {
    context.configure({
        device,
        format
    });
}