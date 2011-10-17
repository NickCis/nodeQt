
# nodeQt 

	by NickCis (http://twitter.com/NickCis) & Alvarez Tomas (https://github.com/TAlvarez)
	nodeQt is a Qt implementation for Javascript, in-progress right now, which aims to provide a simple way to create guis.

## Installation

	git clone git://github.com/NickCis/nodeQt.git
	node-waf configure build

Tested in Qt 4.7

## Basic example

	var nodeQt = require('./build/Release/nodeQt');

	process.nextTick(function() {
		var qApp = new nodeQt.Application();
		var win = new nodeQt.Widget();
		win.resize(200,200);
		var button = new nodeQt.PushButton('Hello World', win);
		button.resize(200,50);
		win.show();
		qApp.exec();
	});

## Versions

Tested with:

	- node 0.5.9
	- Qt 4.7.0

## TODO
	Currently the implementation only has the posibility of creating a QApplication, a QWidget (window) and put a QPushButton in the window. Further development is needed.

	It's planned to make it async. Add more widgets, and support signals.

## License

(The MIT License)

Copyright (c) 2011 NickCis & TAlvarez

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
