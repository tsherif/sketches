export function polygonCoordinates(edge, numSides) {
    const [x1, y1] = edge[0]; 
    const [x2, y2] = edge[1]; 
    const turnAngle = (-2 * Math.PI) / numSides;
    const s = Math.sin(turnAngle);
    const c = Math.cos(turnAngle);
    let vx = x2 - x1;
    let vy = y2 - y1;

    const coords = new Array(numSides);
    coords[0] = [x1, y1];
    coords[1] = [x2, y2];

    let curX = x2;
    let curY = y2;
    for (let i = 2; i < coords.length; ++i) {
        const newVx = c * vx - s * vy;
        const newVy = s * vx + c * vy;
    
        vx = newVx;
        vy = newVy;

        curX += vx;
        curY += vy;

        coords[i] = [curX, curY];
    }

    return coords;
}

export function drawPolygon(ctx, polygon) {
    ctx.beginPath();
    ctx.moveTo(...polygon[0]);
    for (let i = 1; i < polygon.length; ++i) {
        ctx.lineTo(...polygon[i]);
    }
    ctx.closePath();
}

export function outsideEdge(polygon, side) {
    return [
        polygon[(side + 1) % polygon.length],
        polygon[side]
    ];
}

export function scaleEdge(edge, scale) {
    const vx = (edge[1][0] - edge[0][0]) * scale; 
    const vy = (edge[1][1] - edge[0][1]) * scale; 

    return [
        edge[0],
        [edge[0][0] + vx, edge[0][1] + vy]
    ];
}
