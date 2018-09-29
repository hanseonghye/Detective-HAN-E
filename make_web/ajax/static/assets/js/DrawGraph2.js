function DrawGraph2(G_result){

  var margin = {top: 20, right: 120, bottom: 20, left: 200};
    var width = 950 - margin.right - margin.left;
    var height = 800 - margin.top - margin.bottom;


     var tree = d3.layout.tree()
         .size([height,width]);


      /// 이 부분 새로
     var diagonal = d3.svg.diagonal()
         .projection(function (d) {
             return [d.y*2, d.x];
         });

    /// 이 부분 새로
     var svg = d3.select("#div1").append("svg")
     .attr('width', 1280)
     .attr('height',1280)
     .append("g")
     .attr("class", "overlay")
     .attr("transform", "rotate(90,600,250)");


     var root = G_result,
         nodes = tree.nodes(root).reverse(),
         links = tree.links(nodes);

     var link = svg.selectAll(".link")
         .data(links)
         .enter()
         .append("g")
         .attr("class", "link");

     link.append("path")
         .attr("fill", "none")
         .style("stroke", function(d) {
          if (d.target.rule == undefined) return "none";
          else if (d.target.rule >= 85) return "#EB0000";
          else if (d.target.rule >= 60) return "#FFBEBE";
          else return "#FAC87D";})
         .attr("stroke-width", "3px")
         .attr("d", diagonal);



    /// 이 부분 새로
     link.append("text")
         .style("font", "20px sans-serif")
         .style("fill", "black")
           .style("stroke","none")
         .attr("transform", function(d) {
             return "translate(" +
                 ((d.source.y + d.target.y) + 30) + "," +
                 ((d.source.x + d.target.x)/2) + ")";
         })
         .attr("dy", ".30em")
         .attr("text-anchor", "middle")
         .text(function(d) {
              return  d.target.rule;
         });

    /// 이 부분 새로
     var node = svg.selectAll(".node")
         .data(nodes)
         .enter()
         .append("g")
         .attr("class", "node")
         .attr("transform", function (d) {
             return "translate(" + d.y *2+ "," + d.x + ")";
         })
         .on("mouseover", function(d) {
          var g = d3.select(this); // The node
          // The class is used to remove the additional text later
          var info = g.append('text')
             .classed('info', true)
             .attr('x', 0)
             .attr('y', -10)
	.style("font", "20px sans-serif")        
	.style("text-anchor", "middle" )
	.call(wrap, 150)
             .text(function (d) {
		return  d.name;
	});
      })
      .on("mouseout", function() {
          // Remove the info text on mouse out.
          d3.select(this).select('text.info').remove()
        });
    ;

     node.append("circle")
         .attr("r", function(d){
          if (d.name == null) return 0;
          else return 4.5;
       });

    /// 이 부분 새로
 function wrap(text, width) {
     text.each(function () {
         var text = d3.select(this),
             words = text.text().split("").reverse(),
             word,
             line = [],
             lineNumber = 0,
             lineHeight = 1.1, // ems
             x = text.attr('dx'),
             y = text.attr('y'),
             dy = 0, //parseFloat(text.attr('dy')),
             tspan = text.text(null)
                 .append('tspan')
                 .attr('x', x)
                 .attr('y', y-10)
                 .attr('dy', dy + 'em');
         while (word = words.pop()) {
             line.push(word);
             tspan.text(line.join(''));
             if (tspan.node().getComputedTextLength() > width) {
                 line.pop();
                 tspan.text(line.join(''));
                 line = [word];
                 tspan = text.append('tspan')
                     .attr('x', x)
                     .attr('y', y)
                .attr('dy', lineHeight + dy + 'em')
                .text(word);
             }
         }
     });
   }


   //  var treeData=G_result;
   //  var width = 400,
   //  height = 300;
   //
   //  var tree = d3.layout.tree()
   //          .size([height, width - 160]);
   //
   //  var diagonal = d3.svg.diagonal()
   //              .projection(function (d) {
   //                  return [d.y, d.x];
   //              });
   //
   //  var svg = d3.select("#div1").append("svg")
   //            .attr("width", $(document).width())
   //            .attr("height", $(document).height())
   //            .append("g")
   //            .attr("transform", "translate(100,0)");
   //
   //  var root = treeData,
   //             nodes = tree.nodes(root),
   //             links = tree.links(nodes);
   //
   // var link = svg.selectAll(".link")
   //        .data(links)
   //        .enter()
   //        .append("g")
   //        .attr("class", "link")
   //        .on('click', click);
   //
   //  link.append("path")
   //      .attr("fill", "none")
   //      .style("stroke", function(d) {
   //               if (d.target.rule == undefined) return "none";
   //               else if (d.target.rule >= 85) return "#EB0000";
   //               else if (d.target.rule >= 60) return "#FFBEBE";
   //               else return "#FAC87D";})
   //
   //      .attr("stroke-width", "2px")
   //      .attr("d", diagonal);
   //
   //  link.append("text")
   //      .attr("font-family", "Arial, Helvetica, sans-serif")
   //      .attr("fill", "Black")
   //      .style("font", "normal 12px Arial")
   //
   //      .attr("transform", function(d) {
   //            return "translate(" +
   //                  ((d.source.y + d.target.y)/2) + "," +
   //                  ((d.source.x + d.target.x)/2) + ")";
   //            })
   //      .attr("dy", ".50em")
   //      .attr("text-anchor", "middle")
   //      .on("click",function(d){
   //          var where_dir=dir;
   //          if (d.target.rule != undefined){
   //             file1 = d.target.name;
   //             file2 = d.source.name;
   //           }
   //         window.open('show_code?file1='+file1+'&file2='+file2+'&where_dir='+where_dir, '_blank');
   //       })
   //      .text(function(d) {
   //             return  d.target.rule;
   //        });
   //
   //
   //          var node = svg.selectAll(".node")
   //              .data(nodes)
   //              .enter()
   //              .append("g")
   //              .attr("class", "node")
   //              .attr("transform", function (d) {
   //                  return "translate(" + d.y + "," + d.x + ")";
   //              })
   //
   //
   //          node.append("circle")
   //              .attr("r", function(d){
   //               if (d.name == null) return 0;
   //               else return 2.5;
   //            });
   //
   //          node.append("text")
   //              .attr("dx", function (d) {
   //                  return d.children ? -8 : 8;
   //              })
   //              .attr("dy", 20)
   //
   //              .style("text-anchor", function (d) {
   //                  return d.children ? "end" : "start";
   //              })
   //              .text(function (d) {
   //               return  d.name;
   //              });
   //


}

function click(d) {
   if (d3.event.defaultPrevented) return; // click suppressed
   var where_dir=dir;

   if (d.target.rule != undefined){
      file1 = d.target.name;
      file2 = d.source.name;
    }

  window.open('show_code?file1='+file1+'&file2='+file2+'&where_dir='+where_dir, '_blank');
}
