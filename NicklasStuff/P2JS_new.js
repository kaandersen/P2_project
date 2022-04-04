window.addEventListener("mousemove", giveFunctionality);
window.addEventListener("mousemove", loadData);

var counter = 1;
//gives functionality to the button
function giveFunctionality() {
    let buttonID1 = document.getElementById("goforth");
    if (buttonID1) {
        buttonID1.addEventListener("click", collectData);
    }
    let buttonID2 = document.getElementById("createNewSize");
    if (buttonID2) {
        buttonID2.addEventListener("click", () => {
            createNewRoomSize();
        });
    }
    window.removeEventListener("mousemove", giveFunctionality);
}

function createNewRoomSize() {
    counter++;
    let input = document.createElement("input");
    input.type = "text";
    input.id = "#"${}"rooms"
}

//Load the previously saved data and logs it in the console, to check saving capability.
function loadData() {
    console.log(JSON.parse(localStorage.numberOfStudents));
    console.log(JSON.parse(localStorage.numberOf1Rooms));
    console.log(JSON.parse(localStorage.numberOf2Rooms));
    console.log(JSON.parse(localStorage.numberOf3Rooms));
    console.log(JSON.parse(localStorage.numberOf4Rooms));
    console.log(JSON.parse(localStorage.numberOf5Rooms));
    window.removeEventListener("mousemove", loadData);
}

//collects data from input fields when button is pressed and finishes by calling the function for saving the gathered data.
function collectData() {
    let students, amountOf1Rooms, amountOf2Rooms, amountOf3Rooms, amountOf4Rooms, amountOf5Rooms;
    students = document.getElementById("#students").value;
    amountOf1Rooms = document.getElementById("#1rooms").value;
    amountOf2Rooms = document.getElementById("#2rooms").value;
    amountOf3Rooms = document.getElementById("#3rooms").value;
    amountOf4Rooms = document.getElementById("#4rooms").value;
    amountOf5Rooms = document.getElementById("#5rooms").value;

    saveData(students, amountOf1Rooms, amountOf2Rooms, amountOf3Rooms, amountOf4Rooms, amountOf5Rooms);
    window.location.href="./P2HTML_continue.html";
}

//saves the gathered data into localStorage
function saveData(students, amountOf1Rooms, amountOf2Rooms, amountOf3Rooms, amountOf4Rooms, amountOf5Rooms) {
    localStorage.numberOfStudents = JSON.stringify(students);
    localStorage.numberOf1Rooms = JSON.stringify(amountOf1Rooms);
    localStorage.numberOf2Rooms = JSON.stringify(amountOf2Rooms);
    localStorage.numberOf3Rooms = JSON.stringify(amountOf3Rooms);
    localStorage.numberOf4Rooms = JSON.stringify(amountOf4Rooms);
    localStorage.numberOf5Rooms = JSON.stringify(amountOf5Rooms);
    let done = false;
    localStorage.doneFlag = JSON.stringify(done);
}