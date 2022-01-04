import {createStore} from "redux";
import { composeWithDevTools } from 'redux-devtools-extension';

interface StoreState {
    width: number;
    height: number;
}

interface DimensionsPayload {
    width: number;
    height: number;
}

interface DimensionsAction {
    type: "dimensions";
    payload: DimensionsPayload;
}

type StoreAction = DimensionsAction;

const initialState: StoreState = {
    width: window.innerWidth,
    height: window.innerHeight
};

function reducer(state = initialState, action: StoreAction) {
    switch (action.type) {
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

export const store = createStore(reducer, composeWithDevTools());

export const dimensions = (width: number, height: number) => ({ type: "dimensions", payload: { width, height } });
export const dimensionsSelector = (state: StoreState) => ({ width: state.width, height: state.height});