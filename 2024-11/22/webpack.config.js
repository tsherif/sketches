const HtmlWebpackPlugin = require("html-webpack-plugin");

module.exports = {
    entry: "./index.jsx",
    mode: "development",
    plugins: [
        new HtmlWebpackPlugin({title: "24"})
    ],
    module: {
        rules: [
            {
                test: /\.jsx$/,
                loader: "babel-loader",
                exclude: /node_modules/
            }
        ]
    }
};
