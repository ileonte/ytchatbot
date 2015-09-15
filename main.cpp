#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("LtKStudios");
	QCoreApplication::setOrganizationDomain("ltkstudios.net");
	QCoreApplication::setApplicationName("Youtube Chat Bot");

	QApplication a(argc, argv);

	QStringList fontDirs({":/ythelpers/fonts/AnonymousPro", ":/ythelpers/fonts/Roboto"});
	QDir dir;
	foreach (const QString &path, fontDirs) {
		dir.setPath(path);
		foreach (const QString &fname, dir.entryList(QDir::Files)) {
			QString fontPath(QString("%1/%2").arg(path).arg(fname));
			int id = QFontDatabase::addApplicationFont(fontPath);
			if (id < 0)
				qDebug() << "FAILED to add font" << fontPath;
			else
				qDebug() << "ADDED font " << fontPath << "(" << id << ")";
		}
	}

	MainWindow w;
	w.show();

	return a.exec();
}
