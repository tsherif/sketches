import React, { useLayoutEffect, useRef, useState } from "react";
import { Canvas, useLoader, useThree } from "@react-three/fiber";
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';

function Scene() {
    const objectRef = useRef();
    const model = useLoader(GLTFLoader, "models/antique-camera/glTF/AntiqueCamera.gltf");
    const gl = useThree(state => state.gl);
    const camera = useThree(state => state.camera);
    const controlsRef = useRef();

    useLayoutEffect(() => {
        controlsRef.current = new OrbitControls(camera, gl.domElement);
        controlsRef.current.target.set(0, 3.5, 0);
        controlsRef.current.update();
    }, [camera])

    return (
        <>
            <color args={['gray']} attach="background" />
            <ambientLight intensity={0.1} />
            <pointLight position={[5, 5, 5]} color="white" decay={0} intensity={5} />
            <pointLight position={[-5, 5, -5]} color="white" decay={0} intensity={5} />
            <group ref={objectRef} >
                <primitive position={[0, -1, 0]} object={model.scene} />
            </group>
        </>
    )
}

export function App() {
    return (
        <Canvas camera={{fov: 90, near: 0.1, far: 30, position: [0, 6, 4]}} >
            <Scene /> 
        </Canvas>
    );
}