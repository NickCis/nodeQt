#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <node/v8.h>
#include <node/node.h>

#include <QApplication>

class Application : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;
		static void Init(v8::Handle<v8::Object> target);

	protected:
		Application();

		static v8::Handle<v8::Value> New(const v8::Arguments& args);
		static v8::Handle<v8::Value> exec(const v8::Arguments& args);
		static v8::Handle<v8::Value> processEvents(const v8::Arguments& args);

		// Your own object variables here
		QApplication* app;

};

#endif
