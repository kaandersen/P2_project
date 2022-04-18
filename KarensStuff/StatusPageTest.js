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
        td = tr[i].getElementsByTagName("td")[1];
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

function addRows(){ 
	let table = document.getElementById('quest-table');
	let rowCount = table.rows.length;
	let cellCount = table.rows[0].cells.length; 
	let row = table.insertRow(rowCount);

	for(var i = 0; i <= cellCount; i++){
		let cell = 'cell'+ i;
		cell = row.insertCell(i);
		let copycel = document.getElementById('col'+i).innerHTML;
		cell.innerHTML = copycel;
		if(i == 3){ 
			var radioinput = document.getElementById('col3').getElementsByTagName('input'); 
			for(var j = 0; j <= radioinput.length; j++) { 
				if(radioinput[j].type == 'radio') { 
					var rownum = rowCount;
					radioinput[j].name = 'gender['+rownum+']';
				}
			}
		}
	}
}

function deleteRows(){
	let table = document.getElementById('emptbl');
	let rowCount = table.rows.length;
	if(rowCount > '2'){
		let row = table.deleteRow(rowCount-1);
		rowCount--;
	}
	else{
		alert('There should be atleast one row');
	}
}
