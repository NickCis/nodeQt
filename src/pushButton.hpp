#ifndef PUSHBUTTON_HPP
#define PUSHBUTTON_HPP

#include <node/v8.h>
#include <node/node.h>
#include <QPushButton>

#include "Widget.hpp"
#include "QtAction.hpp"

class PushButton : public Widget {
	public:
		static void Init(v8::Handle<v8::Object> target);
		static void RegisterMethods(v8::Local<v8::FunctionTemplate> tpl);
		static v8::Local<v8::String> GetName();
//		QPushButton* qwidget;

	protected:
		PushButton(QString label);
		~PushButton();

		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static v8::Handle<v8::Value> Label(const v8::Arguments& args);

		//Connects
		static v8::Handle<v8::Value> ConnectClicked(const v8::Arguments& args);

		// Your own object variables here
		QString ButtonLabel;
		ActionSlot *asClicked;
};

#endif
