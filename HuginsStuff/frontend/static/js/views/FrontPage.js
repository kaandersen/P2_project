import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
    constructor(params) {
        super(params);
        this.setTitle("Front Page");
    }

    async getHtml() {
        return `
            <h1>Questionnaire based Student allocation</h1>
            <p>
                Welcome to our questionnaire based student allocation program, please proceed:
            </p>
        
            <form id="loginRedirectForm">
            <p id="LoginredirectP">
                <a href="./student" target="_parent"> <button type="button" id="redirectStudent">Student login </button></a>
                <br>
                <br>
                <a href="./admin" target="_parent"><button type="button" id="redirectAdmin">Admin login</button></a>
            </p>
            </form>
        `;
    }
}