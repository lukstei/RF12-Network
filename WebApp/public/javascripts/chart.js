  $(function() {
    new Highcharts.Chart({
      chart: {
        renderTo: "chart"
      },
      title: {
        text: "Messung"
      },
      xAxis: {
        type: "datetime"
      },
      yAxis: {
        title: {
		  text: "Einheit"
        }
      },
      tooltip: {
        formatter: function() {
          return Highcharts.dateFormat("%B %e, %Y", this.x) + ': ' +
            "" + Highcharts.numberFormat(this.y, 2);
        }
      },
	  series: [
	  {
		name: "Messdaten",
		data: [ 1, 2, 3, 4, 5, 10, 20 ]
	  }

	  ]
    });
  });