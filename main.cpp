#include "MainWindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("CamDemoOrg");
	QCoreApplication::setApplicationName("CamDemo");

	MainWindow w;
	w.show();
	w.setupTabs();
	return a.exec();
}
