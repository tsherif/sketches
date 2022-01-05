interface ViewportState {
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

const initialState: ViewportState = {
    width: window.innerWidth,
    height: window.innerHeight,
};


export function viewportReducer(state = initialState, action: DimensionsAction) {
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

export const dimensions = (width: number, height: number) => ({ type: "dimensions", payload: { width, height } });