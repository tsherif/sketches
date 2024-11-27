import React, { useRef, useState } from "react";
import { Canvas, useFrame, useLoader, useThree } from "@react-three/fiber";
import { TextureLoader } from 'three/src/loaders/TextureLoader';
import * as Three from 'three';

function Scene() {
    const backgroundRef = useRef();
    const meshRef = useRef();
    const materialRef = useRef();
    const texture = useLoader(TextureLoader, "img/webgl-logo.png");

    const size = useThree((state) => state.size);
    const viewport = useThree((state) => state.viewport);
    const width = size.width * viewport.dpr
    const height = size.height * viewport.dpr
    const [renderTarget] = useState(() => new Three.WebGLRenderTarget(width, height));


    useFrame(({gl, scene, camera}) => {
        meshRef.current.rotation.x += 0.01;
        meshRef.current.rotation.y += 0.02;

        gl.setRenderTarget(renderTarget);
        backgroundRef.current.set("gray");
        materialRef.current.map = texture;
        gl.render(scene, camera);

        gl.setRenderTarget(null);
        backgroundRef.current.set("black");
        materialRef.current.map = renderTarget.texture;
        gl.render(scene, camera);
    });

    return (
        <>
            <color ref={backgroundRef} attach="background" />
            <ambientLight intensity={0.1} />
            <pointLight position={[1, 1, 0.5]} color="white" decay={0} />
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
            <Scene /> 
        </Canvas>
    );
}