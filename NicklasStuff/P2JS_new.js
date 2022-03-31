window.addEventListener("mousemove", giveFunctionality);
window.addEventListener("mousemove", loadData);

function giveFunctionality() {
    let buttonID = document.getElementById("goforth");
    if (buttonID) {
        buttonID.addEventListener("click", collectData);
    }
}

function loadData() {
    console.log(JSON.parse(localStorage.numberOfStudents));
    console.log(JSON.parse(localStorage.numberOf1Rooms));
    console.log(JSON.parse(localStorage.numberOf2Rooms));
    console.log(JSON.parse(localStorage.numberOf3Rooms));
    console.log(JSON.parse(localStorage.numberOf4Rooms));
    console.log(JSON.parse(localStorage.numberOf5Rooms));
    window.removeEventListener("mousemove", loadData);
}

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

function saveData(students, amountOf1Rooms, amountOf2Rooms, amountOf3Rooms, amountOf4Rooms, amountOf5Rooms) {
    localStorage.numberOfStudents = JSON.stringify(students);
    localStorage.numberOf1Rooms = JSON.stringify(amountOf1Rooms);
    localStorage.numberOf2Rooms = JSON.stringify(amountOf2Rooms);
    localStorage.numberOf3Rooms = JSON.stringify(amountOf3Rooms);
    localStorage.numberOf4Rooms = JSON.stringify(amountOf4Rooms);
    localStorage.numberOf5Rooms = JSON.stringify(amountOf5Rooms);
}

/*Store the variable "myString" at a place in the local storage named "myString", 
the names are the same but they are different things.*/ 
function store() {
    let myString = "Suck on deez";
    localStorage.myString = JSON.stringify(myString+counter);
    counter++;
}

/*Retrieves whatever data is present at localStorage.myString*/
function retrieve() {
    let myString = JSON.parse(localStorage.myString);
    console.log(myString);
}
