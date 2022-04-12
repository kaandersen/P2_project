const express = require("express");
const path = require("path");
const fs = require("fs");
const csv = require("csv-parser");
var bodyParser = require("body-parser");

const app = express();

app.use(bodyParser.urlencoded({ extended: false }));

// parse application/json
app.use(bodyParser.json());

app.use("/public", express.static(path.resolve(__dirname, "public")));

app.get("/", (req, res) => {
  res.sendFile(path.resolve(__dirname, "public", "QuestionairePage.html"));
});

app.get("/Homepage", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(path.resolve(__dirname, "public", "index.html"));
});

console.log("HIs3llæ!!");

const csvparser = require("./public/csv.js");
const csvfs = require("./public/csv.js");

app.post("/writetocsv", (req, res) => {
  const data = req.body.questionsArray;
  const fileName = req.body.fileName;
  console.log("V ",fileName);



  const WritingToCsv = require("csv-writer").createObjectCsvWriter;
  const csvObject = WritingToCsv({
    append : true,
    path: `public/${fileName}-Questionaire.csv`,
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
/*app.listen(3000);*/
app.listen(process.env.PORT || 3000, () =>
  console.log("Server running at http://localhost:3000/")
);
