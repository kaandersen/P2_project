var counter = 0;
let string = "Hello"
window.addEventListener("load", addText(string));
window.addEventListener("load", addButton);
window.addEventListener("load", addButton2);
window.addEventListener("load", addButton3);

function addText(myText) {
    let para = document.createElement("p");
    para.innerHTML = myText;
    para.name = "firText";
    para.id = "firstText";
    document.body.appendChild(para);
}

function addButton() {
    let btn = document.createElement("button");
    btn.innerHTML = "Click Deez Nuts";
    btn.type = "Submit";
    btn.name = "firButton";
    btn.id = "firstButton";
    document.body.appendChild(btn);
}

function addButton2() {
    let btn = document.createElement("button");
    btn.innerHTML = "Store the string 'Suck on deez'";
    btn.type = "Submit";
    btn.name = "secButton";
    btn.id = "secondButton";
    document.body.appendChild(btn);
}

function addButton3() {
    let btn = document.createElement("button");
    btn.innerHTML = "Retrieve previous stored string";
    btn.type = "Submit";
    btn.name = "thiButton";
    btn.id = "thirdButton";
    document.body.appendChild(btn);
}

window.addEventListener("mousemove", giveButtonsFunctionality);

function giveButtonsFunctionality() {
    let button1Name = document.getElementById("firstButton");
    if (button1Name) {
        button1Name.addEventListener("click", editBody);
    }
    let button2Name = document.getElementById("secondButton");
    if (button2Name) {
        button2Name.addEventListener("click", store);
    }
    let button3Name = document.getElementById("thirdButton");
    if (button3Name) {
        button3Name.addEventListener("click", retrieve);
    }
}

function editBody() {
    document.getElementById("firstText").innerHTML = "Hello friend";
    console.log("Deez nuts");
}
/*Store the variable "myString" at a place in the local storage named "myString", 
the names are the same but they are different things.*/ 
function store() {
    let myString = "Suck on deez";
    localStorage.myString = JSON.stringify(myString+counter);
    counter++;
}

/*Retrieves whatever data is present at localStorage.myString*/
function retrieve() {
    let myString = JSON.parse(localStorage.myString);
    console.log(myString);
}
