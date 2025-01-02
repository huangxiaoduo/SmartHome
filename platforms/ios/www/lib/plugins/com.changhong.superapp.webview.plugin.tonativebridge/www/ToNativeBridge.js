cordova.define("com.changhong.superapp.webview.plugin.tonativebridge.ToNativeBridge", function(require, exports, module) { var exec = require('cordova/exec');

exports.sendDataToNative = function(jsn, success, error) {
    exec(success, error, "ToNativeBridge", "sendDataToNative", [jsn]);
};
exports.initData = function(jsn,success, error){
	 exec(success, error, "ToNativeBridge", "initData", jsn);
//	 var a;
//	 a = window.superWebBridge.onWebInit();
//	 window.superWebBridge.onWebInit2(a);
};

});
