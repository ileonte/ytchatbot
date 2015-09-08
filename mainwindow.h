#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVariant>

class YoutubeLogin;
class YTLoginStatusWidget;
class YTChatProxy;

class MainWindow : public QWidget
{
	Q_OBJECT

private:
	YoutubeLogin *login_;
	YTLoginStatusWidget *loginStatus_;
	YTChatProxy *chatProxy_;

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();
};

#endif // MAINWINDOW_H
