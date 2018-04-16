#ifndef CONFIGDIALOG_HPP
#define CONFIGDIALOG_HPP

#include <QDialog>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
	Q_OBJECT

public:
	explicit ConfigDialog(QWidget *parent = 0);
	~ConfigDialog();

private:
	Ui::ConfigDialog *ui;
};

#endif // CONFIGDIALOG_HPP
