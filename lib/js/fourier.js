
// Derived from: https://en.wikipedia.org/wiki/Discrete_Fourier_transform#Multidimensional_DFT
// F(u, v) = sum(x) e ^ (-i * 2 * PI * u * x / w)
//              sum(y)  e ^ (-i * 2 * PI * v * y / h) * f(x, y)
//    = sum(x) sum(y) e ^ (-i * 2 * PI * u * x / w) * e ^ (-i * 2 * PI * v * y / h) * f(x, y)
//    = sum(x) sum(y) e ^ (-i * 2 * PI * (u * x * h + v * y * w) / (w * h)) * f(x, y)
//
// Euler's formula to split e ^ (i * x) into real and imaginary parts.
// https://en.wikipedia.org/wiki/Euler%27s_formula
// real = f(x, y) * cos(-i * 2 * PI * (u * x * h + v * y * w) / (w * h))
// imaginary = f(x, y) * sin(-i * 2 * PI * (u * x * h + v * y * w) / (w * h))
export function fourier(image, width, height) {
    const out = new Float64Array(width * height * 6);

    for (let u = 0; u < width; ++u) {
        for (let v = 0; v < height; ++v) {
            const outI = (v * width + u) * 6;

            // Real and imaginary components for red, green, blue signals.
            let [rr, ri, gr, gi, br, bi] = [0, 0, 0, 0, 0, 0];

            for (let x = 0; x < width; ++x) {
                for (let y = 0; y < height; ++y) {
                    const inI = (y * width + x) * 4;
                    const r = image[inI];
                    const g = image[inI + 1];
                    const b = image[inI + 2];

                    const theta = -2 * Math.PI * (u * x * height + y * v * width) / (width * height);

                    rr += r * Math.cos(theta);
                    ri += r * Math.sin(theta);
                    
                    gr += g * Math.cos(theta);
                    gi += g * Math.sin(theta);
                    
                    br += b * Math.cos(theta);
                    bi += b * Math.sin(theta);    
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

export function transformImages(data, width, height) {
    const magnitude = new Uint8ClampedArray(width * height * 4);
    const redMagnitude = new Uint8ClampedArray(width * height * 4);
    const greenMagnitude = new Uint8ClampedArray(width * height * 4);
    const blueMagnitude = new Uint8ClampedArray(width * height * 4);
    const phase = new Uint8ClampedArray(width * height * 4);
    const redPhase = new Uint8ClampedArray(width * height * 4);
    const greenPhase = new Uint8ClampedArray(width * height * 4);
    const bluePhase = new Uint8ClampedArray(width * height * 4);

    for (let u = 0; u < width; ++u) {
        for (let v = 0; v < height; ++v) {
            const inI = (v * width + u) * 6;
            const rr = data[inI];
            const ri = data[inI + 1];
            const gr = data[inI + 2];
            const gi = data[inI + 3];
            const br = data[inI + 4];
            const bi = data[inI + 5];

            // Divisor just to scale into visible range.
            const rm = Math.sqrt(rr * rr + ri * ri) / Math.sqrt(width);
            const gm = Math.sqrt(gr * gr + gi * gi) / Math.sqrt(width);
            const bm = Math.sqrt(br * br + bi * bi) / Math.sqrt(width);

            const rp = 255 * (Math.atan2(ri, rr) / (2 * Math.PI) + 0.5);
            const gp = 255 * (Math.atan2(gi, gr) / (2 * Math.PI) + 0.5);
            const bp = 255 * (Math.atan2(bi, br) / (2 * Math.PI) + 0.5);

            const outI = (v * width + u) * 4;

            magnitude[outI]     = rm;
            magnitude[outI + 1] = gm;
            magnitude[outI + 2] = bm;
            magnitude[outI + 3] = 255;

            redMagnitude[outI]     = rm;
            redMagnitude[outI + 1] = 0;
            redMagnitude[outI + 2] = 0;
            redMagnitude[outI + 3] = 255;

            greenMagnitude[outI]     = 0;
            greenMagnitude[outI + 1] = gm;
            greenMagnitude[outI + 2] = 0;
            greenMagnitude[outI + 3] = 255;

            blueMagnitude[outI]     = 0;
            blueMagnitude[outI + 1] = 0;
            blueMagnitude[outI + 2] = bm;
            blueMagnitude[outI + 3] = 255;

            phase[outI]     = rp;
            phase[outI + 1] = gp;
            phase[outI + 2] = bp;
            phase[outI + 3] = 255;

            redPhase[outI]     = rp;
            redPhase[outI + 1] = 0;
            redPhase[outI + 2] = 0;
            redPhase[outI + 3] = 255;

            greenPhase[outI]     = 0;
            greenPhase[outI + 1] = gp;
            greenPhase[outI + 2] = 0;
            greenPhase[outI + 3] = 255;

            bluePhase[outI]     = 0;
            bluePhase[outI + 1] = 0;
            bluePhase[outI + 2] = bp;
            bluePhase[outI + 3] = 255;
        }
    }

    return { 
        magnitude,
        redMagnitude,
        greenMagnitude,
        blueMagnitude,
        phase,
        redPhase,
        greenPhase,
        bluePhase,
    };
}

export function filter(data, width, height, props) {
    const out = new Float64Array(data.length);

    const { min, max, scale = 1 } = props;
    const min2 = min * min;
    const max2 = max * max;

    for (let u = 0; u < width; ++u) {
        for (let v = 0; v < height; ++v) {
            const l2 = u * u + v * v;
            if (l2 < min2 || l2 > max2) {
                continue;
            }

            const i = (v * width + u) * 6;
            out[i] = data[i] * scale;
            out[i + 1] = data[i + 1] * scale;
            out[i + 2] = data[i + 2] * scale;
            out[i + 3] = data[i + 3] * scale;
            out[i + 4] = data[i + 4] * scale;
            out[i + 5] = data[i + 5] * scale;
        }
    }

    return out;
}

// Derived from: https://en.wikipedia.org/wiki/Discrete_Fourier_transform#Multidimensional_DFT
// f(x, y) = 1 / (w * h) * sum(x) sum(y) e ^ (i * 2 * PI * (u * x * h + v * y * w) / (w * h)) * f(x, y)
export function inverseFourier(data, width, height) {
    const out = new Uint8ClampedArray(width * height * 4);

    for (let x = 0; x < width; ++x) {
        for (let y = 0; y < height; ++y) {
            const outI = (y * width + x) * 4;
            let [r, g, b] = [0, 0, 0];
            
            for (let u = 0; u < width; ++u) {
                for (let v = 0; v < height; ++v) {
                    const inI = (v * width + u) * 6;
                    const rr = data[inI];
                    const ri = data[inI + 1];
                    const gr = data[inI + 2];
                    const gi = data[inI + 3];
                    const br = data[inI + 4];
                    const bi = data[inI + 5];

                    const theta = 2 * Math.PI * (u * x * height + y * v * width) / (width * height);

                    // Multiplying 2 complex numbers and only care
                    // about the real part of the result:
                    // (cr + i * ci) * (cos(theta) + i * sin(theta))
                    // = cr * cos(theta) - ci * sin(theta) + i (cr * sin(theta) + ci * cos(theta)) 
                    // real = cr * cos(theta) - ci * sin(theta)
                    r += rr * Math.cos(theta) - ri * Math.sin(theta);
                    g += gr * Math.cos(theta) - gi * Math.sin(theta);
                    b += br * Math.cos(theta) - bi * Math.sin(theta);
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