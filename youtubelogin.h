#ifndef YOUTUBELOGIN_H
#define YOUTUBELOGIN_H

#include <QWidget>

class YTLoginProxy;
class QStackedLayout;
class QWebEngineView;

class YoutubeLogin : public QWidget
{
	Q_OBJECT

private:
	YTLoginProxy *loginProxy_;
	QStackedLayout *layout_;
	QWebEngineView *spinView_;
	QWebEngineView *loginView_;

	Q_SLOT void showSpinner();
	Q_SLOT void showLoginPage();

public:
	explicit YoutubeLogin(QWidget *parent = 0);
	virtual ~YoutubeLogin();

	Q_SLOT void log(const QString &v);

signals:

public slots:
	void startLogin();
};

#endif // YOUTUBELOGIN_H
