import React, { useState } from "react";
import { useQuery, QueryKey } from "react-query";

export function App() {
	const [page, setPage] = useState(0);
	const {data, isLoading} = useQuery<unknown, unknown, number[], [string, number]>(["list", page], ({ queryKey: [_, page] }) => {
		return new Promise(resolve => {
			setTimeout(() => resolve(new Array(10).fill(0).map((_, i) => page * 10 + i)), 500)
		}) ;
	});

	return (
		<>
			Select Page:
			<select onChange={data => setPage(Number(data.target.value))}>
				{new Array(10).fill(0).map((_, i) => <option key={`option-${i}`} value={i}>{i}</option>)}
			</select>
			{isLoading ? <div>Loading...</div> : data?.map(i => <div key={`data-${i}`}>{i}</div>)}
		</>
	);
}