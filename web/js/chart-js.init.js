/*
(function(){
    var t;
    function size(animate){
        if (animate == undefined){
            animate = false;
        }
        clearTimeout(t);
        t = setTimeout(function(){
            $("canvas").each(function(i,el){
                $(el).attr({
                    "width":$(el).parent().width(),
                    "height":$(el).parent().outerHeight()
                });
            });
            redraw(animate);
            var m = 0;
            $(".chartJS").height("");
            $(".chartJS").each(function(i,el){ m = Math.max(m,$(el).height()); });
            $(".chartJS").height(m);
        }, 30);
    }
    $(window).on('resize', function(){ size(false); });


    function redraw(animation){
        var options = {};
        if (!animation){
            options.animation = false;
        } else {
            options.animation = true;
        }


        var barChartData = {
            labels : ["January","February","March","April","May","June","July"],
            datasets : [
                {
                    fillColor : "#E67A77",
                    strokeColor : "#E67A77",
                    data : [65,59,90,81,56,55,40]
                },
                {
                    fillColor : "#79D1CF",
                    strokeColor : "#79D1CF",
                    data : [28,48,40,19,96,27,100]
                }
            ]

        }

        var myLine = new Chart(document.getElementById("bar-chart-js").getContext("2d")).Bar(barChartData);


        var Linedata = {
            labels : ["January","February","March","April","May","June","July"],
            datasets : [
                {
                    fillColor : "#E67A77",
                    strokeColor : "#E67A77",
                    pointColor : "#E67A77",
                    pointStrokeColor : "#fff",
                    data : [100,159,190,281,156,155,140]
                },
                {
                    fillColor : "#79D1CF",
                    strokeColor : "#79D1CF",
                    pointColor : "#79D1CF",
                    pointStrokeColor : "#fff",
                    data : [65,59,90,181,56,55,40]
                },
                {
                    fillColor : "#D9DD81",
                    strokeColor : "#D9DD81",
                    pointColor : "#D9DD81",
                    pointStrokeColor : "#fff",
                    data : [28,48,40,19,96,27,100]
                }

            ]
        }
        var myLineChart = new Chart(document.getElementById("line-chart-js").getContext("2d")).Line(Linedata);


        var pieData = [
            {
                value: 30,
                color:"#E67A77"
            },
            {
                value : 50,
                color : "#D9DD81"
            },
            {
                value : 100,
                color : "#79D1CF"
            }

        ];

        var myPie = new Chart(document.getElementById("pie-chart-js").getContext("2d")).Pie(pieData);



        var donutData = [
            {
                value: 30,
                color:"#E67A77"
            },
            {
                value : 50,
                color : "#D9DD81"
            },
            {
                value : 100,
                color : "#79D1CF"
            },
            {
                value : 40,
                color : "#95D7BB"
            },
            {
                value : 120,
                color : "#4D5360"
            }

        ]
        var myDonut = new Chart(document.getElementById("donut-chart-js").getContext("2d")).Doughnut(donutData);
    }




    size(true);

}());

$('#menu-toggle-view li a').click(function() {
    $(this).parent().siblings().find('a').removeClass('current');
    $(this).addClass('current');
});

$('#btn-mem-info').click(function () {
    $('#mem-info-view').siblings().css('display', 'none');
    $('#mem-info-view').css('display', 'block');
});
$('#btn-cpu-info').click(function () {
    $('#cpu-info-view').siblings().css('display', 'none');
    $('#cpu-info-view').css('display', 'block');
});
*/


(function () {
    var t;
    var diskInfoChart;
    var networkInfoChart;
    var serverId = getCookie("serverId");

    var chartInitData = {
        labels: ["1hour", "45min", "30min", "15min", "0"],
        datasets: [
            {
                label: 'CPU Info',
                fillColor: 'rgba(0,0,0,0)',
                strokeColor: '#FF5A5E',
                pointColor: '#FF5A5E',
                pointStrokeColor: '#fff',
                pointHighlightFill: '#fff',
                pointHighlightStroke: '#FF5A5E',
                data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            },
            {
                label: 'CPU Info',
                fillColor: 'rgba(0,0,0,0)',
                strokeColor: '#1FB5AD',
                pointColor: '#1FB5AD',
                pointStrokeColor: '#fff',
                pointHighlightFill: '#fff',
                pointHighlightStroke: '#1FB5AD',
                data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            }
        ]
    };

    var lineChartOptions = {
        pointDotRadius : 0,
        pointDotStrokeWidth : 0,
        pointHitDetectionRadius : 0,
        scaleLineWidth:1
    };

    function resizeLineChart(animate){
        if (animate == undefined){
            animate = false;
        }
        clearTimeout(t);
        t = setTimeout(function(){
            $(".history-panel canvas").each(function(i,el){
                $(el).attr({
                    "width":$(el).parent().width(),
                    "height":$(el).parent().height()
                });
            });
            redrawLineChart(animate);
        }, 30);
    }

    function redrawLineChart(animation) {
        if (!animation) {
            lineChartOptions.animation = false;
        } else {
            lineChartOptions.animation = true;
        }
        var ctx = $('.disk-info-chart').get(0).getContext("2d");
        diskInfoChart = new Chart(ctx).Line(chartInitData, lineChartOptions);
        ctx = $('.network-info-chart').get(0).getContext("2d");
        networkInfoChart = new Chart(ctx).Line(chartInitData, lineChartOptions);
    }

    resizeLineChart(false);
    $(window).on('resize', function(){ resizeLineChart(false); });
})();

(function () {
    var t;
    var cpuHistoryChart;
    var memHistoryChart;
    var diskHistoryChart;
    var chartInitData = {
        labels: ["9天前", "8天前", "7天前", "6天前", "5天前", "4天前", "3天前", "2天前", "1天前"],
        datasets: [
            {
                label: 'CPU Info',
                fillColor: 'rgba(0,0,0,0)',
                strokeColor: '#1FB5AD',
                pointColor: '#1FB5AD',
                pointStrokeColor: '#fff',
                pointHighlightFill: '#fff',
                pointHighlightStroke: '#1FB5AD',
                data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
            }
        ]
    };

    var lineChartOptions = {
        pointDotRadius : 4,
        pointDotStrokeWidth : 2,
        pointHitDetectionRadius : 8,
        scaleLineWidth:1
    };

    function resizeLineChart(animate){
        if (animate == undefined){
            animate = false;
        }
        clearTimeout(t);
        t = setTimeout(function(){
            $(".history-panel canvas").each(function(i,el){
                $(el).attr({
                    "width":$(el).parent().width(),
                    "height":$(el).parent().height()
                });
            });
            redrawLineChart(animate);
        }, 30);
    }

    function redrawLineChart(animation) {
        if (!animation) {
            lineChartOptions.animation = false;
        } else {
            lineChartOptions.animation = true;
        }
        var ctx = $('.cpu-history-info').get(0).getContext("2d");
        cpuHistoryChart = new Chart(ctx).Line(chartInitData, lineChartOptions);
        ctx = $('.mem-history-info').get(0).getContext("2d");
        memHistoryChart = new Chart(ctx).Line(chartInitData, lineChartOptions);
        ctx = $('.disk-history-info').get(0).getContext("2d");
        memHistoryChart = new Chart(ctx).Line(chartInitData, lineChartOptions);
    }
    nReloads = 0;
    function updateHistoryData() {
        nReloads++;
        for (var x = 0; x < 10; x += 1) {
            var v = (5*
                nReloads + x*36) % 360;
            //cpuHistoryChart.datasets[0].points[x].value = (Math.sin(Math.PI * v / 180)+1).toFixed(4)*50;
        }
        //cpuHistoryChart.update();
    }

    resizeLineChart(false);
    $(document).ready(function() {
        updateHistoryData();
    });
    $(window).on('resize', function(){ resizeLineChart(false); });
})();
