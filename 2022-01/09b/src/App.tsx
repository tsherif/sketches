import React, { useEffect, useRef } from "react";
import { useSelector, useDispatch } from "react-redux";
import { PicoGL, App as PicoGLApp, DrawCall, VertexArray, UniformBuffer } from "picogl";
import {vec3, mat4} from "gl-matrix";
import { createCube } from "../../../lib/utils";

import {
    initObservable,
    simulate,
    dimensions,
    selectObservable,
    selectDimensions,
    selectModelMatrix,
    selectProjectionMatrix
} from "./redux/store";

function useModelMatrix() {
    const modelMatrix = useSelector(selectModelMatrix);
    const dispatch = useDispatch();

    useEffect(() => {
        let rafId: number;
        const loop = () => {
            rafId = requestAnimationFrame(loop);
            dispatch(simulate(performance.now()));
        }

        rafId = requestAnimationFrame(loop);

        return () => cancelAnimationFrame(rafId);
    }, []);

    return modelMatrix;
}

function useDimensions() {
    const currentDimensions = useSelector(selectDimensions);
    const dispatch = useDispatch();

    useEffect(() => {
        const handleResize = () => dispatch(dimensions(window.innerWidth, window.innerHeight));

        window.addEventListener("resize", handleResize);

        return () => window.removeEventListener("resize", handleResize);
    }, [])

    return currentDimensions;
}

export function App() {
    const canvasRef = useRef<HTMLCanvasElement>(null);
    const picoglRef = useRef<PicoGLApp>(null);
    const drawCallRef = useRef<DrawCall>(null);
    const viewMatrixRef = useRef<mat4>(null);
    const vertexArrayRef = useRef<VertexArray>(null);
    const sceneUniformRef = useRef<UniformBuffer>(null);
    const { width, height } = useDimensions();
    const modelMatrix = useModelMatrix();
    const projectionMatrix = useSelector(selectProjectionMatrix);
    const observable = useSelector(selectObservable);
    const dispatch = useDispatch();

    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvasRef.current) {
            return;
        }

        picoglRef.current = PicoGL.createApp(canvas)
            .clearColor(0.0, 0.0, 0.0, 1.0)
            .enable(PicoGL.DEPTH_TEST);

        const picogl = picoglRef.current;

        // SET UP GEOMETRY
        let cube = createCube({dimensions: [1.0, 1.0, 1.0]})
        let positions = picogl.createVertexBuffer(PicoGL.FLOAT, 3, cube.positions);
        let uv = picogl.createVertexBuffer(PicoGL.FLOAT, 2, cube.uvs);
        let normals = picogl.createVertexBuffer(PicoGL.FLOAT, 3, cube.normals);

        vertexArrayRef.current = picogl.createVertexArray()
            .vertexAttributeBuffer(0, positions)
            .vertexAttributeBuffer(1, uv)
            .vertexAttributeBuffer(2, normals)

        // SET UP UNIFORM BUFFER
        const lightPosition = vec3.fromValues(1, 1, 0.5);
        const eyePosition = vec3.fromValues(1, 1, 1);

        viewMatrixRef.current = mat4.lookAt(
            mat4.create(),
            eyePosition, 
            vec3.fromValues(0, 0, 0), 
            vec3.fromValues(0, 1, 0)
        );
        
        const viewProjMatrix = mat4.multiply(
            mat4.create(), 
            projectionMatrix,
            viewMatrixRef.current 
        );


        sceneUniformRef.current = picogl.createUniformBuffer([
            PicoGL.FLOAT_MAT4,
            PicoGL.FLOAT_VEC4,
            PicoGL.FLOAT_VEC4
        ])
            .set(0, new Float32Array(viewProjMatrix))
            .set(1, new Float32Array(eyePosition))
            .set(2, new Float32Array(lightPosition))
            .update();

        const vsSource = `
            #version 300 es

            layout(std140, column_major) uniform;

            layout(location=0) in vec4 position;
            layout(location=1) in vec2 uv;
            layout(location=2) in vec4 normal;
            
            uniform SceneUniforms {
                mat4 viewProj;
                vec4 eyePosition;
                vec4 lightPosition;
            };

            uniform mat4 uModel;
            
            out vec3 vPosition;
            out vec2 vUV;
            out vec3 vNormal;

            void main() {
                vec4 worldPosition = uModel * position;
                vPosition = worldPosition.xyz;
                vUV = uv;
                vNormal = (uModel * normal).xyz;
                gl_Position = viewProj * worldPosition;
            }
        `;

        const fsSource = `
            #version 300 es
            precision highp float;

            layout(std140, column_major) uniform;

            uniform SceneUniforms {
                mat4 viewProj;
                vec4 eyePosition;
                vec4 lightPosition;
            };

            uniform sampler2D tex;
            
            in vec3 vPosition;
            in vec2 vUV;
            in vec3 vNormal;

            out vec4 fragColor;
            void main() {
                vec3 color = texture(tex, vUV).rgb;

                vec3 normal = normalize(vNormal);
                vec3 eyeVec = normalize(eyePosition.xyz - vPosition);
                vec3 incidentVec = normalize(vPosition - lightPosition.xyz);
                vec3 lightVec = -incidentVec;
                float diffuse = max(dot(lightVec, normal), 0.0);
                float highlight = pow(max(dot(eyeVec, reflect(incidentVec, normal)), 0.0), 100.0);
                float ambient = 0.1;
                fragColor = vec4(color * (diffuse + highlight + ambient), 1.0);
            }
        `;

        dispatch(initObservable({ picogl, vs: vsSource, fs: fsSource, imageURL: "./webgl-logo.png" }));
    }, []);

    useEffect(() => {
        const picogl = picoglRef.current;

        if (!picogl || !observable) {
            return;
        }

        observable.subscribe({
            next: (({program, image}) => {
                if (!program || !image) {
                    return;
                }

                drawCallRef.current = picogl.createDrawCall(program, vertexArrayRef.current)
                .uniformBlock("SceneUniforms", sceneUniformRef.current)
                .texture("tex", picoglRef.current.createTexture2D(image, { 
                    flipY: true,
                    maxAnisotropy: PicoGL.WEBGL_INFO.MAX_TEXTURE_ANISOTROPY 
                }));
            })
        });
    }, [observable]);

    useEffect(() => {
        const picogl = picoglRef.current;
        
        if (!picogl) {
            return;
        }

        picogl.resize(width, height);
        sceneUniformRef.current.set(0, new Float32Array(mat4.multiply(
            mat4.create(), 
            projectionMatrix,
            viewMatrixRef.current 
        ))).update();
    }, [width, height]);

    useEffect(() => {
        const picogl = picoglRef.current;
        const drawCall = drawCallRef.current;
        
        if (!picogl || !drawCall) {
            return;
        }

        picoglRef.current.clear();
        drawCallRef.current
            .uniform("uModel", modelMatrix)
            .draw();

    }, [modelMatrix, width, height]);

    return (
        <canvas ref={canvasRef}></canvas>
    );
}