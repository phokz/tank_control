var TANK = TANK || {};
document.addEventListener('DOMContentLoaded', function (event) {
  TANK.mode = document.getElementById('mode');
  TANK.unit = document.getElementById('unit');
  TANK.x = document.getElementById('x');
  TANK.y = document.getElementById('y');
  TANK.go = document.getElementById('go');
  TANK.stop = document.getElementById('stop');
  TANK.xhr = function (url, data) {
    var request = new XMLHttpRequest();
    request.open('POST', url, true);
    request.setRequestHeader('Content-type',
      'application/x-www-form-urlencoded');
    request.onreadystatechange = function () {
      if (this.readyState === 4) {
        if (this.status >= 200 && this.status < 400) {
          console.log(this.responseText);
        } else {
          console.log(this.status);
        }
      }
    };
    request.send(data);
  };
  TANK.button = function (event) {
    var el = event.target;
    if (!el.classList.contains('d')) el = el.parentNode;
    TANK.x.value = parseFloat(el.dataset.x);
    TANK.y.value = parseFloat(el.dataset.y);
    TANK.click_go();
  };
  TANK.click_go = function () {
    TANK.xhr('/set.php', 'mode=' + TANK.mode.value + '&unit=' +
      TANK.unit.value + '&x=' + TANK.x.value + '&y=' + TANK.y
      .value);
  };
  TANK.click_stop = function () {
    TANK.xhr('/stop.php', 'stop=1');
  }
  TANK.go.addEventListener('click', TANK.click_go);
  TANK.stop.addEventListener('click', TANK.click_stop);
  var i = 0;
  var nodes = document.querySelectorAll('.d');
  var n = nodes.length;
  for (i = 0; i < n; i++) {
    nodes[i].addEventListener('click', TANK.button);
  }
});
