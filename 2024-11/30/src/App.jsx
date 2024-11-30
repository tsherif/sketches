import React, { useEffect, useRef, useState } from "react";


export function App() {
    const [message, setMessage] = useState("Waiting...");

    useEffect(() => {
        const worker = new Worker(new URL("./worker.js", import.meta.url));
        worker.addEventListener("message", ({data}) => setMessage(data));
        worker.postMessage("Message to worker");

        return () => worker.terminate();
    }, []);

    return (
        <div>{message}</div>
    );
}