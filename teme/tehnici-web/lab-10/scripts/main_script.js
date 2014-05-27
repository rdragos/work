var settings = {
     rows: 5,
     cols: 15,
     rowCssPrefix: 'row-',
     colCssPrefix: 'col-',
     seatWidth: 35,
     seatHeight: 35,
     seatCss: 'seat',
     selectedSeatCss: 'selectedSeat',
     selectingSeatCss: 'selectingSeat'
 };

var init = function (reservedSeat) {
      var str = [], seatNo, className;
      for (i = 0; i < settings.rows; i++) {
          for (j = 0; j < settings.cols; j++) {
              seatNo = (i + j * settings.rows + 1);
              className = settings.seatCss + ' ' + settings.rowCssPrefix + i.toString() + ' ' + settings.colCssPrefix + j.toString();
              str.push('<li class="' + className + '"' +
                        'style="top:' + (i * settings.seatHeight).toString() + 'px;left:' + (j * settings.seatWidth).toString() + 'px">' +
                        '<a title="' + seatNo + '">' + seatNo + '</a>' +
                        '</li>');
          }
      }
      $('#place').html(str.join(''));
  };

init();
