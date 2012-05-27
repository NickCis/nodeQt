#ifndef __Q_ACTION_SLOT__
#define __Q_ACTION_SLOT__

#include <node/v8.h>
#include <node/node.h>
#include <QObject>

class ActionSlot : public QObject
{
	Q_OBJECT

	public:
		ActionSlot();
		~ActionSlot();

		void setCallback(v8::Handle<v8::Function> callback);
		v8::Persistent<v8::Function> getCallback();
		void clearCallback();

	public slots:
		void callCallback();

	private:
		v8::Persistent<v8::Function> callback;
};

#endif
