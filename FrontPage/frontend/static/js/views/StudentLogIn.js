import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
    constructor(params) {
        super(params);
        this.setTitle("Student LogIn");
    }

    async getHtml() {
        return `
        <div class="container">
            <h1>Student login</h1>
            <div class="loginCard">
                <form id="login-form">
                    <div class="input-container">
                        <label for="studentID">Student ID</label>
                        <input type="text" id="logInID" value="" name="ID" placeholder="XXXXX">
                    </div>
                    <div class="button-container">
                        <button type="button" id="logInButton">Go</button>
                        </div>
                </form>
            </div>
        </div>
        `;
    }
}