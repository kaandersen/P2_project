import Dashboard from "./views/FrontPage.js";
import Posts from "./views/StudentLogIn.js";
import Settings from "./views/AdminLogIn.js";
const fs = require("fs");

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
    router();
};

const router = async () => {
    const routes = [
        { path: "/", view: Dashboard },
        { path: "/student", view: Posts },
        { path: "/admin", view: Settings }
    ];

    // Test each route for potential match
    const potentialMatches = routes.map(route => {
        return {
            route: route,
            result: location.pathname.match(pathToRegex(route.path))
        };
    });

    let match = potentialMatches.find(potentialMatch => potentialMatch.result !== null);

    if (!match) {
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
    document.body.addEventListener("click", e => {
        if (e.target.matches("[data-link]")) {
            e.preventDefault();
            navigateTo(e.target.href);
        }
    });

    router();
});

function giveFunctionality() {
    let buttonID = document.getElementById("logInButton");
    if (buttonID) {
        buttonID.addEventListener("click", helloWorld);
    }
}

function helloWorld(){
    if (location.pathname == "/student"){
        console.log("This will now go to answer questionnaire");
    }
    if (location.pathname == "/admin"){
        window.location.href= "C:\Users\hugin\Desktop\P2\P2_project\NicklasStuff\P2HTML_from.html";
    }
}