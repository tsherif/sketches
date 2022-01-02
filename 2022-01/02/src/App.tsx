import React, { useEffect, useRef, useState } from "react";
import { useSelector, useDispatch } from "react-redux";

import {simulate, dimensions, ballsSelector, dimensionsSelector} from "./store";

function useDimensions() {
    const currentDimensions = useSelector(dimensionsSelector);
    const dispatch = useDispatch();

    useEffect(() => {
        const handleResize = () => {
            dispatch(dimensions(window.innerWidth, window.innerHeight));
        };
        window.addEventListener("resize", handleResize);

        return () => window.removeEventListener("resize", handleResize);
    }, [])

    return currentDimensions;
}

function useSimulate() {
    const balls = useSelector(ballsSelector);
    const dispatch = useDispatch();

    useEffect(() => {
        let rafId: number;
        const loop = () => {
            rafId = requestAnimationFrame(loop);
            dispatch(simulate(performance.now()));
        }

        rafId = requestAnimationFrame(loop);

        return () => cancelAnimationFrame(rafId);
    }, []);

    return balls;
}

export function App() {
    const canvasRef = useRef<HTMLCanvasElement>(null);
    const contextRef = useRef<CanvasRenderingContext2D>(null);
    const { width, height } = useDimensions();
    const balls = useSimulate();

    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvasRef.current) {
            return;
        }
        contextRef.current = canvas.getContext("2d");
    }, []);

    useEffect(() => {
        const canvas = canvasRef.current;
        
        if (!canvasRef.current) {
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

        for (const ball of balls) {
            context.beginPath();
            context.fillStyle = ball.color;
            context.arc(ball.x, ball.y, ball.r, 0, 2 * Math.PI);
            context.fill();
        }
    }, [balls, width, height]);

    return (
        <canvas ref={canvasRef}></canvas>
    );
}