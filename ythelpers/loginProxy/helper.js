(function(jQuery) {
	"use strict";

	var YT_DOM_LoginClass = 'signin-container';

	var $ = jQuery.noConflict(true);

	function checkYoutubeLogin() {
		if (location.host.match(/.*\.youtube\..*/)) {
			if (document.getElementsByClassName(YT_DOM_LoginClass).length > 0)
				return false;
			return true;
		}
		return false;
	}

	function loginValidate(loginProxy) {
		if (checkYoutubeLogin()) {
			loginProxy.log("NOW LOGGED IN!");
			loginProxy.signalLoginStatus(true);
			return;
		} else {
			loginProxy.log("Not logged in, redirecting to login page");
			location.href = "https://accounts.google.com/ServiceLogin?uilel=3&service=youtube&passive=true&hl=en&continue=https%3A%2F%2Fwww.youtube.com%2Fsignin%3Faction_handle_signin%3Dtrue%26feature%3Dsign_in_button%26app%3Ddesktop%26hl%3Den%26next%3D%252F#identifier";
			return;
		}
	}

	window.ytLoginHelper = function(operation) {
		var _ = new QWebChannel(qt.webChannelTransport, function(channel) {
			var loginProxy = channel.objects.loginProxy;

			if (operation == "login") {
				if (location.host.match(/\.youtube\.com/)) {
					loginValidate(loginProxy);
					return;
				} else if (location.host.match(/\.google\.com/)) {
					loginProxy.getUrlHost(function(host) {
						loginProxy.log(">> location.host = " + location.host);
						loginProxy.log(">> host          = " + host);
						if (host.match(/\.google\.com/)) {
							loginProxy.log("On some google page, assuming login " + location.href);
							loginProxy.signalNeedsLogin();
						}
						if (host.match(/\.youtube\.com/)) {
							loginValidate(loginProxy);
							return;
						}
					});
				} else {
					loginProxy.log("Redirecting to youtube");
					location.href = "https://www.youtube.com";
					return;
				}
				return;
			}

			if (operation == "testLogin") {
				if (location.host.match(/\.youtube\.com/)) {
					if (checkYoutubeLogin())
						loginProxy.signalLoginStatus(true);
	                        else
						loginProxy.signalLoginStatus(false);
	                  } else {
					loginProxy.log("Redirecting to youtube");
					location.href = "https://www.youtube.com";
					return;
	                  }
	                  return;
	            }

			if (operation == "logout") {
				if (location.host.match(/\.youtube\.com/)) {
					if (checkYoutubeLogin())
						loginProxy.signalLoginStatus(true);
	                        else
						loginProxy.signalLoginStatus(false);
	                  } else {
					loginProxy.log("Redirecting to youtube");
					location.href = "https://www.youtube.com/logout";
					return;
	                  }
	                  return;
	            }
		});
	}
})(jQuery);
