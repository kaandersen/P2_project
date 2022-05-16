var calculateDataArray = [];
var _questionaireEditIndex = 1;
var _questionaireCalculateIndex = 1;

calculateDataArray = [
    ...calculateDataArray,
    { selectedid: "", titleamount: "" },
];


window.addEventListener("mousemove", giveFunctionality);

window.addEventListener('load', (event) => {
    console.log('page is fully loaded');
    loadLocalStorage();
});

//Gives functionality to the buttons and passes along identifiers to determine what button was pressed.
function giveFunctionality() {
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
    if (identifier === "finished") {
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










addRow();
/*getQuestionaireTitle();

async function getQuestionaireTitle() {
}*/


async function addRow() {

    //Get title from csv
    const responseInfo = await fetch("/public/StudentInfoQuestionaire.csv");
    const CSVdataInfo = await responseInfo.text();
    const rowsInfo = CSVdataInfo.split("\n").slice(1);

    var titleColoumnArr = [];

    rowsInfo.forEach((element) => {
        const rowInfo = element.split(",");
        const coloumnTitle = rowInfo[0];
        titleColoumnArr.push(coloumnTitle);
    });

    //Get Questions from csv
   /* const response = await fetch("/public/Questionaire.csv");
    const CSVdata = await response.text();
    const rows = CSVdata.split("\n").slice(1);

    var questionColoumnArr = [];

    rows.forEach((element) => {
        const row = element.split(",");
        const coloumnQuestions = row[2];
        questionColoumnArr.push(coloumnQuestions);
    });

    console.log(questionColoumnArr);*/

    


    let i, j;
    let table = document.getElementById("quest-table");
    let tableBody = document.getElementById("dyn-table-body");

    var newArr = JSON.parse(window.localStorage.getItem('WrapperID'));

    for (i = 0; i < newArr.length; i++) {
        let newRow = table.insertRow(i);
        tableBody.appendChild(newRow);

        var cell1 = newRow.insertCell(0);
        var cell2 = newRow.insertCell(1);
        var cell3 = newRow.insertCell(2);

        //edit button
        var editQuestionaireBtn = document.createElement("button");
        editQuestionaireBtn.innerHTML = "Edit";
        editQuestionaireBtn.setAttribute("id", "" + newArr[i]);
        editQuestionaireBtn.setAttribute("questionairebtnid", "" + _questionaireEditIndex++);
        editQuestionaireBtn.setAttribute("class", "deleteBtnClass");
        editQuestionaireBtn.name = "deleteBtns";

        //Calculate button
        var calculateQuestionaireBtn = document.createElement("button");
        calculateQuestionaireBtn.innerHTML = "Calculate";
        calculateQuestionaireBtn.setAttribute("id", "" + newArr[i]);
        calculateQuestionaireBtn.setAttribute("calculatebtnid", "" + _questionaireCalculateIndex++);
        calculateQuestionaireBtn.setAttribute("class", "deleteBtnClass");
        calculateQuestionaireBtn.name = "deleteBtns";

        cell1.innerHTML = titleColoumnArr[i];
        cell2.appendChild(editQuestionaireBtn);
        cell3.appendChild(calculateQuestionaireBtn);

        cell2.addEventListener('click', (event) => {
            localStorage.btnID = event.target.id;
            localStorage.SelectedBtnID = event.target.getAttribute('questionairebtnid')
            window.location.href = "/Edit";
        })

        cell3.addEventListener('click', async (event) => {
            localStorage.btnID = event.target.id;
            localStorage.SelectedBtnID = event.target.getAttribute('calculatebtnid')

            var questionairebtnID = event.target.getAttribute('calculatebtnid');
            if (questionairebtnID) {
                calculateDataArray = calculateDataArray.map(item => ({...item , selectedid : questionairebtnID}));
            }

            
            var amountOfQuestions = localStorage.getItem("btnID");
            if (amountOfQuestions) {
                calculateDataArray = calculateDataArray.map(item => ({...item , titleamount : amountOfQuestions}));
            }

            
            console.log(titleColoumnArr.length)

            const rawResponse = await fetch("/writetodatacsv", {

                method: "POST",
                headers: {
                    Accept: "application/json",
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({ calculateDataArray }),
            });
            const content = await rawResponse.json();
            console.log(content)
            
           

            /* Activating allocation program */
            function activateProgram(){
                const { spawn } = require('node:child_process');
                const bat = spawn('/AllocationProgram.exe', ['/c', 'my.bat']);
    
                bat.stdout.on('data', (data) => {
                console.log(data.toString());
                });
    
                bat.stderr.on('data', (data) => {
                console.error(data.toString());
                });
    
                bat.on('exit', (code) => {
                console.log(`Child exited with code ${code}`);
                });
            }
            activateProgram();

        })


    }

}



