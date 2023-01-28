addEventListener("message", message => {
    const {start, end, buffer} = message.data;

    console.log(start, end, buffer);

    postMessage({});
})