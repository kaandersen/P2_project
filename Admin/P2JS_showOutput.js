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

    //Creates a link to continue working based on the existance of a questionnaire???

    let p = document.createElement('p');
    document.body.appendChild(p);

    let ul = document.createElement("ul");
    ul.id = "outputList"; //id for css use
    p.appendChild(ul);

    let counter = 0;

    let pairringsString = JSON.parse(localStorage.pairs)
    //let pairrings = pairringsString.split('.');
    fetch("/data.txt").then(response => response.text()).then(data => {
        let pairrings = data.split('.');
        pairrings.forEach(element => {
            let li = document.createElement("li");
            
            if(counter%2 == 0){
                li.id = "evenListItem";
            } else{
                li.id = "oddListItem";
            }


            li.appendChild(document.createTextNode(element));
            ul.appendChild(li); 
            counter ++;
        });
    });

    //appends the ul list to the assigned container
    document.getElementById("outputContent").appendChild(p);
}
