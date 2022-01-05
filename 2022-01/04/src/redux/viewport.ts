import { mat4 } from "gl-matrix";

interface ViewportState {
    width: number;
    height: number;
    projectionMatrix: mat4
}

interface DimensionsPayload {
    width: number;
    height: number;
}

interface DimensionsAction {
    type: "dimensions";
    payload: DimensionsPayload;
}

const initialState: ViewportState = {
    width: window.innerWidth,
    height: window.innerHeight,
    projectionMatrix: mat4.perspective(
        mat4.create(), 
        Math.PI / 2, 
        window.innerWidth / window.innerHeight, 
        0.1, 
        10.0
    )
};


export function viewportReducer(state = initialState, action: DimensionsAction) {
    switch (action.type) {
        case "dimensions":
            const {width, height} = action.payload;
            return {
                ...state,
                width,
                height,
                projectionMatrix: mat4.perspective(
                    mat4.create(), 
                    Math.PI / 2, 
                    width / height, 
                    0.1, 
                    10.0
                )
            }
        default: return state;
    }
}

export const dimensions = (width: number, height: number) => ({ type: "dimensions", payload: { width, height } });