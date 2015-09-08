#ifndef YOUTUBEWEBCHANNEL_H
#define YOUTUBEWEBCHANNEL_H

#include <QObject>
#include <QJsonObject>
#include <QVariant>

class QWebEngineProfile;
class QWebEnginePage;
class QWebChannel;
class QTimer;

class YTLoginProxy : public QObject
{
	Q_OBJECT

private:
	QJsonObject loginStore_;
	QWebEngineProfile *loginProfile_;
	QWebEnginePage *loginPage_;
	QWebChannel *loginChannel_;
	QTimer *loginTimer_;
	QString jsHelper_;
	QString operation_;

	Q_SLOT void loadStarted();
	Q_SLOT void loadFinished(bool ok);
	Q_SLOT void runJSHelper();

public:
	explicit YTLoginProxy(QObject *parent = 0);
	virtual ~YTLoginProxy();

	Q_INVOKABLE QVariant getStore() const;
	Q_INVOKABLE void setStore(const QVariant &obj);

	QWebEnginePage *page() const;

	Q_SLOT void testLogin();
	Q_SLOT void login();
	Q_SLOT void logout();
	Q_SLOT void cancel();

	Q_INVOKABLE void log(const QString &msg);

	Q_INVOKABLE void signalBusy();
	Q_SIGNAL 	void busy();

	Q_INVOKABLE void signalNeedsLogin();
	Q_SIGNAL    void needsLogin();

	Q_INVOKABLE void signalLoginStatus(const QVariant &ok);
	Q_SIGNAL    void loginStatus(bool ok);

	Q_INVOKABLE QVariant getUrlHost();

	Q_SIGNAL void javascriptMessage(const QString &msg);
};

#endif // YOUTUBEWEBCHANNEL_H
