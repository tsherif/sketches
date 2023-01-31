addEventListener("message", message => {
    const {start, end, buffer, width, height} = message.data;

    const balls = new Float32Array(buffer);

    for (let i = start; i <= end; ++i) {
        const bi = i * 5;
        let x =  balls[bi];
        let y =  balls[bi + 1];
        let vx = balls[bi + 2];
        let vy = balls[bi + 3];
        const r =  balls[bi + 4];

        x += vx;
        y += vy;

        if (x < r) {
            x = r;
            vx *= -1;
        }

        if (x > width - r) {
            x = width - r;
            vx *= -1;
        }

        if (y < r) {
            y = r;
            vy *= -1;
        }

        if (y > height - r) {
            y = height - r;
            vy *= -1;
        }

        balls[bi]     = x;
        balls[bi + 1] = y;
        balls[bi + 2] = vx;
        balls[bi + 3] = vy;
    }

    postMessage("done");
})