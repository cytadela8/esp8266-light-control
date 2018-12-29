const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="manifest" href="/manifest.json">
  <title>Sterowanie Żarówką</title>
  <link rel="stylesheet" href="https://unpkg.com/purecss@1.0.0/build/pure-min.css" integrity="sha384-nn4HPE8lTHyVtfCBi5yW9d20FjT8BJwUXyWZT9InLYax14RDjBj46LmSztkmNP9w" crossorigin="anonymous">
<style>
.content {
  max-width: 800px;
  margin: auto;
}
</style>

</head>
<body>
<div class="content">
  <h1>Żarówka</h1>
  <div class="pure-g">
    <button class="pure-u-1-2 pure-button pure-button-primary" type="button" onclick="sendData('OFF')" id="buttonOff">OFF</button>
    <button class="pure-u-1-2 pure-button pure-button-primary" type="button" onclick="sendData('ON')" id="buttonOn">ON</button>
  </div>
  <div id="status">Loading...</div> 
</div>
<script>

function sendData(led) {
  var request = new XMLHttpRequest();
  request.open('GET', 'setLamp?lampState='+led, true);
  
  request.onload = function() {
    if (this.status == 200) {
      parseStatus(this.responseText);
    }
  };
  
  request.send();
}

function getState() {
  var request = new XMLHttpRequest();
  request.open('GET', 'getState', true);

  request.onload = function() {
    if (this.status == 200) {
      parseStatus(this.responseText);
    } else {
      document.getElementById("status").innerHTML = "ERROR 1";
    }
  };

  
  request.send();
}

function parseStatus(statusText) {
  data = JSON.parse(statusText);
  buttonOn = document.getElementById("buttonOn")
  buttonOff = document.getElementById("buttonOff")
  
  if (data['lamp'] == "ON") {
    buttonOn.disabled = true;
    buttonOff.disabled = false;
  } else if (data['lamp'] == "OFF") {
    buttonOn.disabled = false;
    buttonOff.disabled = true;
  } else {
    buttonOn.disabled = false;
    buttonOff.disabled = false;
  }
  document.getElementById("status").innerHTML = statusText;
}

setInterval(getState, 1000);
</script>
</body>
</html>
)=====";

const char MANIFEST_json[] = R"=====(
{
  "short_name": "Żarówka",
  "name": "Sterowanie Żarówką",
  "icons": [],
  "start_url": "/",
  "background_color": "#AAAAAA",
  "display": "standalone",
  "scope": "/",
  "theme_color": "#3333FF"
}
)=====";
