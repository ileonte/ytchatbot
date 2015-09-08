#ifndef YTCHATPROXY_H
#define YTCHATPROXY_H

#include <QObject>
#include <QVariant>

class QWebEngineProfile;
class QWebEnginePage;
class QWebChannel;
class QTimer;

class YTChatProxy : public QObject
{
	Q_OBJECT

private:
	QWebEngineProfile *chatProfile_;
	QWebEnginePage *chatPage_;
	QWebChannel *chatChannel_;
	QTimer *chatTimer_;
	QString jsHelper_;

	Q_SLOT void loadStarted();
	Q_SLOT void loadFinished(bool ok);
	Q_SLOT void runJSHelper();

public:
	explicit YTChatProxy(QObject *parent = 0);
	virtual ~YTChatProxy();

	Q_INVOKABLE void log(const QString &msg);
	Q_SLOT void connectToChat();

signals:

public slots:
};

#endif // YTCHATPROXY_H
