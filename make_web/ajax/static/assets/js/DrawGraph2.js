function DrawGraph2(G_result){
    var treeData=G_result;
    var width = 400,
    height = 300;

    var tree = d3.layout.tree()
            .size([height, width - 160]);

    var diagonal = d3.svg.diagonal()
                .projection(function (d) {
                    return [d.y, d.x];
                });

    var svg = d3.select("#div1").append("svg")
              .attr("width", $(document).width())
              .attr("height", $(document).height())
              .append("g")
              .attr("transform", "translate(100,0)");

    var root = treeData,
               nodes = tree.nodes(root),
               links = tree.links(nodes);

   var link = svg.selectAll(".link")
          .data(links)
          .enter()
          .append("g")
          .attr("class", "link")
          .on('click', click);

    link.append("path")
        .attr("fill", "none")
        .style("stroke", function(d) {
                 if (d.target.rule == undefined) return "none";
                 else if (d.target.rule >= 85) return "#EB0000";
                 else if (d.target.rule >= 60) return "#FFBEBE";
                 else return "#FAC87D";})

        .attr("stroke-width", "2px")
        .attr("d", diagonal);

    link.append("text")
        .attr("font-family", "Arial, Helvetica, sans-serif")
        .attr("fill", "Black")
        .style("font", "normal 12px Arial")

        .attr("transform", function(d) {
              return "translate(" +
                    ((d.source.y + d.target.y)/2) + "," +
                    ((d.source.x + d.target.x)/2) + ")";
              })
        .attr("dy", ".50em")
        .attr("text-anchor", "middle")
        .on("click",function(d){
            var where_dir=dir;
            if (d.target.rule != undefined){
               file1 = d.target.name;
               file2 = d.source.name;
             }
           window.open('show_code?file1='+file1+'&file2='+file2+'&where_dir='+where_dir, '_blank');
         })
        .text(function(d) {
               return  d.target.rule;
          });


            var node = svg.selectAll(".node")
                .data(nodes)
                .enter()
                .append("g")
                .attr("class", "node")
                .attr("transform", function (d) {
                    return "translate(" + d.y + "," + d.x + ")";
                })


            node.append("circle")
                .attr("r", function(d){
                 if (d.name == null) return 0;
                 else return 2.5;
              });

            node.append("text")
                .attr("dx", function (d) {
                    return d.children ? -8 : 8;
                })
                .attr("dy", 20)

                .style("text-anchor", function (d) {
                    return d.children ? "end" : "start";
                })
                .text(function (d) {
                 return  d.name;
                });



}

function click(d) {
   if (d3.event.defaultPrevented) return; // click suppressed
   var where_dir=dir;
   console.log("click")

   if (d.target.rule != undefined){
      file1 = d.target.name;
      file2 = d.source.name;
    }

  window.open('show_code?file1='+file1+'&file2='+file2+'&where_dir='+where_dir, '_blank');
}
