import React, {useState, useEffect, useRef} from "react";
import ReactDom from "react-dom";

const GRAVITY = 0.01;
const FLOOR = 100;
const PLAYER_DIM = 40;
const PLAYER_WALK = 0.5;
const PLAYER_JUMP = -2;

interface Player {
    x: number;
    y: number;
    vx: number;
    vy: number;
    jumping: boolean;
}

interface Input {
    left: boolean;
    right: boolean;
    up: boolean;
    down: boolean;
    jump: boolean;
}

function useDeltaTime() {
    const [dt, setDt] = useState(0);
    useEffect(() => {
        let tickId = 0;
        let lastTime = performance.now();
        function tick() {
            tickId = requestAnimationFrame(tick);
            let time = performance.now();
            setDt(time - lastTime);
            lastTime = time;
        };

        tickId = requestAnimationFrame(tick);

        return () => cancelAnimationFrame(tickId);
    }, []);

    return dt;
}

function useDimensions() {
    const [dimensions, setDimensions] = useState<[number, number]>([window.innerWidth, window.innerHeight])
    useEffect(() => {
        function resize() {
            setDimensions([window.innerWidth, window.innerHeight]);
        };

        window.addEventListener("resize", resize);

        return () => window.removeEventListener("resize", resize);
    }, []);

    return dimensions;
}

function useInput() {
    const [input, setInput] = useState<Input>({
        left: false,
        right: false,
        up: false,
        down: false,
        jump: false
    });

    useEffect(() => {
        function keyDown(e: KeyboardEvent) {
            const newInput = {...input};
            let changed = false;
            switch (e.key) {
                case "ArrowUp": newInput.up = true; changed = true; break;
                case "ArrowDown": newInput.down = true; changed = true; break;
                case "ArrowLeft": newInput.left = true; changed = true; break;
                case "ArrowRight": newInput.right = true; changed = true; break;
                case " ": newInput.jump = true; changed = true; break;
            }

            if (changed) {
                setInput(newInput);
            }
        } 

        function keyUp(e: KeyboardEvent) {
            const newInput = {...input};
            let changed = false;
            switch (e.key) {
                case "ArrowUp": newInput.up = false; changed = true; break;
                case "ArrowDown": newInput.down = false; changed = true; break;
                case "ArrowLeft": newInput.left = false; changed = true; break;
                case "ArrowRight": newInput.right = false; changed = true; break;
                case " ": newInput.jump = false; changed = true; break;
            }

            if (changed) {
                setInput(newInput);
            }
        } 

        document.addEventListener("keydown", keyDown);
        document.addEventListener("keyup", keyUp);

        return () => {
            document.removeEventListener("keydown", keyDown);
            document.removeEventListener("keyup", keyUp);
        };
    }, [input]);

    useEffect(() => {
        if (input.jump) {
            setInput({...input, jump: false});
        }
    }, [input]);

    return input;   
}

function usePlayer(input: Input, dt: number, width: number, height: number) {
    const [player, setPlayer] = useState<Player>({
        x: width / 2,
        y: height - FLOOR - PLAYER_DIM,
        vx: 0,
        vy: 0,
        jumping: false
    });

    useEffect(() => {
        let {x, y, vx, vy, jumping} = {...player};
        let ay = 0;

        if (input.left) {
            vx = -PLAYER_WALK;
        } else if (input.right) {
            vx = PLAYER_WALK;
        } else {
            vx = 0;
        }

        if (input.jump && !jumping) {
            vy = PLAYER_JUMP;
            jumping = true;
        }

        if (y < height - PLAYER_DIM - FLOOR) {
            ay = GRAVITY;
            vy += GRAVITY * dt;
        }

        x += vx * dt;
        y += vy * dt + ay * dt * dt;

        if (x < 0) {
            x = x = 0;
        }

        if (x > width - PLAYER_DIM) {
            x = width - PLAYER_DIM;
        }

        if (y > height - PLAYER_DIM - FLOOR) {
            y = height - PLAYER_DIM - FLOOR;
            jumping = false;
            vy = 0;
        }

        setPlayer({x, y, vx, vy, jumping});
    }, [dt, input, width, height]);

    return player;
}

function useDraw(canvasRef: React.MutableRefObject<HTMLCanvasElement>, player: Player, width: number, height: number) {
    const contextRef = useRef<CanvasRenderingContext2D>(null);
    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvas) {
            return;
        }
        contextRef.current = canvas.getContext("2d");
    }, []);

    useEffect(() => {
        const canvas = canvasRef.current;
        if (!canvas) {
            return;
        }

        canvas.width = width;
        canvas.height = height;
    }, [width, height]);

    useEffect(() => {
        const context = contextRef.current;

        if (!context) {
            return;
        }

        context.fillStyle = "black";
        context.fillRect(0, 0, width, height);

        context.fillStyle = "red";
        context.fillRect(0, height - FLOOR, width, FLOOR);

        context.fillStyle = "blue";
        context.fillRect(player.x, player.y, PLAYER_DIM, PLAYER_DIM);

    }, [player, width, height]);
}

export function JumpCanvas() {
    const canvasRef = useRef<HTMLCanvasElement>(null);

    const [width, height] = useDimensions();
    const dt = useDeltaTime();
    const input = useInput();
    const player = usePlayer(input, dt, width, height);
    useDraw(canvasRef, player, width, height);

    return (
        <canvas ref={canvasRef}></canvas>
    );
}