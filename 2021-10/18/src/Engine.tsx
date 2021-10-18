import React, {useState, useEffect, useRef} from "react";
import { Renderer } from "./Renderer"

const GRAVITY = 0.01;
const PLAYER_WALK = 0.5;
const PLAYER_JUMP = -2;
const PLAYER_DIM = 40;
const FLOOR = 100;

interface Player {
    x: number;
    y: number;
    vx: number;
    vy: number;
    jumping: boolean;
    timestamp: number;
}

interface Input {
    left: boolean;
    right: boolean;
    up: boolean;
    down: boolean;
    jump: boolean;
}

function useTime() {
    const [time, setTime] = useState(performance.now());
    useEffect(() => {
        let tickId = 0;
        let lastTime = performance.now();
        function tick() {
            tickId = requestAnimationFrame(tick);
            setTime(performance.now());
        };

        tickId = requestAnimationFrame(tick);

        return () => cancelAnimationFrame(tickId);
    }, []);

    return time;
}

function useDimensions() {
    const dimensions = useRef<[number, number]>([window.innerWidth, window.innerHeight])
    useEffect(() => {
        function resize() {
            dimensions.current = [window.innerWidth, window.innerHeight];
        };

        window.addEventListener("resize", resize);

        return () => window.removeEventListener("resize", resize);
    }, []);

    return dimensions.current;
}

function useInput() {
    const input = useRef<Input>({
        left: false,
        right: false,
        up: false,
        down: false,
        jump: false
    });

    useEffect(() => {
        function keyDown(e: KeyboardEvent) {
            const newInput = {...input.current};
            switch (e.key) {
                case "ArrowUp": newInput.up = true; break;
                case "ArrowDown": newInput.down = true; break;
                case "ArrowLeft": newInput.left = true; break;
                case "ArrowRight": newInput.right = true; break;
                case " ": newInput.jump = true; break;
            }

            input.current = newInput;
        } 

        function keyUp(e: KeyboardEvent) {
            const newInput = {...input.current};
            switch (e.key) {
                case "ArrowUp": newInput.up = false; break;
                case "ArrowDown": newInput.down = false; break;
                case "ArrowLeft": newInput.left = false; break;
                case "ArrowRight": newInput.right = false; break;
                case " ": newInput.jump = false; break;
            }

            input.current = newInput;
        } 

        document.addEventListener("keydown", keyDown);
        document.addEventListener("keyup", keyUp);

        return () => {
            document.removeEventListener("keydown", keyDown);
            document.removeEventListener("keyup", keyUp);
        };
    }, []);

    const currentInput = input.current;
    input.current = {...currentInput, jump: false};     

    return currentInput;   
}

function usePlayer(input: Input, time: number, width: number, height: number) {
    const playerRef = useRef<Player>({
        x: width / 2,
        y: height - FLOOR - PLAYER_DIM,
        vx: 0,
        vy: 0,
        jumping: false,
        timestamp: performance.now()
    });

    useEffect(() => {
        const player = playerRef.current;
        const dt = time - player.timestamp;

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

        playerRef.current = {x, y, vx, vy, jumping, timestamp: time};
    }, [time, input, width, height]);

    return playerRef.current;
}

export function Engine() {

    const [width, height] = useDimensions();
    const time = useTime();
    const input = useInput();
    const player = usePlayer(input, time, width, height);

    return (
        <Renderer 
            objects={[
                {
                    x: player.x,
                    y: player.y,
                    width: PLAYER_DIM,
                    height: PLAYER_DIM,
                    color: "red"
                },
                {
                    x: 0,
                    y: height - FLOOR,
                    width,
                    height: FLOOR,
                    color: "blue"
                }
            ]}
            width={width}
            height={height}
        />
    );
}