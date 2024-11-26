import React, { useRef } from "react";
import { Canvas, useFrame, useLoader } from "@react-three/fiber";
import { TextureLoader } from 'three/src/loaders/TextureLoader'

function Box() {
    const meshRef = useRef();

    useFrame(() => {
        meshRef.current.rotation.x += 0.01;
        meshRef.current.rotation.y += 0.02;
    });

    const texture = useLoader(TextureLoader, "img/webgl-logo.png");

    return (
        <mesh ref={meshRef}>
            <boxGeometry args={[1, 1, 1]} />
            <meshPhongMaterial map={texture} specular={0xFFFFFF} shininess={100} />
        </mesh>
    )
}

export function App() {
    return (
        <Canvas camera={{fov: 90, near: 0.1, far: 10, position: [1, 1, 1]}}>
            <color attach="background" args={['black']} />
            <ambientLight intensity={0.1} />
            <pointLight position={[1, 1, 0.5]} color="white" decay={0} />
            <Box />
        </Canvas>
    )
}