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
        .enable(PicoGL.SCISSOR_TEST);
        this.widgets = [];
        this.boundaries = [];

        const loop = () => {
            requestAnimationFrame(loop);

            this.boundaries.length = this.widgets.length;
            this.widgets.forEach((w, i) => this.boundaries[i] = w.element.getBoundingClientRect());

            this.app
            .clearColor(0, 0, 0, 0)
            .clear();
            
            this.widgets.forEach((w, i) => {
                const boundary = this.boundaries[i];

                const viewportLeft = boundary.left;
                const viewportRight = boundary.right;
                const viewportTop = boundary.top;
                const viewportBottom = boundary.bottom;

                const viewportWidth = viewportRight - viewportLeft;
                const viewportHeight = viewportBottom - viewportTop;
                const viewportX = viewportLeft;
                const viewportY = window.innerHeight - viewportBottom;

                const scissorLeft = Math.max(0, viewportLeft);
                const scissorRight = Math.min(window.innerWidth, viewportRight);
                const scissorTop = Math.max(0, viewportTop);
                const scissorBottom = Math.min(window.innerHeight, viewportBottom);

                const scissorWidth = scissorRight - scissorLeft;
                const scissorHeight = scissorBottom - scissorTop;
                const scissorX = scissorLeft;
                const scissorY = window.innerHeight - scissorBottom;

                if (scissorWidth < 1 || scissorHeight < 1) {
                    return;
                }

                this.app.viewport(viewportX, viewportY, viewportWidth, viewportHeight);
                this.app.scissor(scissorX, scissorY, scissorWidth, scissorHeight);

                w.draw();
            });

        }

        requestAnimationFrame(loop);
    }

    registerWidget(w) {
        this.widgets.push(w);

    }
}

const WebGLEngine = React.createContext();

function WebGLWidget(props) {
    const engine = useContext(WebGLEngine);
    const style = Object.assign({
        width: 100,
        height: 100,
        display: "inline-block"
    }, props.style);
    const ref = React.createRef();

    useEffect(() => {
        if (!engine || !ref.current) {
            return;
        }

        const {app} = engine;

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

        app.createPrograms([vs, fs]).then(([program]) => {
            const drawCall = app.createDrawCall(program, vertexArray)

            engine.registerWidget({
                element: ref.current,
                draw: () => {
                    app.clearColor(0, 0, 0, 1)
                    .clear();

                    drawCall.draw();
                }
            });
        });
    }, [engine, ref.current]);

    return <div style={style} ref={ref}></div>;
}

function WebGLDashboard(props) {
    const [engine, setEngine] = useState(null);
    const [dimensions, setDimensions] = useState({width: 0, height: 0});
    const canvasRef = React.createRef();

    useEffect(() => {
        setEngine(new Engine(canvasRef.current));
    }, []);

    useEffect(() => {
        setDimensions({width: window.innerWidth, height: window.innerHeight});
    }, [window.innerWidth, window.innerHeight]);

    const style = {
        position: "fixed",
        top: 0,
        left: 0
    };

    return (
        <WebGLEngine.Provider value={engine}>
            <canvas ref={canvasRef} width={window.innerWidth} height={window.innerHeight} style={style} />
            {props.children}
        </WebGLEngine.Provider>
    );
}

ReactDOM.render(
    (
        <WebGLDashboard>
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            <div style={{margin: 20}}>
                <h1>Mixing WebGL widgets...</h1>
                <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
                <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            </div>
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            <div>
                <h2>...with other things!</h2>
                <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
                <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
                <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            </div>
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
            <WebGLWidget style={{width: Math.random() * 100 + 100, height: Math.random() * 100 + 100, margin: 5}} />
        </WebGLDashboard>
    ),
    document.getElementById("root")
);
