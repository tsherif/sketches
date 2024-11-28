module.exports = {
    entry: "./src/index.jsx",
    mode: "development",
    devtool: "inline-source-map",
    module: {
        rules: [
            {
                test: /\.jsx/,
                loader: "babel-loader",
                exclude: /node_modules/
            }
        ]
    },
    output: {
        filename: "app.js"
    }
};
