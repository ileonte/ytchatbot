#include <QLabel>
#include <QHBoxLayout>
#include <QDebug>
#include <QTime>

#include "youtubelogin.h"
#include "ytloginstatuswidget.h"

YTLoginStatusWidget::YTLoginStatusWidget(QWidget *parent) : QWidget(parent)
{
	auto layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);

	iconLabel_ = new QLabel(this);
	iconLabel_->setMaximumSize(32, 32);
	iconLabel_->setMinimumSize(32, 32);
	layout->addWidget(iconLabel_);

	textLabel_ = new QLabel(this);
	layout->addWidget(textLabel_);

	offlineIcon_.load(":/ythelpers/offline.png");
	onlineIcon_.load(":/ythelpers/online.png");
	loadAnimation_ = new QMovie(this);
	loadAnimation_->setFileName(":/ythelpers/spinner-big.gif");
	loadAnimation_->setScaledSize(QSize(32, 32));

	setLogin(nullptr);
}

void YTLoginStatusWidget::setOfflineState()
{
	loadAnimation_->stop();
	iconLabel_->setPixmap(offlineIcon_);
	textLabel_->setText(tr("Not logged in"));
}

void YTLoginStatusWidget::setOnlineState()
{
	loadAnimation_->stop();
	iconLabel_->setPixmap(onlineIcon_);
	textLabel_->setText(tr("Logged in"));
}

void YTLoginStatusWidget::setLoggingInState(bool check)
{
	iconLabel_->setMovie(loadAnimation_);
	loadAnimation_->start();
	if (check)
		textLabel_->setText(tr("Checking login"));
	else
		textLabel_->setText(tr("Logging in"));
}

void YTLoginStatusWidget::setLoggingOutState()
{
	iconLabel_->setMovie(loadAnimation_);
	loadAnimation_->start();
	textLabel_->setText(tr("Logging out"));
}

void YTLoginStatusWidget::updateLoginState(YoutubeLogin *login)
{
	if (!login) {
		setOfflineState();
		return;
	}

	switch (login->operation()) {
		case YoutubeLogin::Login:
		case YoutubeLogin::TestLogin: {
			switch (login->state()) {
				case YoutubeLogin::LoggedIn: {
					setOnlineState();
					break;
				}
				case YoutubeLogin::Working: {
					setLoggingInState(login->operation() == YoutubeLogin::TestLogin);
					break;
				}
				default: {
					setOfflineState();
					break;
				}
			}
			break;
		}
		case YoutubeLogin::Logout: {
			switch (login->state()) {
				case YoutubeLogin::Working: {
					setLoggingOutState();
					break;
				}
				default: {
					setOfflineState();
					break;
				}
			}

			break;
		}
		case YoutubeLogin::None: {
			setOfflineState();
			break;
		}
	}
}

void YTLoginStatusWidget::setLogin(YoutubeLogin *login)
{
	updateLoginState(login);
	if (login)
		connect(login, &YoutubeLogin::stateChanged, this, &YTLoginStatusWidget::loginStateChanged);
}

void YTLoginStatusWidget::loginStateChanged()
{
	YoutubeLogin *login = qobject_cast<YoutubeLogin *>(sender());
	updateLoginState(login);
	qDebug() << QTime::currentTime() << login->operation() << login->state();
}

