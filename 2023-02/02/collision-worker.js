importScripts("../../lib/js/gl-matrix.js");

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

            // Check collision
            vec2.sub(d, p1, p2);
            const l2 = vec2.squaredLength(d);
            const rSum = r1 + r2;

            if (l2 < rSum * rSum) {
                ///////////////////////////////////////////////////
                // The collisions array is prefixed with a lock
                // at element 0, and a count of collisions at
                // element 1. Starting at element 2, the array
                // contains pairs of indices representing
                // collisions.
                // A 1 at element 0 indicates that the array
                // is currently locked, while a zero indicates
                // that it is free.
                ///////////////////////////////////////////////////

                // Acquire lock
                while (Atomics.compareExchange(collisions, 0, 0, 1) === 1) {
                    Atomics.wait(collisions, 0, 1);
                }

                // Store new collision.
                const count = collisions[1];
                const lastIndex = count * 2 + 2;
                if (lastIndex < collisions.length) {
                    collisions[lastIndex]     = i;
                    collisions[lastIndex + 1] = j;
                    ++collisions[1];
                }

                // Release lock
                Atomics.store(collisions, 0, 0);
                Atomics.notify(collisions, 0);
            }
        }
    }

    postMessage("done");
});
