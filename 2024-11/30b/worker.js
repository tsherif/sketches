addEventListener("message", ({data}) => {
    const { canvas } = data;
    const ctx = canvas.getContext("2d");

    const balls = new Array(100).fill().map(() => ({
        x: Math.random() * canvas.width,
        y: Math.random() * canvas.height,
        vx: Math.random() * 10 - 5,
        vy: Math.random() * 10 - 5,
        r: Math.random() * 40 + 5,
        color: `rgb(${Math.random() * 255},${Math.random() * 255},${Math.random() * 255})`
    }))

    postMessage("Starting offscreen render loop");

    requestAnimationFrame(function loop() {
        requestAnimationFrame(loop);

        ctx.fillStyle = "black";
        ctx.fillRect(0, 0, canvas.width, canvas.height);

        balls.forEach(b => {
            b.x += b.vx;
            b.y += b.vy;

            if (b.x < b.r) {
                b.x = b.r;
                b.vx *= -1;
            }

            if (b.x > canvas.width -  b.r) {
                b.x = canvas.width -  b.r;
                b.vx *= -1;
            }

            if (b.y < b.r) {
                b.y = b.r;
                b.vy *= -1;
            }

            if (b.y > canvas.height -  b.r) {
                b.y = canvas.height -  b.r;
                b.vy *= -1;
            }

            ctx.fillStyle = b.color;
            ctx.beginPath();
            ctx.arc(b.x, b.y, b.r, 0, 2 * Math.PI);
            ctx.fill();
        });
    });
});


