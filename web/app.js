var ws;

function add(text) {
    var chat = $('#websocket-display');
    chat.text(chat.text() + "\n" + text);
}

$(function begin() {

    ws = new WebSocket('ws://' + document.location.host + '/stream');
    ws.onopen = function () {
        console.log('onopen');
    };
    ws.onclose = function () {
        console.log('onclose');
    };
    ws.onmessage = function (message) {
        add(message.data);
    };
    ws.onerror = function (error) {
        console.log("ERROR: " + error);
    };
});
