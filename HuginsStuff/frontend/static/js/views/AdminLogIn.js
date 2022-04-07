import AbstractView from "./AbstractView.js";

export default class extends AbstractView {
    constructor(params) {
        super(params);
        this.setTitle("Admin LogIn");
    }

    async getHtml() {
        return `
        <h1>Admin logIn</h1>
        <button type="button" id="logInButton">Log in</button>
        `;
    }
}