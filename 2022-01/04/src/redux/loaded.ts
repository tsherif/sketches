interface LoadedState {
    program: boolean;
    texture: boolean;
}

interface LoadedProgramAction {
    type: "loaded/program";
}

interface LoadedTextureAction {
    type: "loaded/texture";
}

type LoadedAction = LoadedProgramAction | LoadedTextureAction;

const initialState: LoadedState = {
    program: false,
    texture: false
};

export function loadedReducer(state = initialState, action: LoadedAction) {
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

export const programLoaded = () => ({ type: "loaded/program" });
