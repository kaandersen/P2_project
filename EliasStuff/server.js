const express = require("express");
const path = require("path");
const fs = require("fs");
const csv = require("csv-parser");
var bodyParser = require("body-parser");
const { TIMEOUT } = require("dns");
results = [];

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

app.get("/Selected", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(path.resolve(__dirname, "public", "SelectedQuestionaire.html"));
});

app.get("/Edit", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(path.resolve(__dirname, "public", "EditQuestionaire.html"));
});

console.log("HIs3llæ!!");

// update csv route

app.post("/updateCsv", async (req, res) => {
  let results = [];

  fs.createReadStream("public/Questionaire.csv")
    .pipe(csv())
    .on("data", (data) => results.push(data))
    .on("end", () => {
      // match questoinaire id and id
      for (let i = 0; i < results.length; i++) {
        if (results[i].questionaireid == req.body.retrievedSelectedBtnID) {
          req.body.questionsArray.map((question) => {
            if (question.id == results[i].id) {
              results[i].question = question.question;
              results[i].checkbox = question.checkbox;
              results[i].answerOption = question.answerOption;
              results[i].questionaireid = req.body.retrievedSelectedBtnID;
            }
          });
        }
        const WritingToCsv = require("csv-writer").createObjectCsvWriter;
        const csvObject = WritingToCsv({
          path: "public/Questionaire.csv",
          header: [
            { id: "questionaireid", title: "questionaireid" },
            { id: "id", title: "id" },
            { id: "question", title: "question" },
            { id: "answerOption", title: "answerOption" },
            { id: "checkbox", title: "checkbox" },
          ],
        });
        csvObject
          .writeRecords(results)
          .then(() => console.log("The CSV file was written successfully"));
      }
    });

  res.send("Updated!");
});

app.post("/writetocsv", (req, res) => {
  let temp_data = [];

  fs.createReadStream("public/Questionaire.csv")
    .on("error", (err) => {
      const data = req.body.questionsArray;
      const WritingToCsv = require("csv-writer").createObjectCsvWriter;
      const csvObject = WritingToCsv({
        path: "public/Questionaire.csv",
        header: [
          { id: "questionaireid", title: "questionaireid" },
          { id: "id", title: "id" },
          { id: "question", title: "question" },
          { id: "answerOption", title: "answerOption" },
          { id: "checkbox", title: "checkbox" },
        ],
      });
      csvObject
        .writeRecords(data)
        .then(() => console.log("The CSV file was written successfully"));

      return;
    })

    .pipe(csv())
    .on("data", (row) => {
      console.log("I am Running");
      temp_data.unshift(row);
    })
    .on("end", () => {
      // temp_data.concat(req.body.questionsArray);
      console.log(temp_data);
      console.log(req.body.questionsArray);
      const final_data = [...temp_data, ...req.body.questionsArray];

      for (let i = 0; i < final_data.length; i++) {
        final_data[i].id = i;
      }
      //console.log(final_data);

      const WritingToCsv = require("csv-writer").createObjectCsvWriter;
      const csvObject = WritingToCsv({
        path: "public/Questionaire.csv",
        header: [
          { id: "questionaireid", title: "questionaireid" },
          { id: "id", title: "id" },
          { id: "question", title: "question" },
          { id: "answerOption", title: "answerOption" },
          { id: "checkbox", title: "checkbox" },
        ],
      });
      csvObject
        .writeRecords(final_data)
        .then(() => console.log("The CSV file was written successfully"));
    });

  res.status(200).json({
    message: "Successfully wrote to csv",
  });
});

//RISK
app.post("/writetostudentcsv", (req, res) => {
  let temp_data = [];

  fs.createReadStream("public/PublicQuestionaire.csv")
    .on("error", (err) => {
      const data = req.body.questionsArray;

      const WritingToCsv = require("csv-writer").createObjectCsvWriter;
      const csvObject = WritingToCsv({
        path: "public/PublicQuestionaire.csv",
        header: [
          { id: "id", title: "id" },
          { id: "question", title: "question" },
          { id: "answer", title: "answer" },
          { id: "answerOption", title: "answerOption" },
          { id: "checkbox", title: "checkbox" },
        ],
      });
      csvObject
        .writeRecords(data)
        .then(() => console.log("The CSV file was written successfully"));

      return;
    })
    .pipe(csv())
    .on("data", (row) => {
      console.log("I am Running");
      temp_data.unshift(row);

    })
    .on("end", () => {
      // temp_data.concat(req.body.questionsArray);
      // console.log(temp_data);
      //  console.log(req.body.questionsArray);
      const final_data = [...temp_data, ...req.body.questionsArray];

      for (let i = 0; i < final_data.length; i++) {
        final_data[i].id = i;
      }
      //console.log(final_data);

      const WritingToCsv = require("csv-writer").createObjectCsvWriter;
      const csvObject = WritingToCsv({
        path: "public/PublicQuestionaire.csv",
        header: [
          { id: "id", title: "id" },
          { id: "question", title: "question" },
          { id: "answer", title: "answer" },
          { id: "answerOption", title: "answerOption" },
          { id: "checkbox", title: "checkbox" },
        ],
      });
      csvObject
        .writeRecords(final_data)
        .then(() => console.log("The CSV file was written successfully"));

    });

  res.status(200).json({
    message: "Successfully wrote to csv",
  });


});

/*app.listen(3000);*/
app.listen(process.env.PORT || 3000, () =>
  console.log("Server running at http://localhost:3000/")
);
