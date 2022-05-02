const express = require("express");
const path = require("path");
const fs = require("fs");
const csv = require("csv-parser");
var bodyParser = require("body-parser");

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

app.use(bodyParser.urlencoded({ extended: false }));

// parse application/json
app.use(bodyParser.json());



app.get("/EliasStuff/public", (req, res) => {
    res.sendFile(path.resolve(__dirname, "EliasStuff", "public", "QuestionairePage.html"));
    app.use("/EliasStuff/public", express.static(path.resolve(__dirname, "EliasStuff", "public")));
});

console.log("HIs3llæ!!");

const csvparser = require("./EliasStuff/public/csv.js");
const csvfs = require("./EliasStuff/public/csv.js");

app.post("/writetocsv", (req, res) => {
  const data = req.body.questionsArray;
  const fileName = req.body.fileName;
  console.log("V ",fileName);

  const WritingToCsv = require("csv-writer").createObjectCsvWriter;
  const csvObject = WritingToCsv({
    append : true,
    path: `EliasStuff/public/${fileName}-Questionaire.csv`,
    header: [
      { id: "id", title: "ID" },
      { id: "question", title: "Question" },
      { id: "answer", title: "Answer" },
      { id: "rooms", title: "Rooms" },
    ],

  });
  csvObject
    .writeRecords(data)
    .then(() =>
      console.log("The CSV file was written successfully", data[0].id)
    );

  res.status(200).json({
    message: "Successfully wrote to csv",
  });
});

app.listen(process.env.PORT || 5000, () => console.log("Server running at http://localhost:5000/"));