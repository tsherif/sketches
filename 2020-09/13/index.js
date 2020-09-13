import React, {useEffect, useState} from "react";
import ReactDOM from "react-dom";
import PicoGL from "picogl";

const vs = `
    #version 300 es

    layout(location=0) in vec4 position;
    layout(location=1) in vec3 color;

    out vec3 vColor;

    void main() {
        vColor = color;
        gl_Position = position;
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

function Demo() {

    const [count, setCount] = useState(0);
    const canvasRef = React.createRef();

    console.log(`Count: ${count}`);

    useEffect(() => {
        console.log("SETUP");

        const app = PicoGL.createApp(canvasRef.current);
        const resources = [];

        app.clearColor(0, 0, 0, 1)
        .clear();

        const positionData = new Float32Array([
            -0.5, -0.5,
            0.5, -0.5,
            0.0, 0.5
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

        resources.push(positions, colors, vertexArray);

        app.createPrograms([vs, fs]).then(([program]) => {
            resources.push(program);

            app.createDrawCall(program, vertexArray)
            .draw();

        });

        return () => {
            console.log("TEARDOWN");
            resources.forEach(r => r.delete());
        }
    }, [])

    return <canvas ref={canvasRef} width={window.innerWidth} height={window.innerHeight} onClick={() => setCount(count + 1)} />
}

ReactDOM.render(
    <Demo />,
    document.getElementById("root")
);
