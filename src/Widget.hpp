#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <v8.h>
#include <node.h>

#include <QWidget>

class Widget : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;
		static void Init(v8::Handle<v8::Object> target);
		QWidget* qwidget;

	protected:
		Widget();

		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static v8::Handle<v8::Value> resize(const v8::Arguments& args);
		static v8::Handle<v8::Value> show(const v8::Arguments& args);

		// Your own object variables here

};

#endif
