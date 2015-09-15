#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVariant>

class QWebEngineView;
class QTextEdit;
class YoutubeLogin;
class YTLoginStatusWidget;
class YTChatProxy;
class ChatLine;
class QTextDocument;

class MainWindow : public QWidget
{
	Q_OBJECT

private:
	YoutubeLogin *login_;
	YTLoginStatusWidget *loginStatus_;
	YTChatProxy *chatProxy_;
	QTextEdit *chatDisplay_;
	QTextDocument *chatDocument_;
	ChatLine *chatLine_;

	bool loggedIn_;
	bool canChat_;

	Q_SLOT void setLoggedIn(bool yesno);
	Q_SLOT void setCanChat(bool yesno);

	Q_SLOT void newMessage(const QString &sender, const QString &message);

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();
};

#endif // MAINWINDOW_H
