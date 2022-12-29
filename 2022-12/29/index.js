(async () => {
    const canvas = document.getElementById("canvas");
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
    const gl = canvas.getContext("webgl2");
    if (!gl) {
        return;
    }
    const vsShader = gl.createShader(gl.VERTEX_SHADER);
    const fsShader = gl.createShader(gl.FRAGMENT_SHADER);
    const program = gl.createProgram();
    const [vsSource, fsSource] = await Promise.all([
        fetch("./quad.vert").then(res => res.text()),
        fetch("./triangle.frag").then(res => res.text())
    ]);
    gl.shaderSource(vsShader, vsSource);
    gl.compileShader(vsShader);
    gl.shaderSource(fsShader, fsSource);
    gl.compileShader(fsShader);
    gl.attachShader(program, vsShader);
    gl.attachShader(program, fsShader);
    gl.linkProgram(program);
    gl.useProgram(program);
    gl.uniform2fv(gl.getUniformLocation(program, "dimensions"), new Float32Array([canvas.width, canvas.height]));
    const quadPositions = new Float32Array([
        -1.0, -1.0,
        1.0, -1.0,
        -1.0, 1.0,
        1.0, 1.0
    ]);
    const quadBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, quadBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, quadPositions, gl.STATIC_DRAW);
    gl.vertexAttribPointer(0, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(0);
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
})();
//# sourceMappingURL=index.js.map