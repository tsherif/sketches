import React, {useState, useEffect, useRef} from "react";
import ReactDom from "react-dom";

interface Ball {
    x: number;
    y: number;
    r: number;
    vx: number;
    vy: number;
    color: string;
    highlight: boolean;
}

function useDeltaTime() {
    const [dt, setDt] = useState(0);
    useEffect(() => {
        let tickId = 0;
        let lastTime = performance.now();
        function tick() {
            tickId = requestAnimationFrame(tick);
            let time = performance.now();
            setDt(time - lastTime);
            lastTime = time;
        };

        tickId = requestAnimationFrame(tick);

        return () => cancelAnimationFrame(tickId);
    }, []);

    return dt;
}

function useResize() {
    const [dimensions, setDimensions] = useState<[number, number]>([window.innerWidth, window.innerHeight])
    useEffect(() => {
        function resize() {
            setDimensions([window.innerWidth, window.innerHeight]);
        };

        window.addEventListener("resize", resize);

        return () => window.removeEventListener("resize", resize);
    }, []);

    return dimensions;
}

function use2DContext(canvasRef: React.MutableRefObject<HTMLCanvasElement>, width: number, height: number) {
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

    return contextRef.current;
}

export function BallCanvas() {
    const [balls, setBalls] = useState<Ball[]>(new Array(30).fill(null).map(() => ({
        x: Math.random() * window.innerWidth,
        y: Math.random() * window.innerHeight,
        r: Math.random() * 20 + 10,
        vx: Math.random() * 2 - 1,
        vy: Math.random() * 2 - 1,
        color: `rgb(${Math.random() * 255}, ${Math.random() * 255}, ${Math.random() * 255})`,
        highlight: false
    })));
    const canvasRef = useRef<HTMLCanvasElement>(null);

    const dt = useDeltaTime();
    const [width, height] = useResize();
    const context = use2DContext(canvasRef, width, height);

    useEffect(() => {
        const newBalls = balls.map(b => {
            const ball = {...b};

            ball.x += ball.vx * dt;
            ball.y += ball.vy * dt;

            if (ball.x - ball.r < 0) {
                ball.x = ball.r;
                ball.vx *= -1;
            }

            if (ball.x + ball.r > width) {
                ball.x = width - ball.r;
                ball.vx *= -1;
            }

            if (ball.y - ball.r < 0) {
                ball.y = ball.r;
                ball.vy *= -1;
            }

            if (ball.y + ball.r > height) {
                ball.y = height - ball.r;
                ball.vy *= -1;
            }

            return ball;
        });

        setBalls(newBalls);
    }, [dt]);

    useEffect(() => {
        if (!context) {
            return;
        }

        context.fillStyle = "black";
        context.fillRect(0, 0, width, height);

        for (const ball of balls) {
            context.fillStyle = ball.highlight ? "yellow" : ball.color;
            context.beginPath();
            context.arc(ball.x, ball.y, ball.r, 0, Math.PI * 2);
            context.fill();
        }
    }, [balls, width, height]);

    return (
        <canvas ref={canvasRef}></canvas>
    );
}