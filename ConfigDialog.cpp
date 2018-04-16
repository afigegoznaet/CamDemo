#include "ConfigDialog.hpp"
#include "ui_ConfigDialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ConfigDialog)
{
	ui->setupUi(this);
}

ConfigDialog::~ConfigDialog()
{
	delete ui;
}
