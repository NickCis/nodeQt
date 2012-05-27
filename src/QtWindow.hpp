#ifndef __Q_WINDOW__
#define __Q_WINDOW__

//#include <node/v8.h>
//#include <node/node.h>
#include <QObject>

class QWindow : public QWidget
{
	Q_OBJECT

	public:
		Window();
		~Window();

	signals:
		void closed();

};
#endif
