
var elem = document.getElementById('myCanvas');
var elemLeft = elem.offsetLeft;
var elemTop = elem.offsetTop,
    context = elem.getContext('2d'),
    elements = [],
    STARTED_GAME, MARKED_HARD;

MARKED_HARD = 0;
// Add event listener for `click` events.
var player_turn = 0;

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

function refresh_records() {
    //Don't know why the fuck is wrong

    var records = localStorage.getObject('records');
    //console.log(records);
    records.sort(function(a, b) {
        return parseInt(a.spent_time) < parseInt(b.spent_time);
    });

    var table = document.getElementById("scorestable");
    table.innerHTML = "";

    for (var i = 0; i < Math.min(records.length, 10); i++) {
        var row = table.insertRow(0);

        var cell1 = row.insertCell(0);
        var cell2 = row.insertCell(1);

        cell1.innerHTML = records[i].person_name;
        cell2.innerHTML = records[i].spent_time + " seconds";
    }
}
function eval_game(state) {
    if (STARTED_GAME == 0) {
        return 0;
    }
    STARTED_GAME = 0;

    redraw();
    sessionStorage.end_time = Date.now();

    if (state == 0) {
        //Player lost
        alert("You lost!");
    } else {

        var w = open("form.html", "form", "width=300, height=300, screenx=100, screeny=100");
        w.alert("Lol you won");
        var polltimer = setInterval(function() {
            if (w.closed) {
                refresh_records();
                redraw();
                clearInterval(polltimer);
            }
        }, 500);

    }
}
function check_if_empty(obj) {
    var ok = 0;
    for (var i = 0; i < obj.length; i++) {
        ok |= obj[i].length;
    }
    return (ok == 0);

}
function play_hard() {

    var s = 0;
    for (var i = 0; i < elements.length; i++) {
        s ^= elements[i].length;
    }
    //oh no? player wins.

    if (check_if_empty(elements)) {
        eval_game(1);
        return 0;
    }

    player_turn = 0;
    for (var i = 0; i < elements.length; i++) {
        for (j = 1; j <= elements[i].length; j++) {
            if ( ((s ^ elements[i].length) ^ (elements[i].length - j)) == 0 ) {
                elements[i].splice(elements[i].length - j, j) ;

                //player loses
                if (check_if_empty(elements)) {
                    eval_game(0);
                }
                return 0;
            }
        }
    }
    //selecting random stack
    var k;

    for (k = Math.floor(Math.random() * elements.length) ; elements[k].length == 0; ) {
        k = Math.floor(Math.random() * elements.length);
    }

    var how_many = Math.floor(Math.random() * elements[k].length + 1);
    var n = elements[k].length;
    elements[k].splice(n - how_many, how_many);

    return 0;

}

function play_easy() {
    if (check_if_empty(elements)) {
        eval_game(1);
        return 0;
    }
    player_turn = 0;
    var k;

    for (k = Math.floor(Math.random() * elements.length) ; elements[k].length == 0; ) {
        k = Math.floor(Math.random() * elements.length);
    }

    var how_many = Math.floor(Math.random() * elements[k].length + 1);
    var n = elements[k].length;
    elements[k].splice(n - how_many, how_many);

    if (check_if_empty(elements)) {
        eval_game(0);
    }
    return 0;
}
elem.addEventListener('click', function(event) {

    var x = event.pageX - elemLeft,
        y = event.pageY - elemTop;

    // Collision detection between clicked offset and element.

    if (player_turn == 1) {
        return 0;
    }
    for (var i = 0; i < elements.length; i++) {
        for (var j = 0; j < elements[i].length; j++) {

            var element = elements[i][j];
            if (element.inside(x, y)) {
                elements[i].splice(j, elements[i].length - j);
                player_turn = 1;
                if (MARKED_HARD) {
                    setTimeout(play_hard, 1000);
                } else {
                    setTimeout(play_easy, 1000);
                }
                return 0;
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

    //not having clicked start game before the other finishes
    if (!check_if_empty(elements)) {
        return 0;
    }
    STARTED_GAME = 1;
    MARKED_HARD = document.getElementById("marked_hard").checked;
    sessionStorage.start_time = Date.now();

    var selected_radius = 40;
    var x = selected_radius;
    var y = selected_radius;
    player_turn = 0;
    elements = [];

    for (var stack = 5; stack >= 1; stack--) {
        elements.push(new Array());
        for (var i = 1; i <= stack; i++) {
            elements[5 - stack].push(new Circle(2 * selected_radius * (6 - stack) , 2 * (6 - i) * selected_radius, selected_radius));
        }
    }
    setInterval(redraw,10);
}

function initialize_storage() {
    localStorage.setObject('records', null);
}
