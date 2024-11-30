import React, { useLayoutEffect, useRef, useState } from "react";
import { Canvas, useFrame, useLoader, useThree } from "@react-three/fiber";
import { TextureLoader } from 'three/src/loaders/TextureLoader';
import { CameraControls, useFBO } from "@react-three/drei";

function Scene() {
    const backgroundRef = useRef();
    const meshRef = useRef();
    const materialRef = useRef();
    const texture = useLoader(TextureLoader, "img/webgl-logo.png");
    const fbo = useFBO();

    useFrame(({gl, scene, camera}) => {
        meshRef.current.rotation.x += 0.01;
        meshRef.current.rotation.y += 0.02;

        gl.setRenderTarget(fbo);
        backgroundRef.current.set("gray");
        materialRef.current.map = texture;
        gl.render(scene, camera);

        gl.setRenderTarget(null);
        backgroundRef.current.set("black");
        materialRef.current.map = fbo.texture;
        gl.render(scene, camera);
    });

    return (
        <>
            <color ref={backgroundRef} attach="background" />
            <ambientLight intensity={0.2} />
            <pointLight position={[1, 1, 1]} color="white" decay={0} />
            <pointLight position={[-1, 1, -1]} color="white" decay={0} />
            <pointLight position={[0, -1, 0]} color="white" decay={0} />
            <mesh ref={meshRef}>
                <boxGeometry args={[1, 1, 1]} />
                <meshPhongMaterial ref={materialRef} specular={0xFFFFFF} shininess={100} />
            </mesh>
        </>
    )
}

export function App() {
    return (
        <Canvas camera={{fov: 90, near: 0.1, far: 10, position: [1, 1, 1]}}>
            <CameraControls />
            <Scene /> 
        </Canvas>
    );
}