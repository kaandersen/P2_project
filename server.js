// add modules
const express = require("express");
const path = require("path");
const fs = require("fs");
const csv = require("csv-parser");
var bodyParser = require("body-parser");
const { TIMEOUT } = require("dns");
results = [];

const app = express();

// parse application/json from post requests
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());


// directs into the folders of existing folders
app.use(
  "/static",
  express.static(path.resolve(__dirname, "HuginsStuff", "frontend", "static"))
);
app.use(
  "/public",
  express.static(path.resolve(__dirname, "EliasStuff", "public"))
);


// directs into the main page
app.get("/", (req, res) => {
  res.sendFile(
    path.resolve(__dirname, "HuginsStuff", "frontend", "index.html")
  );
});

// directs into the "Admin" folder, which contains the admin related stuff
app.get("/Admin", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "Admin")));
  res.sendFile(path.resolve(__dirname, "Admin", "redirectFrom.html"));
});

app.get("/AdminOverviewpage", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "Admin")));
  res.sendFile(path.resolve(__dirname, "Admin", "overviewPage.html"));
});

app.get("/AdminResults", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "Admin")));
  res.sendFile(path.resolve(__dirname, "Admin", "P2HTML_showOutput.html"));
});

app.get("/AdminNewQuestionaire", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "Admin")));
  res.sendFile(path.resolve(__dirname, "Admin", "new.html"));
});

app.get("/Create", (req, res) => {
  res.sendFile(
    path.resolve(__dirname, "EliasStuff", "public", "CreateQuestionnaire.html")
  );
});

app.get("/Edit", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(
    path.resolve(__dirname, "EliasStuff", "public", "EditQuestionaire.html")
  );
});

app.get("/data.txt", (req, res) => {
  res.sendFile(path.resolve(__dirname, "Admin", "output.txt"));
});



// directs into the "Student" folder, which contains the student related stuff
app.get("/StudentHome", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "Student")));
  res.sendFile(path.resolve(__dirname, "Student", "StudentHomePage.html"));
});

app.get("/StudentQuestionnairesPage", (req, res) => {
  res.sendFile(
    path.resolve(__dirname, "Student", "questionnaireRedirectPage.html")
  );
});

app.get("/StudentQuestionaireForm", (req, res) => {
  app.use(express.static(path.resolve(__dirname, "public")));
  res.sendFile(
    path.resolve(__dirname, "EliasStuff", "public", "StudentQuestionnaireForm.html")
  );
});

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


//Save pre-questionnaire CSV (containing room & student info)
app.post("/writeinfotocsv", (req, res) => {
  
  //Get array from the POST request in P2JS.new
  const data = req.body.finalQuestionaireInfo;

  // opens file as an writeable csv (specifices headers & path based on csvObject)
  const WritingToCsv = require("csv-writer").createObjectCsvWriter;
  const csvObject = WritingToCsv({
    append: true,
    path: `EliasStuff/public/StudentInfoQuestionaire.csv`,
    header: [
      { id: "questionaireTitle", title: "Title" },
      { id: "totalStudents", title: "Amount" },
      { id: "maxRooms", title: "Max" },      
      { id: "amountOfRoomsForPersons", title: "Rooms" },
    ],
  });
  // prints the object
  csvObject
    .writeRecords(data)
    .then(() => console.log("The CSV file was written successfully"));

  res.status(200).json({
    message: "Successfully wrote to csv",
  });
});


//Save main questionaire CSV (containing question boxes)
app.post("/writetocsv", (req, res) => {
  let temp_data = [];

  // opens the file as a readable csv and structures the id 
  fs.createReadStream("EliasStuff/public/Questionaire.csv")
    .pipe(csv())
    .on("data", (row) => {
      console.log("I am Running");
      temp_data.unshift(row);
    })
    .on("end", () => {
      console.log(temp_data);
      console.log(req.body.questionsArray);
      const final_data = [...temp_data, ...req.body.questionsArray];

      for (let i = 0; i < final_data.length; i++) {
        final_data[i].id = i;
      }

      // opens file as an writeable csv (specifices headers & path based on csvObject)
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

      // prints the object
      csvObject
        .writeRecords(final_data)
        .then(() => console.log("The CSV file was written successfully"));
    });

  res.status(200).json({
    message: "Successfully wrote to csv",
  });
});


//Edit CSV
app.post("/updateCsv", async (req, res) => {
  
  //Creates empty array where the data can be pushed into
  let results = [];

  // opens the file as a readable csv
  fs.createReadStream("EliasStuff/public/Questionaire.csv")
    .pipe(csv())
    .on("data", (data) => results.push(data))
    .on("end", () => {
      // match questoinaire id and button id and change csv data
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
        // opens file as writeable csv (specifices headers & path based on csvObject)
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
        // prints the object
        csvObject
          .writeRecords(results)
          .then(() => console.log("The CSV file was written successfully"));
      }
    });

  res.send("Updated!");
});


//Student response CSV
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

//saves questionnaire id and amount of questions of the given questionnaire to a csv file
//Overrides, existing data whenever, executed.
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
