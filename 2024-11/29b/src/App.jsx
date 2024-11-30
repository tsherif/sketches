import React, { useLayoutEffect, useRef, useState } from "react";
import { Canvas, useLoader, useThree } from "@react-three/fiber";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader";
import { CameraControls } from "@react-three/drei";

function Scene() {
    const model = useLoader(GLTFLoader, "models/antique-camera/glTF/AntiqueCamera.gltf");

    return (
        <>
            <color args={['gray']} attach="background" />
            <ambientLight intensity={0.1} />
            <pointLight position={[5, 5, 5]} color="white" decay={0} intensity={5} />
            <pointLight position={[-5, 5, -5]} color="white" decay={0} intensity={5} />
            <primitive position={[0, -4, 0]} object={model.scene} />
        </>
    )
}

export function App() {
    return (
        <Canvas camera={{fov: 90, near: 0.1, far: 30, position: [0, 0, 7]}} >
            <CameraControls />
            <Scene /> 
        </Canvas>
    );
}