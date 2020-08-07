export function createTetrahedron() {
    const TRIANGLE_HEIGHT = Math.sin(Math.PI / 3);
    const TRIANGLE_APOTHEM = TRIANGLE_HEIGHT / 3;
    const TRIANGLE_RADIUS = Math.sqrt(0.25 + TRIANGLE_APOTHEM * TRIANGLE_APOTHEM)
    const TRIANGLE_ANGLE = 2 * Math.PI / 3;
    const START_ANGLE = Math.PI * 0.5;
    const TETRAHEDRON_HEIGHT = Math.sqrt(TRIANGLE_HEIGHT * TRIANGLE_HEIGHT - TRIANGLE_APOTHEM * TRIANGLE_APOTHEM);

    const p1 = [
        TRIANGLE_RADIUS,
        0,
        0
    ];
    const p2 = [
        TRIANGLE_RADIUS * Math.sin(TRIANGLE_ANGLE + START_ANGLE),
        0,
        TRIANGLE_RADIUS * Math.cos(TRIANGLE_ANGLE + START_ANGLE)
    ];
    const p3 = [
        TRIANGLE_RADIUS * Math.sin(TRIANGLE_ANGLE * 2 + START_ANGLE),
        0,
        TRIANGLE_RADIUS * Math.cos(TRIANGLE_ANGLE * 2 + START_ANGLE)
    ];

    const p4 = [
        0,
        TETRAHEDRON_HEIGHT,
        0
    ];

    const positions = new Float32Array([
        ...p3, ...p2, ...p1,
        ...p1, ...p2, ...p4,
        ...p2, ...p3, ...p4,
        ...p3, ...p1, ...p4
    ]);

    return positions;
}

export function createHexahedron() {
    let fbl = [ -0.5, -0.5, 0.5 ];
    let fbr = [ 0.5, -0.5, 0.5 ];
    let ftl = [ -0.5, 0.5, 0.5 ];
    let ftr = [ 0.5, 0.5, 0.5 ];
    let bbl = [ -0.5, -0.5, -0.5  ];
    let bbr = [ 0.5, -0.5, -0.5  ];
    let btl = [ -0.5, 0.5, -0.5  ];
    let btr = [ 0.5, 0.5, -0.5  ];

    let positions = new Float32Array([
        //front
        fbl[0], fbl[1], fbl[2],
        fbr[0], fbr[1], fbr[2],
        ftl[0], ftl[1], ftl[2],
        ftl[0], ftl[1], ftl[2],
        fbr[0], fbr[1], fbr[2],
        ftr[0], ftr[1], ftr[2],

        //right
        fbr[0], fbr[1], fbr[2],
        bbr[0], bbr[1], bbr[2],
        ftr[0], ftr[1], ftr[2],
        ftr[0], ftr[1], ftr[2],
        bbr[0], bbr[1], bbr[2],
        btr[0], btr[1], btr[2],

        //back
        fbr[0], bbr[1], bbr[2],
        bbl[0], bbl[1], bbl[2],
        btr[0], btr[1], btr[2],
        btr[0], btr[1], btr[2],
        bbl[0], bbl[1], bbl[2],
        btl[0], btl[1], btl[2],

        //left
        bbl[0], bbl[1], bbl[2],
        fbl[0], fbl[1], fbl[2],
        btl[0], btl[1], btl[2],
        btl[0], btl[1], btl[2],
        fbl[0], fbl[1], fbl[2],
        ftl[0], ftl[1], ftl[2],

        //top
        ftl[0], ftl[1], ftl[2],
        ftr[0], ftr[1], ftr[2],
        btl[0], btl[1], btl[2],
        btl[0], btl[1], btl[2],
        ftr[0], ftr[1], ftr[2],
        btr[0], btr[1], btr[2],

        //bottom
        bbl[0], bbl[1], bbl[2],
        bbr[0], bbr[1], bbr[2],
        fbl[0], fbl[1], fbl[2],
        fbl[0], fbl[1], fbl[2],
        bbr[0], bbr[1], bbr[2],
        fbr[0], fbr[1], fbr[2]
    ]);

    return positions;

}

export function createOctahedron() {
    const p1 = [-1, -1, 0];
    const p2 = [1, -1, 0];
    const p3 = [1, 1, 0];
    const p4 = [-1, 1, 0];

    const height = Math.sqrt(2);
    const p5 = [0, 0, height];
    const p6 = [0, 0, -height];

    const positions = new Float32Array([
        ...p1, ...p2, ...p5,
        ...p2, ...p3, ...p5,
        ...p3, ...p4, ...p5,
        ...p4, ...p1, ...p5,
        ...p2, ...p1, ...p6,
        ...p3, ...p2, ...p6,
        ...p4, ...p3, ...p6,
        ...p1, ...p4, ...p6,
    ]);

    return positions;
}

export function createDodecahedron() {
    const PENTAGON_ANGLE = 0.4 * Math.PI;
    const PENTAGON_HALF_ANGLE = 0.2 * Math.PI;
    const PENTAGON_RADIUS = 0.5 / Math.cos(3 * Math.PI / 10); // PENTAGON CENTER TO VERTEX
    const PENTAGON_APOTHEM = PENTAGON_RADIUS * Math.sin(3 * Math.PI / 10); // PENTAGON CENTER TO SIDE
    const PENTAGON_SAGITTA = PENTAGON_RADIUS - PENTAGON_APOTHEM; 
    const PENTAGON_HEIGHT = PENTAGON_APOTHEM + PENTAGON_RADIUS;
    const START_ANGLE = Math.PI * 0.5;
    const SHORT_HEIGHT = PENTAGON_RADIUS; // VERTICAL HEIGHT FROM BASE SIDE TO OPPOSITE VERTEX
    const LONG_HEIGHT = 2 * PENTAGON_APOTHEM;  // VERTICAL HEIGHT FROM BASE VERTEX TO END OF ADJACENT EDGE
    const DODECAHEDRON_HEIGHT = LONG_HEIGHT + SHORT_HEIGHT;
    const DODECAHEDRON_LARGE_RADIUS = 2 * PENTAGON_APOTHEM;


    const TOP_Y = 0.5 * DODECAHEDRON_HEIGHT;
    const ROW2_Y = TOP_Y - SHORT_HEIGHT;
    const ROW3_Y = TOP_Y - LONG_HEIGHT;
    const BOTTOM_Y = -0.5 * DODECAHEDRON_HEIGHT;

    const p1 = [
        PENTAGON_RADIUS,
        TOP_Y,
        0
    ];
    const p2 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE + START_ANGLE),
        TOP_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE + START_ANGLE)
    ];
    const p3 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 2 + START_ANGLE),
        TOP_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 2 + START_ANGLE)
    ];
    const p4 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 3 + START_ANGLE),
        TOP_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 3 + START_ANGLE)
    ];
    const p5 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 4 + START_ANGLE),
        TOP_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 4 + START_ANGLE)
    ];

    const p6 = [
        DODECAHEDRON_LARGE_RADIUS,
        ROW2_Y,
        0
    ];
    const p7 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE + START_ANGLE),
        ROW2_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE + START_ANGLE)
    ];
    const p8 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE * 2 + START_ANGLE),
        ROW2_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE * 2 + START_ANGLE)
    ];
    const p9 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE * 3 + START_ANGLE),
        ROW2_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE * 3 + START_ANGLE)
    ];
    const p10 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE * 4 + START_ANGLE),
        ROW2_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE * 4 + START_ANGLE)
    ];

    const p11 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(START_ANGLE + PENTAGON_HALF_ANGLE),
        ROW3_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p12 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE + START_ANGLE + PENTAGON_HALF_ANGLE),
        ROW3_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p13 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE * 2 + START_ANGLE + PENTAGON_HALF_ANGLE),
        ROW3_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE * 2 + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p14 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE * 3 + START_ANGLE + PENTAGON_HALF_ANGLE),
        ROW3_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE * 3 + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p15 = [
        DODECAHEDRON_LARGE_RADIUS * Math.sin(PENTAGON_ANGLE * 4 + START_ANGLE + PENTAGON_HALF_ANGLE),
        ROW3_Y,
        DODECAHEDRON_LARGE_RADIUS * Math.cos(PENTAGON_ANGLE * 4 + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];

    const p16 = [
        PENTAGON_RADIUS * Math.sin(START_ANGLE + PENTAGON_HALF_ANGLE),
        BOTTOM_Y,
        PENTAGON_RADIUS * Math.cos(START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p17 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE + START_ANGLE + PENTAGON_HALF_ANGLE),
        BOTTOM_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p18 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 2 + START_ANGLE + PENTAGON_HALF_ANGLE),
        BOTTOM_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 2 + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p19 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 3 + START_ANGLE + PENTAGON_HALF_ANGLE),
        BOTTOM_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 3 + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];
    const p20 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 4 + START_ANGLE + PENTAGON_HALF_ANGLE),
        BOTTOM_Y,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 4 + START_ANGLE + PENTAGON_HALF_ANGLE)
    ];


    const positions = new Float32Array([
        // PENTAGON 1: p1, p2, p3, p4, p5
        ...p1, ...p2, ...p3, 
        ...p1, ...p3, ...p4, 
        ...p1, ...p4, ...p5,


        // PENTAGON 2: p1, p6, p11, p7, p2
        ...p1, ...p6, ...p11,
        ...p1, ...p11, ...p7,
        ...p1, ...p7, ...p2,

        // PENTAGON 3: p2, p7, p12, p8, p3
        ...p2, ...p7, ...p12,
        ...p2, ...p12, ...p8,
        ...p2, ...p8, ...p3,

        // PENTAGON 4: p3, p8, p13, p9, p4
        ...p3, ...p8, ...p13,
        ...p3, ...p13, ...p9,
        ...p3, ...p9, ...p4,

        // PENTAGON 5: p4, p9, p14, p10, p5
        ...p4, ...p9, ...p14,
        ...p4, ...p14, ...p10,
        ...p4, ...p10, ...p5,

        // PENTAGON 6: p5, p10, p15, p6, p1
        ...p5, ...p10, ...p15,
        ...p5, ...p15, ...p6,
        ...p5, ...p6, ...p1,

        // PENTAGON 7: p6, p15, p20, p16, p11
        ...p6, ...p15, ...p20,
        ...p6, ...p20, ...p16,
        ...p6, ...p16, ...p11,

        // PENTAGON 8: p7, p11, p16, p17, p12
        ...p7, ...p11, ...p16,
        ...p7, ...p16, ...p17,
        ...p7, ...p17, ...p12,

        // PENTAGON 9: p8, p12, p17, p18, p13
        ...p8, ...p12, ...p17,
        ...p8, ...p17, ...p18,
        ...p8, ...p18, ...p13,

        // PENTAGON 10: p9, p13, p18, p19, p14
        ...p9, ...p13, ...p18,
        ...p9, ...p18, ...p19,
        ...p9, ...p19, ...p14,

        // PENTAGON 11: p10, p14, p19, p20, p15
        ...p10, ...p14, ...p19,
        ...p10, ...p19, ...p20,
        ...p10, ...p20, ...p15,

        // PENTAGON 12: p16, p17, p18, p19, p20
        ...p16, ...p20, ...p19,
        ...p16, ...p19, ...p18,
        ...p16, ...p18, ...p17
    ]);

    return positions;
}

export function createIcosahedron() {
    const PENTAGON_ANGLE = 0.4 * Math.PI;
    const PENTAGON_HALF_ANGLE = 0.2 * Math.PI;
    const PENTAGON_RADIUS = 0.5 / Math.cos(3 * Math.PI / 10); // PENTAGON CENTER TO VERTEX
    const TRIANGLE_HEIGHT = Math.sin(Math.PI / 3); // TRIANGLE HEIGHT
    const PENTAGON_PERP = PENTAGON_RADIUS * Math.sin(3 * Math.PI / 10); // PENTAGON CENTER TO SIDE

    const CENTER_HALF_HEIGHT = 0.5 * Math.sqrt(TRIANGLE_HEIGHT * TRIANGLE_HEIGHT - PENTAGON_RADIUS * PENTAGON_RADIUS - PENTAGON_PERP * PENTAGON_PERP + 2 * PENTAGON_PERP * PENTAGON_RADIUS);
    const CAP_HEIGHT = Math.sqrt(TRIANGLE_HEIGHT * TRIANGLE_HEIGHT - PENTAGON_PERP * PENTAGON_PERP); 

    const top = [
        0,
        CAP_HEIGHT + CENTER_HALF_HEIGHT,
        0
    ];
    const p1 = [
        0,
        CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS
    ];
    const p2 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE),
        CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE)
    ];
    const p3 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 2),
        CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 2)
    ];
    const p4 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 3),
        CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 3)
    ];
    const p5 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_ANGLE * 4),
        CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_ANGLE * 4)
    ];
    const p6 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_HALF_ANGLE),
        -CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_HALF_ANGLE)
    ];
    const p7 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE),
        -CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE)
    ];
    const p8 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE * 2),
        -CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE * 2)
    ];
    const p9 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE * 3),
        -CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE * 3)
    ];
    const p10 = [
        PENTAGON_RADIUS * Math.sin(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE * 4),
        -CENTER_HALF_HEIGHT,
        PENTAGON_RADIUS * Math.cos(PENTAGON_HALF_ANGLE + PENTAGON_ANGLE * 4)
    ];
    const bottom = [
        0,
        -CAP_HEIGHT - CENTER_HALF_HEIGHT,
        0
    ];

    const positions = new Float32Array([
        ...top, ...p1,  ...p2,
        ...top, ...p2,  ...p3,
        ...top, ...p3,  ...p4,
        ...top, ...p4,  ...p5,
        ...top, ...p5,  ...p1,
        ...p1,  ...p6,  ...p2,
        ...p6,  ...p7,  ...p2,
        ...p2,  ...p7,  ...p3,
        ...p7,  ...p8,  ...p3,
        ...p3,  ...p8,  ...p4,
        ...p8,  ...p9,  ...p4,
        ...p4,  ...p9,  ...p5,
        ...p9,  ...p10,  ...p5,
        ...p5,  ...p10, ...p1,
        ...p10,  ...p6, ...p1,
        ...p6, ...bottom, ...p7,
        ...p7, ...bottom, ...p8,
        ...p8, ...bottom, ...p9,
        ...p9, ...bottom, ...p10,
        ...p10, ...bottom, ...p6
    ]);

    return positions;
}
