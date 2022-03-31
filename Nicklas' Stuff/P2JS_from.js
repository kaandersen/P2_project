window.addEventListener("load", checkForQuestionnaire);

function checkForQuestionnaire() {
    let existance = "Yes";
    localStorage.existance = JSON.stringify(existance);
    let exists = JSON.parse(localStorage.existance);
    let a = document.createElement('a');
    let linkText;
    if (exists==="Yes") {
        linkText = document.createTextNode("Continue working on questionnaire");
        a.appendChild(linkText);
        a.title = "Continue";
        a.href = "file:///C:/Users/Nickl/Desktop/P2%20Projekt/P2HTML_continue.html";
        document.body.appendChild(a);
    } else {
        linkText = document.createTextNode("Create new questionnaire");
        a.appendChild(linkText);
        a.title = "Create new";
        a.href = "file:///C:/Users/Nickl/Desktop/P2%20Projekt/P2HTML_new.html";
        document.body.appendChild(a);
    }
}
