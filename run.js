//var nodeQt = require('./build/Release/nodeQt');
console.log('aaa');
var nodeQt = require('./lib/nodeQt');
console.log('aaa');

process.nextTick(function() {
	var qApp = new nodeQt.Application();
	var win = new nodeQt.Widget();
	win.resize(200,200);

	for (key in nodeQt)
		console.log(key);
	var button = new nodeQt.PushButton('Hello World', win);
	button.resize(200,50);

	button.ConnectClicked(function() {
		var a = Math.random() *500,
			b = Math.random() *500;
		console.log(" %d x %d ", a, b);
		win.resize(a, b);
	});

	win.show();
	qApp.initialize();

/*	setInterval(function() {
		qApp.processEvents();
	}, 1);*/
//	qApp.exec();
});
