#include "QtWindow.moc"

//using namespace v8;

QWindow::QWindow() {}
QWindow::~QWindow() {}

void QWindow::closeEvent(QCloseEvent *event)
{
/*	if (maybeSave()) {
		writeSettings();
		event->accept();
	} else {
		event->ignore();
	}*/
	emit closed();
	event->accept();
}
