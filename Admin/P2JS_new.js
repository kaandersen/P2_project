window.addEventListener("mousemove", giveFunctionality);
window.addEventListener("mousemove", loadData);

var counter = 1;
//gives functionality to the button
function giveFunctionality() {
    let buttonID1 = document.getElementById("goforth");
    if (buttonID1) {
        buttonID1.addEventListener("click", validateData);
    }
    let buttonID2 = document.getElementById("createNewSize");
    if (buttonID2) {
        buttonID2.addEventListener("click", () => {
            counter++;
            createNewRoomSize();
        });
    }
    window.removeEventListener("mousemove", giveFunctionality);
}

//Creates the ability to add a room of a size larger than the previous, when clicking a button
function createNewRoomSize() {
    counterString = counter.toString(10);

    let input = document.createElement("input");
    input.type = "text";
    input.id = "#"+counterString+"rooms";
    input.value = "0";
    input.className = "roomData"; //adds classs name for css use

    let label = document.createElement("label");
    label.setAttribute = ("for","lname");
    label.id = "label#"+counterString+"rooms";
    label.innerHTML = "Amount of "+ counterString  +" person rooms: ";

    let linebreak = document.createElement("br");
    let form = document.getElementById("roomDefiner"); //changed name so that it affects the fieldset instead of the form
    form.lastElementChild.parentNode.insertBefore(label, form.lastElementChild);
    form.lastElementChild.parentNode.insertBefore(input, form.lastElementChild);
    form.lastElementChild.parentNode.insertBefore(linebreak, form.lastElementChild);
}

//Load the previously saved data and logs it in the console, to check saving capability.
function loadData() {
    console.log("Amount of students: " + JSON.parse(localStorage.numberOfStudents));
    console.log("Amount of rooms: " + JSON.parse(localStorage.numberOfRooms));
    let numberOfRooms = JSON.parse(localStorage.numberOfRooms).split(',').map(Number);
    numberOfRooms.pop();
    numberOfRooms.unshift(0);
    console.log(numberOfRooms);
    window.removeEventListener("mousemove", loadData);
}

//Validates the input data, if everything is ok, then it goes ahead, if not it alerts the user to the error.
function validateData() {
    if (checkIfStringHasOnlyDigits(document.getElementById("#students").value) && checkRoomInputs()) {
        if (checkSpaceForStudents()) {
            collectData();
            window.location.href="./P2HTML_continue.html";
        } else {
            alert("There are more students than there is space for, that is not okay.");
        }
    } else {
        alert("Something is wrong with one of the inputs");
    }
}

//collects data from input fields when button is pressed and saves it to the localStorage.
function collectData() {
    let myString = "";

    /* * 
    *   
    *   possibly add the ability to also save the name of the questionnairef from the first field. 
    *   Related question: how are we naming the file containing the questionnaire  set up by the teacher
    * 
    * */

    localStorage.numberOfStudents = JSON.stringify(document.getElementById("#students").value);
    for (let index = 1; index <= counter; index++) {
        indexString = index.toString(10);
        myString += document.getElementById("#"+indexString+"rooms").value+",";
    }
    localStorage.numberOfRooms = JSON.stringify(myString);
}

//Checks if a given string only contains digits, used for validation of input fields.
function checkIfStringHasOnlyDigits(_string){
    if(_string.match(/^[0-9]+$/) != null)
    {
        return true;
    } else {
        return false;
    }
}

//Checks each of the input fields for room types to see if they contain anything other than digits. 
function checkRoomInputs() {
    let myString = "";
    for (let index = 1; index <= counter; index++) {
        indexString = index.toString(10);
        myString += document.getElementById("#"+indexString+"rooms").value;
    }
    if (checkIfStringHasOnlyDigits(myString)) {
        return true;
    } else {
        return false;
    }
}

//Checks if there are more students than there is room for them, or the other way around. 
function checkSpaceForStudents() {
    let students = document.getElementById("#students").value;
    let myString = "";
    for (let index = 1; index <= counter; index++) {
        indexString = index.toString(10);
        myString += document.getElementById("#"+indexString+"rooms").value*index+",";
    }
    let numberOfRooms = myString.split(',').map(Number);
    numberOfRooms.pop();
    numberOfRooms.unshift(0);

    if (students <= numberOfRooms.reduce((a, b) => a + b, 0)) {
        return true;
    } else {
        return false;
    }
}