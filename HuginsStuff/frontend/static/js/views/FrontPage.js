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
                <button type="button" id="redirectStudent">Student login</button>
                <br>
                <br>
                <button type="button" id="redirectAdmin">Admin login</button>
            </p>
            </form>
        `;
    }
}