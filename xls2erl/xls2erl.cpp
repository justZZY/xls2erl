#include "xls2erl.h"

xls2erl::xls2erl(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("������������"));
	this->setWindowIcon(QIcon("Resources\\title.ico"));
	this->resize(470, 400);
	this->setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
	this->setFixedSize(this->width(), this->height());
	init();
	showJsonKeys();
	connect(addBtn, SIGNAL(clicked()), this, SLOT(clickChooseBtn()));
	connect(changeBtn, SIGNAL(clicked()), this, SLOT(clickChooseBtn()));
	connect(inputFileBtn, SIGNAL(clicked()), this, SLOT(getExcelPath()));
	connect(outputFileBtn, SIGNAL(clicked()), this, SLOT(getConfigPath()));
	connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(showSelectJsonText()));
	connect(okBtn, SIGNAL(clicked()), this, SLOT(writeJson()));
}

xls2erl::~xls2erl()
{
	delete okBtn;
	delete gridLayout;
}

void xls2erl::init()
{
	gridLayout = new QGridLayout(this);
	jsonPath = "../game_server.spec";
	okBtn = new QPushButton(QString::fromLocal8Bit("�޸�"));
	genBtn = new QPushButton(QString::fromLocal8Bit("����"));
	btnLayout = new QHBoxLayout(this);
	btnLayout->addWidget(okBtn);
	btnLayout->addWidget(genBtn);
	comboBox = new QComboBox();
	comboBox->setDisabled(true);
	changeBtn = new QRadioButton(QString::fromLocal8Bit("�޸�"));
	addBtn = new QRadioButton(QString::fromLocal8Bit("����"));
	addBtn->setChecked(true);
	chooseBtnGroup = new QButtonGroup(this);
	chooseBtnGroup->addButton(addBtn, 0);
	chooseBtnGroup->addButton(changeBtn, 1);
	chooseLayout = new QHBoxLayout(this);
	chooseLayout->addWidget(addBtn);
	chooseLayout->addWidget(changeBtn);
	nameLabel = new QLabel(QString::fromLocal8Bit("�ļ�������"));
	nameLineEdit = new QLineEdit();
	nameLineEdit->setPlaceholderText(QString::fromLocal8Bit("��bash�������õ�"));
	desLabel = new QLabel(QString::fromLocal8Bit("������"));
	desLineEdit = new QLineEdit();
	desLineEdit->setPlaceholderText(QString::fromLocal8Bit("xxx���ñ�"));
	inputLabel = new QLabel(QString::fromLocal8Bit("Excel�ļ�·����"));
	inputLineEdit = new QLineEdit();
	inputFileBtn = new QPushButton(tr("..."));
	inputFileBtn->setMaximumWidth(30);
	outputLabel = new QLabel(QString::fromLocal8Bit("Config���·����"));
	outputLineEdit = new QLineEdit();
	outputLineEdit->setPlaceholderText(QString::fromLocal8Bit("�����ļ���������ѭ�ø�ʽ->data_xxx.config"));
	outputFileBtn = new QPushButton(tr("..."));
	outputFileBtn->setMaximumWidth(30);
	sheetLabel = new QLabel(QString::fromLocal8Bit("sheet������"));
	sheetLineEdit = new QLineEdit();
	sheetLineEdit->setPlaceholderText(QString::fromLocal8Bit("��Excel�еı�����"));
	labelLabel = new QLabel(QString::fromLocal8Bit("�����ʼ��(Ĭ��5)��"));
	labelLineEdit = new QLineEdit(tr("5"));
	QRegExp regx("[1-9][0-9]+$");
	QValidator *validator = new QRegExpValidator(regx);
	labelLineEdit->setValidator(validator);
	beginLabel = new QLabel(QString::fromLocal8Bit("������ʼ��(Ĭ��6)��"));
	beginLineEdit = new QLineEdit(tr("6"));
	beginLineEdit->setValidator(validator);
	primarykeyLabel = new QLabel(QString::fromLocal8Bit("��������"));
	primarykeyLineEdit = new QLineEdit();
	primarykeyLineEdit->setPlaceholderText(QString::fromLocal8Bit("���ű��������"));
	syntaxLabel = new QLabel(QString::fromLocal8Bit("�﷨��⿪�أ�"));
	syntaxOnBtn = new QRadioButton(QString::fromLocal8Bit("����"));
	syntaxOffBtn = new QRadioButton(QString::fromLocal8Bit("�ر�"));
	syntaxOffBtn->setChecked(true);
	syntaxBtnGroup = new QButtonGroup(this);
	syntaxBtnGroup->addButton(syntaxOnBtn, 0);
	syntaxBtnGroup->addButton(syntaxOffBtn, 1);
	syntaxLayout = new QHBoxLayout(this);
	syntaxLayout->addWidget(syntaxOnBtn);
	syntaxLayout->addWidget(syntaxOffBtn);
	gridLayout->addLayout(chooseLayout, 1, 1);
	gridLayout->addWidget(comboBox, 1, 2);
	gridLayout->addWidget(nameLabel, 2, 1);
	gridLayout->addWidget(nameLineEdit, 2, 2);
	gridLayout->addWidget(desLabel, 3, 1);
	gridLayout->addWidget(desLineEdit, 3, 2);
	gridLayout->addWidget(inputLabel, 4, 1);
	gridLayout->addWidget(inputLineEdit, 4, 2);
	gridLayout->addWidget(inputFileBtn, 4, 3);
	gridLayout->addWidget(sheetLabel, 5, 1);
	gridLayout->addWidget(sheetLineEdit, 5, 2);
	gridLayout->addWidget(outputLabel, 6, 1);
	gridLayout->addWidget(outputLineEdit, 6, 2);
	gridLayout->addWidget(outputFileBtn, 6, 3);
	gridLayout->addWidget(labelLabel, 7, 1);
	gridLayout->addWidget(labelLineEdit, 7, 2);
	gridLayout->addWidget(beginLabel, 8, 1);
	gridLayout->addWidget(beginLineEdit, 8, 2);
	gridLayout->addWidget(primarykeyLabel, 9, 1);
	gridLayout->addWidget(primarykeyLineEdit, 9, 2);
	gridLayout->addWidget(syntaxLabel, 10, 1);
	gridLayout->addLayout(syntaxLayout, 10, 2);
	gridLayout->addLayout(btnLayout, 11, 2);
	this->setLayout(gridLayout);
}

QJsonObject xls2erl::getAllJsonObject()
{
	QFile file(jsonPath);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QString value = file.readAll();
	file.close();

	QJsonParseError parseJsonErr;
	QJsonDocument document = QJsonDocument::fromJson(value.toUtf8(), &parseJsonErr);
	if (!(parseJsonErr.error == QJsonParseError::NoError))
	{
		qDebug() << tr("����json�ļ�����");
		return QJsonObject();
	}
	QJsonObject jsonObject = document.object();
	return jsonObject;
}

void xls2erl::showJsonKeys()
{
	QJsonObject jsonObject = getAllJsonObject();
	comboBox->addItems(jsonObject.keys().toVector().toList());
}

void xls2erl::clickChooseBtn()
{
	switch (chooseBtnGroup->checkedId())
	{
	case 0:
		comboBox->setDisabled(true);
		nameLineEdit->setDisabled(false);
		break;
	case 1:
		comboBox->setDisabled(false);
		nameLineEdit->setDisabled(true);
		break;
	default:
		break;
	}
}

void xls2erl::showSelectJsonText()
{
	int Index = comboBox->currentIndex();
	QJsonObject jsonObject = getAllJsonObject();
	QString Key = jsonObject.keys().toVector().at(Index);
	QJsonValue jsonValueList =  jsonObject.value(Key);
	QJsonObject item = jsonValueList.toObject();
	nameLineEdit->setText(Key);
	desLineEdit->setText(item["description"].toString());
	inputLineEdit->setText(item["workbook"].toString());
	outputLineEdit->setText(item["output"].toString());
	sheetLineEdit->setText(item["sheet"].toString());
	labelLineEdit->setText(QString::number(item["label"].toInt()));
	beginLineEdit->setText(QString::number(item["begin"].toInt()));
	primarykeyLineEdit->setText(item["primkey"].toString());
	QString syntaxFlag = item["syntax"].toString();
	if (syntaxFlag.compare(tr("off")) == 0)
	{
		syntaxOffBtn->setChecked(true);
		syntaxOnBtn->setChecked(false);
	}
	else
	{
		syntaxOffBtn->setChecked(false);
		syntaxOnBtn->setChecked(true);
	}
	return;
}

void xls2erl::getExcelPath()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ��Excel�ļ�"),
		tr("."), tr("Excel Files(*.xlsm)"));
	if (!fileName.isEmpty() && fileName.indexOf("doc") != -1)
	{
		QStringList pathList = fileName.split("doc");
		inputLineEdit->setText(tr("../../doc").append(pathList[1]));
	}
}

void xls2erl::getConfigPath()
{
	QString fileName = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("ѡ��Config�ļ�"),
		tr("."), tr("Config Files(*.config)"));
	if (!fileName.isEmpty() && fileName.indexOf("doc") != -1)
	{
		QStringList pathList = fileName.split("doc");
		outputLineEdit->setText(tr("../../doc").append(pathList[1]));
	}
}

void xls2erl::writeJson()
{
	if (!nameLineEdit->text().isEmpty() && !desLineEdit->text().isEmpty()
		&& !inputLineEdit->text().isEmpty() && !sheetLineEdit->text().isEmpty()
		&& !outputLineEdit->text().isEmpty() && !labelLineEdit->text().isEmpty()
		&& !beginLineEdit->text().isEmpty() && !primarykeyLineEdit->text().isEmpty())
	{
		QJsonObject jsonObject = getAllJsonObject();
		QString key = nameLineEdit->text();
		QJsonObject writeObject;
		jsonObject.insert(key, getInsertJsonObject(writeObject));
		QFile file(jsonPath);
		if (file.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			QMessageBox::about(NULL, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("д��ɹ�"));
			QJsonDocument jsonDocument;
			jsonDocument.setObject(jsonObject);
			file.write(jsonDocument.toJson(QJsonDocument::Indented));
			file.close();
			showJsonKeys();
		}
		else
		{
			QMessageBox::about(NULL, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("д��ʧ�ܣ�����Ƿ�����ļ�ռ������"));
		}
	}
	else
	{
		QMessageBox::about(NULL, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("д��ʧ�ܣ�����Ƿ����δ��д�Ŀ���"));
	}
	return;
}

QJsonObject xls2erl::getInsertJsonObject(QJsonObject jsonObject)
{
	jsonObject.insert("description", desLineEdit->text());
	jsonObject.insert("workbook", inputLineEdit->text());
	jsonObject.insert("output", outputLineEdit->text());
	jsonObject.insert("sheet", sheetLineEdit->text());
	jsonObject.insert("label", labelLineEdit->text().toInt());
	jsonObject.insert("begin", beginLineEdit->text().toInt());
	jsonObject.insert("primkey", primarykeyLineEdit->text());
	if (syntaxOffBtn->isChecked())
	{
		jsonObject.insert("syntax", tr("off"));
	}
	else
	{
		jsonObject.insert("syntax", tr("on"));
	}
	return jsonObject;
}