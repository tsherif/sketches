import {createStore} from "redux";
import { composeWithDevTools } from 'redux-devtools-extension';

interface StoreState {
	value: number;
}

interface StoreAction {
	type: string;
}

const initialState: StoreState = {
	value: 0
};

function reducer(state = initialState, action: StoreAction) {
	switch (action.type) {
		case "increment": return {...state, value: state.value + 1};
		case "decrement": return {...state, value: state.value - 1};
		default: return state;
	}
}

export const store = createStore(reducer, composeWithDevTools());

export const increment = () => ({ type: "increment"});
export const decrement = () => ({ type: "decrement"});
export const valueSelector = (state: StoreState) => state.value;