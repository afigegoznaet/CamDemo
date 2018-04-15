#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>
#include <QFrame>
#include <QTableView>
#include <QMediaPlayer>
#include <QFileDialog>
#include <QDir>
#include <QStandardPaths>

#include "VideoWidget.hpp"
#include "CustomModel.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void setupTabs();

private slots:
	void openFile(QMediaPlayer* player);
	void setUrl(QMediaPlayer* player, const QUrl &url);

	void on_playButton_clicked();

	void on_stopButton_clicked();

	void on_stillButton_clicked();

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

	QMediaPlayer* player0;
	QMediaPlayer* player1;
	qint64 lastPosition = 0;

	CustomModel * model;

	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
