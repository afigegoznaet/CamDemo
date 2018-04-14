#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

#include <QVideoWidget>
#include <QKeyEvent>
#include <QDebug>

class VideoWidget : public QVideoWidget{
	Q_OBJECT
public:
	explicit VideoWidget(QWidget *parent = nullptr);

signals:

public slots:

protected:
	void keyPressEvent(QKeyEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
};

#endif // VIDEOWIDGET_HPP
