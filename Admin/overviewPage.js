window.addEventListener("mousemove", giveFunctionality);

window.addEventListener('load', (event) => {
    console.log('page is fully loaded');
    loadLocalStorage();
});

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

/**
 * This function related to the search bar 
 */
function searchQuestionnaire() {
    // Declare variables
    var input, filter, table, tr, td, i, txtValue;
    input = document.getElementById("searchbar");
    filter = input.value.toUpperCase();
    table = document.getElementById("quest-table");
    tr = table.getElementsByTagName("tr");

    // Loop through all table rows, and hide those who don't match the search query
    for (i = 0; i < tr.length; i++) {
        td = tr[i].getElementsByTagName("td")[0];
        if (td) {
            txtValue = td.textContent || td.innerText;
            if (txtValue.toUpperCase().indexOf(filter) > -1) {
                tr[i].style.display = "";
            } else {
                tr[i].style.display = "none";
            }
        }
    }
}

// addRow();

// function addRow(){
//    let i, j;
//     let table = document.getElementById("quest-table");
//     let tableBody = document.getElementById("dyn-table-body");
//     // let numQuestionnaire = localStorage.getItem("wrapperID");
//     let numQuestionnaire = 4;
//     let questTitle = ["questionnaire 1", "questionnaire 2","questionnaire 3"]; //Replace this with the values from the qctual questionnaires

//     let tableData = '<tr><td>${questionTitle[0]}</td><td><button id="edit-Odense-uni-2021" title="Edit questionnaire" class="editButton">Edit</button></td></tr>';
        

// }


