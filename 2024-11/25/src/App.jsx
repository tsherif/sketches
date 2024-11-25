import React, { useRef, useMemo } from "react";
import { Canvas, useFrame } from "@react-three/fiber";

function Box({position, vxr, vyr, scale}) {
    const meshRef = useRef();

    useFrame((state, delta) => {
        meshRef.current.rotation.x += vxr * delta;
        meshRef.current.rotation.y += vyr * delta;
    });

    return (
        <mesh ref={meshRef} position={position} scale={[scale, scale, scale]}>
            <boxGeometry args={[1, 1, 1]} />
            <meshStandardMaterial color="white" />
        </mesh>
    )
}

export function App() {

    const boxes = useMemo(() => (
        new Array(100).fill().map(() => ({
            position: [
                Math.random() * 6 - 3,
                Math.random() * 6 - 3,
                Math.random() * 6 - 3
            ],
            vxr: Math.random() * 4 - 2,
            vyr: Math.random() * 4 - 2,
            scale: Math.random() * 0.7 + 0.1
        })) 
    ), []);

    const lights = useMemo(() => (
        new Array(10).fill().map(() => ({
            position: [
                Math.random() * 6 - 3,
                Math.random() * 6 - 3,
                Math.random() * 6
            ],
            color: ["red", "green", "blue"][Math.floor(Math.random() * 3)]
        })) 
    ), []);
    

    return (
        <Canvas background="black">
            <color attach="background" args={['black']} />
            <ambientLight intensity={0.05} />
            {
                lights.map(l => (
                    <pointLight {...l} />
                ))
            }
            {boxes.map(b => (
                <Box {...b} />
            ))}
        </Canvas>
    )
}