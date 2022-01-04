import {createStore} from "redux";
import { composeWithDevTools } from 'redux-devtools-extension';
import { mat4 } from "gl-matrix";

interface StoreState {
    width: number;
    height: number;
    angleX: number;
    angleY: number;
    modelMatrix: mat4;
    timestamp: number;
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
    width: window.innerWidth,
    height: window.innerHeight,
    angleX: 0,
    angleY: 0,
    modelMatrix: mat4.create(),
    timestamp: performance.now()
};

let rotateXMatrix = mat4.create();
let rotateYMatrix = mat4.create();

function reducer(state = initialState, action: StoreAction) {
    switch (action.type) {
        case "simulate":
            const dt = action.payload - state.timestamp;

            const angleX = state.angleX + 0.01;
            const angleY = state.angleY + 0.02;

            mat4.fromXRotation(rotateXMatrix, angleX);
            mat4.fromYRotation(rotateYMatrix, angleY);
            return {
                ...state, 
                angleX,
                angleY,
                modelMatrix: mat4.multiply(mat4.create(), rotateXMatrix, rotateYMatrix),
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

export const selectModelMatrix = (state: StoreState) => state.modelMatrix;
export const selectDimensions = (state: StoreState) => ({ width: state.width, height: state.height});