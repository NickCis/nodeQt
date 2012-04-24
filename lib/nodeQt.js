(function() {
	var nodeQt = require('../build/Release/nodeQt');

	nodeQt.Application.prototype.initialize = function(num) {
		var self = this,
			nextTickFunct = function() {
				self.processEvents();
				process.nextTick(nextTickFunct);
			};
		if (num === 0)
			process.nextTick(function() {
				nextTickFunct();
			});
		else {
			num = (isNaN(num) ) ? 1 : num;
			nextTickFunct = null;
			setInterval(function() {self.processEvents();}, num);
		}
	};
	module.exports = nodeQt;
})(this);
