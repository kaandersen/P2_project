const express = require("express");
const path = require("path");

const app = express();

app.use("/static", express.static(path.resolve(__dirname, "HuginsStuff", "frontend", "static")));

app.get("/", (req, res) => {
    res.sendFile(path.resolve(__dirname, "HuginsStuff","frontend", "index.html"));
});

app.get("/Nicklas", (req, res) => {
    app.use(express.static(path.resolve(__dirname, "NicklasStuff")));
    res.sendFile(path.resolve(__dirname, "NicklasStuff", "P2HTML_from.html"));
})

app.listen(process.env.PORT || 5000, () => console.log("Server running at http://localhost:5000/"));