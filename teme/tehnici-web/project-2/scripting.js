
var elem = document.getElementById('myCanvas');
var elemLeft = elem.offsetLeft;
var elemTop = elem.offsetTop,
    context = elem.getContext('2d'),
    elements = [];

// Add event listener for `click` events.


function Point(_x, _y) {
	this.x = _x;
	this.y = _y;
}

Point.prototype.distance = function(other) {
	var f_dist = (this.x - other.x) * (this.x - other.x)
	var s_dist = (this.y - other.y) * (this.y - other.y);
	return Math.sqrt(f_dist + s_dist);
}
 function Circle(x, y, radius) {
	this.point = new Point(x, y)
	this.radius = radius;
}

Circle.prototype.inside = function(x, y) {
    var p2 = new Point(x, y);
    return this.point.distance(p2) <= this.radius;
}
elem.addEventListener('click', function(event) {
    var x = event.pageX - elemLeft,
        y = event.pageY - elemTop;

    // Collision detection between clicked offset and element.

    for (var i = 0; i < elements.length; i++) {
        for (var j = 0; j < elements[i].length; j++) {

            var element = elements[i][j];
            if (element.inside(x, y)) {
                elements[i].splice(j, elements[i].length - j);
            }

        }
    }


}, false);

// Add element.


// Render elements.

function redraw() {
    context.clearRect(0, 0, 600, 600)
    for (var i = 0; i < elements.length; i++) {
        for (var j = 0; j < elements[i].length; j++) {
            element = elements[i][j];

            context.beginPath();
            context.arc(element.point.x, element.point.y, element.radius, 0, 2 * Math.PI);

            context.stroke();
            context.closePath();
        }
    }
}


function game_main() {

    var selected_radius = 40;
    var x = selected_radius;
    var y = selected_radius;

    for (var stack = 5; stack >= 1; stack--) {
        elements.push(new Array());
        for (var i = 1; i <= stack; i++) {
            elements[5 - stack].push(new Circle(2 * selected_radius * (6 - stack) , 2 * (6 - i) * selected_radius, selected_radius));
        }
    }
    setInterval(redraw, 30);
}
