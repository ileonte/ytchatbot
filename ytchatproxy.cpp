#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QWebChannel>
#include <QDebug>
#include <QTime>
#include <QJsonDocument>
#include <QJsonObject>

#include "ytchatproxy.h"
#include "utils.h"

YTChatProxy::YTChatProxy(QObject *parent) : QObject(parent)
{
	jsHelper_ = QString::fromUtf8(Utils::readFile(":/ythelpers/jquery.js")) + "\n" +
			QString::fromUtf8(Utils::readFile(":/qtwebchannel/qwebchannel.js")) + "\n" +
			QString::fromUtf8(Utils::readFile(":/ythelpers/chatProxy/helper.js"));

	chatChannel_ = new QWebChannel(this);
	chatChannel_->registerObject("chatProxy", this);

	chatProfile_ = Utils::browerProfile(this);

	chatPage_ = new QWebEnginePage(chatProfile_, this);
	chatPage_->setWebChannel(chatChannel_);
	connect(chatPage_, &QWebEnginePage::loadStarted, this, &YTChatProxy::loadStarted);
	connect(chatPage_, &QWebEnginePage::loadFinished, this, &YTChatProxy::loadFinished);
}

YTChatProxy::~YTChatProxy()
{
}

void YTChatProxy::loadStarted()
{
	qDebug() << QTime::currentTime() << "LOAD STARTED: " << chatPage_->requestedUrl().host().toLower();
}

void YTChatProxy::loadFinished(bool ok)
{
	qDebug() << QTime::currentTime() <<"LOAD FINISHED " << ok << chatPage_->url().host().toLower();
	if (ok && !jsHelper_.isEmpty())
		chatPage_->runJavaScript(jsHelper_ + QString("\nwindow.ytChatHelper();"));
}

void YTChatProxy::log(const QString &msg)
{
	qDebug() << QTime::currentTime() << "JavaScript:" << msg;
}

void YTChatProxy::chatMessage(const QString &msg)
{
	qDebug() << QTime::currentTime() << QJsonDocument::fromJson(msg.toUtf8()).object();
}

void YTChatProxy::connectToChat()
{
	chatPage_->load(QUrl("qrc:///ythelpers/empty.html"));
}
