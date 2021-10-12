import React, {useState, useEffect, useRef} from "react";
import ReactDom from "react-dom";

interface Ball {
	x: number;
	y: number;
	r: number;
	color: string;
	highlight: boolean;
}

interface BallCanvasProps {
	balls: Ball[];
	dimensions: [number, number];
	onClick: (ball: Ball, i: number) => void
}

function pointInBall(x: number, y: number, ball: Ball) {
	const dx = x - ball.x;
	const dy = y - ball.y;

	return dx * dx + dy * dy <= ball.r * ball.r;
}


function BallCanvas(props: BallCanvasProps) {
	const {balls, dimensions, onClick} = props;
	const [width, height] = dimensions;
	const canvasRef = useRef<HTMLCanvasElement>(null);
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

		context.clearRect(0, 0, width, height);

		for (const ball of balls) {
			context.fillStyle = ball.highlight ? "yellow" : ball.color;
			context.beginPath();
			context.arc(ball.x, ball.y, ball.r, 0, Math.PI * 2);
			context.fill();
		}
	}, [balls, dimensions]);

	useEffect(() => {
		const canvas = canvasRef.current;
		if (!canvas) {
			return;
		}

		const handleClick = (event: MouseEvent) => {
			const x = event.clientX;
			const y = event.clientY;
			const reverseBalls = balls.reverse(); // Front to back
			for (let i = 0; i < balls.length; ++i) {
				const ball = balls[i];
				if (pointInBall(x, y, ball)) {
					onClick(ball, i);
					break;
				}
			}
		};

		canvas.addEventListener("click", handleClick);

		return () => canvas.removeEventListener("click", handleClick);
	}, [balls]);

	return (
		<canvas ref={canvasRef}></canvas>
	);
}

export function App() {
	const [balls, setBalls] = useState([]);
	const [dimensions, setDimensions] = useState<[number, number]>([window.innerWidth, window.innerHeight]);
	const [width, height] = dimensions;

	useEffect(() => {
		const newBalls = new Array(30).fill(null).map(() => ({
			x: Math.random() * window.innerWidth,
			y: Math.random() * window.innerHeight,
			r: Math.random() * 20 + 10,
			color: `rgb(${Math.random() * 255}, ${Math.random() * 255}, ${Math.random() * 255})`,
			highlight: false
		}));

		setBalls(newBalls);
	}, []);

	useEffect(() => {
		function resize() {
			setDimensions([window.innerWidth, window.innerHeight]);
		};

		window.addEventListener("resize", resize);

		return () => window.removeEventListener("resize", resize);
	}, []);

	return (
		<BallCanvas
			balls={balls}
			dimensions={dimensions}
			onClick={(ball, i) => {
				const newBalls = balls.slice();
				const newBall = {...ball, highlight: !ball.highlight };
				newBalls[i] = newBall;

				setBalls(newBalls);
			}}
		/>
	);
}