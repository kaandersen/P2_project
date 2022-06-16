roomInputFieldCounter = 1;
var questionaireInfo = {
  questionaireTitle: "",
  totalStudents: 0,
  maxRooms: "",
  amountOfRoomsForPersons: [],
};


// add on change event listener to the input field with id questName
var questionaireTitle = document.getElementById("questionaireTitle");
questionaireTitle.addEventListener("change", function () {
  questionaireInfo.questionaireTitle = questionaireTitle.value;
});

// add on change event listener to the input field with id totalStudents

var totalStudents = document.getElementById("totalStudents");
totalStudents.addEventListener("change", function () {
  questionaireInfo.totalStudents = totalStudents.value;
});

// attach on change listener to the input with id

var createNewRoomSizeFirstInput = document.getElementById("#0rooms");

createNewRoomSizeFirstInput.addEventListener("change", (event) => {
  handleInputChange(event, 0);
});

// attach on click event listener to the button with id addNewRoomInputField

var addNewRoomInputField = document.getElementById("createNewSize");
addNewRoomInputField.addEventListener("click", function () {
  roomInputFieldCounterString = roomInputFieldCounter + 1;
  roomInputFieldCounterString = roomInputFieldCounterString.toString(10);

  let input = document.createElement("input");
  input.type = "number";
  input.id = "#" + roomInputFieldCounter + "rooms";
  input.value = "0";
  input.className = "roomData"; //adds classs name for css use
  let label = document.createElement("label");
  label.setAttribute = ("for", roomInputFieldCounterString);
  label.id = roomInputFieldCounterString;
  label.innerHTML =
    "Amount of " + roomInputFieldCounterString + " person rooms: ";
  let linebreak = document.createElement("br");
  let form = document.getElementById("roomDefiner"); 
  form.lastElementChild.parentNode.insertBefore(label, form.lastElementChild);
  form.lastElementChild.parentNode.insertBefore(input, form.lastElementChild);
  form.lastElementChild.parentNode.insertBefore(
    linebreak,
    form.lastElementChild

    
  );

  // get index by label id

  const index = label.id - 1;

  input.onchange = (event) =>
    handleInputChange(event, index, roomInputFieldCounter);

  roomInputFieldCounter++;
});

// handle input change of dynamic room input fields

const handleInputChange = (event, index, totalStudents) => {
  questionaireInfo.amountOfRoomsForPersons[index] = event.target.value;
};

// add on click event listener to the button with id createQuestionaire`

const createNewQuestionaire = async () => {
  // convert amountOfRoomsForPersons to string separated by -

  // there should not be more students than rooms

  // check if there are enough rooms for all students
  let totalAmountOfRoomsForPersons = 0;
  for (let i = 0; i < questionaireInfo.amountOfRoomsForPersons.length; i++) {
    totalAmountOfRoomsForPersons +=
      (i + 1) * parseInt(questionaireInfo.amountOfRoomsForPersons[i]);
  }

  const totalStudents = parseInt(questionaireInfo.totalStudents);

  if (totalStudents > totalAmountOfRoomsForPersons) {
    alert("You cannot have more students than rooms");
    return;
  }

  let finalQuestionaireInfo = {
    ...questionaireInfo,
    amountOfRoomsForPersons: questionaireInfo.amountOfRoomsForPersons.join("-"), maxRooms: questionaireInfo.amountOfRoomsForPersons.length,
  };


  finalQuestionaireInfo = [finalQuestionaireInfo];

  // Send POST request to the server

  const rawResponse = await fetch("/writeinfotocsv", {
    method: "POST",
    headers: {
      Accept: "application/json",
      "Content-Type": "application/json",
    },
    body: JSON.stringify({ finalQuestionaireInfo }),
  });
  const content = await rawResponse.json();

  window.location.href = "/Create";
};
