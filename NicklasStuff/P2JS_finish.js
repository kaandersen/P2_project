window.addEventListener("mousemove", giveFunctionality);

//Gives functionality to the buttons and passes along identifiers to determine what button was pressed.
function giveFunctionality() {
    console.log("Hi");
    let buttonID1 = document.getElementById("finished");
    if (buttonID1) {
        buttonID1.addEventListener("click", () => {
            store(buttonID1.id);
        });
    }
    let buttonID2 = document.getElementById("editable");
    if (buttonID2) {
        buttonID2.addEventListener("click", () => {
            store(buttonID2.id);
        });
    }
    window.removeEventListener("mousemove", giveFunctionality);
}

//Identifies the button pressed and changes the localStorage variable accordingly. 
function store(identifier) {
    if (identifier==="finished") {
        let done = true;
        localStorage.doneFlag = JSON.stringify(done);
    } else {
        let done = false;
        localStorage.doneFlag = JSON.stringify(done);
    }
}