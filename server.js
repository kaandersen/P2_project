const express = require("express");
const path = require("path");
const fs = require("fs");

const app = express();

app.use("/static", express.static(path.resolve(__dirname, "HuginsStuff", "frontend", "static")));

app.get("/", (req, res) => {
    res.sendFile(path.resolve(__dirname, "HuginsStuff","frontend", "index.html"));
});

app.get("/Nicklas", (req, res) => {
    app.use(express.static(path.resolve(__dirname, "NicklasStuff")));
    res.sendFile(path.resolve(__dirname, "NicklasStuff", "redirectFrom.html"));
})

app.get("/views/StudentID.txt", (req, res) => {
    res.sendFile(path.resolve(__dirname, "HuginsStuff", "frontend", "static", "js", "views", "StudentID.txt"))
})

app.get("/data.txt", (req, res) => {
    res.sendFile(path.resolve(__dirname, "NicklasStuff", "output.txt"))
})

app.listen(process.env.PORT || 5000, () => console.log("Server running at http://localhost:5000/"));