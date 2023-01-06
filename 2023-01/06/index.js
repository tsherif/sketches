"use strict";
(() => {
    const canvas = document.getElementById("canvas");
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
    const ctx = canvas.getContext("2d");
    if (!ctx) {
        return;
    }
    const balls = new Array(100).fill(undefined).map(() => ({
        x: Math.random() * canvas.width,
        y: Math.random() * canvas.height,
        r: Math.random() * 20 + 10,
        color: `rgb(${Math.random() * 255}, ${Math.random() * 255}, ${Math.random() * 255})`,
        vx: Math.random() - 0.5,
        vy: Math.random() - 0.5
    }));
    requestAnimationFrame(function loop() {
        requestAnimationFrame(loop);
        ctx.fillStyle = "black";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        for (const b of balls) {
            b.x += b.vx;
            b.y += b.vy;
            if (b.x < b.r) {
                b.x = b.r;
                b.vx = -b.vx;
            }
            if (b.x + b.r > canvas.width) {
                b.x = canvas.width - b.r;
                b.vx = -b.vx;
            }
            if (b.y < b.r) {
                b.y = b.r;
                b.vy = -b.vy;
            }
            if (b.y + b.r > canvas.height) {
                b.y = canvas.height - b.r;
                b.vy = -b.vy;
            }
            ctx.fillStyle = b.color;
            ctx.beginPath();
            ctx.arc(b.x, b.y, b.r, 0, 2 * Math.PI);
            ctx.fill();
        }
    });
})();
//# sourceMappingURL=index.js.map