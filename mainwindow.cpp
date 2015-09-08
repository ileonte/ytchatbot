#include "mainwindow.h"
#include "youtubelogin.h"

#include <QHBoxLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
	login_ = new YoutubeLogin();

	auto l = new QHBoxLayout(this);

	auto b = new QPushButton("Login", this);
	connect(b, &QPushButton::pressed, [this]() {
		login_->show();
		login_->startLogin();
	});
	l->addWidget(b);

	b = new QPushButton("Logout", this);
	connect(b, &QPushButton::pressed, [this]() {
	});
	l->addWidget(b);
}

MainWindow::~MainWindow()
{
}
