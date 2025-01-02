cordova.define("com.superapp.dataplugin.DataTransport", function(require, exports, module) {
	exports.registerCallback = function(func) {
		callback = func;
	};

	exports.onJSONfromNative = function(json) {
		callback(json);
	};

});
