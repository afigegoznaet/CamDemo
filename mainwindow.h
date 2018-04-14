#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>
#include <QFrame>
#include <QTableView>
#include "CustomModel.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void setupTabs();

private:
	void saveSettings();
	void loadSettings();

	void setframeState(QAction* elem, QFrame* frame);
	void setTabState(QAction *action, QWidget *tabwidget, QString tabName);

	QTableView* flex0 = nullptr;
	QTableView* can0 = nullptr;
	QTableView* ae0 = nullptr;

	QTableView* flex1 = nullptr;
	QTableView* can1 = nullptr;
	QTableView* ae1 = nullptr;

	CustomModel * model;

	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
