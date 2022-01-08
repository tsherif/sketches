import { createStore, combineReducers, applyMiddleware, AnyAction } from "redux";
import { useDispatch } from "react-redux";
import createSagaMiddleware from "redux-saga";
import { composeWithDevTools } from "redux-devtools-extension";
import type { App as PicoGLApp, Program } from "picogl";
import { loadingReducer, loadingSaga } from "./loading";
import { sceneReducer } from "./scene";
import { viewportReducer } from "./viewport";

const sagaMiddleware = createSagaMiddleware();

export const store = createStore(
    combineReducers({
        viewport: viewportReducer,
        scene: sceneReducer,
        loaded: loadingReducer
    }), 
    composeWithDevTools(applyMiddleware(sagaMiddleware))
);

sagaMiddleware.run(loadingSaga);
type StoreState = ReturnType<typeof store.getState>

// Actions
export { buildProgram, fetchTextureImage } from "./loading";
export { dimensions } from "./viewport";
export { simulate } from "./scene";

// Selectors
export const selectLoaded = (state: StoreState) => Boolean(state.loaded.program && state.loaded.textureImage);
export const selectProgram = (state: StoreState) => state.loaded.program;
export const selectTextureImage = (state: StoreState) => state.loaded.textureImage;
export const selectModelMatrix = (state: StoreState) => state.scene.modelMatrix;
export const selectDimensions = (state: StoreState) => ({ width: state.viewport.width, height: state.viewport.height});
export const selectProjectionMatrix = (state: StoreState) => state.viewport.projectionMatrix;
