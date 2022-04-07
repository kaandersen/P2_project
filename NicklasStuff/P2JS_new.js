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

    let label = document.createElement("label");
    label.setAttribute = ("for","lname");
    label.id = "label#"+counterString+"rooms";
    label.innerHTML = "Amount of "+ counterString  +" person rooms:";

    let linebreak = document.createElement("br");
    let form = document.getElementById("roomDefiner"); //changed name so that it affects the fieldset instead of the form
    form.lastElementChild.parentNode.insertBefore(label, form.lastElementChild);
    form.lastElementChild.parentNode.insertBefore(input, form.lastElementChild);
    form.lastElementChild.parentNode.insertBefore(linebreak, form.lastElementChild);
}

//Load the previously saved data and logs it in the console, to check saving capability.
function loadData() {
    console.log(JSON.parse(localStorage.numberOfRooms));
    let numberOfRooms = JSON.parse(localStorage.numberOfRooms).split(',').map(Number);
    numberOfRooms.pop();
    numberOfRooms.unshift(0);
    console.log(numberOfRooms);
    window.removeEventListener("mousemove", loadData);
}

//collects data from input fields when button is pressed and saves it to the localStorage.
function collectData() {
    let myString = "";
    localStorage.numberOfStudents = JSON.stringify(document.getElementById("#students").value);
    for (let index = 1; index <= counter; index++) {
        indexString = index.toString(10);
        myString += document.getElementById("#"+indexString+"rooms").value+",";
    }
    console.log(myString);
    localStorage.numberOfRooms = JSON.stringify(myString);

    window.location.href="./P2HTML_continue.html";
}