#ifndef YTCHATPROXY_H
#define YTCHATPROXY_H

#include <QObject>
#include <QByteArray>
#include <QVariant>

class QWebEngineProfile;
class QWebEnginePage;
class QWebChannel;

class YTChatProxy : public QObject
{
	Q_OBJECT

private:
	QWebEngineProfile *chatProfile_;
	QWebEnginePage *chatPage_;
	QWebChannel *chatChannel_;
	QString jsHelper_;

	Q_SLOT void loadStarted();
	Q_SLOT void loadFinished(bool ok);

public:
	explicit YTChatProxy(QObject *parent = 0);
	virtual ~YTChatProxy();

	Q_INVOKABLE void log(const QString &msg);
	Q_INVOKABLE void chatMessage(const QByteArray &msg);
	Q_INVOKABLE void emitCanChat(bool yesno);
	Q_SLOT void connectToChat();

	Q_SIGNAL void newMessage(const QString &from, const QString &msg);
	Q_SIGNAL void canChat(bool yesno);

	Q_SIGNAL void sendMessage(const QString &msg);
};

#endif // YTCHATPROXY_H
