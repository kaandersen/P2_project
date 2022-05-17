var questionsArray = [];
var questionaireArray = [];
var roomArray = [];
var counter = 0;
var _IDIndex = 1;
var globalVar;
var IDvariable = 0;



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
  trueFalseOption.value = "YES/NO"


  //overruling
  var overrulingCheckbox = document.createElement("input");
  var overrulingLabel = document.createElement("label");
  overrulingLabel.innerText = "Overruling";
  overrulingLabel.id = "overruling"

  overrulingCheckbox.type = "checkbox";
  overrulingCheckbox.id = "overruling";
  overrulingCheckbox.value = "overruling";


  //classes
  questionContainer.className = `question-wrapper ${questionsArray.length}`;
  questionHeader.className = "question-header";
  questionNumber.className = "question-number";
  crossButton.className = "cross-icon-button";
  questionContent.className = "question-content";
  questionInput.className = "question-input";
  questionInput.name = "question-input-name";
  questionInput.setAttribute("id","input-"+ _IDIndex++);
  //questionInput.id = "question-input-id";
  questionInput.placeholder = "question content...";
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
  questionHeading.innerHTML = "Question " + questionsArray.length;
  crossButton.innerHTML = "X";
  scaleOption.innerText = "Scale";
  textInputOption.innerText = "Text Input";
  trueFalseOption.innerText = "True/False";
  answerType.innerText = "-";


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

  document.getElementById("questions-container").appendChild(questionContainer);

  let index = parseInt(questionContainer.classList[1]);

  //   handlers

  questionInput.onchange = (event) => handleQuestionInputChange(event, index);
  answerType.onclick = () => handleDropdownClick(index);
  scaleOption.onclick = (event) => handleScaleClick(event, optionContainer, index);
  textInputOption.onclick = (event) => handleTextInputClick(event, optionContainer, index);
  trueFalseOption.onclick = (event) => handleTrueFalseClick(event, optionContainer, index);
  overrulingCheckbox.onclick = (event) => handleCheckboxClick(event, index);


     // delete wrapper (Contains Error)
     function DeleteQuestionWrapper(){
      crossButton.addEventListener("click", function () {
        document.getElementById("questions-container").removeChild(questionContainer);

        questionsArray[index - 1].checkbox = null;
        questionsArray[index - 1].question = null;
        questionsArray[index - 1].answerOption = null;
        questionsArray[index - 1].answer = null;

  
        /*console.log(questionNumber.innerHTML, "this is number", questionsArray.length - 1);
        questionNumber.innerHTML = questionsArray.length - 1;*/
      });}
      DeleteQuestionWrapper();

  random = questionInput.id
  console.log(random);
}


// on add button click

function onNewQuestionAdd() {
  //var randomNumber = Math.floor((Math.random() * 100) + 1);
  questionsArray = [
    ...questionsArray,
    {id: questionsArray.length, question: "", answerOption: "", answer: "", checkbox: ""},
  ];

  //console.log(globalVar);
  renderQuestion();
  counter = counter + 1;
  
}

// handle answer type dropdown

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
  
    questionsArray[index - 1].checkbox = event.target.value;
  
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

  questionsArray[index - 1].answerOption = event.target.value;
}

// question input on change

function handleQuestionInputChange(event, index) {
  questionsArray[index - 1].question = event.target.value;
  //questionsArray[index - 1].questionaireid = 3;
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


function storeQuestionaireInLocalStorage () {
  
  var questionBoxAmount = questionsArray.length;
  
  if (localStorage.getItem('WrapperID') == null) {
    localStorage.setItem('WrapperID', '[]');
  }

  var old_WrapperID_Data = JSON.parse(localStorage.getItem('WrapperID'));
  old_WrapperID_Data.push(questionBoxAmount);
  localStorage.setItem('WrapperID', JSON.stringify(old_WrapperID_Data));



  if (localStorage.getItem('QuestionContentID') == null) {
    localStorage.setItem('QuestionContentID', '[]');
  }

  var old_QuestionContentID = JSON.parse(localStorage.getItem('QuestionContentID'));
  inputValues = document.getElementsByClassName('question-input');
  for (let i = 0; i < inputValues.length; i++) {
    printValues = inputValues[i].value
    old_QuestionContentID.push(printValues);
  }

  localStorage.setItem('QuestionContentID', JSON.stringify(old_QuestionContentID));

}


/*
function viewLocalStorage(){
  if (localStorage.getItem('WrapperID') == null) {
    document.getElementById('output').innerHTML =  JSON.parse(localStorage.getItem('WrapperID'))
  }
  console.log("ok");
}*/




/*function storeInArray(){
  var saveBtn = document.getElementById("SaveButton");

  for (var k = 0; k < saveBtn.length; k++) {
    var div = document.body.appendChild(document.createElement('div'));
    questionaireArray.push(div);  
  }
  console.log(questionaireArray);

  /*questionsArray = [
    ...questionsArray,
    { id: questionsArray.length, question: "", answerOption: "", answer: "", checkbox: ""},
  ];
  
  for (let i = 0; i < questionsArray.length; i++) {
    //const element = array[index];
    console.log("Hello " + [i]);


    renderQuestion();
  }
}*/
//post questionaire to new page
// function storeQuestionaireID(){
//   localStorage.questionaireID = 1;
// }


// write question array to csv file
//document.getElementById("fileName-input").value;
async function createCsvFileFromQuestionArray() {
//   console.log(window.section_id);
//   if(window.section_id===undefined){
//   let element_save =  document.getElementById("SaveButton");  
//   let sectionID=element_save.getAttribute("data-section");
//   window.section_ID=sectionID ;
//   element_save.setAttribute("data-section", parseInt( sectionID)+1);  
//     window.section_id=parseInt (element_save.getAttribute("data-section")); 
//   if(sectionID){
//     questionsArray = questionsArray.map(item => ({...item , questionaireid : sectionID}));
//   }
// }
// else{
    
//   questionsArray = questionsArray.map(item => ({...item , questionaireid :window.section_id }));
//       window.section_id=window.section_id+1
// }
     
var sectionID = localStorage.getItem("questionaireID");
if(sectionID===undefined ||sectionID===null ){

  localStorage.setItem("questionaireID", 1);
  sectionID=1;
}
//  localStorage.setItem("questionaireID", sectionID);
  console.log(sectionID);

  if(sectionID){
    questionsArray = questionsArray.map(item => ({...item , questionaireid : sectionID}));
  }
  localStorage.setItem("questionaireID", ++sectionID);

/*
var questionaireid = 5;
window.globalVar = questionaireid;*/

/*var questionaireid = 5;
console.log(questionaireid);*/

//questionsArray = questionsArray.map(item => ({...item , questionaireid : sectionID}));







  const rawResponse = await fetch("/writetocsv", {

    method: "POST",
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
    body: JSON.stringify({questionsArray}),
  });
  const content = await rawResponse.json();

  console.log(content);
  
  arrayLength = questionsArray.length;
  

  window.location.href = "/Admin";
  document.getElementById("SaveButton").disabled = true;

 /*
   IDvariable +=1;
   //console.log(IDvariable);
   localStorage.questionaireID = IDvariable;
   var retrievedID = localStorage.getItem("questionaireID");
   console.log(retrievedID);
   retrievedID++;
   localStorage.questionaireID = retrievedID;
   console.log(retrievedID);  
*/
  
  //storeInArray();
  storeQuestionaireInLocalStorage();

  
}


//async function testBtn() {
  /*IDvariable +=1
  console.log(IDvariable)*/


  /*const rawResponse = await fetch("/writetocsv", {

    method: "DELETE",
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
    body: null
  });
  const content = await rawResponse.json();

  console.log(content);*/
  
  
 /* console.log("This is a test button");

  const inputClass = document.getElementsByClassName('question-input');
  const arr = [...inputClass].map(input => input.value);
  
  console.log(arr);

  
  inputValues = document.getElementsByClassName('question-input');

  for (let i = 0; i < inputValues.length; i++) {
    printValues = inputValues[i].value
    console.log(printValues)
    
  }*/


 



//}


