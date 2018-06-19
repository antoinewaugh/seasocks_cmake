var ws;

$(function begin() {

    ws = new WebSocket('ws://' + document.location.host + '/stream');
    ws.onopen = function () {
        console.log('onopen');
    };
    ws.onclose = function () {
        console.log('onclose');
    };
    ws.onmessage = function (message) {
        console.log(message.data);
    };
    ws.onerror = function (error) {
        console.log("ERROR: " + error);
    };
});
