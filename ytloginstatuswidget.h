#ifndef YTLOGINSTATUSWIDGET_H
#define YTLOGINSTATUSWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPixmap>
#include <QMovie>

class QLabel;
class YoutubeLogin;

class YTLoginStatusWidget : public QWidget
{
	Q_OBJECT

private:
	QPixmap  offlineIcon_;
	QPixmap  onlineIcon_;
	QMovie  *loadAnimation_;

	QLabel *iconLabel_;
	QLabel *textLabel_;

	void setOfflineState();
	void setOnlineState();
	void setLoggingInState(bool check);
	void setLoggingOutState();

	void updateLoginState(YoutubeLogin *login);
	Q_SLOT void loginStateChanged();

public:
	explicit YTLoginStatusWidget(QWidget *parent = 0);

	void setLogin(YoutubeLogin *login);

signals:

public slots:
};

#endif // YTLOGINSTATUSWIDGET_H
