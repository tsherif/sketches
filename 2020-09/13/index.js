import React, {useEffect, useState} from "react";
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

function Demo() {

    const [angle, setAngle] = useState(0);
    const [renderParameters] = useState({ angle })
    const canvasRef = React.createRef();

    console.log(`Angle: ${angle}`);

    renderParameters.angle = angle;

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

        let rafHandle = null;
        app.createPrograms([vs, fs]).then(([program]) => {
            resources.push(program);

            const drawCall = app.createDrawCall(program, vertexArray)

            function loop() {
                rafHandle = requestAnimationFrame(loop);

                app.clear();

                drawCall
                .uniform("angle", renderParameters.angle)
                .draw();
            }

            rafHandle = requestAnimationFrame(loop);

        });

        return () => {
            console.log("TEARDOWN");
            resources.forEach(r => r.delete());
            cancelAnimationFrame(rafHandle);
        }
    }, [])

    return <canvas id={angle} ref={canvasRef} width={window.innerWidth} height={window.innerHeight} onClick={() => setAngle(angle + 0.1)} />
}

ReactDOM.render(
    <Demo />,
    document.getElementById("root")
);
