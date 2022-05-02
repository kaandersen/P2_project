questionsArray = [];

var retrievedBtnID = localStorage.getItem("btnID");
console.log(retrievedBtnID);

var retrievedSelectedBtnID = localStorage.getItem("SelectedBtnID");
console.log(retrievedBtnID);

/*getCsvData();

async function getCsvData() {
const response = await fetch("/public/Questionaire.csv");
const CSVdata = await response.text();
console.table(CSVdata);

const rows = CSVdata.split('\n').slice(1);
console.log(rows);
rows.forEach(element => { 
    const row = element.split(',');
    const coloumnID = row[0];
    //const coloumnQuestion = row[2];
    //console.log(coloumnID, coloumnQuestion);
    
    if (coloumnID === retrievedEditBtnID) {
        console.log(row[2]);
    }
    else {
      console.log("coloumnID does not match retrievedBtnID?")
    }
});

//return coloumnQuestion;

}*/

async function editQuestionaire() {
  //var coloumnNewQuestionID = await getCsvData();
  //console.log(coloumnNewQuestionID);

  const response = await fetch("/public/Questionaire.csv");
  const CSVdata = await response.text();
  //console.table(CSVdata);
  const rows = CSVdata.split("\n").slice(1);
  console.log(rows);

  let questionColoumnArr = [];
  let answerColoumnArr = [];
  let coloumnQuestionIdArr = [];
  let checkboxColoumnArr = [];

  rows.forEach((element) => {
    const row = element.split(",");
    const coloumnID = row[0];
    const coloumnQuestionId = row[1];
    const coloumnQuestion = row[2];
    const coloumnAnswer = row[3];
    const coloumnCheckbox = row[4];
    //console.log(coloumnID, coloumnQuestion);

    if (coloumnID === retrievedSelectedBtnID) {
      questionColoumnArr.push(coloumnQuestion);
      coloumnQuestionIdArr.push(coloumnQuestionId);
      answerColoumnArr.push(coloumnAnswer);
      checkboxColoumnArr.push(coloumnCheckbox);
    }
  });

  //console.log(questionColoumnArr);
  //console.log(answerColoumnArr);
  //console.log(checkboxColoumnArr);

  /*for (let i = 0; i < globalVar.length; i++) {
    const elementsInList = globalVar[i];
    console.log(elementsInList);
    
  }*/

  // console.log(globalVar);

  for (let i = 0; i < questionColoumnArr.length; i++) {
    questionColoumnArr[i];
  }

  for (let i = 0; i < answerColoumnArr.length; i++) {
    answerColoumnArr[i];
  }

  for (let i = 0; i < checkboxColoumnArr.length; i++) {
    checkboxColoumnArr[i];
    //console.log(checkboxColoumnArr[i]);
  }

  var newInputArr = JSON.parse(
    window.localStorage.getItem("QuestionContentID")
  );
  //var exit_loops = false;
  for (var i = 0; i < newInputArr.length; i++) {
    joe = newInputArr[i];
    //console.log(joe);
    /*if (i == eventID){
        break;
    }*/
  }

  /*for (let k = 0; k < coloumnQuestion.length; k++) {
    inputID = coloumnQuestion[i];
    console.log(inputID)
    
  }*/

  for (var i = 0; i < retrievedBtnID; i++) {
    /*if (retrievedBtnID[i] >= 3) {
        console.log("angryy");
    }*/

    questionsArray = [
      ...questionsArray,
      {
        id: coloumnQuestionIdArr[i],
        question: questionColoumnArr[i],
        answerOption: answerColoumnArr[i],
        answer: "",
        checkbox: checkboxColoumnArr[i],
      },
    ];

    console.log("questionsArray", questionsArray);

    function renderQuestion() {
      // container
      var questionContainer = document.createElement("div");

      // header
      var questionHeader = document.createElement("div");
      var questionNumber = document.createElement("div");
      var questionHeading = document.createElement("div");
      var crossButton = document.createElement("button");
      var optionContainer = document.createElement("div");

      // question content
      var questionContent = document.createElement("div");
      var questionInput = document.createElement("input");

      // answer type wrapper
      var answerTypeWrapper = document.createElement("div");
      var answerType = document.createElement("button");
      var postionRelativeDiv = document.createElement("div");
      var answerTypeList = document.createElement("div");

      // options
      var scaleOption = document.createElement("button");
      var textInputOption = document.createElement("button");
      var trueFalseOption = document.createElement("button");

      scaleOption.value = "SCALE";
      textInputOption.value = "TEXT";
      trueFalseOption.value = "TRUE/FALSE";

      //overruling
      var overrulingCheckbox = document.createElement("input");
      var overrulingLabel = document.createElement("label");
      overrulingLabel.innerText = "Overruling";
      overrulingLabel.id = "overruling";
      overrulingCheckbox.type = "checkbox";
      overrulingCheckbox.id = "overruling";
      overrulingCheckbox.value = "overruling";

      if (checkboxColoumnArr[i] === overrulingCheckbox.value) {
        overrulingCheckbox.checked = true;
      }

      //classes
      questionContainer.className = `question-wrapper ${questionsArray.length}`;
      questionHeader.className = "question-header";
      questionNumber.className = "question-number";
      crossButton.className = "cross-icon-button";
      questionContent.className = "question-content";
      questionInput.className = "question-input";
      questionInput.placeholder = questionColoumnArr[i];

      /*if (newInputArr[i] === event.target.id) {
          questionInput.innerHTML = "hello " + newInputArr[i];
      }
      else {
          console.log("something went wrong");
          console.log(newInputArr.length);
      }*/

      /*if (newInputArr[i] >= event.target.id[i]) {
          console.log("This will be a good day");
      }*/

      //TASK 2.
      // questionInput.innerHTML = newInputArr[i];

      //questionInput.innerHTML = bye;
      optionContainer.className = "option-container";
      questionHeading.className = "question-heading";
      answerTypeWrapper.className = "answer-type-wrapper";
      answerType.className = "answer-type";
      postionRelativeDiv.className = "position-relative";
      answerTypeList.className = "answer-type-list";
      scaleOption.className = "option";
      textInputOption.className = "option";
      trueFalseOption.className = "option";

      questionNumber.innerHTML = questionsArray.length;
      questionHeading.innerHTML = "Sample Q " + questionsArray.length;
      crossButton.innerHTML = "X";
      scaleOption.innerText = "Scale";
      textInputOption.innerText = "Text Input";
      trueFalseOption.innerText = "True/False";
      answerType.innerText = answerColoumnArr[i];

      // adding question number, question heading and cross button to question header
      questionHeader.appendChild(questionNumber);
      questionHeader.appendChild(questionHeading);
      questionHeader.appendChild(crossButton);
      questionContent.appendChild(questionInput);

      // adding question input , option container to question content
      for (let i = 0; i < questionsArray; i++) {
        questionContent.appendChild(overrulingLabel);
        console.log("goodnight " + [i]);
      }
      questionContent.appendChild(overrulingCheckbox);
      questionContent.appendChild(overrulingLabel);

      questionContent.appendChild(optionContainer);
      questionContent.appendChild(answerTypeWrapper);

      // adding question content to question container
      questionContainer.appendChild(questionHeader);
      questionContainer.appendChild(questionContent);

      // adding answer type type to answer type wrapper

      answerTypeWrapper.appendChild(answerType);
      answerTypeWrapper.appendChild(postionRelativeDiv);
      postionRelativeDiv.appendChild(answerTypeList);
      answerTypeList.appendChild(scaleOption);
      answerTypeList.appendChild(textInputOption);
      answerTypeList.appendChild(trueFalseOption);

      // adding question wrapper to questions container

      document
        .getElementById("questions-container")
        .appendChild(questionContainer);

      let index = parseInt(questionContainer.classList[1]);

      //   handlers

      questionInput.onchange = (event) =>
        handleQuestionInputChange(event, index);
      answerType.onclick = () => handleDropdownClick(index);
      scaleOption.onclick = (event) =>
        handleScaleClick(event, optionContainer, index);
      textInputOption.onclick = (event) =>
        handleTextInputClick(event, optionContainer, index);
      trueFalseOption.onclick = (event) =>
        handleTrueFalseClick(event, optionContainer, index);
      overrulingCheckbox.onclick = (event) => handleCheckboxClick(event, index);

      // delete wrapper (Contains Error)
      function DeleteQuestionWrapper() {
        crossButton.addEventListener("click", function () {
          document
            .getElementById("questions-container")
            .removeChild(questionContainer);

          questionsArray[index - 1].checkbox = null;
          questionsArray[index - 1].question = null;
          questionsArray[index - 1].answerOption = null;
          questionsArray[index - 1].answer = null;

          /*console.log(questionNumber.innerHTML, "this is number", questionsArray.length - 1);
          questionNumber.innerHTML = questionsArray.length - 1;*/
        });
      }
      DeleteQuestionWrapper();
    }
    renderQuestion();
  }
}

function handleDropdownClick(index) {
  var dropdown = document.getElementsByClassName("answer-type-list")[index - 1];
  dropdown.classList.toggle("answer-type-list-show");
}

function handleScaleClick(event, optionContainer, index) {
  document.getElementsByClassName("answer-type")[index - 1].innerText = "Scale";
  var scaleOptionsWrapper = document.createElement("div");
  var agreeText = document.createElement("p");
  var disagreeText = document.createElement("p");

  agreeText.innerText = "Agree";
  disagreeText.innerText = "Disagree";

  scaleOptionsWrapper.className = "scale-options-wrapper";

  // creating scale radio buttons

  var scale1 = document.createElement("input");
  var scale2 = document.createElement("input");
  var scale3 = document.createElement("input");
  var scale4 = document.createElement("input");
  var scale5 = document.createElement("input");

  scale1.name = "scale" + index;
  scale2.name = "scale" + index;
  scale3.name = "scale" + index;
  scale4.name = "scale" + index;
  scale5.name = "scale" + index;

  scale1.type = "radio";
  scale2.type = "radio";
  scale3.type = "radio";
  scale4.type = "radio";
  scale5.type = "radio";

  scale1.value = "1";
  scale2.value = "2";
  scale3.value = "3";
  scale4.value = "4";
  scale5.value = "5";

  scale1.onclick = () => handleScaleOptionSelect(scale1.value, index);
  scale2.onclick = () => handleScaleOptionSelect(scale2.value, index);
  scale3.onclick = () => handleScaleOptionSelect(scale3.value, index);
  scale4.onclick = () => handleScaleOptionSelect(scale4.value, index);
  scale5.onclick = () => handleScaleOptionSelect(scale5.value, index);

  // adding scale radio buttons to scale options wrapper

  scaleOptionsWrapper.appendChild(agreeText);
  scaleOptionsWrapper.appendChild(scale1);
  scaleOptionsWrapper.appendChild(scale2);
  scaleOptionsWrapper.appendChild(scale3);
  scaleOptionsWrapper.appendChild(scale4);
  scaleOptionsWrapper.appendChild(scale5);
  scaleOptionsWrapper.appendChild(disagreeText);

  optionContainer.innerHTML = "";
  optionContainer.appendChild(scaleOptionsWrapper);

  console.log("Bad day?");

  questionsArray[index - 1].answerOption = event.target.value;
}

function handleTextInputClick(event, optionContainer, index) {
  document.getElementsByClassName("answer-type")[index - 1].innerText =
    "Text Input";
  var yourAnswerWrapper = document.createElement("div");
  var textInput = document.createElement("input");

  yourAnswerWrapper.className = "your-anwser-option";

  textInput.type = "text";
  textInput.placeholder = "text input";

  yourAnswerWrapper.className = "text-input-wrapper";
  yourAnswerWrapper.appendChild(textInput);

  optionContainer.innerHTML = "";
  optionContainer.appendChild(yourAnswerWrapper);

  textInput.onchange = (event) => handleTextInputChange(event, index);

  questionsArray[index - 1].answerOption = event.target.value;
}

//overruling
function handleCheckboxClick(event, index) {
  questionsArray[index - 1].checkbox = event.target.checked
    ? event.target.value
    : "";
}

function handleTrueFalseClick(event, optionContainer, index) {
  document.getElementsByClassName("answer-type")[index - 1].innerText =
    "True/False";
  var trueFalseOptionsWrapper = document.createElement("div");
  var trueText = document.createElement("p");
  var falseText = document.createElement("p");

  trueText.innerText = "Yes";
  falseText.innerText = "No";

  trueFalseOptionsWrapper.className = "yes-no-wrapper";

  // creating true false radio buttons

  var trueButton = document.createElement("input");
  var falseButton = document.createElement("input");

  trueButton.type = "radio";
  falseButton.type = "radio";

  trueButton.value = "true";
  falseButton.value = "false";

  trueButton.name = "true-false" + index;
  falseButton.name = "true-false" + index;

  trueButton.onclick = () =>
    handleTrueFalseOptionSelect(trueButton.value, index);
  falseButton.onclick = () =>
    handleTrueFalseOptionSelect(falseButton.value, index);

  // adding true false radio buttons to true false options wrapper

  trueFalseOptionsWrapper.appendChild(trueText);
  trueFalseOptionsWrapper.appendChild(trueButton);
  trueFalseOptionsWrapper.appendChild(falseText);
  trueFalseOptionsWrapper.appendChild(falseButton);

  optionContainer.innerHTML = "";
  optionContainer.appendChild(trueFalseOptionsWrapper);

  questionsArray[index - 1].answerOption = event.target.value;
}

// question input on change

function handleQuestionInputChange(event, index) {
  questionsArray[index - 1].question = event.target.value;
}
/*
function handleStudentInputChange(event, index) {
  questionsArray[index - 1].studentamount = event.target.value;
}*/

// handle scale option select

function handleScaleOptionSelect(value, index) {
  questionsArray[index - 1].answer = value;
  var answerType = document.getElementsByClassName("answer-type")[index - 1];
  answerType.innerText = "Scale";
}

// handle text input change

function handleTextInputChange(event, index) {
  questionsArray[index - 1].answer = event.target.value;
}

// handle true false option select

function handleTrueFalseOptionSelect(value, index) {
  questionsArray[index - 1].answer = value;
}

function CancelChanges() {
  window.location.href = "/Homepage";
}

async function UploadChangesToCsv() {
  console.log("questionsArray", questionsArray);
  /*var sectionID = localStorage.getItem("SelectedBtnID");

  console.log(sectionID);

  if (sectionID) {
    questionsArray = questionsArray.map(item => ({ ...item, questionaireid: sectionID }));
  }*/
  /*
  const rawResponse = await fetch("/writetocsv", {

    method: "PUT",
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ questionsArray }),
    append: true,
  });
  const content = await rawResponse.json();

  console.log(content);*/
  /* let resultElement = document.getElementById("putResult");
   resultElement.innerHTML = "";
   const id = 3;
   const title = 4;
   const description = 5;
   const published = 3;
   const putData = {
     title: title,
     description: description,
     published: published,
   };
   try {
     const res = await fetch("/public/Questionaire.csv", {
       method: "put",
       headers: {
         "Content-Type": "application/json",
         "x-access-token": "token-value",
       },
       body: JSON.stringify(putData),
     });
     if (!res.ok) {
       const message = `An error has occured: ${res.status} - ${res.statusText}`;
       throw new Error(message);
     }
     const data = await res.json();
     const result = {
       status: res.status + "-" + res.statusText,
       headers: { "Content-Type": res.headers.get("Content-Type") },
       data: data,
     };
     console.log(result)
   } catch (err) {
     connsole.log(htmlizeResponse(err.message));
   }*/
  /*const rawResponse = await fetch("/writetostudentcsv", {
        method: "POST",
        headers: {
          Accept: "application/json",
          "Content-Type": "application/json",
        },
        body: JSON.stringify({questionsArray}),
      });
      const content = await rawResponse.json();
    
      console.log(content);
      

       window.location.href = "/Homepage";*/

  // send updated questions to server

  const rawResponse = await fetch("/updateCsv", {
    method: "POST",
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ questionsArray, retrievedSelectedBtnID }),
  });
  // reload
  window.location.reload();
  window.location.href = "/Homepage";
}

editQuestionaire();


/*import DATA from './Questionaire.csv';
const DATA_ARRAY = [];



async function getData() {
const response = await fetch("/public/Questionaire.csv");
const response = await fetch(DATA, {
  headers : { 
    'content-type': 'text/csv;charset=UTF-8'
   }
  })
  .catch(function() {
    console.log("error");
}); 


const data = await response.text();
// console.log(data);

const rows = data.split((/\r?\n|\r/)).slice(1);
// console.log(rows[1]);
rows.forEach(elt => {
        const colums = elt.split(';');
        const titre = colums[0];
        // console.log(titre);
        DATA_ARRAY.push(titre);
})

console.log(DATA_ARRAY);
  }



getData();
*/
