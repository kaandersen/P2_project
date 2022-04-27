const express = require("express");
const path = require("path");
const fs = require("fs");

const app = express();

app.use("/static", express.static(path.resolve(__dirname, "HuginsStuff", "frontend", "static")));

app.get("/", (req, res) => {
    res.sendFile(path.resolve(__dirname, "HuginsStuff","frontend", "index.html"));
});

//directs into the "Admin" folder, which contains the admin related stuff
app.get("/Admin", (req, res) => {
    app.use(express.static(path.resolve(__dirname, "Admin")));
    res.sendFile(path.resolve(__dirname, "Admin", "redirectFrom.html"));
})

//directs into the "Student" folder, which contains the student related stuff
app.get("/StudentHome", (req, res) => {
    app.use(express.static(path.resolve(__dirname, "Student")));
    res.sendFile(path.resolve(__dirname, "Student", "StudentHomePage.html"));
})


app.get("/views/StudentID.txt", (req, res) => {
    res.sendFile(path.resolve(__dirname, "HuginsStuff", "frontend", "static", "js", "views", "StudentID.txt"))
})

app.get("/data.txt", (req, res) => {
    res.sendFile(path.resolve(__dirname, "Admin", "output.txt"))
})

app.listen(process.env.PORT || 5000, () => console.log("Server running at http://localhost:5000/"));