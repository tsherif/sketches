import React, {useEffect, useState, useContext} from "react";
import ReactDOM from "react-dom";
import PicoGL from "picogl";

const vs = `
    #version 300 es

    layout(location=0) in vec2 position;
    layout(location=1) in vec3 color;

    uniform float angle;

    out vec3 vColor;

    void main() {
        float c = cos(angle);
        float s = sin(angle);
        mat2 rot = mat2(
            c, s,
            -s, c
        );

        vColor = color;
        gl_Position = vec4(rot * position, 0.0, 1.0);
    }
`;

const fs = `
    #version 300 es
    precision highp float;

    in vec3 vColor;

    out vec4 fragColor;

    void main() {
        fragColor = vec4(vColor, 1.0);
    }
`;

class Engine {
    constructor(canvas) {
        this.canvas = canvas;
        this.app = PicoGL.createApp(this.canvas)
        .clearColor(0, 0, 0, 1);
        this.drawCalls = [];

        const loop = () => {
            requestAnimationFrame(loop);

            this.app.clear();
            this.drawCalls.forEach(d => d.draw());
        }

        requestAnimationFrame(loop);
    }

    addDrawCall(d) {
        this.drawCalls.push(d);
    }
}

const WebGLEngine = React.createContext();

function WebGLComponentLeft() {
    const engine = useContext(WebGLEngine);

    useEffect(() => {
        if (!engine) {
            return;
        }

        const {app} = engine;

        app.clearColor(0, 0, 0, 1)
        .clear();

        const positionData = new Float32Array([
            -0.7, -0.5,
            -0.3, -0.5,
            -0.5, 0.5
        ]);

        const colorData = new Uint8Array([
            255, 0, 0,
            0, 255, 0,
            0, 0, 255
        ]);

        const positions = app.createVertexBuffer(PicoGL.FLOAT, 2, positionData);
        const colors = app.createVertexBuffer(PicoGL.UNSIGNED_BYTE, 3, colorData);

        const vertexArray = app.createVertexArray()
        .vertexAttributeBuffer(0, positions)
        .vertexAttributeBuffer(1, colors, {normalized: true});

        app.createPrograms([vs, fs]).then(([program]) => {
            const drawCall = app.createDrawCall(program, vertexArray)

            engine.addDrawCall(drawCall);
        });
    }, [engine]);

    return null;
}

function WebGLComponentRight() {
    const engine = useContext(WebGLEngine);

    useEffect(() => {
        if (!engine) {
            return;
        }

        const {app} = engine;

        app.clearColor(0, 0, 0, 1)
        .clear();

        const positionData = new Float32Array([
            0.3, -0.5,
            0.7, -0.5,
            0.5, 0.5
        ]);

        const colorData = new Uint8Array([
            255, 0, 0,
            0, 255, 0,
            0, 0, 255
        ]);

        const positions = app.createVertexBuffer(PicoGL.FLOAT, 2, positionData);
        const colors = app.createVertexBuffer(PicoGL.UNSIGNED_BYTE, 3, colorData);

        const vertexArray = app.createVertexArray()
        .vertexAttributeBuffer(0, positions)
        .vertexAttributeBuffer(1, colors, {normalized: true});

        app.createPrograms([vs, fs]).then(([program]) => {
            const drawCall = app.createDrawCall(program, vertexArray)

            engine.addDrawCall(drawCall);
        });
    }, [engine]);

    return null;
}

function Demo() {
    const [engine, setEngine] = useState(null);
    const canvasRef = React.createRef();

    useEffect(() => {
        setEngine(new Engine(canvasRef.current));
    }, []);

    return (
        <WebGLEngine.Provider value={engine}>
            <canvas ref={canvasRef} width={window.innerWidth} height={window.innerHeight} />
            <WebGLComponentLeft />
            <WebGLComponentRight />
        </WebGLEngine.Provider>
    );
}

ReactDOM.render(
    <Demo />,
    document.getElementById("root")
);
