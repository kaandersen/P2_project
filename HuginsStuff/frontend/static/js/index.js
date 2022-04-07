import FrontPage from "./views/FrontPage.js";
import Student from "./views/StudentLogIn.js";
import Admin from "./views/AdminLogIn.js";
import About from "./views/AboutPage.js";


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

const router = async () => {
    const routes = [
        { path: "/", view: FrontPage },
        { path: "/student", view: Student },
        { path: "/admin", view: Admin }, 
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

function giveFunctionality() {
    let buttonID = document.getElementById("logInButton");
    if (buttonID) { //if login button is clicked
        buttonID.addEventListener("click", helloWorld);
    } 
}

function helloWorld(){
    if (location.pathname == "/student"){
        fetch("/views/StudentID.txt").then(response => response.text()).then(data => {
            console.log(data);
        });
        let inputvalue = document.getElementById("logInID").value;
        console.log(inputvalue);
    }
    if (location.pathname == "/admin"){
        location.pathname = "/Nicklas";
    }
}