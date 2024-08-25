export function fourier(image, width, height) {
    const out = new Float64Array(width * height * 6);

    for (let u = 0; u < width; ++u) {
        for (let v = 0; v < height; ++v) {
            const outI = (v * width + u) * 6;
            let [rr, ri, gr, gi, br, bi] = [0, 0, 0, 0, 0, 0];

            // F(u, v) = sum f(x, y) * e ^ (-i * 2 * PI * (u * x + y * v) / N)
            // real = f(x, y) * cos(-2 * PI * (u * x + y * v) / N)
            // imaginary = f(x, y) * sin(-2 * PI * (u * x + y * v) / N)
            // https://www.cs.unm.edu/~brayer/vision/fourier.html

            for (let x = 0; x < width; ++x) {
                for (let y = 0; y < height; ++y) {
                    const inI = (y * width + x) * 4;
                    const r = image[inI];
                    const g = image[inI + 1];
                    const b = image[inI + 2];

                    const arg = -2 * Math.PI * (u * x * height + y * v * width) / (width * height);

                    rr += r * Math.cos(arg);
                    ri += r * Math.sin(arg);
                    
                    gr += g * Math.cos(arg);
                    gi += g * Math.sin(arg);
                    
                    br += b * Math.cos(arg);
                    bi += b * Math.sin(arg);    
                }
            }

            out[outI]       = rr;
            out[outI + 1]   = ri;
            out[outI + 2]   = gr;
            out[outI + 3]   = gi;
            out[outI + 4]   = br;
            out[outI + 5]   = bi;
        }

    }

    return out;
}

export function inverseFourier(data, width, height) {
    const out = new Uint8ClampedArray(width * height * 4);

    for (let x = 0; x < width; ++x) {
        for (let y = 0; y < height; ++y) {
            const outI = (y * width + x) * 4;
            let [r, g, b] = [0, 0, 0];

            // f(x, y) = sum F(u, v) * e ^ (i * 2 * PI * (u * x + y * v) / N)
            // real = Fr * cos(2 * PI * (u * x + y * v) / N) - Fi * sin(2 * PI * (u * x + y * v) / N)
            // https://www.cs.unm.edu/~brayer/vision/fourier.html

            
            for (let u = 0; u < width; ++u) {
                for (let v = 0; v < height; ++v) {
                    const inI = (v * width + u) * 6;
                    const rr = data[inI];
                    const ri = data[inI + 1];
                    const gr = data[inI + 2];
                    const gi = data[inI + 3];
                    const br = data[inI + 4];
                    const bi = data[inI + 5];

                    const arg = 2 * Math.PI * (u * x * height + y * v * width) / (width * height);

                    r += rr * Math.cos(arg) - ri * Math.sin(arg);
                    g += gr * Math.cos(arg) - gi * Math.sin(arg);
                    b += br * Math.cos(arg) - bi * Math.sin(arg);
                }
            }

            out[outI]       = r / (width * height);
            out[outI + 1]   = g / (width * height);
            out[outI + 2]   = b / (width * height);
            out[outI + 3]   = 255;
        }

    }

    return out;
}