var questionsArray = [];

function returnToHomepage() {
    window.location.href="/StudentHome";
}

var retrievedBtnID = localStorage.getItem("btnID");
console.log(retrievedBtnID);

var retrievedSelectedBtnID = localStorage.getItem("SelectedBtnID");
console.log(retrievedBtnID);




async function renderQuestionaireBtn() {

  const response = await fetch("/public/Questionaire.csv");
  const CSVdata = await response.text();
  const rows = CSVdata.split('\n').slice(1);
  console.log(rows);

  let questionColoumnArr = [];
  let answerColoumnArr = [];

  rows.forEach(element => {
    const row = element.split(',');
    const coloumnID = row[0];
    const coloumnQuestion = row[2];
    const coloumnAnswer = row[3];

    if (coloumnID === retrievedSelectedBtnID) {
      questionColoumnArr.push(coloumnQuestion)
      answerColoumnArr.push(coloumnAnswer);
    }
  });

for (let i = 0; i < questionColoumnArr.length; i++) {
  questionColoumnArr[i];
}

for (let i = 0; i < answerColoumnArr.length; i++) {
  answerColoumnArr[i];
}

    var newInputArr = JSON.parse(window.localStorage.getItem('QuestionContentID'));

    for (var i = 0; i < newInputArr.length; i++) {
       joe = newInputArr[i];
    }

    for (var i = 0; i < retrievedBtnID; i++) {

        questionsArray = [
            ...questionsArray,
            { id: questionsArray.length, question: "", answerOption: "", answer: "", checkbox: ""},
          ];
        
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
            var questionInput = document.createElement("div");
          
            // options
            var scaleOption = document.createElement("button");
            var textInputOption = document.createElement("button");
            var trueFalseOption = document.createElement("button");
          
            scaleOption.value = "SCALE";
            textInputOption.value = "TEXT";
            trueFalseOption.value = "YES/NO"
          
          
            //classes
            questionContainer.className = `question-wrapper ${questionsArray.length}`;
            questionHeader.className = "question-header";
            questionNumber.className = "question-number";
            crossButton.className = "cross-icon-button";
            questionContent.className = "question-content";
            questionInput.className = "question-input";

            //TASK 2.
            questionInput.innerHTML = questionColoumnArr[i];;
            
            optionContainer.className = "option-container";
            questionHeading.className = "question-heading";
          
            questionNumber.innerHTML = questionsArray.length;
            questionHeading.innerHTML = "Question " + questionsArray.length;
            crossButton.innerHTML = "X";
            scaleOption.innerText = "Scale";
            textInputOption.innerText = "Text Input";
            trueFalseOption.innerText = "True/False";
          
            // adding question number, question heading and cross button to question header
            questionHeader.appendChild(questionNumber);
            questionHeader.appendChild(questionHeading);
            questionHeader.appendChild(crossButton);
            questionContent.appendChild(questionInput);
          
            questionContent.appendChild(optionContainer);
          
            // adding question content to question container
            questionContainer.appendChild(questionHeader);
            questionContainer.appendChild(questionContent);
          
            // adding question wrapper to questions container
          
            document.getElementById("questions-container").appendChild(questionContainer);
          
            let index = parseInt(questionContainer.classList[1]);
          
            //   handlers
          
            questionInput.onchange = (event) => handleQuestionInputChange(event, index);

            if (answerColoumnArr[i] === scaleOption.value) {
              handleScaleClick(optionContainer, index);
            }
            
            
            if (answerColoumnArr[i] === textInputOption.value) {
              handleTextInputClick(optionContainer, index);
            }

            if (answerColoumnArr[i] === trueFalseOption.value) {
              handleTrueFalseClick(optionContainer, index);
            }
          
          
               // delete wrapper (Contains Error)
               function DeleteQuestionWrapper(){
                crossButton.addEventListener("click", function () {
                  document.getElementById("questions-container").removeChild(questionContainer);
          
                  //questionsArray[index - 1].checkbox = null;
                  questionsArray[index - 1].question = null;
                  questionsArray[index - 1].answerOption = null;
                  questionsArray[index - 1].answer = null;
                });}
                DeleteQuestionWrapper();
          
          }
          renderQuestion();
          
    }
}
renderQuestionaireBtn();


  function handleScaleClick(optionContainer, index) {
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
  }
  
  function handleTextInputClick(optionContainer, index) {
    //  "Text Input";
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
  }
  
  function handleTrueFalseClick(optionContainer, index) {
    //  "True/False";
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
  
    trueButton.value = "True";
    falseButton.value = "False";
  
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
  }
  
  // question input on change
  
  function handleQuestionInputChange(event, index) {
    
    questionsArray[index - 1].question = event.target.value;
  }
  
  // handle scale option select
  
  function handleScaleOptionSelect(value, index) {
    questionsArray[index - 1].answer = value;
  }
  
  // handle text input change
  
  function handleTextInputChange(event, index) {
    questionsArray[index - 1].answer = event.target.value;
  }
  
  // handle true false option select
  
  function handleTrueFalseOptionSelect(value, index) {
    questionsArray[index - 1].answer = value;
  }
  

  async function UploadToCsv() {

    var studentBtnID = localStorage.getItem("SelectedBtnID");
    if (studentBtnID) {
        questionsArray = questionsArray.map(item => ({...item , questionaireid : studentBtnID}));
    }

    const rawResponse = await fetch("/writetostudentcsv", {
      method: "POST",
      headers: {
        Accept: "application/json",
        "Content-Type": "application/json",
      },
      body: JSON.stringify({questionsArray}),
    });
    const content = await rawResponse.json();
  
    console.log(content);

  
     window.location.href = "/StudentHome";
     
  }
