#include "VideoWidget.hpp"

VideoWidget::VideoWidget(QWidget *parent) : QVideoWidget(parent){
	QPalette p = palette();
	p.setColor(QPalette::Window, Qt::black);
	setPalette(p);
}



void VideoWidget::keyPressEvent(QKeyEvent *event){
	if (event->key() == Qt::Key_Escape && isFullScreen()) {
		setFullScreen(false);
		event->accept();
	} else if (event->key() == Qt::Key_Enter && event->modifiers() & Qt::Key_Alt) {
		if(hasVideo)
			setFullScreen(!isFullScreen());
		event->accept();
	} else {
		QVideoWidget::keyPressEvent(event);
	}
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event){
	qDebug()<<"window state before "<<windowState();
	setFullScreen(hasVideo && !isFullScreen());

	event->accept();
	qDebug()<<"window state after "<<windowState();

}

void VideoWidget::mousePressEvent(QMouseEvent *event){
	QVideoWidget::mousePressEvent(event);
}
