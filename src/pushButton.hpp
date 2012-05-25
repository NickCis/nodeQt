#ifndef PUSHBUTTON_HPP
#define PUSHBUTTON_HPP

#include <node/v8.h>
#include <node/node.h>
#include <QPushButton>

#include "Widget.hpp"
#include "QtAction.hpp"

//TODO: sacar stdio.h
#include <stdio.h>

class PushButton : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;
		static void Init(v8::Handle<v8::Object> target);

		//static Handle<Value> GetOnClick(Local<String> name, const AccessorInfo& info);
		//static void SetOnClick(Local<String> name, Local<Value> value, const AccessorInfo& info);

	protected:
		PushButton(QString label);

		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static v8::Handle<v8::Value> Label(const v8::Arguments& args);
		static v8::Handle<v8::Value> resize(const v8::Arguments& args);
		static v8::Handle<v8::Value> show(const v8::Arguments& args);
		static v8::Handle<v8::Value> Callback(const v8::Arguments& args);

		// Your own object variables here
		QString ButtonLabel;
		QPushButton* qwidget;
		//Persistent<Function> onClick;

};

#endif
