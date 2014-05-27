var turn = 0;

var container = [];

$(document).ready(function() {
	for (var i = 0; i < 3; i++) {
		var div = document.createElement("div");
		$(div).attr('class', 'lol');
		for (var j = 0; j < 3; j++) {
			var bt = document.createElement("button");
			bt.style.width="50px";
			bt.style.height="50px";
			$(bt).attr("id", "special");
			$(bt).text("?");

			container.push(bt);
			div.appendChild(bt);
		}
		document.body.appendChild(div);
		//nice one. next
	}
});

$(".lol #special").click(function() {
	if ($(this).text() != "?") {
		return ;
	}
	if (turn % 2) {
		$(this).text("X");
	} else {
		$(this).text("0");
	}
	turn += 1;
})
function get_sign(val) {
	if (val < 0) {
		return -1;
	} else {
		return 1;
	}
}
function eval_game() {

	//check on rows

	var X = new Array(3);
	var winner = 0;

	for (var i = 0; i < 3; i++) {
		var finished = 0;
		var cnt1 = 0;
		var cnt0 = 0;

		X[i] = 0;
		for (var j = 0; j < 3; j++) {
			var ret = $(container[i * 3 + j]).text();
			if (ret == 'X') {
				X[i] += 1;
			} else if (ret == '0') {
				X[i] -= 1;
			}
		}
	}
	for (var i = 0; i < 3; i++) {
		if (X[i] == 3 || X[i] == -3) {
			winner = get_sign(X[i]);
		}
	}
	//check on columns

	var Y = new Array(3);
	for (var col = 0; col < 3; col++) {
		var cnt1 = 0;
		var cnt0 = 0;

		Y[col] = 0;
		for (var row = 0; row < 3; row++) {
			var ret = $(container[row * 3 + col]).text();
			if (ret == 'X') {
				Y[col] += 1;
			} else if (ret == '0') {
				Y[col] -= 1;
			}
		}
	}
	console.log(Y);
	for (var col = 0; col < 3; ++col) {
		if (Y[col] == 3 || Y[col] == -3) {
			winner = get_sign(Y[col]);
		}
	}
	// first diagonal

	var primary = 0;

	for (var i = 0; i < 3; i++) {
		var ret = $(container[i * 3 + i]).text();
		if (ret == 'X') {
			primary += 1;
		} else if (ret == '0') {
			primary -= 1;
		}
	}
	if (primary == 3 || primary == -3) {
		winner = get_sign(primary);
	}
	var secondary = 0;
	for (var i = 0; i < 3; i++) {
		var ret = $(container[i * 3 + (3 - i - 1)]);
		if (ret == 'X') {
			secondary += 1;
		} else if (ret == '0') {
			secondary -= 1;
		}
	}
	if (secondary == 3 || secondary == -3) {
		winner = get_sign(secondary);
	}

	if (winner != 0) {
		clear_function(winner)
	}
}
ret_function = setInterval(eval_game, 1000);

function clear_function(winner) {
	clearInterval(ret_function);
	if (winner == 1) {
		alert("X wins")
	} else {
		alert("O wins");
	}
}