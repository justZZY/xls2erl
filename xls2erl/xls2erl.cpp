#include "xls2erl.h"

xls2erl::xls2erl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	init();
	showJsonKeys();
	connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(showSelectJsonText()));
}

xls2erl::~xls2erl()
{
	delete okBtn;
	delete textEdit;
	delete layout;
}

void xls2erl::init()
{
	layout = new QGridLayout(this);
	okBtn = new QPushButton(tr("ok"));
	textEdit = new QTextEdit();
	comboBox = new QComboBox();
	layout->addWidget(comboBox, 1, 1);
	layout->addWidget(textEdit, 1, 2);
	layout->addWidget(okBtn, 2, 2);
	this->setLayout(layout);
}

QJsonObject xls2erl::getJsonObject()
{
	QFile file("Resources\\game_server.spec");
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QString value = file.readAll();
	file.close();

	QJsonParseError parseJsonErr;
	QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
	if (!(parseJsonErr.error == QJsonParseError::NoError))
	{
		qDebug() << tr("½âÎöjsonÎÄ¼þ´íÎó£¡");
		return QJsonObject();
	}
	QJsonObject jsonObject = document.object();
	return jsonObject;
}

void xls2erl::showJsonKeys()
{
	QJsonObject jsonObject = getJsonObject();
	comboBox->addItems(jsonObject.keys().toVector().toList());
}

void xls2erl::showSelectJsonText()
{
	int Index = comboBox->currentIndex();
	QJsonObject jsonObject = getJsonObject();
	QString Key = jsonObject.keys().toVector().at(Index);
	QString Text = jsonObject[Key].toString();
	textEdit->setText(Text);
	return;
}