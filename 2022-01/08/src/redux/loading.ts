import { put, takeEvery, all, SimpleEffect } from "redux-saga/effects";
import type { App as PicoGLApp, Program } from "picogl";

interface LoadingState {
    program: Program | null;
    textureImage: HTMLImageElement | null;
}

interface LoadingBuildProgramAction {
    type: "LOADING_BUILD_PROGRAM";
    payload: { 
        picogl: PicoGLApp, 
        vs: string; 
        fs: string 
    }
}

interface LoadingFetchImageAction {
    type: "LOADING_FETCH_IMAGE";
    payload: string
}

interface LoadingProgramBuiltAction {
    type: "LOADING_PROGRAM_BUILT";
    payload: Program;
}

interface LoadingImageFetchedAction {
    type: "LOADING_IMAGE_FETCHED";
    payload: HTMLImageElement;
}

type LoadingAction = LoadingBuildProgramAction | LoadingFetchImageAction | LoadingProgramBuiltAction | LoadingImageFetchedAction;

const initialState: LoadingState = {
    program: null,
    textureImage: null
};

export function loadingReducer(state = initialState, action: LoadingAction) {
    switch (action.type) {
        case "LOADING_PROGRAM_BUILT":
            return {
                ...state,
                program: action.payload
            };
        case "LOADING_IMAGE_FETCHED":
            return {
                ...state,
                textureImage: action.payload
            };
        default: return state;
    }
}

// Actions
export const buildProgram = (picogl: PicoGLApp, vs: string, fs: string) => {
    return {
        type: "LOADING_BUILD_PROGRAM",
        payload: {
            picogl,
            vs,
            fs
        }
    };
}

export const fetchTextureImage = (url: string) => {
    return {
        type: "LOADING_FETCH_TEXTURE",
        payload: url
    };
}

// Sagas
function* buildProgramSaga({payload: { picogl, vs, fs }} : LoadingBuildProgramAction): Generator<Promise<Program[]> | SimpleEffect<"PUT">, void, Program[]> {
    const [program] = yield picogl.createPrograms([vs, fs]);
    yield put({type: "LOADING_PROGRAM_BUILT", payload: program });
}

function* watchBuildProgram() {
    yield takeEvery("LOADING_BUILD_PROGRAM", buildProgramSaga)
}

function* fetchTextureImageSaga({payload: url} : LoadingFetchImageAction): Generator<Promise<HTMLImageElement> | SimpleEffect<"PUT">, void, HTMLImageElement> {
    const image = yield new Promise((resolve) => {
        const image =  new Image();
        image.onload = () => {
            resolve(image);
        };
        image.src = url;
    });
    yield put({type: "LOADING_IMAGE_FETCHED", payload: image});
}

function* watchFetchTexture() {
    yield takeEvery("LOADING_FETCH_TEXTURE", fetchTextureImageSaga)
}

export function* loadingSaga() {
    yield all([
        watchFetchTexture(),
        watchBuildProgram()
    ]);
}
