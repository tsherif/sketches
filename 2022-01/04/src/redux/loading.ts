import { AnyAction } from "redux";
import { ThunkAction } from "redux-thunk";
import type { App as PicoGLApp, Program } from "picogl";

interface LoadingState {
    program: boolean;
    texture: boolean;
}

interface LoadingProgramAction {
    type: "loaded/program";
}

interface LoadingTextureAction {
    type: "loaded/texture";
}

type LoadingAction = LoadingProgramAction | LoadingTextureAction;

const initialState: LoadingState = {
    program: false,
    texture: false
};

export function loadingReducer(state = initialState, action: LoadingAction) {
    switch (action.type) {
        case "loaded/program":
            return {
                ...state,
                program: true
            };
        case "loaded/texture":
            return {
                ...state,
                texture: true
            };
        default: return state;
    }
}

export const buildProgram = (picogl: PicoGLApp, vs: string, fs: string): ThunkAction<Promise<Program>, unknown, unknown, AnyAction> => {
    return async (dispatch)  => {
        const [program] = await picogl.createPrograms([vs, fs]);
        dispatch({type: "loaded/program"});
        return program;
    }
}

export const fetchTextureImage = (url: string): ThunkAction<Promise<HTMLImageElement>, unknown, unknown, AnyAction> => {
    return (dispatch)  => {
        return new Promise((resolve) => {
            const image =  new Image();
            image.onload = () => {
                dispatch({type: "loaded/texture"});
                resolve(image);
            };
            image.src = url;
        });
    }
}
