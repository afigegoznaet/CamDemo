#include "MainWindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow){
	ui->setupUi(this);

	ui->tabWidget->setUsesScrollButtons(true);
	ui->tabWidget->tabBar()->setTabsClosable(true);
	player0 = new QMediaPlayer(this);
	player0->setVideoOutput(ui->cam0);

	player1 = new QMediaPlayer(this);
	player1->setVideoOutput(ui->cam1);

	ui->horizontalSlider->setRange(0,0);

	ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

	ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

	ui->stillButton->setIcon(style()->standardIcon(QStyle::SP_ToolBarHorizontalExtensionButton));

	connect(ui->horizontalSlider, &QAbstractSlider::sliderMoved,
			[&](int value){
				player1->pause();
				player1->setPosition(value);
				player1->play();
		});

	connect(ui->horizontalSlider, SIGNAL(sliderMoved(int)),
			player1, SLOT(setPosition(qint64)));

	connect(player1, &QMediaPlayer::positionChanged, [&](qint64 position){
		ui->horizontalSlider->setValue(position);
		ui->ts1->setText(QString::number(position));
	});

	connect(player1, &QMediaPlayer::durationChanged, [&](){
		if(player1->duration() == 0)
			return;
		ui->horizontalSlider->setRange(0, player1->duration());
		ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
		ui->ts0->setText("0");
		ui->ts1->setText("0");
	});


	loadSettings();

	model = new CustomModel((QObject*)this);
	connect(ui->actionE_xit, &QAction::triggered, [&](){
		QApplication::quit();
	});

	connect(ui->actionSelect_Media_File, &QAction::triggered, [&](){this->openFile(player1);});

	connect(ui->actionCAM0, &QAction::changed, [&](){setframeState(ui->actionCAM0, ui->frame0);});
	connect(ui->actionCAM1, &QAction::changed, [&](){setframeState(ui->actionCAM1, ui->frame1);});


	connect(ui->actionFlexRay0, &QAction::changed, [&](){ setTabState(ui->actionFlexRay0, flex0, "FlexRay0");});
	connect(ui->actionFlexRay1, &QAction::changed, [&](){ setTabState(ui->actionFlexRay1, flex1, "FlexRay1");});
	connect(ui->actionCAN0, &QAction::changed, [&](){ setTabState(ui->actionCAN0, can0, "Can0");});
	connect(ui->actionCAN1, &QAction::changed, [&](){ setTabState(ui->actionCAN1, can1, "Can1");});

	connect(ui->actionAE0, &QAction::changed, [&](){ setTabState(ui->actionAE0, ae0, "AE0");});
	connect(ui->actionAE1, &QAction::changed, [&](){ setTabState(ui->actionAE1, ae1, "AE1");});

	ui->actionE_xit->setShortcut(QKeySequence::Quit);
	ui->actionE_xit->setShortcut(QKeySequence(Qt::ALT + Qt::Key_X));

}

void MainWindow::setframeState(QAction* elem, QFrame* frame){

	if(elem->isChecked())
		frame->setVisible(true);
	else
		frame->setVisible(false);

}


void MainWindow::openFile(QMediaPlayer *player){
	QFileDialog fileDialog(this);
	fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
	fileDialog.setWindowTitle(tr("Open File"));
	QStringList supportedMimeTypes = player->supportedMimeTypes();
	if (!supportedMimeTypes.isEmpty())
		fileDialog.setMimeTypeFilters(supportedMimeTypes);
	fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
	if (fileDialog.exec() == QDialog::Accepted)
		setUrl(player, fileDialog.selectedUrls().constFirst());
}

void MainWindow::setUrl(QMediaPlayer* player, const QUrl &url){
	//errorLabel->setText(QString());
	setWindowFilePath(url.isLocalFile() ? url.toLocalFile() : QString());
	player->setMedia(url);
	player->play();

}


void MainWindow::setupTabs(){
	flex0 = new QTableView(ui->tabWidget);
	flex0->setModel(model);
	if(ui->actionFlexRay0->isChecked())
		ui->tabWidget->addTab(flex0, "FlexRay0");
	can0 = new QTableView(ui->tabWidget);
	can0->setModel(model);

	if(ui->actionCAN0->isChecked())
		ui->tabWidget->addTab(can0, "Can0");
	ae0 = new QTableView(ui->tabWidget);
	ae0->setModel(model);

	if(ui->actionAE0->isChecked())
		ui->tabWidget->addTab(ae0, "AE0");

	flex1 = new QTableView(ui->tabWidget);
	flex1->setModel(model);

	if(ui->actionFlexRay1->isChecked())
		ui->tabWidget->addTab(flex1, "FlexRay1");
	can1 = new QTableView(ui->tabWidget);
	can1->setModel(model);

	if(ui->actionCAN1->isChecked())
		ui->tabWidget->addTab(can1, "Can1");
	ae1 = new QTableView(ui->tabWidget);
	ae1->setModel(model);
	if(ui->actionAE1->isChecked())
		ui->tabWidget->addTab(ae1, "AE1");

}

void MainWindow::setTabState(QAction* action, QWidget *tabwidget, QString tabName){
	qDebug()<<"count: "<<ui->tabWidget->count();
	if(action->isChecked()){
		ui->tabWidget->addTab(tabwidget, tabName);
		ui->tabWidget->setCurrentWidget(tabwidget);
		//tabwidget->setVisible(true);
	}else{
		auto idx= ui->tabWidget->indexOf(tabwidget);
		//tabwidget->setVisible(false);
		if(idx>=0)
			ui->tabWidget->removeTab(idx);
	}
	qDebug()<<"count: "<<ui->tabWidget->count();
}

MainWindow::~MainWindow()
{
	saveSettings();
	delete ui;
}

void MainWindow::saveSettings(){
	QSettings settings;

	settings.beginGroup("MainWindow");
	settings.setValue("size", size());
	settings.setValue("pos", pos());
	settings.setValue("splitterSizes", ui->splitter->saveState());
	//Menus
	settings.setValue("Cam0", ui->actionCAM0->isChecked());
	settings.setValue("Cam1", ui->actionCAM1->isChecked());
	settings.setValue("Flex0", ui->actionFlexRay0->isChecked());
	settings.setValue("Flex1", ui->actionFlexRay1->isChecked());
	settings.setValue("Can0", ui->actionCAN0->isChecked());
	settings.setValue("Can1", ui->actionCAN1->isChecked());
	settings.setValue("Ae0", ui->actionAE0->isChecked());
	settings.setValue("Ae1", ui->actionAE1->isChecked());

	settings.endGroup();
}

void MainWindow::loadSettings(){
	QSettings settings;
	settings.beginGroup("MainWindow");
	resize(settings.value("size", QSize(400, 400)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());

	ui->actionCAM0->setChecked(settings.value("Cam0", true).toBool());
	ui->actionCAM1->setChecked(settings.value("Cam1", true).toBool());
	ui->actionFlexRay0->setChecked(settings.value("Flex0", true).toBool());
	ui->actionFlexRay1->setChecked(settings.value("Flex1", false).toBool());
	ui->actionCAN0->setChecked(settings.value("Can0", true).toBool());
	ui->actionCAN1->setChecked(settings.value("Can1", false).toBool());

	ui->actionAE0->setChecked(settings.value("Ae0", true).toBool());
	ui->actionAE1->setChecked(settings.value("Ae1", false).toBool());

	QByteArray splitterSizes = settings.value("splitterSizes").toByteArray();
	if(!ui->splitter->restoreState(splitterSizes))
		ui->splitter->setSizes({200,200});
	settings.endGroup();
}



void MainWindow::on_playButton_clicked(){
	if(player1->position() > lastPosition && player1->isVideoAvailable()){
		qDebug()<<"Position: "<<player1->position() << " "<<lastPosition;
		lastPosition = player1->position();
		player0->pause();
		player1->pause();
		ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

	}else if(player1->isVideoAvailable()){
		qDebug()<<"Button: "<<player1->isVideoAvailable();

		player0->play();
		player1->play();
		ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	}
}

void MainWindow::on_stopButton_clicked(){
	player0->stop();
	player1->stop();
}

void MainWindow::on_stillButton_clicked(){
	if(!player1->isVideoAvailable())
		return;
	ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
	player0->pause();
	player1->pause();
	lastPosition = player1->position();
	player1->setPosition(++lastPosition);
}
