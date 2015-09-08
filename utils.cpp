#include "utils.h"

#include <QFile>

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
