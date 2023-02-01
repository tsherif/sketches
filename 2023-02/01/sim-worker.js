importScripts("../../lib/gl-matrix.js");

const n = vec2.create();
const d = vec2.create();
const vProjN = vec2.create();
const correction = vec2.create();

addEventListener("message", message => {
    const {start, end, width, height, input, output, numBalls, mutexes } = message.data;

    for (let i = start; i < end; ++i) {
        const bi = i * 5;
        const inP1 = input.subarray(bi, bi + 2);
        const inV1 = input.subarray(bi + 2, bi + 4);
        const r1 =  input[bi + 4];

        const p1 = output.subarray(bi, bi + 2);
        const v1 = output.subarray(bi + 2, bi + 4);
        
        withMutex(mutexes, i, () => {
            vec2.copy(p1, inP1);
            vec2.copy(v1, inV1);
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
        });

        for (let j = i + 1; j < numBalls; ++j) {

            const bi2 = j * 5;
            const inP2 = input.subarray(bi2, bi2 + 2);
            const inV2 = input.subarray(bi2 + 2, bi2 + 4);
            const r2 =  input[bi2 + 4];

            const p2 = output.subarray(bi2, bi2 + 2);
            const v2 = output.subarray(bi2 + 2, bi2 + 4);

            withMutex(mutexes, j, () => {
                vec2.copy(p2, inP2);
                vec2.copy(v2, inV2);
            });

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
                
                // Resolve overlap
                vec2.scale(correction, n, dl);
               
                withMutex(mutexes, i, () => {
                    vec2.sub(v1, v1, vProjN);
                    vec2.add(p1, p1, correction);
                });
                

                // Same for second ball
                vec2.negate(n, n);
                vDotN = vec2.dot(v2, n);
                vec2.scale(vProjN, n, 2 * vDotN);
                
                vec2.scale(correction, n, dl);
                
                withMutex(mutexes, j, () => {
                    vec2.sub(v2, v2, vProjN);
                    vec2.add(p2, p2, correction);
                });
            }
        }
    }

    postMessage("done");
});

function withMutex(mutexes, index, fn) {
    while (Atomics.compareExchange(mutexes, index, 0, 1) === 1) {
        waits++;
        Atomics.wait(mutexes, index, 1);
    }

    fn();

    Atomics.store(mutexes, index, 0);
    Atomics.notify(mutexes, index);
}
