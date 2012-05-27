#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <node/v8.h>
#include <node/node.h>

#include <QWidget>
#include "QtAction.hpp"

class Widget : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;
		static void Init(v8::Handle<v8::Object> target);
		static void RegisterMethods(v8::Local<v8::FunctionTemplate> tpl);
		static v8::Local<v8::String> GetName();
		QWidget *qwidget;

	protected:
		Widget();
		~Widget();

		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static v8::Handle<v8::Value> resize(const v8::Arguments& args);
		static v8::Handle<v8::Value> show(const v8::Arguments& args);


		//Connects
		static v8::Handle<v8::Value> ConnectDestroyed(const v8::Arguments& args);

		// Your own object variables here
		ActionSlot *asDestroyed;
};

#endif
