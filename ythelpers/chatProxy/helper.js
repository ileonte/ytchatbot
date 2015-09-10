(function(jQuery) {
	"use strict";

	var $ = jQuery.noConflict(true);

	window.ytChatHelper = function() {
		var _ = new QWebChannel(qt.webChannelTransport, function(channel) {
			var chatProxy = channel.objects.chatProxy;

			if (!location.href.match(/https?:\/\/www\.youtube\.com\/live_chat\?v=/)) {
				chatProxy.log("Redirecting to youtube chat from " + location.href);
				location.href = "https://www.youtube.com/live_chat?v=a9soTa1UA2c";
				return;
			}

			$("#comments-scroller #all-comments").bind("DOMNodeInserted", function(e) {
				var qe = $(e.target);
				var msg;

				if (qe.hasClass("removed")) {
					msg = {
						"id": qe.attr('id'),
						"removed": true
					};
				} else {
					msg = {
						"id": qe.attr('id'),
						"removed": false,
						"author": qe.children(".content").children(".byline").children(".author").children(".yt-user-name").text(),
						"message": qe.children(".content").children(".comment-text").text()
					};
				}
				chatProxy.chatMessage(JSON.stringify(msg));
			});
		});
	}
})(jQuery);
