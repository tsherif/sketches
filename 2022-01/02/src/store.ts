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
}

interface StoreAction {
    type: string;
}

const initialState: StoreState = {
    balls: new Array(30).fill(null).map(() => ({
        x: Math.random() * window.innerWidth,
        y: Math.random() * window.innerHeight,
        r: Math.random() * 20 + 5,
        vx: Math.random() * 4 - 2,
        vy: Math.random() * 4 - 2,
        color: `rgb(${Math.random() * 255}, ${Math.random() * 255}, ${Math.random() * 255})`,
    }))
};

function reducer(state = initialState, action: StoreAction) {
    switch (action.type) {
        case "simulate": 
            return {
                ...state, 
                balls: state.balls.map(b => {
                    let vx = b.vx;
                    let vy = b.vy;
                    let x = b.x + vx;
                    let y = b.y + vy;
                    const r = b.r;

                    if (x < r) {
                        x = r;
                        vx *= -1;
                    }

                    if (x > window.innerWidth - r) {
                        x = window.innerWidth - r;
                        vx *= -1;
                    }

                    if (y < r) {
                        y = r;
                        vy *= -1;
                    }

                    if (y > window.innerHeight - r) {
                        y = window.innerHeight - r;
                        vy *= -1;
                    }

                    return {
                        ...b,
                        x,
                        y,
                        vx,
                        vy
                    }
                })
            };
        default: return state;
    }
}

export const store = createStore(reducer, composeWithDevTools());

export const simulate = () => ({ type: "simulate"});
export const ballsSelector = (state: StoreState) => state.balls;