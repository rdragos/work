
var context;

var x_first=100;
var y_first=100;
var radius_first = 40;
var dx_first=5;
var dy_first=5;
var mass_first = 4;

var radius_second = 40;
var x_second = 40;
var y_second = 30;
var dx_second = 2;
var dy_second = 5;
var mass_second = 10;

function game_main() {
	context = canvas.getContext('2d');
	setInterval(draw,10);
}


function collide() {

	if (x_first + radius_first + radius_second > x_second) {
		if (x_first < x_second + radius_first + radius_second) {
			if (y_first + radius_first + radius_second > y_second) {
				if (y_first < y_second + radius_first + radius_second) {
					var d  = (x_first - x_second) * (x_first - x_second) + (y_first - y_second) * (y_first - y_second)	;
					if (Math.sqrt(d) <= radius_second + radius_second) {
						return 1;
					}
				}
			}
		}
	}

}
function draw()
{
	context.clearRect(0, 0, 500, 400)
	context.beginPath();
	context.fillStyle="black";
	// Draws a circle of radius 20 at the coordinates 100,100 on the canvas
	context.arc(x_first, y_first, radius_first, 0, Math.PI*2, true);

	context.closePath();
	context.fill();
	if(x_first <20 || x_first> 480) {
		dx_first = -dx_first;
	}

	if(y_first <20|| y_first > 380) {
		dy_first = -dy_first;
	}
	x_first += dx_first;
	y_first += dy_first;

	context.beginPath()
	context.arc(x_second, y_second, radius_second, 0, Math.PI * 2, true)
	context.closePath()
	context.fill()

	if (x_second <= 20 || x_second > 480) {
		dx_second = -dx_second;
	}
	if (y_second <= 20 || y_second > 380) {
		dy_second = -dy_second;
	}

	x_second += dx_second
	y_second += dy_second

	if (collide()) {
		context.fillStyle = "blue";
		context.fillRect(x_second, y_second, 10, 10);
		dx_second *= -1;
		dx_first *= -1;
	}
}
