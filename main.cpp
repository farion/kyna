#define FLAG_DEBUG

#include <QApplication>
#include <QMainWindow>
#include <QDebug>
#include <iostream>

#include "kynawindow.h"

void myMessageOutput ( QtMsgType type, const char *msg )
{
	switch ( type )
	{
		default:
			std::cout << msg << std::endl;
	}
}


void cleanLayout(QLayout *layout)
{
	QLayoutItem *child;
	while ( ( child = layout->takeAt ( 0 ) ) != 0 )
	{
		delete child;
	}
}


int main ( int argc, char *argv[] )
{
	qInstallMsgHandler ( myMessageOutput );

	QApplication app ( argc, argv );
	KynaWindow *window = new KynaWindow();
	window->grabKeyboard ();
	window->show();

	return app.exec();

}
