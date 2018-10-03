function DrawGraph2(G_result) {

    var margin = {top: 20, right: 120, bottom: 20, left: 200};
    var width = 950 - margin.right - margin.left;
    var height = 800 - margin.top - margin.bottom;

    //var file1, file2

    var tree = d3.layout.tree()
        .size([height, width]);


    /// 이 부분 새로
    var diagonal = d3.svg.diagonal()
        .projection(function (d) {
            return [d.y * 3 / 2, d.x];
        });

    /// 이 부분 새로
    var svg = d3.select("#div1").append("svg")
        .attr('width', 1280)
        .attr('height', 1280)
        .append("g")
        .attr("class", "overlay")
        .attr("transform", "rotate(90,550,300)");

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
        .style("stroke", function (d) {
            if (d.target.rule == undefined) return "none";
            else if (d.target.rule >= 85) return "#EB0000";
            else if (d.target.rule >= 60) return "#FFBEBE";
            else return "#FAC87D";
        })
        .attr("stroke-width", "8px")
        .attr("d", diagonal);


    /// 이 부분 새로
    link.append("text")
        .style("cursor", "pointer")
        .style("font", "20px sans-serif")
        .style("fill", "black")
        .style("stroke", "none")
        .attr("transform", function (d) {
            return "translate(" +
                ((d.source.y + d.target.y) / 4 * 3 + 30) + "," +
                ((d.source.x + d.target.x) / 2) + ")";
        })
        .attr("dy", ".30em")
        .attr("text-anchor", "middle")
        .on("click", function (d) {
            var where_dir = dir;
            if (d.target.rule != undefined) {
                var file1 = d.target.name;
                var file2 = d.source.name;
            }
            window.open('show_code?file1=' + file1 + '&file2=' + file2 + '&where_dir=' + where_dir, '_blank');
        })
        .text(function (d) {
            return d.target.rule;
        });

    /// 이 부분 새로
    var node = svg.selectAll(".node")
        .data(nodes)
        .enter()
        .append("g")
        .attr("class", "node")
        .attr("transform", function (d) {
            return "translate(" + d.y * 3 / 2 + "," + d.x + ")";
        })
        .on("mouseover", function (d) {
            var g = d3.select(this); // The node
            // The class is used to remove the additional text later
            var info = g.append('text')
                .classed('info', true)
                .attr('x', 0)
                .attr('y', -10)
                .style("font", "20px sans-serif")
                .style("text-anchor", "middle")
                .call(wrap, 150)
                .text(function (d) {
                    return d.name;
                });
        })
        .on("mouseout", function () {
            // Remove the info text on mouse out.
            d3.select(this).select('text.info').remove()
        });
    ;

    node.append("circle")
        .attr("r", function (d) {
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
                    .attr('y', y - 10)
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
}