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

/**
 *  This function is meant to publish questionnaires
 *  <input type="checkbox" name="selected" id="Selection">  
 * */ 
function publish(){
    let rows = document.getElementsByTagName('tr'); //amounts of rows in table
    let validations = new Array(rows.length);

    for(let i=0; i < rows.length; i++){//run through all rows
        let checkbox = rows[i].getElementsByTagName("input");
        validations[i] = validate(checkbox);
    }

    for(let i=0; i < validations.length; i++){
        if(validations[i] == true){
            //change local storage variable to be published
        }
    }
}

/**
 *  This function is meant to unpublish questionnaires
 * */ 
function unpublish(){
    let rows = document.getElementsByTagName('tr'); //amounts of rows in table
    let validations = new Array(rows.length);

    for(let i=0; i < rows.length; i++){//run through all rows
        let checkbox = rows[i].getElementsByTagName("input");
        validations[i] = validate(checkbox);
    }

    for(let i=0; i < validations.length; i++){
        if(validations[i] == true){
            //change local storage variable to be unpublished
        }
    }

}

/**
 * This function checks if  checkbox is selected or not
 * @param {*} checkbox 
 * @returns a boolean true or false
 */
function validate(checkbox){ 
    if(checkbox.checked){
        return true;
    } else{
        return false;
    }
}

/**
 * This functions should load the "unpulished/pulished" tags into the table on page load, by
 * retrievning data from local storage....
 */
function loadLocalStorage(){
    let rows = document.getElementsByTagName('tr'); //amounts of rows in table



}
