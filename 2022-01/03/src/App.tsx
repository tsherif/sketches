import React, { useEffect, useRef, useState } from "react";
import { useSelector, useDispatch } from "react-redux";
import { PicoGL, App as PicoGLApp, DrawCall } from "picogl";

import {dimensions, dimensionsSelector} from "./store";

function useDimensions() {
    const currentDimensions = useSelector(dimensionsSelector);
    const dispatch = useDispatch();

    useEffect(() => {
        const handleResize = () => {
            dispatch(dimensions(window.innerWidth, window.innerHeight));
        };
        window.addEventListener("resize", handleResize);

        return () => window.removeEventListener("resize", handleResize);
    }, [])

    return currentDimensions;
}

export function App() {
    const canvasRef = useRef<HTMLCanvasElement>(null);
    const picoglRef = useRef<PicoGLApp>(null);
    const drawCallRef = useRef<DrawCall>(null);
    const { width, height } = useDimensions();
    const [loaded, setLoaded] = useState(false);

    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvasRef.current) {
            return;
        }

        picoglRef.current = PicoGL.createApp(canvas)
        .clearColor(0.0, 0.0, 0.0, 1.0);

        const picogl = picoglRef.current;

        // GEOMETRY IN VERTEX BUFFERS
        let positions = picogl.createVertexBuffer(PicoGL.FLOAT, 2, new Float32Array([
            -0.5, -0.5,
             0.5, -0.5,
             0.0, 0.5, 
        ]));

        let colors = picogl.createVertexBuffer(PicoGL.UNSIGNED_BYTE, 3, new Uint8Array([
            255, 0, 0,
            0, 255, 0,
            0, 0, 255
        ]));

        // COMBINE VERTEX BUFFERS INTO VERTEX ARRAY
        let triangleArray = picogl.createVertexArray()
        .vertexAttributeBuffer(0, positions)
        .vertexAttributeBuffer(1, colors, { normalized: Number(true) });

        const vsSource = `
            #version 300 es
            
            layout(location=0) in vec4 position;
            layout(location=1) in vec3 color;
            
            out vec3 vColor; 
            void main() {
                vColor = color;
                gl_Position = position;
            }
        `;

        const fsSource = `
            #version 300 es
            precision highp float;
            
            in vec3 vColor;
            
            out vec4 fragColor;
            void main() {
                fragColor = vec4(vColor, 1.0);
            }
        `;

        picogl.createPrograms([vsSource, fsSource]).then(function([program]) {
            drawCallRef.current = picogl.createDrawCall(program, triangleArray);
            setLoaded(true);
        });
    }, []);

    useEffect(() => {
        const picogl = picoglRef.current;
        
        if (!picogl) {
            return;
        }

        picogl.resize(width, height);
    }, [width, height]);

    useEffect(() => {
        if (!loaded) {
            return;
        }

        const picogl = picoglRef.current;
        const drawCall = drawCallRef.current;

        picogl.clear();
        drawCall.draw();
    }, [loaded, width, height]);

    return (
        <canvas ref={canvasRef}></canvas>
    );
}