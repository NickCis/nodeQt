#include <node/v8.h>
#include <node/node.h>

#include <QApplication>

#include "Application.hpp"

using namespace v8;

Persistent<FunctionTemplate> Application::constructor;

void Application::Init(Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	Local<String> name = String::NewSymbol("Application");

	constructor = Persistent<FunctionTemplate>::New(tpl);
	// ObjectWrap uses the first internal field to store the wrapped pointer.
	constructor->InstanceTemplate()->SetInternalFieldCount(1);
	constructor->SetClassName(name);

	// Add all prototype methods, getters and setters here.
	NODE_SET_PROTOTYPE_METHOD(constructor, "exec", exec);
	NODE_SET_PROTOTYPE_METHOD(constructor, "processEvents", processEvents);

	// This has to be last, otherwise the properties won't show up on the
	// object in JavaScript.
	target->Set(name, constructor->GetFunction());
}

Application::Application(): ObjectWrap() {}


Handle<Value> Application::New(const Arguments& args) {
	HandleScope scope;

	// Creates a new instance object of this type and wraps it.
	Application* obj = new Application();

	obj->app = new QApplication(0, NULL);

	obj->Wrap(args.This());

	return args.This();
}


Handle<Value> Application::exec(const Arguments& args) {
	HandleScope scope;

	// Retrieves the pointer to the wrapped object instance.
	Application* obj = ObjectWrap::Unwrap<Application>(args.This());

	obj->app->exec();

	return scope.Close(Boolean::New(true));
}

Handle<Value> Application::processEvents(const Arguments& args) {
	HandleScope scope;

	// Retrieves the pointer to the wrapped object instance.
	Application* obj = ObjectWrap::Unwrap<Application>(args.This());
	if (obj->app->hasPendingEvents())
		obj->app->processEvents();

	return scope.Close(Boolean::New(true));
}
