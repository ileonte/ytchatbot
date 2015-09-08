#ifndef YOUTUBELOGIN_H
#define YOUTUBELOGIN_H

#include <QWidget>

class YTLoginProxy;
class QStackedLayout;
class QWebEngineView;

class YoutubeLogin : public QWidget
{
	Q_OBJECT

public:
	enum Operation {
		None,
		Login,
		Logout,
		TestLogin
	};

	enum State {
		LoggedOut,
		Working,
		LoggedIn
	};

private:
	YTLoginProxy *loginProxy_;
	QStackedLayout *layout_;
	QWebEngineView *spinView_;
	QWebEngineView *loginView_;

	Operation operation_;
	State state_;

	Q_SLOT void showSpinner();
	Q_SLOT void showLoginPage();

	Q_SLOT void proxyLoginStatus(bool ok);

public:
	explicit YoutubeLogin(QWidget *parent = 0);
	virtual ~YoutubeLogin();

	State state() const;
	Operation operation() const;

	Q_SLOT void log(const QString &v);

signals:
	void stateChanged();

public slots:
	void login();
	void testLogin();
	void logout();
};

#endif // YOUTUBELOGIN_H
