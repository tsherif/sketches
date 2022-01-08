import React from "react";
import ReactDom from "react-dom";
import {QueryClient, QueryClientProvider} from "react-query";

import { App } from "./App";

const queryClient = new QueryClient();

ReactDom.render(
	<QueryClientProvider client={queryClient}>
		<App />
	</QueryClientProvider>,
	document.getElementById("root")
);