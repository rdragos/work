var total = 0;


$("#movie,#day").on("click", function() {
    $.each($('#place li.' + settings.selectingSeatCss), function (index, value) {
        $(this).toggleClass(settings.selectingSeatCss);
    });
});
function cost_function(delta) {
    var movie = parseInt($("#movie").val());
    var day = parseInt($("#day").val());
    return (settings.rows * settings.cols - delta + 1) * movie * day * 10;

}
$('.' + settings.seatCss).click(function () {
    if ($(this).hasClass(settings.selectedSeatCss)){
        alert('This seat is already reserved');
    }
    else{
        var price = parseInt($(this).find('a').text());
        console.log(cost_function(price));
        price = cost_function(price);
        if ($(this).hasClass(settings.selectingSeatCss)) {
            total -= price;
        }
        else {
            total += price;
        }
        $("#total_seat_price p").text("Total Price: " + total + " $");

        $(this).toggleClass(settings.selectingSeatCss);
    }
});

$('.' + settings.seatCss).hover(
    function() {
        var price = parseInt($(this).find('a').text());
        price = cost_function(price);
        $("#seat_price p").text("Price: " + price.toString() + " $");
    },
    function() {
        $("#seat_price p").text("Price: 0 $");
    }
);