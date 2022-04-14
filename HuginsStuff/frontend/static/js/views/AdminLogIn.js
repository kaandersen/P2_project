import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
    constructor(params) {
        super(params);
        this.setTitle("Admin LogIn");
    }

    async getHtml() {
        return `
            <h1>Admin logIn</h1>
            <label for="adminID">Admin ID:</label>
            <input type="text" id="logInID" value="">
            <button type="button" id="logInButton">Log in</button>
        `;
    }
}