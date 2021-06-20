const canvas = document.getElementById("canvas") as HTMLCanvasElement;
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

const ctx = canvas.getContext("2d");

interface ball {
	x: number;
	y: number;
	r: number;
	vx: number;
	vy: number;
	vMag: number;
	color: string;
}

const BG_COLOR = "#000";
const NUM_BALLS = 100;
const balls : ball[] = new Array(NUM_BALLS);

for (let i = 0; i < NUM_BALLS; ++i) {
	const vx = Math.random() * 0.8 - 0.4;
	const vy = Math.random() * 0.8 - 0.4;
	balls[i] = {
		x: Math.random() * canvas.width,
		y: Math.random() * canvas.height,
		r: Math.random() * 18 + 2,
		vx,
		vy,
		vMag: Math.sqrt(vx * vx + vy * vy),
		color: `rgb(${Math.random() * 255}, ${Math.random() * 255}, ${Math.random() * 255})`
	}
}

requestAnimationFrame(function draw() {
	requestAnimationFrame(draw);

	ctx.fillStyle = BG_COLOR;
	ctx.fillRect(0, 0, canvas.width, canvas.height);

	for (let i = 0; i < NUM_BALLS; ++i) {
		const ball = balls[i];
		ball.x += ball.vx;
		ball.y += ball.vy;

		if (ball.x - ball.r < 0) {
			ball.x = ball.r;
			ball.vx *= -1;
		}

		if (ball.x + ball.r > canvas.width) {
			ball.x = canvas.width - ball.r;
			ball.vx *= -1;
		}

		if (ball.y - ball.r < 0) {
			ball.y = ball.r;
			ball.vy *= -1;
		}

		if (ball.y + ball.r > canvas.height) {
			ball.y = canvas.height - ball.r;
			ball.vy *= -1;
		}

		for (let j = i + 1; j < NUM_BALLS; ++j) {
			const other = balls[j];
			const rSum = other.r + ball.r;
			const dx = other.x - ball.x;
			const dy = other.y - ball.y;
			const d2 = dx * dx + dy * dy;
			if (d2 < rSum * rSum) {
				const d = Math.sqrt(d2);
				const dxNorm = dx / d;
				const dyNorm = dy / d;
				other.vx = dxNorm * other.vMag;
				other.vy = dyNorm * other.vMag;
				ball.vx = -dxNorm * ball.vMag;
				ball.vy = -dyNorm * ball.vMag;
			} 
		}

		ctx.fillStyle = ball.color;
		ctx.beginPath();
		ctx.arc(ball.x, ball.y, ball.r, 0, Math.PI * 2);
		ctx.fill();
	}
});