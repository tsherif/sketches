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
    constructor(container, canvas) {
        this.container = container;
        this.canvas = canvas;
        this.app = PicoGL.createApp(this.canvas)
        .enable(PicoGL.SCISSOR_TEST);
        this.widgets = [];
        this.boundaries = [];

        const pixelRatio = window.devicePixelRatio;

        const loop = () => {
            requestAnimationFrame(loop);

            const windowPixelWidth = window.innerWidth * pixelRatio;
            const windowPixelHeight = window.innerHeight * pixelRatio;
            
            const containerBoundary = this.container.getBoundingClientRect();

            const containerLeft = containerBoundary.left * pixelRatio;
            const containerRight = containerBoundary.right * pixelRatio;
            const containerTop = containerBoundary.top * pixelRatio;
            const containerBottom = containerBoundary.bottom * pixelRatio;

            this.boundaries.length = this.widgets.length;
            this.widgets.forEach((w, i) => this.boundaries[i] = w.element.getBoundingClientRect());

            this.app
            .clearColor(0, 0, 0, 0)
            .clear();

            this.widgets.forEach((w, i) => {
                const boundary = this.boundaries[i];

                const viewportLeft = boundary.left * pixelRatio;
                const viewportRight = boundary.right * pixelRatio;
                const viewportTop = boundary.top * pixelRatio;
                const viewportBottom = boundary.bottom * pixelRatio;

                const viewportWidth = viewportRight - viewportLeft;
                const viewportHeight = viewportBottom - viewportTop;
                const viewportX = viewportLeft;
                const viewportY = windowPixelHeight - viewportBottom;

                const scissorLeft = Math.max(0, viewportLeft, containerLeft);
                const scissorRight = Math.min(windowPixelWidth, viewportRight, containerRight);
                const scissorTop = Math.max(0, viewportTop, containerTop);
                const scissorBottom = Math.min(windowPixelHeight, viewportBottom, containerBottom);

                const scissorWidth = scissorRight - scissorLeft;
                const scissorHeight = scissorBottom - scissorTop;
                const scissorX = scissorLeft;
                const scissorY = windowPixelHeight - scissorBottom;

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
        display: "inline-block",
        backgroundColor: "red"
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
    const containerRef = React.createRef();
    const canvasRef = React.createRef();

    useEffect(() => {
        setEngine(new Engine(containerRef.current, canvasRef.current));
    }, []);

    useEffect(() => {
        setDimensions({width: window.innerWidth, height: window.innerHeight});

        function resize() {
            setDimensions({width: window.innerWidth, height: window.innerHeight});
        }

        window.addEventListener("resize", resize);

        return () => window.removeEventListener("resize", resize);
    }, [window.innerWidth, window.innerHeight]);

    const containerStyle = Object.assign({
        width: 400,
        height: 400,
        display: "inlineBlock",
        overflow: "auto"
    }, props.style);

    const canvasStyle = {
        position: "fixed",
        top: 0,
        left: 0,
        pointerEvents: "none",
        width: dimensions.width,
        height: dimensions.height
    };

    return (
        <div ref={containerRef} style={containerStyle}>
            <WebGLEngine.Provider value={engine}>
                <canvas ref={canvasRef} width={dimensions.width * window.devicePixelRatio} height={dimensions.height * window.devicePixelRatio} style={canvasStyle} />
                {props.children}
            </WebGLEngine.Provider>
        </div>
    );
}

ReactDOM.render(
    (
        <WebGLDashboard style={{height: 600, width: window.innerWidth}}>
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
