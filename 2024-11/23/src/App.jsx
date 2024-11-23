import React, { useRef } from "react";
import { Canvas, useFrame } from "@react-three/fiber";

function Box() {
    const meshRef = useRef();

    useFrame((state, delta) => {
        meshRef.current.rotation.x += delta;
        meshRef.current.rotation.y += 0.5 * delta;
    });

    return (
        <mesh ref={meshRef}>
            <boxGeometry args={[1, 1, 1]} />
            <meshStandardMaterial color="white" />
        </mesh>
    )
}

export function App() {
    

    return (
        <Canvas>
            <ambientLight intensity={0.1} />
            <pointLight position={[1, 1, 1]} color="red" />
            <pointLight position={[-1, 1, 1]} color="blue" />
            <pointLight position={[0, -1, 1]} color="green" />
            <Box />
        </Canvas>
    )
}