#include <QHBoxLayout>
#include <QPushButton>

#include "mainwindow.h"
#include "youtubelogin.h"
#include "ytloginstatuswidget.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	login_ = new YoutubeLogin();

	auto l = new QHBoxLayout(this);

	loginStatus_ = new YTLoginStatusWidget(this);
	loginStatus_->setLogin(login_);
	l->addWidget(loginStatus_);

	auto b = new QPushButton("Login", this);
	connect(b, &QPushButton::pressed, [this]() {
		login_->login();
	});
	l->addWidget(b);

	b = new QPushButton("Logout", this);
	connect(b, &QPushButton::pressed, [this]() {
		login_->logout();
	});
	l->addWidget(b);

	login_->testLogin();
}

MainWindow::~MainWindow()
{
}
