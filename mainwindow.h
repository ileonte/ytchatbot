#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVariant>

class YoutubeLogin;

class MainWindow : public QWidget
{
	Q_OBJECT

private:
	YoutubeLogin *login_;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();
};

#endif // MAINWINDOW_H
