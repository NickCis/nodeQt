#ifndef __Q_ACTION_SLOT__
#define __Q_ACTION_SLOT__
//TODO: sacar stdio.h
#include <stdio.h>
#include <QObject>

#include <node/v8.h>
#include <node/node.h>

class ActionSlot : public QObject
{
	Q_OBJECT

	public:
		ActionSlot();
		int getValue();
		v8::Handle<v8::Function> call;

	public slots:
		void printMe();
		void calleame();

	private:
		int m_value;
};

#endif
