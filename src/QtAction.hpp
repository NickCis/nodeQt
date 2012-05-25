#ifndef __Q_ACTION_SLOT__
#define __Q_ACTION_SLOT__
#include <stdio.h>
#include <QObject>

class ActionSlot : public QObject
{
	Q_OBJECT

	public:
		ActionSlot();
		int getValue();

	public slots:
		void printMe();

	private:
		int m_value;
};

#endif
