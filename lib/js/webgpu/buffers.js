
export const Buffers = {
    init,
};

function init(device) {
    return {
        create: (props) => create(device, props)
    }
}

function create(device, props) {
    const size = props.size ? props.size : props.data.byteLength;
    const type = props.type ? props.type : getDataType(props.data);
    const usage = getUsageFlags(props.usage);

    const handle = device.createBuffer({
        size,
        usage
    });
    
    if (props.data) {
        device.queue.writeBuffer(handle, 0, props.data);
    }

    return { handle, type, usage };
}

function getDataType(data) {
    switch (data.type) {
        case Float32Array:
            return "float32";
        case Uint8Array:
            return "uint8";
        case Uint16Array:
            return "uint16";
        case Uint32Array:
            return "uint32";
        case Int8Array:
            return "sint8";
        case Int16Array:
            return "sint16";
        case Int32Array:
            return "sint32";
    }
}

const FLAG_NAMES_TO_BIT = {
    vertex: GPUBufferUsage.VERTEX,
    index: GPUBufferUsage.INDEX,
    uniform: GPUBufferUsage.UNIFORM,
    storage: GPUBufferUsage.STORAGE,
    indirect: GPUBufferUsage.INDIRECT,
    "copy-src": GPUBufferUsage.COPY_SRC,
    "copy-dst": GPUBufferUsage.COPY_DST,
    "map-read": GPUBufferUsage.MAP_READ,
    "map-write": GPUBufferUsage.MAP_WRITE,
    "query-resove": GPUBufferUsage.QUERY_RESOLVE
};

function getUsageFlags(flagNames) {
    return flagNames.reduce((bits, name) => bits | FLAG_NAMES_TO_BIT[name], 0);
}