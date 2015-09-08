#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QByteArray>

class QObject;
class QWebEngineProfile;

namespace Utils {
	QByteArray readFile(const QString &name);
	QWebEngineProfile *browerProfile(QObject *parent = 0);
}

#endif // UTILS_H
