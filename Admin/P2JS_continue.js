window.addEventListener("load", checkForQuestionnaire);

//This function removes the functionality to edit your questionnaire, if it is set as done. 
function checkForQuestionnaire() {
    //Checks for the done state of the questionnaire
    let isDone = JSON.parse(localStorage.doneFlag);
    
    //Gives you access to change the done state of the questionnaire.
    let a1 = document.createElement('a');
    let linkText1 = document.createTextNode("Change done state");
    a1.appendChild(linkText1);
    a1.title = "Change state";
    a1.href = "./StatusPage.html";
    document.body.appendChild(a1);

    document.body.appendChild(document.createElement("br"));
    //If the questionnaires done state = flase, then it wont give you access to the diting of the page.
    if (isDone==true) {
        let p = document.createElement('p');
        let pText = document.createTextNode("Your questionnaire is set to done, if you wish to edit, then please change the state of the current questionnaire.");
        p.appendChild(pText);
        document.body.appendChild(p);
    } else {
        //If the questionnaires done state = true, then it will let you edit the page.
        let a2 = document.createElement('a');
        let linkText2 = document.createTextNode("Edit current questionnaire");
        a2.appendChild(linkText2);
        a2.title = "Edit";
        a2.href = "./P2HTML_edit.html";
        document.body.appendChild(a2);
    }
}
