import { createStore, combineReducers, applyMiddleware, AnyAction } from "redux";
import { useDispatch } from "react-redux";
import thunkMiddleware, { ThunkDispatch, ThunkAction } from "redux-thunk";
import { composeWithDevTools } from 'redux-devtools-extension';
import type { App as PicoGLApp, Program } from "picogl";
import { loadedReducer } from "./loaded";
import { sceneReducer } from "./scene";
import { viewportReducer } from "./viewport";

export const store = createStore(
    combineReducers({
        viewport: viewportReducer,
        scene: sceneReducer,
        loaded: loadedReducer
    }), 
    composeWithDevTools(applyMiddleware(thunkMiddleware))
);
type StoreState = ReturnType<typeof store.getState>
export const useAppDispatch = () => useDispatch<ThunkDispatch<StoreState, unknown, AnyAction>>();


// Actions
export { programLoaded } from "./loaded";
export { dimensions } from "./viewport";
export { simulate } from "./scene";

export const buildProgram = (picogl: PicoGLApp, vs: string, fs: string): ThunkAction<Promise<Program>, StoreState, unknown, AnyAction> => {
    return async (dispatch)  => {
        const [program] = await picogl.createPrograms([vs, fs]);
        dispatch({type: "loaded/program"});
        return program;
    }
}

export const fetchTextureImage = (url: string): ThunkAction<Promise<HTMLImageElement>, StoreState, unknown, AnyAction> => {
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

// Selectors
export const selectLoaded = (state: StoreState) => state.loaded.program && state.loaded.texture;
export const selectModelMatrix = (state: StoreState) => state.scene.modelMatrix;
export const selectDimensions = (state: StoreState) => ({ width: state.viewport.width, height: state.viewport.height});
export const selectProjectionMatrix = (state: StoreState) => state.viewport.projectionMatrix;
