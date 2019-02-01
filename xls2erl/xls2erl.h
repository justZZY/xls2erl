#pragma once

#include <QtWidgets/QDialog>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qfile.h>
#include <qtextedit.h>
#include <qdebug.h>
#include <qcombobox.h>
#include "ui_xls2erl.h"


class xls2erl : public QDialog
{
	Q_OBJECT

public:
	xls2erl(QWidget *parent = Q_NULLPTR);
	~xls2erl();
	void init();
	void showJsonKeys();
	QJsonObject getJsonObject();

public slots:
	void showSelectJsonText();

private:
	Ui::xls2erlClass ui;
	QPushButton *okBtn;
	QGridLayout *layout;
	QTextEdit *textEdit;
	QComboBox *comboBox;
};
