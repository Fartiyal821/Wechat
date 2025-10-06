const socket = new WebSocket("ws://localhost:9001");

const form = document.getElementById("chat-form");
const chatBox = document.getElementById("chat-box");

form.addEventListener("submit", function (e) {
    e.preventDefault();

    const username = document.getElementById("username").value.trim();
    const message = document.getElementById("message").value.trim();

    if (username && message) {
        const msg = `${username}: ${message}`;
        socket.send(msg);
        appendMessage(msg);  // Show own message
        document.getElementById("message").value = "";
    }
});

socket.onmessage = function (event) {
    appendMessage(event.data);
};

function appendMessage(msg) {
    const p = document.createElement("p");
    p.textContent = msg;
    chatBox.appendChild(p);
    chatBox.scrollTop = chatBox.scrollHeight;
}
