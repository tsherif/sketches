import { put, takeEvery, all, SimpleEffect } from "redux-saga/effects";
import { Observable, scan } from "rxjs";
import type { App as PicoGLApp, Program } from "picogl";

type LoadingObservable = Observable<{ program: Program | null, image: HTMLImageElement | null}>;

interface LoadingState {
    observable: LoadingObservable | null;
}

interface LoadingInitObservableAction {
    type: "LOADING_INIT_OBSERVABLE";
    payload: { 
        picogl: PicoGLApp, 
        vs: string; 
        fs: string,
        imageURL: string;
    }
}

interface LoadingObservableInitializedAction {
    type: "LOADING_OBSERVABLE_INITIALIZED";
    payload: LoadingObservable;
}

type LoadingAction = LoadingObservableInitializedAction;

const initialState: LoadingState = {
   observable: null
};

export function loadingReducer(state = initialState, action: LoadingAction) {
    switch (action.type) {
        case "LOADING_OBSERVABLE_INITIALIZED":
            return {
                ...state,
                observable: action.payload
            };
        default: return state;
    }
}

// Actions
export const initObservable = (payload : LoadingInitObservableAction["payload"]) => {
    return {
        type: "LOADING_INIT_OBSERVABLE",
        payload
    };
}

// Sagas
function* initObservableSaga({payload: { picogl, vs, fs, imageURL }} : LoadingInitObservableAction): Generator<Promise<Program[]> | SimpleEffect<"PUT">, void, Program[]> {
    const [program] = yield picogl.createPrograms([vs, fs]);

    const observable = new Observable<Program | HTMLImageElement>(subscriber => {
        picogl.createPrograms([vs, fs]).then(([program]) => subscriber.next(program));
        const image =  new Image();
        image.onload = () => subscriber.next(image);
        image.src = imageURL;
    }).pipe(scan((acc, curr) => {
        if (isProgram(curr)) {
            acc.program = curr;
        } else {
            acc.image = curr;
        }

        return acc;
    }, { program: null, image: null }));

    yield put({type: "LOADING_OBSERVABLE_INITIALIZED", payload: observable });
}

function* watchInitObservable() {
    yield takeEvery("LOADING_INIT_OBSERVABLE", initObservableSaga)
}

export function* loadingSaga() {
    yield watchInitObservable();
}

function isProgram(test: unknown): test is Program {
    if ((test as Program).gl !== undefined) {
        return true;
    }

    return false;
}
