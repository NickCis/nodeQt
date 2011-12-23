#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <v8.h>
#include <node.h>

#include <QWidget>
#include <QApplication>

//Handle<Value> Async(const Arguments& args);
void AsyncWork(uv_work_t* req);
void AsyncAfter(uv_work_t* req);
// We use a struct to store information about the asynchronous "work request".

class Application : public node::ObjectWrap {
	public:
		static v8::Persistent<v8::FunctionTemplate> constructor;
		static void Init(v8::Handle<v8::Object> target);
		QApplication* app;

	protected:
		Application();

		static v8::Handle<v8::Value> New(const v8::Arguments& args);

		// Your own object variables here

};

#endif
