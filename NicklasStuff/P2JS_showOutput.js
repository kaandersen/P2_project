window.addEventListener("load", loadPairrings);

function loadPairrings() {
    let pair1 = "Room 1: 8 | Satisfaction: 25.";
    let pair2 = "Room 2: 18 - 43 | Satisfaction: 7.";
    let pair3 = "Room 3: 25 - 3 | Satisfaction: 5.";
    let pair4 = "Room 4: 38 - 9 | Satisfaction: 6.";
    let pair5 = "Room 5: 42 - 1 | Satisfaction: 6.";
    let myString = pair1 + pair2 + pair3 + pair4 + pair5;
    localStorage.pairs = JSON.stringify(myString);
    //let pairString = JSON.parse(localStorage.pair);

    //Creates a link to continue working based on the existance of a questionnaire. 

    let p = document.createElement('p');
    document.body.appendChild(p);

    let ul = document.createElement("ul");
    p.appendChild(ul);

    let pairringsString = JSON.parse(localStorage.pairs)
    let pairrings = pairringsString.split('.');

    pairrings.forEach(element => {
        let li = document.createElement("li");
        li.appendChild(document.createTextNode(element));
        ul.appendChild(li); 
    });
}