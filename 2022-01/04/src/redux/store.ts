import { createStore, combineReducers, applyMiddleware, AnyAction } from "redux";
import { useDispatch } from "react-redux";
import thunkMiddleware, { ThunkDispatch, ThunkAction } from "redux-thunk";
import { composeWithDevTools } from 'redux-devtools-extension';
import type { App as PicoGLApp, Program } from "picogl";
import { loadingReducer } from "./loading";
import { sceneReducer } from "./scene";
import { viewportReducer } from "./viewport";

export const store = createStore(
    combineReducers({
        viewport: viewportReducer,
        scene: sceneReducer,
        loaded: loadingReducer
    }), 
    composeWithDevTools(applyMiddleware(thunkMiddleware))
);
type StoreState = ReturnType<typeof store.getState>
export const useAppDispatch = () => useDispatch<ThunkDispatch<unknown, unknown, AnyAction>>();

// Actions
export { buildProgram, fetchTextureImage } from "./loading";
export { dimensions } from "./viewport";
export { simulate } from "./scene";

// Selectors
export const selectLoaded = (state: StoreState) => state.loaded.program && state.loaded.texture;
export const selectModelMatrix = (state: StoreState) => state.scene.modelMatrix;
export const selectDimensions = (state: StoreState) => ({ width: state.viewport.width, height: state.viewport.height});
export const selectProjectionMatrix = (state: StoreState) => state.viewport.projectionMatrix;
