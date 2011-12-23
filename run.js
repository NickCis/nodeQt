var nodeQt = require('./build/Release/nodeQt');
setInterval(function(){console.log('asd');}, 100);
process.nextTick(function() {
	var qApp = new nodeQt.Application(function() {
		console.log('asd');
	});
//	var win = new nodeQt.Widget();
//	win.resize(200,200);
//	var button = new nodeQt.PushButton('Hello World', win);
//	button.resize(200,50);
//	win.show();
});
