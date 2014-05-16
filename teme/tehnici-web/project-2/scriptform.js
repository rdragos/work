function form_click() {
    var input = document.getElementById("winner_form");
    var i_text = input.value;

    start_time = sessionStorage.start_time

    end_time = Date.now();
    console.log(start_time);
    console.log(end_time);
    if (i_text == "") {
        alert("Please Enter a valid name");
    } else {

    }
}