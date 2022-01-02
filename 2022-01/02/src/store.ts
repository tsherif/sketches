import {createStore} from "redux";
import { composeWithDevTools } from 'redux-devtools-extension';

interface Ball {
    x: number;
    y: number;
    r: number;
    vx: number;
    vy: number;
    color: string;
}

interface StoreState {
    balls: Ball[];
    timestamp: number;
    width: number;
    height: number;
}

interface DimensionsPayload {
    width: number;
    height: number;
}

interface DimensionsAction {
    type: "dimensions";
    payload: DimensionsPayload;
}

interface SimulateAction {
    type: "simulate";
    payload: number;
}

type StoreAction = SimulateAction | DimensionsAction;

const initialState: StoreState = {
    balls: new Array(100).fill(null).map(() => ({
        x: Math.random() * window.innerWidth,
        y: Math.random() * window.innerHeight,
        r: Math.random() * 20 + 5,
        vx: Math.random() - 0.5,
        vy: Math.random() - 0.5,
        color: `rgb(${Math.random() * 255}, ${Math.random() * 255}, ${Math.random() * 255})`,
    })),
    timestamp: performance.now(),
    width: window.innerWidth,
    height: window.innerHeight
};

function reducer(state = initialState, action: StoreAction) {
    switch (action.type) {
        case "simulate":
            const dt = action.payload - state.timestamp;
            return {
                ...state, 
                balls: state.balls.map(b => {
                    let vx = b.vx;
                    let vy = b.vy;
                    let x = b.x + vx * dt;
                    let y = b.y + vy * dt;
                    const r = b.r;

                    if (x < r) {
                        x = r;
                        vx *= -1;
                    }

                    if (x > state.width - r) {
                        x = state.width - r;
                        vx *= -1;
                    }

                    if (y < r) {
                        y = r;
                        vy *= -1;
                    }

                    if (y > state.height - r) {
                        y = state.height - r;
                        vy *= -1;
                    }

                    return {
                        ...b,
                        x,
                        y,
                        vx,
                        vy
                    }
                }),
                timestamp: action.payload
            };
        case "dimensions":
            const {width, height} = action.payload;
            return {
                ...state,
                width,
                height
            }
        default: return state;
    }
}

export const store = createStore(reducer, composeWithDevTools());

export const simulate = (timestamp: number) => ({ type: "simulate", payload: timestamp});
export const dimensions = (width: number, height: number) => ({ type: "dimensions", payload: { width, height } });
export const ballsSelector = (state: StoreState) => state.balls;
export const dimensionsSelector = (state: StoreState) => ({ width: state.width, height: state.height});