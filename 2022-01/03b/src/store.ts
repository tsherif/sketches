import {createStore, applyMiddleware, Dispatch, Action} from "redux";
import thunkMiddleware from 'redux-thunk';
import { composeWithDevTools } from 'redux-devtools-extension';


type LoadState = "init" | "loading" | "loaded";

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
    loadState: LoadState;
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

interface LoadStartedAction {
    type: "load/started";
}

interface LoadSuccessAction {
    type: "load/success";
    payload: {
        numBalls: number;
        colors: string[]
    }
}

interface LoadFailureAction {
    type: "load/failure";
}

type StoreAction = SimulateAction | DimensionsAction | LoadStartedAction | LoadSuccessAction | LoadFailureAction;

const initialState: StoreState = {
    balls: [],
    loadState: "init",
    timestamp: performance.now(),
    width: window.innerWidth,
    height: window.innerHeight
};

function reducer(state = initialState, action: StoreAction) {
    switch (action.type) {
        case "load/started":
            return {
                ...state,
                loadState: "loading"
            }
        case "load/success":
            const {numBalls, colors} = action.payload;
            return {
                ...state,
                loadState: "loaded",
                balls: new Array(numBalls).fill(null).map(() => ({
                    x: Math.random() * window.innerWidth,
                    y: Math.random() * window.innerHeight,
                    r: Math.random() * 20 + 5,
                    vx: Math.random() - 0.5,
                    vy: Math.random() - 0.5,
                    color: colors[Math.floor(Math.random() * colors.length)],
                }))
            }

        case "load/failure":
            return {
                ...state,
                loadState: "init"
            }
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

export const store = createStore(reducer, composeWithDevTools(applyMiddleware(thunkMiddleware)));

export const simulate = (timestamp: number) => ({ type: "simulate", payload: timestamp});
export const dimensions = (width: number, height: number) => ({ type: "dimensions", payload: { width, height } });
export const loadConfig = (dispatch: Dispatch<Action>, getState: () => StoreState) => {
    if (getState().loadState !== "init") {
        return Promise.resolve();
    }

    dispatch({ type: "load/started"});

    return fetch("./ball-config.json")
        .then(res => res.json())
        .then(json => dispatch({type: "load/success", payload: json}))
        .catch(() => dispatch({type: "load/failure"}))
}

export const selectBalls = (state: StoreState) => state.balls;
export const selectDimensions = (state: StoreState) => ({ width: state.width, height: state.height});
export const selectLoadState = (state: StoreState) => state.loadState;