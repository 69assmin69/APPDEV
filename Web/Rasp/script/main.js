var updated = false;
var halted = false;

var xVal = 0;
var yNew = [];
var yOld = [];

var updateInterval = 1001;
var dataLength = 500;

var data = [];
var chart;
var play = false;

function gebi(x) {return document.getElementById(x);}

function updateChart(yNew,ID) {
	if (play && (typeof ID != "undefined")) {
		var audio = new Audio('data/data_'+ID+'.wav');
		audio.load()
		audio.play();
	}
	var yVal;
	for (var i = 0; i < yNew.length; i++) {
		yVal = yNew[i];
		data.push({
			x: xVal,
			y: yVal
		});
		xVal++;
		if (data.length > dataLength)
			data.shift();
	};
	chart.render();
};

function compare_array(a,b) {	//Return true if they are equal
	var diff = 0.0;
	if (a.length!=b.length) return false;
	for(i in a) {
		diff+=Math.abs(a[i]-b[i]);
		if (diff>0.1) return false;
	}
	return true;
}

function Update() {
	updated = false;
	halted = false;
	$.get('getlastest.php',
		function(data) {
	        updated = true;
	        yNew = data.split("\n");
	        if (data=="offline") {
	        	Offline();
	        	return;
	        } else {
	        	Online()
	        }
	        var ID = yNew[yNew.length-1];
	        yNew.pop();
	        for (x in yNew)
	        	yNew[x] = Number(yNew[x]);
	        if (!compare_array(yNew,yOld)) {
	        	yOld = yNew.slice();
			    updateChart(yNew,ID);
			}
		}
	);
}

function Online() {
	gebi("status").innerHTML = "ONLINE";
	gebi("status").style.color = "green";	
}
function Offline() {
	gebi("status").innerHTML = "OFFLINE";
	gebi("status").style.color = "grey";	
}


function toggle_play(x) {
	play = !play;
	if (play)
		x.value = "Mute";
	else
		x.value = "Play"
}

function init() {
	chart = new CanvasJS.Chart("chartContainer",{
		title :{
			text: "Live sound"
		},
		data: [{
			type: "line",
			dataPoints: data
		}]
	});
	for(var i=0;i<dataLength;i++)
		updateChart([0]);
	setInterval(function(){Update()}, updateInterval);
}

window.onload = init