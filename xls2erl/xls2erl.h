#pragma once

#include <QtWidgets/QDialog>
#include <qpushbutton.h>
#include <qgridlayout.h>
#include <qboxlayout.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qjsonvalue.h>
#include <qfile.h>
#include <qdebug.h>
#include <qcombobox.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qregexp.h>
#include <qvalidator.h>
#include <qsplashscreen.h>
#include <qpalette.h>
#include <qprocess.h>
#include "ui_xls2erl.h"


class xls2erl : public QDialog
{
	Q_OBJECT

public:
	xls2erl(QWidget *parent = Q_NULLPTR);
	~xls2erl();
	void init();
	void showJsonKeys();
	QJsonObject getAllJsonObject();
	QJsonObject getInsertJsonObject(QJsonObject);

public slots:
	void clickChooseBtn();
	void getExcelPath();
	void getConfigPath();
	void showSelectJsonText();
	void writeJson();
	void genConfig();

private:
	Ui::xls2erlClass ui;
	QGridLayout *gridLayout;
	QPushButton *okBtn;
	QPushButton *genBtn;
	QHBoxLayout *btnLayout;
	QComboBox *comboBox;
	QRadioButton *changeBtn;
	QRadioButton *addBtn;
	QButtonGroup *chooseBtnGroup;
	QHBoxLayout *chooseLayout;
	QLabel *nameLabel;
	QLineEdit *nameLineEdit;
	QLabel *desLabel;
	QLineEdit *desLineEdit;
	QLabel *inputLabel;
	QLineEdit *inputLineEdit;
	QPushButton *inputFileBtn;
	QLabel *outputLabel;
	QLineEdit *outputLineEdit;
	QPushButton *outputFileBtn;
	QLabel *sheetLabel;
	QLineEdit *sheetLineEdit;
	QLabel *labelLabel;
	QLineEdit *labelLineEdit;
	QLabel *beginLabel;
	QLineEdit *beginLineEdit;
	QLabel *primarykeyLabel;
	QLineEdit *primarykeyLineEdit;
	QLabel *syntaxLabel;
	QRadioButton *syntaxOnBtn;
	QRadioButton *syntaxOffBtn;
	QButtonGroup *syntaxBtnGroup;
	QHBoxLayout *syntaxLayout;
	QString jsonPath;
};
