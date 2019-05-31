var TANK = TANK || {};
document.addEventListener('DOMContentLoaded', function(event) {
TANK.mode = document.getElementById('mode');
TANK.unit = document.getElementById('unit');
TANK.x = document.getElementById('x');
TANK.y = document.getElementById('y');
TANK.go = document.getElementById('go');
TANK.xhr = function(url, data, options) {
  options = options || {};
  var request = new XMLHttpRequest();
  request.open('POST', url, true);
  request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
  request.onreadystatechange = function () {
    if (this.readyState === 4) {
      if (this.status >= 200 && this.status < 400) {
        options.success && option.success(parse(this.responseText));
      } else {
        options.error && options.error(this.status);
      }
    }
  };
  request.send(data);
}
TANK.button = function(event) {
  console.log(event.target);
  var x = parseFloat(event.target.dataset['x'])
  var y = parseFloat(event.target.dataset['y'])
  TANK.x.value = x
  TANK.y.value = y
  TANK.click_go();
}
TANK.click_go = function() {
  TANK.xhr('/set.php','mode='+TANK.mode.value+'&unit='+TANK.unit.value+'&x='+TANK.x.value+'&y='+TANK.y.value, {});
}
TANK.go.addEventListener('click', TANK.click_go);
var i = 0;
var nodes = document.querySelectorAll('.d')
var n = nodes.length
for (i=0; i<n; i++) {
  nodes[i].addEventListener('click', TANK.button);
}

});
