import React, { useRef, useState } from "react";
import { Canvas, useFrame, useLoader } from "@react-three/fiber";
import { TextureLoader } from 'three/src/loaders/TextureLoader';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';

function Scene() {
    const objectRef = useRef();
    const model = useLoader(GLTFLoader, "models/duck/glTF/Duck.gltf");

    useFrame(() => {
        objectRef.current.rotation.x += 0.01;
        objectRef.current.rotation.y += 0.02;
    });

    return (
        <>
            <color args={['black']} attach="background" />
            <ambientLight intensity={0.1} />
            <pointLight position={[1, 1, 0.5]} color="white" decay={0} />
            <group ref={objectRef} >
                <primitive position={[0, -1, 0]} object={model.scene} />
            </group>
        </>
    )
}

export function App() {
    return (
        <Canvas camera={{fov: 90, near: 0.1, far: 10, position: [1.5, 1.5, 1.5]}} >
            <Scene /> 
        </Canvas>
    );
}