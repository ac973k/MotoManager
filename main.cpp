#include "MotoManager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	MotoManager moto;
	moto.show();
	
	return app.exec();
}
