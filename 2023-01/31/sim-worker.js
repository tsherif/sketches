importScripts("../../lib/gl-matrix.js");

const n = vec2.create();
const d = vec2.create();
const vProjN = vec2.create();
const correction = vec2.create();

addEventListener("message", message => {
    const {start, end, width, height, input, output, numBalls } = message.data;

    for (let i = start; i < end; ++i) {
        const bi = i * 5;
        const inP = input.subarray(bi, bi + 2);
        const inV = input.subarray(bi + 2, bi + 4);
        const r1 =  input[bi + 4];

        const p1 = output.subarray(bi, bi + 2);
        vec2.copy(p1, inP);
        const v1 = output.subarray(bi + 2, bi + 4);
        vec2.copy(v1, inV);

        vec2.add(p1, p1, v1);

        if (p1[0] < r1) {
            p1[0] = r1;
            v1[0] *= -1;
        }

        if (p1[0] > width - r1) {
            p1[0] = width - r1;
            v1[0] *= -1;
        }

        if (p1[1] < r1) {
            p1[1] = r1;
            v1[1] *= -1;
        }

        if (p1[1] > height - r1) {
            p1[1] = height - r1;
            v1[1] *= -1;
        }

        for (let j = 0; j < numBalls; ++j) {
            if (i === j) {
                continue;
            }
            
            const bi2 = j * 5;
            const p2 = input.subarray(bi2, bi2 + 2);
            const r2 =  input[bi2 + 4];

            vec2.sub(d, p1, p2);
            const l2 = vec2.squaredLength(d);
            const rSum = r1 + r2;

            if (l2 < rSum * rSum) {
                const l = Math.sqrt(l2);
                const dl = (rSum - l) * 0.5;

                // v' = v - 2 * (v . N) * N
                vec2.normalize(n, d);
                let vDotN = vec2.dot(v1, n);
                vec2.scale(vProjN, n, 2 * vDotN);
                vec2.sub(v1, v1, vProjN);

                // Resolve overlap
                vec2.scale(correction, n, dl);
                vec2.add(p1, p1, correction);
            }
        }
    }

    postMessage("done");
})