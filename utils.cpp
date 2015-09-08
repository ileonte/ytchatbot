#include <QFile>
#include <QWebEngineProfile>
#include <QStandardPaths>
#include <QDebug>

#include "utils.h"

QByteArray Utils::readFile(const QString &name)
{
	QFile f(name);
	QByteArray r;
	if (f.open(QFile::ReadOnly)) {
		r = f.readAll();
		f.close();
	}
	return r;
}

QWebEngineProfile *Utils::browerProfile(QObject *parent)
{
	QString loc = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
	qDebug() << "WRITABLE LOCATION" << loc;

	auto profile = new QWebEngineProfile("YoutubeProfile", parent);
	profile->setPersistentStoragePath(loc + "/Profiles/YoutubeProfile/WebData");
	profile->setCachePath(loc + "/Profiles/YoutubeProfile/WebCache");
	profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
	profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

	return profile;
}
