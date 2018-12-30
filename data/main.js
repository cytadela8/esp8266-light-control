function setState(state) {
    var request = new XMLHttpRequest();
    request.open('GET', 'setLamp?lampState=' + state, true);

    request.onload = function () {
        if (this.status === 200) {
            parseStatus(this.responseText);
        }
    };

    request.send();
}

function refreshState() {
    var request = new XMLHttpRequest();
    request.open('GET', 'getState', true);

    request.onload = function () {
        if (this.status === 200) {
            parseStatus(this.responseText);
            setTimeout(refreshState, 500);
        } else {
            document.getElementById("status").innerHTML = "Error: Response status " + this.status;
            setTimeout(refreshState, 5000);
        }
    };

    request.onerror = function () {
        document.getElementById("status").innerHTML = "Error: request errored";
        setTimeout(refreshState, 5000);
    };

    request.send();
}

function parseStatus(statusText) {
    data = JSON.parse(statusText);
    buttonOn = document.getElementById("buttonOn")
    buttonOff = document.getElementById("buttonOff")

    if (data['lamp'] === "ON") {
        buttonOn.disabled = true;
        buttonOff.disabled = false;
    } else if (data['lamp'] === "OFF") {
        buttonOn.disabled = false;
        buttonOff.disabled = true;
    } else {
        buttonOn.disabled = false;
        buttonOff.disabled = false;
    }

    var status = document.getElementById("status");
    status.innerHTML = "";
    for (var key in data) {
        status.innerHTML += key + ": " + data[key] + "<br>";
    }
}

refreshState();