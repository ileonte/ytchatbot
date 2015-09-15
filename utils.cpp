#include <QDir>
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
	QString cachePath = loc + "/Profiles/YoutubeProfile/WebCache";
	QString dataPath = loc + "/Profiles/YoutubeProfile/WebData";

	QDir(dataPath).remove("Visited Links");

	qDebug() << "WRITABLE LOCATION" << loc;

	auto profile = new QWebEngineProfile("YoutubeProfile", parent);
	profile->setPersistentStoragePath(dataPath);
	profile->setCachePath(cachePath);
	profile->setHttpCacheType(QWebEngineProfile::DiskHttpCache);
	profile->setPersistentCookiesPolicy(QWebEngineProfile::AllowPersistentCookies);

	return profile;
}
