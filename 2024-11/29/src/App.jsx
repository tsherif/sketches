import React, { useRef, useState } from "react";
import { Canvas, useFrame, useLoader } from "@react-three/fiber";
import { TextureLoader } from 'three/src/loaders/TextureLoader';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';

function Scene() {
    const objectRef = useRef();
    const model = useLoader(GLTFLoader, "models/antique-camera/glTF/AntiqueCamera.gltf");

    useFrame(({camera}) => {
        camera.lookAt(0, 3.5, 0);
        objectRef.current.rotation.y += 0.01;
    });

    return (
        <>
            <color args={['gray']} attach="background" />
            <ambientLight intensity={0.1} />
            <pointLight position={[5, 5, 5]} color="white" decay={0} />
            <pointLight position={[-5, 5, 5]} color="white" decay={0} />
            <group ref={objectRef} >
                <primitive position={[0, -1, 0]} object={model.scene} />
            </group>
        </>
    )
}

export function App() {
    return (
        <Canvas camera={{fov: 90, near: 0.1, far: 10, position: [0, 6, 4]}} >
            <Scene /> 
        </Canvas>
    );
}