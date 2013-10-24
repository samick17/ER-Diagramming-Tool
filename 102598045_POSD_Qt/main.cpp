#include "MyThread.h"
#include "GUIView.h"
#include <QtGui/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
	MyThread thread1 = MyThread();

	thread1.start();

	QApplication  a(argc, argv);
	
	GUIView guiView;
	guiView.show();	
	return a.exec();
	
	/*QCoreApplication a(argc, argv);
	a.exec();
	return 0;*/
}