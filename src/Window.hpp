#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <node/v8.h>
#include <node/node.h>
#include "Widget.hpp"

#include <QWidget>
#include "QtAction.hpp"
#include "QtWindow.hpp"

class Window : public Widget {
	public:
		static void Init(v8::Handle<v8::Object> target);
		QWindow *qwidget;

	protected:
		Window();
		~Window();

		//Connects
		static v8::Handle<v8::Value> ConnectClosed(const v8::Arguments& args);

		// Your own object variables here
		ActionSlot *asClosed;
};

#endif
