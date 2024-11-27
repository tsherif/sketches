import React from "react";
import { createRoot } from "react-dom/client";
import { App } from "./App.jsx";

const root = createRoot(document.getElementById("container"));
root.render(<App />);