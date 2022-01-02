import React from "react";
import { useSelector, useDispatch } from "react-redux";

import {increment, decrement, valueSelector} from "./store";

const style = {
	marginLeft: "3px",
	marginRight: "3px"
};

const controlStyle = {
	...style,
	cursor: "pointer"
}

export function App() {
	const count = useSelector(valueSelector);
	const dispatch = useDispatch();

	return (
		<div>
			<span style={style}>{count}</span>
			<button style={controlStyle} onClick={() => dispatch(increment())}>+</button>
			<button style={controlStyle} onClick={() => dispatch(decrement())}>-</button>
		</div>
	);
}