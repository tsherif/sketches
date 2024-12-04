let canvas;
let ctx;
let balls;
let hoveredBall = -1;
let selectedBall = -1;

const input = {
    x: -1,
    y: -1,
    lastX: -1,
    lastY: -1,
    dragging: false
}

addEventListener("message", ({data}) => {
    switch(data.type) {
        case "init":
            canvas = data.canvas;
            ctx = canvas.getContext("2d");
            balls = new Array(100).fill().map(() => ({
                x: Math.random() * canvas.width,
                y: Math.random() * canvas.height,
                r: Math.random() * 40 + 5,
                color: `rgb(${Math.random() * 255},${Math.random() * 255},${Math.random() * 255})`
            }))
            postMessage("Starting offscreen render loop");

            requestAnimationFrame(function loop() {
                requestAnimationFrame(loop);

                ctx.fillStyle = "black";
                ctx.fillRect(0, 0, canvas.width, canvas.height);


                balls.forEach((b, i) => {
                    if (selectedBall === i && input.dragging) {
                        const dx = input.x - input.lastX;
                        const dy = input.y - input.lastY;
                        b.x += dx;
                        b.y += dy;
                    }

                    if (b.x < b.r) {
                        b.x = b.r;
                    }

                    if (b.x > canvas.width -  b.r) {
                        b.x = canvas.width -  b.r;
                    }

                    if (b.y < b.r) {
                        b.y = b.r;
                    }

                    if (b.y > canvas.height -  b.r) {
                        b.y = canvas.height -  b.r;
                    }

                    ctx.fillStyle = hoveredBall === i ? "yellow": b.color;
                    ctx.beginPath();
                    ctx.arc(b.x, b.y, b.r, 0, 2 * Math.PI);
                    ctx.fill();
                });

                input.lastX = input.x;
                input.lastY = input.y;
            });
            return;
        case "input":
            switch (data.event) {
                case "mousedown":
                    balls.forEach((b, i) => {
                        const vx = data.x - b.x;
                        const vy = data.y - b.y;
                        if (vx * vx + vy * vy < b.r * b.r) {
                            selectedBall = i;
                        }
                    })
                    input.x = input.lastX = data.x;
                    input.y = input.lastY = data.y;
                    input.dragging = true;
                    return;
                case "mouseup":
                    selectedBall = -1;
                    input.y = input.lastX = -1;
                    input.x = input.lastY = -1;
                    input.dragging = false;
                    return;
                case "mousemove":
                    input.x = data.x;
                    input.y = data.y;
                    if (selectedBall > -1) {
                        hoveredBall = selectedBall;
                        return;
                    }
                    hoveredBall = -1;
                    balls.forEach((b, i) => {
                        const vx = data.x - b.x;
                        const vy = data.y - b.y;
                        if (vx * vx + vy * vy < b.r * b.r) {
                            hoveredBall = i;
                        }
                    })
                    return;
            }
            return;
    }
});


