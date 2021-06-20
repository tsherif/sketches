var canvas = document.getElementById("gl-canvas");
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;
var ctx = canvas.getContext("2d");
var BG_COLOR = "#000";
var NUM_BALLS = 100;
var balls = new Array(100);
for (var i = 0; i < NUM_BALLS; ++i) {
    balls[i] = {
        r: Math.random() * 8 + 2,
        x: Math.random() * canvas.width,
        y: Math.random() * canvas.height,
        vx: Math.random() * 1 - 0.5,
        vy: Math.random() * 1 - 0.5,
        color: "rgb(" + Math.random() * 255 + ", " + Math.random() * 255 + ", " + Math.random() * 255 + ")"
    };
}
requestAnimationFrame(function draw() {
    requestAnimationFrame(draw);
    ctx.fillStyle = BG_COLOR;
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    for (var i = 0; i < NUM_BALLS; ++i) {
        var ball = balls[i];
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
        ctx.fillStyle = ball.color;
        ctx.beginPath();
        ctx.arc(ball.x, ball.y, ball.r, 0, Math.PI * 2);
        ctx.fill();
    }
});
