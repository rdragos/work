
var start_time, end_time, time_spent;


function submit_on_enter(e) {
    var enterKey = 13;
    var code = e.keyCode ? e.keyCode : e.which;
    if (code == enterKey) {
        form_click();
    }
}
function form_click() {
    var input = document.getElementById("winner_form");
    var i_text = input.value;
    // time spent in seconds

    if (i_text == "") {
        alert("Please Enter a valid name");
    } else {

    	var records = localStorage.getObject('records');
        if (records == null) {
            records = [];
        }
        records.push({
            'person_name': i_text,
            'spent_time': time_spent
        })
        localStorage.setObject('records', records);
        document.write("Congratulations on a new record!");
        setTimeout(function() {
            window.close();
        }, 1000)
    }
}
function boot_body() {
	start_time = sessionStorage.start_time;
	end_time = sessionStorage.end_time;

	time_spent = (end_time - start_time) / 1000;

	document.getElementById("score").innerHTML="Game ended in " + time_spent+ " seconds";

}