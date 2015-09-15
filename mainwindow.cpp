#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QWebChannel>
#include <QWebEngineView>
#include <QTextDocument>
#include <QTextCursor>
#include <QFont>
#include <QScrollBar>
#include <QDebug>

#include "mainwindow.h"
#include "chatline.h"
#include "youtubelogin.h"
#include "ytloginstatuswidget.h"
#include "ytchatproxy.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent), loggedIn_(false), canChat_(false)
{
	setMinimumSize(400, 600);

	login_ = new YoutubeLogin();
	chatProxy_ = new YTChatProxy(this);
	connect(chatProxy_, &YTChatProxy::canChat, this, &MainWindow::setCanChat);
	connect(chatProxy_, &YTChatProxy::newMessage, this, &MainWindow::newMessage);
	connect(login_, &YoutubeLogin::stateChanged, [this](){
		qDebug() << "Logged in";
		if (login_->state() == YoutubeLogin::LoggedIn) {
			setLoggedIn(true);
			chatProxy_->connectToChat();
		} else {
			setLoggedIn(false);
		}
	});

	auto vl = new QVBoxLayout(this);

	auto hl = new QHBoxLayout; {
		hl->setContentsMargins(0, 0, 0, 0);

		loginStatus_ = new YTLoginStatusWidget(this);
		loginStatus_->setLogin(login_);
		hl->addWidget(loginStatus_);

		auto b = new QPushButton("Login", this);
		connect(b, &QPushButton::pressed, [this]() {
			login_->login();
		});
		hl->addWidget(b);

		b = new QPushButton("Logout", this);
		connect(b, &QPushButton::pressed, [this]() {
			login_->logout();
		});
		hl->addWidget(b);
	}
	vl->addLayout(hl);

	QFont font;
	font.setFamily("Roboto");
	font.setPixelSize(13);

	chatDocument_ = new QTextDocument(this);
	chatDisplay_ = new QTextEdit(this);
	chatDisplay_->setReadOnly(true);
	chatDisplay_->setAcceptRichText(true);
	chatDisplay_->setDocument(chatDocument_);
	chatDisplay_->setFont(font);
	vl->addWidget(chatDisplay_);

	chatLine_ = new ChatLine(this);
	connect(chatLine_, &ChatLine::send, chatProxy_, &YTChatProxy::sendMessage);
	vl->addWidget(chatLine_);

	login_->testLogin();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setLoggedIn(bool yesno)
{
	loggedIn_ = yesno;
	chatLine_->setEnabled(loggedIn_ && canChat_);
}

void MainWindow::setCanChat(bool yesno)
{
	canChat_ = yesno;
	chatLine_->setEnabled(loggedIn_ && canChat_);
}

void MainWindow::newMessage(const QString &sender, const QString &message)
{
	QTextCursor cur(chatDocument_);
	bool scroll = chatDisplay_->verticalScrollBar()->value() >= chatDisplay_->verticalScrollBar()->maximum();

	cur.movePosition(QTextCursor::End);
	cur.beginEditBlock(); {
		if (!chatDocument_->isEmpty()) cur.insertBlock();
		cur.insertHtml(QString("<b>%1</b>&nbsp;").arg(sender));
		cur.insertHtml(message);
	} cur.endEditBlock();

	if (scroll)
		chatDisplay_->verticalScrollBar()->setValue(chatDisplay_->verticalScrollBar()->maximum());
}
