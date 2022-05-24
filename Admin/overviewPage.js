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

addRow();

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
        editQuestionaireBtn.setAttribute("class", "editBtnClass");
        editQuestionaireBtn.name = "editBtns";

        //Calculate button
        var calculateQuestionaireBtn = document.createElement("button");
        calculateQuestionaireBtn.innerHTML = "Calculate";
        calculateQuestionaireBtn.setAttribute("id", "" + newArr[i]);
        calculateQuestionaireBtn.setAttribute("calculatebtnid", "" + _questionaireCalculateIndex++);
        calculateQuestionaireBtn.setAttribute("class", "editBtnClass");
        calculateQuestionaireBtn.name = "edtiBtns";

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
            
            window.location.href = "/Please_work"
            /* Activating allocation program */

        })


    }

}



