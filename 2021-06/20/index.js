var canvas = document.getElementById("canvas");
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;
var ctx = canvas.getContext("2d");
var BG_COLOR = "#000";
var NUM_BALLS = 100;
var balls = new Array(NUM_BALLS);
for (var i = 0; i < NUM_BALLS; ++i) {
    var vx = Math.random() * 0.8 - 0.4;
    var vy = Math.random() * 0.8 - 0.4;
    balls[i] = {
        x: Math.random() * canvas.width,
        y: Math.random() * canvas.height,
        r: Math.random() * 18 + 2,
        vx: vx,
        vy: vy,
        vMag: Math.sqrt(vx * vx + vy * vy),
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
        for (var j = i + 1; j < NUM_BALLS; ++j) {
            var other = balls[j];
            var rSum = other.r + ball.r;
            var dx = other.x - ball.x;
            var dy = other.y - ball.y;
            var d2 = dx * dx + dy * dy;
            if (d2 < rSum * rSum) {
                var d = Math.sqrt(d2);
                var dxNorm = dx / d;
                var dyNorm = dy / d;
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
