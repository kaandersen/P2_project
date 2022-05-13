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

app.use(
  "/static",
  express.static(path.resolve(__dirname, "HuginsStuff", "frontend", "static"))
);
app.use(
  "/public",
  express.static(path.resolve(__dirname, "EliasStuff", "public"))
);

app.get("/", (req, res) => {
  res.sendFile(
    path.resolve(__dirname, "HuginsStuff", "frontend", "index.html")
  );
});

//directs into the "Admin" folder, which contains the admin related stuff
app.get("/Admin", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "Admin")));
  res.sendFile(path.resolve(__dirname, "Admin", "redirectFrom.html"));
});

//directs into the "Student" folder, which contains the student related stuff
app.get("/StudentHome", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "Student")));
  res.sendFile(path.resolve(__dirname, "Student", "StudentHomePage.html"));
});

app.get("/Please_work", (req, res) => {
  function activateProgram(){
    const { spawn } = require('node:child_process');
    const bat = spawn('AllocationProgram.exe', ['/c', 'my.bat']);

    bat.stdout.on('data', (data) => {
    console.log(data.toString());
    });

    bat.stderr.on('data', (data) => {
    console.error(data.toString());
    });

    bat.on('exit', (code) => {
    console.log(`Child exited with code ${code}`);
    });
  }
  activateProgram();
})

app.get("/views/StudentID.txt", (req, res) => {
  res.sendFile(
    path.resolve(
      __dirname,
      "HuginsStuff",
      "frontend",
      "static",
      "js",
      "views",
      "StudentID.txt"
    )
  );
});

app.get("/data.txt", (req, res) => {
  res.sendFile(path.resolve(__dirname, "Admin", "output.txt"));
});

app.get("/Create", (req, res) => {
  res.sendFile(
    path.resolve(__dirname, "EliasStuff", "public", "QuestionairePage.html")
  );
});

app.get("/Homepage", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(path.resolve(__dirname, "EliasStuff", "public", "index.html"));
});

app.get("/Selected", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(
    path.resolve(__dirname, "EliasStuff", "public", "SelectedQuestionaire.html")
  );
});

app.get("/Edit", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(
    path.resolve(__dirname, "EliasStuff", "public", "EditQuestionaire.html")
  );
});

//Edit CSV
app.post("/updateCsv", async (req, res) => {
  let results = [];

  fs.createReadStream("EliasStuff/public/Questionaire.csv")
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
          path: "EliasStuff/public/Questionaire.csv",
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

//Save questionaire CSV
app.post("/writetocsv", (req, res) => {
  let temp_data = [];

  fs.createReadStream("EliasStuff/public/Questionaire.csv")
    .on("error", (err) => {
      const data = req.body.questionsArray;
      const WritingToCsv = require("csv-writer").createObjectCsvWriter;
      const csvObject = WritingToCsv({
        path: "EliasStuff/public/Questionaire.csv",
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
        path: "EliasStuff/public/Questionaire.csv",
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

/*
  //Student
  app.post("/writetostudentcsv", (req, res) => {
    let temp_data = [];
  
    fs.createReadStream("EliasStuff/public/PublicQuestionaire.csv")
      .on("error", (err) => {
        const data = req.body.questionsArray;
  
        const WritingToCsv = require("csv-writer").createObjectCsvWriter;
        const csvObject = WritingToCsv({
          path: "EliasStuff/public/PublicQuestionaire.csv",
          header: [
            { id: "id", title: "id" },
            { id: "studentid", title: "studentid" },
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
          path: "EliasStuff/public/PublicQuestionaire.csv",
          header: [
            { id: "id", title: "id" },
            { id: "studentid", title: "studentid" },
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
  
  
  });*/

//Student Info
/*app.post("/writeinfotocsv", (req, res) => {
    let temp_data = [];
  
    fs.createReadStream("EliasStuff/public/StudentInfoQuestionaire.csv")
      .on("error", (err) => {
        const data = req.body.studentInfoArray;
  
        const WritingToCsv = require("csv-writer").createObjectCsvWriter;
        const csvObject = WritingToCsv({
          path: "EliasStuff/public/StudentInfoQuestionaire.csv",
          header: [
            { id: "title", title: "Title" },
            { id: "amount", title: "Amount" },
            { id: "rooms", title: "Rooms" },
            { id: "max", title: "Max" },
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
        const final_data = [...temp_data, ...req.body.studentInfoArray];
  
        for (let i = 0; i < final_data.length; i++) {
          final_data[i].id = i;
        }
  
        const WritingToCsv = require("csv-writer").createObjectCsvWriter;
        const csvObject = WritingToCsv({
          path: "EliasStuff/public/StudentInfoQuestionaire.csv",
          header: [
            { id: "title", title: "Title" },
            { id: "amount", title: "Amount" },
            { id: "rooms", title: "Rooms" },
            { id: "max", title: "Max" },
          ],
        });
        csvObject
          .writeRecords(final_data)
          .then(() => console.log("The CSV file was written successfully"));
  
      });
  
    res.status(200).json({
      message: "Successfully wrote to csv",
    });
  
  
  });*/

//Student info
app.post("/writeinfotocsv", (req, res) => {
  const data = req.body.finalQuestionaireInfo;
  const WritingToCsv = require("csv-writer").createObjectCsvWriter;
  const csvObject = WritingToCsv({
    append: true,
    path: `EliasStuff/public/StudentInfoQuestionaire.csv`,
    header: [
      { id: "questionaireTitle", title: "Title" },
      { id: "totalStudents", title: "Amount" },
      { id: "amountOfRoomsForPersons", title: "Rooms" },
    ],
  });
  csvObject
    .writeRecords(data)
    .then(() => console.log("The CSV file was written successfully"));

  res.status(200).json({
    message: "Successfully wrote to csv",
  });
});

//Student DATA
app.post("/writetostudentcsv", (req, res) => {
  const data = req.body.questionsArray;

  const WritingToCsv = require("csv-writer").createObjectCsvWriter;
  const csvObject = WritingToCsv({
    append: true,
    path: `EliasStuff/public/StudentQuestionaire.csv`,
    header: [
      { id: "questionaireid", title: "questionaireid" },
      { id: "answer", title: "answer" },
    ],
  });
  csvObject
    .writeRecords(data)
    .then(() => console.log("The CSV file was written successfully"));

  res.status(200).json({
    message: "Successfully wrote to csv",
  });
});

//Questionaire DATA
app.post("/writetodatacsv", (req, res) => {
  const data = req.body.calculateDataArray;

  const WritingToCsv = require("csv-writer").createObjectCsvWriter;
  const csvObject = WritingToCsv({
    path: `EliasStuff/public/QuestionaireData.csv`,
    header: [
      { id: "selectedid", title: "selectedid" },
      { id: "titleamount", title: "titleamount" },
    ],
  });
  csvObject
    .writeRecords(data)
    .then(() => console.log("The CSV file was written successfully"));

  res.status(200).json({
    message: "Successfully wrote to csv",
  });
});

app.listen(process.env.PORT || 4000, () =>
  console.log("Server running at http://localhost:4000/")
);
