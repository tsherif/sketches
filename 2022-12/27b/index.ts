(async () => {
    const canvas = document.getElementById("canvas") as HTMLCanvasElement;

    if (!canvas) {
        return;
    }

    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;

    const ctx = canvas.getContext("2d");

    if (!ctx) {
        return;
    }

    ctx.fillStyle = "red";
    ctx.fillRect(0, 0, canvas.width, canvas.height);
})();