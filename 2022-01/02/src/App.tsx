import React, { useEffect, useRef } from "react";
import { useSelector, useDispatch } from "react-redux";

import {simulate, ballsSelector} from "./store";

export function App() {
    const canvasRef = useRef<HTMLCanvasElement>(null);
    const contextRef = useRef<CanvasRenderingContext2D>(null);
    const balls = useSelector(ballsSelector);
    const dispatch = useDispatch();

    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvasRef.current) {
            return;
        }
        contextRef.current = canvas.getContext("2d");
    }, []);

    useEffect(() => {
        let rafId: number;
        const loop = () => {
            rafId = requestAnimationFrame(loop);
            dispatch(simulate());
        }

        rafId = requestAnimationFrame(loop);
    }, []);

    useEffect(() => {
        const context = contextRef.current;
        if (!context) {
            return;
        }

        context.fillStyle = "black";
        context.fillRect(0, 0, window.innerWidth, window.innerHeight);

        for (const ball of balls) {
            context.beginPath();
            context.fillStyle = ball.color;
            context.arc(ball.x, ball.y, ball.r, 0, 2 * Math.PI);
            context.fill();
        }
    }, [balls])

    return (
        <canvas ref={canvasRef} width={window.innerWidth} height={window.innerHeight}></canvas>
    );
}