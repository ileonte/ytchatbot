(function(jQuery) {
	"use strict";

	var $ = jQuery.noConflict(true);

	window.ytChatHelper = function() {
		var _ = new QWebChannel(qt.webChannelTransport, function(channel) {
			var chatProxy = channel.objects.chatProxy;

			if (!location.href.match(/https?:\/\/www\.youtube\.com\/live_chat\?v=/)) {
				chatProxy.log("Redirecting to youtube chat from " + location.href);
				location.href = "https://www.youtube.com/live_chat?v=QvCzql17aoQ";
				return;
			}

			var chatContainer = $("#comments-scroller #all-comments");
			console.log(chatContainer);
			var chatMessages = chatContainer.children(".comment");
			console.log(chatMessages);
			chatProxy.log("Found " + chatMessages.length + " comments");
//			chatContainer.bind("DOMNodeInserted", function(e) {
//			});
		});
	}
})(jQuery);
