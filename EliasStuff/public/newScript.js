var questionsArray = [];
var roomArray = [];
var counter = 0;
// render question & rooms


function renderRooms() {
  //container
  var roomContainer = document.createElement("div");

  //Wrapper

  //header
  var roomHeader = document.createElement("div");

  //room content
  var roomContainer = document.createElement("div");
  var roomInput = document.createElement("input");


  //Classes & co.
  roomContainer.className = `room-wrapper ${roomArray.length}`;
  roomHeader.className = "room-header";
  roomContent.className = "room-content";
  roomInput.className = "room-input";
  roomInput.placeholder = "Enter number of rooms of x size";
  roomHeader.innerHTML = "rooms of" + roomArray.length + "students";


  //appending to header
  roomContent.appendChild(roomInput);
  roomContainer.appendChild(roomHeader);
  roomContainer.appendChild(roomContent);

  // adding content-wrapper to questions container
  document.getElementById("room-container").appendChild(roomContainer);

}


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


  //overruling
  var overrulingCheckbox = document.createElement("input");
  overrulingCheckbox.type = "checkbox";
  overrulingCheckbox.innerText = "Overruling";
  overrulingCheckbox.innerHTML = "Overruling";
  overrulingCheckbox.name = "overruling";
  overrulingCheckbox.id = "overruling";


  //classes
  questionContainer.className = `question-wrapper ${questionsArray.length}`;
  questionHeader.className = "question-header";
  questionNumber.className = "question-number";
  crossButton.className = "cross-icon-button";
  questionContent.className = "question-content";
  questionInput.className = "question-input";
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
  questionHeading.innerHTML = "Sample Q " + questionsArray.length;
  crossButton.innerHTML = "X";
  scaleOption.innerText = "Scale";
  textInputOption.innerText = "Text Input";
  trueFalseOption.innerText = "True/False";
  answerType.innerText = "-";


  // adding question number, question heading and cross button to question header
  questionHeader.appendChild(questionNumber);
  questionHeader.appendChild(questionHeading);
  questionHeader.appendChild(crossButton);

  // adding question input , option container to question content
  questionContent.appendChild(questionInput);
  questionContent.appendChild(overrulingCheckbox);

  
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
  scaleOption.onclick = () => handleScaleClick(optionContainer, index);
  textInputOption.onclick = () => handleTextInputClick(optionContainer, index);
  trueFalseOption.onclick = () => handleTrueFalseClick(optionContainer, index);

     // delete wrapper (Contains Error)
     function DeleteQuestionWrapper(){
      crossButton.addEventListener("click", function () {
        document.getElementById("questions-container").removeChild(questionContainer);
  
        console.log(questionNumber.innerHTML, "this is number", questionsArray.length - 1);
        questionNumber.innerHTML = questionsArray.length - 1;
      });}
      DeleteQuestionWrapper();
}

// on add button click

function onNewQuestionAdd() {
  questionsArray = [
    ...questionsArray,
    { id: questionsArray.length, question: "", answer: "" },
  ];

  renderQuestion();
  counter = counter + 1;
}

// handle answer type dropdown

function handleDropdownClick(index) {
  var dropdown = document.getElementsByClassName("answer-type-list")[index - 1];
  dropdown.classList.toggle("answer-type-list-show");
}

function handleScaleClick(optionContainer, index) {
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
}

function handleTextInputClick(optionContainer, index) {
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
}

function handleTrueFalseClick(optionContainer, index) {
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
}

// question input on change

function handleQuestionInputChange(event, index) {
  questionsArray[index - 1].question = event.target.value;
}

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


// write question array to csv file

async function createCsvFileFromQuestionArray() {
  const fileName = document.getElementById("fileName-input").value;
  if(fileName){
    questionsArray = questionsArray.map(item => ({...item , student : fileName}));
  }
  const rawResponse = await fetch("/writetocsv", {
    method: "POST",
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ questionsArray, fileName }),
  });
  const content = await rawResponse.json();

  console.log(content);
}
