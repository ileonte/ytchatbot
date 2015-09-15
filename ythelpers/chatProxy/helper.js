(function(jQuery) {
	"use strict";

	var $ = jQuery.noConflict(true);
	window.$$ = $;

	window.ytChatHelper = function() {
		var _ = new QWebChannel(qt.webChannelTransport, function(channel) {
			var chatProxy = channel.objects.chatProxy;

			if (!location.href.match(/https?:\/\/www\.youtube\.com\/live_chat\?v=/)) {
				chatProxy.log("Redirecting to youtube chat from " + location.href);
				location.href = "https://www.youtube.com/live_chat?v=fe4yQkxt_FQ";
				return;
			}

			$("#comments-scroller #all-comments").bind("DOMNodeInserted", function(e) {
				var qe = $(e.target);
				var id = qe.attr("id");
				var msg;

				if (!id.match(/^comment-/)) return;
				if (id.match(/^comment-local/)) return;

				if (qe.hasClass("removed")) {
					msg = {
						"id": qe.attr('id'),
						"removed": true
					};
				} else {
					msg = {
						"id": qe.attr('id'),
						"removed": false,
						"author": qe.children(".content").children(".byline").children(".author").children(".yt-user-name").html(),
						"message": qe.children(".content").children(".comment-text").html()
					};
				}
				chatProxy.chatMessage(JSON.stringify(msg));
			});

			var form = $(".live-chat-comment-form");
			chatProxy.emitCanChat(form.length > 0);

			console.log(chatProxy);
			chatProxy.sendMessage.connect(function(message) {
				$("#live-comments-input-field").html(message);
				$(".post-button").trigger("click");
			});
		});
	}
})(jQuery);
