#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QCoreApplication::setOrganizationName("LtKStudios");
	QCoreApplication::setOrganizationDomain("ltkstudios.net");
	QCoreApplication::setApplicationName("Youtube Chat Bot");

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
