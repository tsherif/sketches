import React, { useState, useEffect } from "react";

function delayedValue(n: number, delay: number): Promise<number> {
	return new Promise(resolve => {
		setTimeout(() => resolve(n), delay);
	});
}

type PromiseGenerator<T> = Generator<Promise<T>[], void, T[]>;

function asyncBlock<T>(generator: () => PromiseGenerator<T>) {
	const iterator = generator();

	function next(n: T[]) {
		const state = iterator.next(n);

		if (!state.done && state.value) {
			Promise.all(state.value).then(next);
		}
	}

	next([]);
}

export function App() {
	const [number, setNumber] = useState(0);

	useEffect(() => {
		asyncBlock(function* () {
			const [x] = yield [delayedValue(5, 1000)];
			setNumber(x);
			const [_, y] = yield [delayedValue(7, 1000), delayedValue(8, 2000)];
			setNumber(y);
		});
	}, []); 

	return <div>{number}</div>;
}