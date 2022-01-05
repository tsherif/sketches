import { createStore, applyMiddleware, AnyAction } from "redux";
import { useDispatch } from "react-redux";
import thunkMiddleware, { ThunkAction, ThunkDispatch } from "redux-thunk";
import { composeWithDevTools } from 'redux-devtools-extension';
import { mat4 } from "gl-matrix";

interface StoreState {
    width: number;
    height: number;
    angleX: number;
    angleY: number;
    modelMatrix: mat4;
    timestamp: number;
    programLoaded: boolean;
    textureLoaded: boolean;
}

interface DimensionsPayload {
    width: number;
    height: number;
}


interface ProgramLoadedAction {
    type: "programLoaded";
}

interface TextureLoadedAction {
    type: "textureLoaded";
}

interface DimensionsAction {
    type: "dimensions";
    payload: DimensionsPayload;
}

interface SimulateAction {
    type: "simulate";
    payload: number;
}

type StoreAction = ProgramLoadedAction | TextureLoadedAction | SimulateAction | DimensionsAction;

const initialState: StoreState = {
    width: window.innerWidth,
    height: window.innerHeight,
    angleX: 0,
    angleY: 0,
    modelMatrix: mat4.create(),
    timestamp: performance.now(),
    programLoaded: false,
    textureLoaded: false
};

let rotateXMatrix = mat4.create();
let rotateYMatrix = mat4.create();

function reducer(state = initialState, action: StoreAction) {
    switch (action.type) {
        case "programLoaded":
            return {
                ...state,
                programLoaded: true
            };
        case "textureLoaded":
            return {
                ...state,
                textureLoaded: true
            };
        case "simulate":
            const dt = action.payload - state.timestamp;
            const angleX = state.angleX + 0.001 * dt;
            const angleY = state.angleY + 0.002 * dt;

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

export const store = createStore(reducer, composeWithDevTools(applyMiddleware(thunkMiddleware)));
export const useAppDispatch = () => useDispatch<ThunkDispatch<StoreState, unknown, AnyAction>>();

export const programLoaded = () => ({ type: "programLoaded" });
export const textureLoaded = () => ({ type: "textureLoaded" });
export const simulate = (timestamp: number) => ({ type: "simulate", payload: timestamp});
export const dimensions = (width: number, height: number) => ({ type: "dimensions", payload: { width, height } });
export const fetchTextureImage = (): ThunkAction<Promise<HTMLImageElement>, StoreState, unknown, AnyAction> => {
    return (dispatch)  => {
        return new Promise((resolve) => {
            const image =  new Image();
            image.onload = () => {
                dispatch({type: "textureLoaded"});
                resolve(image);
            };
            image.src = "./webgl-logo.png";
        });
    }
}

export const selectLoaded = (state: StoreState) => state.programLoaded && state.textureLoaded;
export const selectModelMatrix = (state: StoreState) => state.modelMatrix;
export const selectDimensions = (state: StoreState) => ({ width: state.width, height: state.height});
