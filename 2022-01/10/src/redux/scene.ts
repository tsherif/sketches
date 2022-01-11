import { mat4 } from "gl-matrix";

interface SceneState {
    angleX: number;
    angleY: number;
    modelMatrix: mat4;
    timestamp: number;
}

interface SimulateAction {
    type: "SCENE_SIMULATE";
    payload: number;
}

const initialState: SceneState = {
    angleX: 0,
    angleY: 0,
    modelMatrix: mat4.create(),
    timestamp: performance.now()
};

const rotateXMatrix = mat4.create();
const rotateYMatrix = mat4.create();

export function sceneReducer(state = initialState, action: SimulateAction) {
    switch (action.type) {
        case "SCENE_SIMULATE":
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
        default: return state;
    }
}

export const simulate = (timestamp: number) => ({ type: "SCENE_SIMULATE", payload: timestamp});
