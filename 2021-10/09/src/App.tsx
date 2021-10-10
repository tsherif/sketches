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
}

function BallCanvas(props: BallCanvasProps) {
	const {balls, dimensions} = props;
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
			context.fillStyle = ball.color;
			context.beginPath();
			context.arc(ball.x, ball.y, ball.r, 0, Math.PI * 2);
			context.fill();
		}
	}, [balls, dimensions]);

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
		/>
	);
}