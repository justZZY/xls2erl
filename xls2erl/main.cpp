#include "xls2erl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	xls2erl w;
	w.show();
	return a.exec();
}
