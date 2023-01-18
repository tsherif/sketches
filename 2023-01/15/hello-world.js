const fs = require("fs");
const wasmCode = fs.readFileSync("./hello-world.wasm");

const startIndex = 100;
const buffer = new WebAssembly.Memory({ initial: 1 });

const importObject = {
    env: {
        buffer,
        startIndex,
        printString(len) {
            const bytes = new Uint8Array(buffer.buffer, startIndex, len);
            const text = new TextDecoder("utf8").decode(bytes);
            console.log(text);
        }
    }
};

(async () => {
    const wasm = await WebAssembly.instantiate(new Uint8Array(wasmCode), importObject);
    const { helloWorld } = wasm.instance.exports;
    helloWorld();
})();