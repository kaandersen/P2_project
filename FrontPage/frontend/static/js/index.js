import FrontPage from "./views/FrontPage.js";
import Student from "./views/StudentLogIn.js";
import Admin from "./views/AdminLogIn.js";
import About from "./views/AboutPage.js";

//This is to surcomvent adding script in the html
window.addEventListener("mousemove", giveFunctionality);


const pathToRegex = path => new RegExp("^" + path.replace(/\//g, "\\/").replace(/:\w+/g, "(.+)") + "$");

const getParams = match => {
    const values = match.result.slice(1);
    const keys = Array.from(match.route.path.matchAll(/:(\w+)/g)).map(result => result[1]);

    return Object.fromEntries(keys.map((key, i) => {
        return [key, values[i]];
    }));
};

const navigateTo = url => {
    history.pushState(null, null, url);
    router(); //calls the client side router to process the new history entry
};
//Serves the dynamic pages
const router = async () => {
    const routes = [
        { path: "/", view: FrontPage },
        { path: "/studentLogin", view: Student },
        { path: "/adminLogin", view: Admin }, 
        { path: "/about", view: About}
    ];

    // Test each route for potential match
    const potentialMatches = routes.map(route => {
        return {
            route: route,
            result: location.pathname.match(pathToRegex(route.path))
        };
    });

    let match = potentialMatches.find(potentialMatch => potentialMatch.result !== null);

    if (!match) { //if there is no match for the route we default to the front page
        match = {
            route: routes[0],
            result: [location.pathname]
        };
    }

    const view = new match.route.view(getParams(match));

    document.querySelector("#app").innerHTML = await view.getHtml();
};


/* Runs code, when going "back" */
window.addEventListener("popstate", router);


/* Adds a seamless transition between sites */
document.addEventListener("DOMContentLoaded", () => {
    document.body.addEventListener("click", e => { //delegated event listener
        if (e.target.matches("[data-link]")) {
            e.preventDefault();
            navigateTo(e.target.href);
        }
    });

    router();
});


//if login button is clicked on either page
function giveFunctionality() {
    let buttonID = document.getElementById("logInButton");
    if (buttonID) { 
        buttonID.addEventListener("click", helloWorld);
    } 
}

//redirects into the Admin or student folder after login
function helloWorld(){
    let adminIDs = ["12345", "67891", "23456", "56789"];
    let studentIDs = ["54321", "19876", "65432", "98765"];

    let loginForm = document.getElementById("login-form");
    let userID = loginForm.ID.value;

    console.log(userID);
    //If the admin log in input matches the hardcoded list of id's, then the admin home page is loaded
    if (location.pathname == "/adminLogin"){
        if(userID == adminIDs[adminIDs.indexOf(userID)]){
            location.pathname = "/Admin";
        } else{
            alert("Incorrect admin ID");
        }
    }
    //If the student log in input matches the hardcoded list of id's, then the student home page is loaded
    if (location.pathname == "/studentLogin"){
        if(userID == studentIDs[studentIDs.indexOf(userID)]){
            location.pathname = "/StudentHome";
        } else{
            alert("Incorrect student ID");
        }  
    }
}