importScripts("../../lib/gl-matrix.js");

const n = vec2.create();
const d = vec2.create();
const vProjN = vec2.create();
const correction = vec2.create();

addEventListener("message", message => {
    const {start, end, balls, numBalls, collisions } = message.data;

    for (let i = start; i < end; ++i) {
        const bi = i * 5;
        const p1 = balls.subarray(bi, bi + 2);
        const r1 = balls[bi + 4];

        for (let j = i + 1; j < numBalls; ++j) {

            const bi2 = j * 5;
            const p2 = balls.subarray(bi2, bi2 + 2);
            const r2 = balls[bi2 + 4];

            vec2.sub(d, p1, p2);
            const l2 = vec2.squaredLength(d);
            const rSum = r1 + r2;

            if (l2 < rSum * rSum) {
                withMutex(collisions, 0, () => {
                    const count = collisions[1];
                    if (count < collisions.length) {
                        collisions[2 + count]     = i;
                        collisions[2 + count + 1] = j;
                        collisions[1] += 2;
                    }
                });
            }
        }
    }

    postMessage("done");
});

function withMutex(mutexes, index, fn) {
    while (Atomics.compareExchange(mutexes, index, 0, 1) === 1) {
        Atomics.wait(mutexes, index, 1);
    }

    fn();

    Atomics.store(mutexes, index, 0);
    Atomics.notify(mutexes, index);
}
