window.addEventListener("load", checkForQuestionnaire);

function checkForQuestionnaire() {
    let done = true;
    localStorage.doneness = JSON.stringify(done);
    let isDone = JSON.parse(localStorage.doneness);

    let a1 = document.createElement('a');
    let linkText1 = document.createTextNode("Change done state");
    a1.appendChild(linkText1);
    a1.title = "Change state";
    a1.href = "./P2HTML_finish.html";
    document.body.appendChild(a1);

    document.body.appendChild(document.createElement("br"));
    
    if (isDone!==true) {
        let p = document.createElement('p');
        let pText = document.createTextNode("Your questionnaire is set to done, if you wish to edit, then please change the state of the current questionnaire.");
        p.appendChild(pText);
        document.body.appendChild(p);
    } else {
        let a2 = document.createElement('a');
        let linkText2 = document.createTextNode("Edit current questionnaire");
        a2.appendChild(linkText2);
        a2.title = "Edit";
        a2.href = "./P2HTML_edit.html";
        document.body.appendChild(a2);
    }
}
