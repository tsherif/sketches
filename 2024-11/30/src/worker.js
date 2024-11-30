addEventListener("message", ({data}) => {
    postMessage(`Received message: ${data}`);
})