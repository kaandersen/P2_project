var questionsArray = [];

function returnToHomepage() {
    window.location.href="/Homepage";
}

var retrievedBtnID = localStorage.getItem("btnID");
console.log(retrievedBtnID);

var retrievedSelectedBtnID = localStorage.getItem("SelectedBtnID");
console.log(retrievedBtnID);




async function renderQuestionaireBtn() {

  const response = await fetch("EliasStuff/public/Questionaire.csv");
  const CSVdata = await response.text();
  //console.table(CSVdata);
  const rows = CSVdata.split('\n').slice(1);
  console.log(rows);

  let questionColoumnArr = [];
  let answerColoumnArr = [];
  //let checkboxColoumnArr = [];

  rows.forEach(element => {
    const row = element.split(',');
    const coloumnID = row[0];
    const coloumnQuestion = row[2];
    const coloumnAnswer = row[3];
    //const coloumnCheckbox = row[4];
    //console.log(coloumnID, coloumnQuestion);

    if (coloumnID === retrievedSelectedBtnID) {
      questionColoumnArr.push(coloumnQuestion)
      answerColoumnArr.push(coloumnAnswer);
      //checkboxColoumnArr.push(coloumnCheckbox);

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

/*for (let i = 0; i < checkboxColoumnArr.length; i++) {
             
 checkboxColoumnArr[i];
 //console.log(checkboxColoumnArr[i]);

}*/

    var newInputArr = JSON.parse(window.localStorage.getItem('QuestionContentID'));
    //var exit_loops = false;
    for (var i = 0; i < newInputArr.length; i++) {
       joe = newInputArr[i];
        //console.log(joe);
        /*if (i == eventID){
            break;
        }*/
      }

    for (var i = 0; i < retrievedBtnID; i++) {

        /*if (retrievedBtnID[i] >= 3) {
            console.log("angryy");
        }*/

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
          
          
            // answer type wrapper
            // var answerTypeWrapper = document.createElement("div");
            //var answerType = document.createElement("button");
            //var postionRelativeDiv = document.createElement("div");
            //var answerTypeList = document.createElement("div");
          
            // options
            var scaleOption = document.createElement("button");
            var textInputOption = document.createElement("button");
            var trueFalseOption = document.createElement("button");
          
            scaleOption.value = "SCALE";
            textInputOption.value = "TEXT";
            trueFalseOption.value = "TRUE/FALSE"
          
          
            //overruling
            /*var overrulingCheckbox = document.createElement("input");
            var overrulingLabel = document.createElement("label");
            overrulingLabel.innerText = "Overruling";
            overrulingLabel.id = "overruling"
          
            overrulingCheckbox.type = "checkbox";
            overrulingCheckbox.id = "overruling";
            overrulingCheckbox.value = "overruling";

           if (checkboxColoumnArr[i] === overrulingCheckbox.value) {
              overrulingCheckbox.checked = true;;
            }*/
            
            /*var newInputArr = JSON.parse(window.localStorage.getItem('QuestionContentID'));
            for (let l = 0; l < newInputArr.length; l++) {
                bye = newInputArr[l];
            }*/
          
            //classes
            questionContainer.className = `question-wrapper ${questionsArray.length}`;
            questionHeader.className = "question-header";
            questionNumber.className = "question-number";
            crossButton.className = "cross-icon-button";
            questionContent.className = "question-content";
            questionInput.className = "question-input";
        

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
                questionInput.innerHTML = questionColoumnArr[i];;
            
            
            
            
        
        
        
            
        
            //questionInput.innerHTML = bye;
            optionContainer.className = "option-container";
            questionHeading.className = "question-heading";
            //answerTypeWrapper.className = "answer-type-wrapper";
            //answerType.className = "answer-type";
            //postionRelativeDiv.className = "position-relative";
            //answerTypeList.className = "answer-type-list";
            //scaleOption.className = "option";
            //textInputOption.className = "option";
            //trueFalseOption.className = "option";
          
            questionNumber.innerHTML = questionsArray.length;
            questionHeading.innerHTML = "Sample Q " + questionsArray.length;
            crossButton.innerHTML = "X";
            scaleOption.innerText = "Scale";
            textInputOption.innerText = "Text Input";
            trueFalseOption.innerText = "True/False";
            //answerType.innerText = "-";
          
          
            // adding question number, question heading and cross button to question header
            questionHeader.appendChild(questionNumber);
            questionHeader.appendChild(questionHeading);
            questionHeader.appendChild(crossButton);
            questionContent.appendChild(questionInput);
          
          
            
          
            // adding question input , option container to question content
           /* for (let i = 0; i < questionsArray; i++) {
              questionContent.appendChild(overrulingLabel);
              console.log("goodnight " + [i]);
            }*/
            /*questionContent.appendChild(overrulingCheckbox);
            questionContent.appendChild(overrulingLabel);*/
            
            questionContent.appendChild(optionContainer);
            //questionContent.appendChild(answerTypeWrapper);
          
            // adding question content to question container
            questionContainer.appendChild(questionHeader);
            questionContainer.appendChild(questionContent);
          
            // adding answer type type to answer type wrapper
          
            // answerTypeWrapper.appendChild(answerType);
            // answerTypeWrapper.appendChild(postionRelativeDiv);
            // postionRelativeDiv.appendChild(answerTypeList);
            // answerTypeList.appendChild(scaleOption);
            // answerTypeList.appendChild(textInputOption);
            // answerTypeList.appendChild(trueFalseOption);
          
            // adding question wrapper to questions container
          
            document.getElementById("questions-container").appendChild(questionContainer);
          
            let index = parseInt(questionContainer.classList[1]);
          
            //   handlers
          
            questionInput.onchange = (event) => handleQuestionInputChange(event, index);
            //answerType.onclick = () => handleDropdownClick(index);

            if (answerColoumnArr[i] === scaleOption.value) {
              handleScaleClick(optionContainer, index);
            }
            
            
            if (answerColoumnArr[i] === textInputOption.value) {
              handleTextInputClick(optionContainer, index);
            }

            if (answerColoumnArr[i] === trueFalseOption.value) {
              handleTrueFalseClick(optionContainer, index);
            }

            //overrulingCheckbox.onclick = (event) => handleCheckboxClick(event, index);
          
          
               // delete wrapper (Contains Error)
               function DeleteQuestionWrapper(){
                crossButton.addEventListener("click", function () {
                  document.getElementById("questions-container").removeChild(questionContainer);
          
                  //questionsArray[index - 1].checkbox = null;
                  questionsArray[index - 1].question = null;
                  questionsArray[index - 1].answerOption = null;
                  questionsArray[index - 1].answer = null;
          
            
                  /*console.log(questionNumber.innerHTML, "this is number", questionsArray.length - 1);
                  questionNumber.innerHTML = questionsArray.length - 1;*/
                });}
                DeleteQuestionWrapper();
          
          }
          renderQuestion();
          
    }
}
renderQuestionaireBtn();

/*function handleDropdownClick(index) {
    var dropdown = document.getElementsByClassName("answer-type-list")[index - 1];
    dropdown.classList.toggle("answer-type-list-show");
  }*/
  
  function handleScaleClick(optionContainer, index) {
    //document.getElementsByClassName("answer-type")[index - 1].innerText = "Scale";
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
  
  
    //questionsArray[index - 1].answerOption = event.target.value;
    
  
  }
  
  function handleTextInputClick(optionContainer, index) {
    //document.getElementsByClassName("answer-type")[index - 1].innerText =
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
  
    //questionsArray[index - 1].answerOption = event.target.value;
  }
  
  //overruling
  /*function handleCheckboxClick(event, index) {
    
      questionsArray[index - 1].checkbox = event.target.value;
    
  }*/
  
  function handleTrueFalseClick(optionContainer, index) {
    //document.getElementsByClassName("answer-type")[index - 1].innerText =
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
  
   // questionsArray[index - 1].answerOption = event.target.value;
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
    //var answerType = document.getElementsByClassName("answer-type")[index - 1];
    //answerType.innerText = "Scale";
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

  
     window.location.href = "/Homepage";
     
  }
