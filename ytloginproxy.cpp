#include "ytloginproxy.h"

#include <QWebEngineScript>
#include <QWebEngineProfile>
#include <QWebEnginePage>
#include <QWebEngineScript>
#include <QWebEngineScriptCollection>
#include <QWebChannel>
#include <QDebug>
#include <QJsonDocument>
#include <QTimer>
#include <QTime>
#include <QStandardPaths>

#include "utils.h"

YTLoginProxy::YTLoginProxy(QObject *parent) : QObject(parent)
{
	jsHelper_ = QString::fromUtf8(Utils::readFile(":/ythelpers/jquery.js")) + "\n" +
			QString::fromUtf8(Utils::readFile(":/qtwebchannel/qwebchannel.js")) + "\n" +
			QString::fromUtf8(Utils::readFile(":/ythelpers/loginProxy/helper.js"));

	loginTimer_ = new QTimer(this);
	loginTimer_->setSingleShot(true);
	connect(loginTimer_, &QTimer::timeout, this, &YTLoginProxy::runJSHelper);

	loginChannel_ = new QWebChannel(this);
	loginChannel_->registerObject("loginProxy", this);

	QString loc = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
	qDebug() << "WRITABLE LOCATION" << loc;
	loginProfile_ = new QWebEngineProfile("TestProfile", this);
	loginProfile_->setPersistentStoragePath(loc + "/Profiles/TestProfile/WebData");
	loginProfile_->setCachePath(loc + "/Profiles/TestProfile/WebCache");
	loginProfile_->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
	loginProfile_->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

	loginPage_ = new QWebEnginePage(loginProfile_, this);
	loginPage_->setWebChannel(loginChannel_);
	connect(loginPage_, &QWebEnginePage::loadStarted, this, &YTLoginProxy::loadStarted);
	connect(loginPage_, &QWebEnginePage::loadFinished, this, &YTLoginProxy::loadFinished);
}

YTLoginProxy::~YTLoginProxy()
{
}

QVariant YTLoginProxy::getUrlHost()
{
	return loginPage_->url().host().toLower();
}

void YTLoginProxy::runJSHelper()
{
	if (!jsHelper_.isEmpty())
		loginPage_->runJavaScript(jsHelper_ + QString("\nwindow.ytLoginHelper(\"%1\");").arg(operation_));
}

void YTLoginProxy::loadStarted()
{
	qDebug() << QTime::currentTime() << "LOAD STARTED: " << loginPage_->requestedUrl().host().toLower();
	emit busy();
}

void YTLoginProxy::loadFinished(bool ok)
{
	qDebug() << QTime::currentTime() <<"LOAD FINISHED " << ok << loginPage_->url().host().toLower();
	if (ok) {
		if (!operation_.isEmpty())
			loginTimer_->start(3000);
	} else {
		emit loginStatus(false);
	}
}

void YTLoginProxy::signalBusy()
{
	qDebug() << QTime::currentTime() << "SIGNAL busy";
	emit busy();
}

void YTLoginProxy::signalNeedsLogin()
{
	qDebug() << QTime::currentTime() << "SIGNAL needsLogin";
	emit needsLogin();
}

void YTLoginProxy::signalLoginStatus(const QVariant &ok)
{
	if (ok.type() == QVariant::Bool) {
		emit loginStatus(ok.toBool());
	}
}

QWebEnginePage *YTLoginProxy::page() const
{
	return loginPage_;
}

void YTLoginProxy::log(const QString &msg)
{
	emit javascriptMessage(msg);
}

QVariant YTLoginProxy::getStore() const
{
	return loginStore_.toVariantHash();
}

void YTLoginProxy::setStore(const QVariant &obj)
{
	loginStore_ = QJsonObject::fromVariantHash(obj.toHash());
	qDebug() << QTime::currentTime() << "SETSTORE" << obj;
}

void YTLoginProxy::testLogin()
{
	operation_ = "testLogin";
	loginPage_->load(QUrl("qrc:///ythelpers/empty.html"));
}

void YTLoginProxy::login()
{
	operation_ = "login";
	loginPage_->load(QUrl("qrc:///ythelpers/empty.html"));
}

void YTLoginProxy::logout()
{
	operation_ = "logout";
	loginPage_->load(QUrl("qrc:///ythelpers/empty.html"));
}

void YTLoginProxy::cancel()
{
	if (!operation_.isEmpty()) {
		operation_ = QString();
		loginPage_->load(QUrl("qrc:///ythelpers/empty.html"));
	}
}
