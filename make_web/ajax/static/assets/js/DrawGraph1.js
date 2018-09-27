function drawBarG(d){

  var data = d;
  var chartWidth       = 400,
      barHeight        = 35,
      groupHeight      = barHeight * data.series.length,
      gapBetweenGroups = 10,
      spaceForLabels   = 400,
      spaceForLegend   = 150;

  // Zip the series data together (first values, second values, etc.)
  var zippedData = [];
  for (var i=0; i<data.labels.length; i++) {
    for (var j=0; j<data.series.length; j++) {
      zippedData.push(data.series[j].values[i]);
    }
  }

  // Color scale
  var color = d3.scale.category20();
  var chartHeight = barHeight * zippedData.length + gapBetweenGroups * data.labels.length;

  var x = d3.scale.linear()
      .domain([0, d3.max(zippedData)])
      .range([0, chartWidth]);

  var y = d3.scale.linear()
      .range([chartHeight + gapBetweenGroups, 0]);

  var yAxis = d3.svg.axis()
      .scale(y)
      .tickFormat('')
      .tickSize(0)
      .orient("left");

  // Specify the chart area and dimensions
  var chart = d3.select(".chart")
      .attr("width", spaceForLabels + chartWidth + spaceForLegend)
      .attr("height", chartHeight);

  // Create bars
  var bar = chart.selectAll("g")
      .data(zippedData)
      .enter().append("g")
      .attr("transform", function(d, i) {
        return "translate(" + spaceForLabels + "," + (i * barHeight + gapBetweenGroups * (0.5 + Math.floor(i/data.series.length))) + ")";
      });

  //Create rectangles of the correct width
  bar.append("rect")
      .attr("fill", function(d,i) {
          if ( data.series[0].values[i] >= 85 ) return "#FE2E2E";
          else if ( data.series[0].values[i] >=60 ) return "#FD7442";
          return "#FFC170"
        })// return color(i % data.series.length); })
      .attr("class", "bar")
      .attr("width", x)
      .attr("height", barHeight - 1)
      .on("click",function(d,i){
          var click=data.labels[i];
          var click_bar=click.split(',');
          var file1=click_bar[0]
          var file2=click_bar[1]
          var where_dir=dir

          window.open('show_code?file1='+file1+'&file2='+file2+'&where_dir='+where_dir, '_blank');
      })
      .attr("file",function(d,i){
          return data.labels[i];
      })


  // Add text label in bar
  bar.append("text")
      .attr("x", function(d) { return x(d) - 3; })
      .attr("y", barHeight / 2)
      .attr("fill", "red")
      .attr("dy", ".35em")
      .text(function(d) { return d; });

  // Draw labels
  bar.append("text")
      .attr("class", "label")
      .attr("x", function(d) { return - 10; })
      .attr("y", groupHeight / 2)
      .attr("dy", ".35em")
      .text(function(d,i) {
        if (i % data.series.length === 0)
          return data.labels[Math.floor(i/data.series.length)];
        else
          return ""});

  chart.append("g")
        .attr("class", "y axis")
        .attr("transform", "translate(" + spaceForLabels + ", " + -gapBetweenGroups/2 + ")")
        .call(yAxis);

  // Draw legend
  var legendRectSize = 18,
      legendSpacing  = 4;

  var legend = chart.selectAll('.legend')
      .data(data.series)
      .enter()
      .append('g')
      .attr('transform', function (d, i) {
          var height = legendRectSize + legendSpacing;
          var offset = -gapBetweenGroups/2;
          var horz = spaceForLabels + chartWidth + 40 - legendRectSize;
          var vert = i * height - offset;
          return 'translate(' + horz + ',' + vert + ')';
      });
}
