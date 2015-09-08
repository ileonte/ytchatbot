#include "youtubelogin.h"

#include <QStackedLayout>
#include <QString>
#include <QDebug>
#include <QWebEngineView>

#include "ytloginproxy.h"

YoutubeLogin::YoutubeLogin(QWidget *parent) : QWidget(parent), operation_(None), state_(LoggedOut)
{
	setWindowTitle(tr("YouTube Login"));

	layout_ = new QStackedLayout(this);
	layout_->setMargin(0);
	layout_->setContentsMargins(0, 0, 0, 0);

	setMinimumSize(800, 800);

	spinView_ = new QWebEngineView(this);
	spinView_->load(QUrl("qrc:///ythelpers/spinner.html"));
	layout_->addWidget(spinView_);

	loginProxy_ = new YTLoginProxy(this);
	connect(loginProxy_, &YTLoginProxy::javascriptMessage, this, &YoutubeLogin::log);
	connect(loginProxy_, &YTLoginProxy::busy, this, &YoutubeLogin::showSpinner);
	connect(loginProxy_, &YTLoginProxy::needsLogin, this, &YoutubeLogin::showLoginPage);
	connect(loginProxy_, &YTLoginProxy::loginStatus, this, &YoutubeLogin::proxyLoginStatus);

	loginView_ = new QWebEngineView(this);
	loginView_->setPage(loginProxy_->page());
	layout_->addWidget(loginView_);
}

YoutubeLogin::~YoutubeLogin()
{
}

YoutubeLogin::State YoutubeLogin::state() const
{
	return state_;
}

YoutubeLogin::Operation YoutubeLogin::operation() const
{
	return operation_;
}

void YoutubeLogin::showSpinner()
{
	layout_->setCurrentIndex(0);
}

void YoutubeLogin::showLoginPage()
{
	layout_->setCurrentIndex(1);
	show();
}

void YoutubeLogin::log(const QString &v)
{
	qDebug() << QTime::currentTime() << "JavaScript:" << v;
}

void YoutubeLogin::proxyLoginStatus(bool ok)
{
	if (ok) {
		if (operation_ == Login || operation_ == TestLogin) {
			state_ = LoggedIn;
			hide();
		} else
			state_ = LoggedOut;
	} else
		state_ = LoggedOut;

	emit stateChanged();
}

void YoutubeLogin::login()
{
	if (state_ == LoggedOut) {
		operation_ = Login;
		state_ = Working;
		emit stateChanged();

		loginProxy_->login();
	}
}

void YoutubeLogin::testLogin()
{
	if (operation_ == None) {
		operation_ = TestLogin;
		state_ = Working;
		emit stateChanged();

		loginProxy_->testLogin();
	}
}

void YoutubeLogin::logout()
{
	if (state_ == LoggedIn) {
		operation_ = Logout;
		state_ = Working;
		emit stateChanged();

		loginProxy_->logout();
	}
}
