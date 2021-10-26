import React, {useState, useEffect, useRef} from "react";

interface RenderObject {
    x: number;
    y: number;
    width: number;
    height: number;
    color: string;
}

interface RendererProps {
    objects: RenderObject[];
    width: number;
    height: number;
}

function useDraw(canvasRef: React.MutableRefObject<HTMLCanvasElement>, objects: RenderObject[], width: number, height: number) {
    const contextRef = useRef<CanvasRenderingContext2D>(null);
    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvas) {
            return;
        }
        contextRef.current = canvas.getContext("2d");
    }, []);

    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvas) {
            return;
        }

        canvas.width = width;
        canvas.height = height;
    }, [width, height]);

    useEffect(() => {
        const context = contextRef.current;

        if (!context) {
            return;
        }

        context.fillStyle = "black";
        context.fillRect(0, 0, width, height);

        for (const object of objects) {
            const {x, y, width, height, color} = object;
            context.fillStyle = color;;
            context.fillRect(x, y, width, height);
        }

    }, [objects, width, height]);
}

export function Renderer(props: RendererProps) {
    const { objects, width, height } = props;

    const canvasRef = useRef<HTMLCanvasElement>(null);

    useDraw(canvasRef, objects, width, height);

    return (
        <canvas ref={canvasRef}></canvas>
    );
}