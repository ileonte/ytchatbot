#include "youtubelogin.h"

#include <QStackedLayout>
#include <QString>
#include <QDebug>
#include <QWebEngineView>

#include "ytloginproxy.h"

YoutubeLogin::YoutubeLogin(QWidget *parent) : QWidget(parent)
{
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

	loginView_ = new QWebEngineView(this);
	loginView_->setPage(loginProxy_->page());
	layout_->addWidget(loginView_);
}

YoutubeLogin::~YoutubeLogin()
{
}

void YoutubeLogin::showSpinner()
{
	layout_->setCurrentIndex(0);
}

void YoutubeLogin::showLoginPage()
{
	layout_->setCurrentIndex(1);
}

void YoutubeLogin::log(const QString &v)
{
	qDebug() << QTime::currentTime() << "JavaScript:" << v;
}

void YoutubeLogin::startLogin()
{
	loginProxy_->login();
}
