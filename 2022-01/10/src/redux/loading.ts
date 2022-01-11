import { Observable, reduce, concat } from "rxjs";
import type { App as PicoGLApp, Program } from "picogl";

type LoadingObservable = Observable<[Program, HTMLImageElement]>;

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

type LoadingAction = LoadingInitObservableAction;

const initialState: LoadingState = {
   observable: null
};

export function loadingReducer(state = initialState, action: LoadingAction) {
    switch (action.type) {
        case "LOADING_INIT_OBSERVABLE":
            const { picogl, vs, fs, imageURL } = action.payload;
            return {
                ...state,
                observable: concat(
                    new Observable<Program>(subscriber => {
                        picogl.createPrograms([vs, fs]).then(([program]) => {
                            subscriber.next(program);
                            subscriber.complete();
                        });
                    }),
                    new Observable<HTMLImageElement>(subscriber => {
                        const image =  new Image();
                        image.onload = () => {
                            subscriber.next(image);
                            subscriber.complete();
                        };
                        image.src = imageURL;
                    })
                ).pipe(
                    reduce((acc, curr) => {
                        acc.push(curr);
                        return acc;
                    }, [])
                )
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
