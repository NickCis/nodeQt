#include "Widget.hpp"

using namespace v8;

Persistent<FunctionTemplate> Widget::constructor;

void Widget::Init(Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	Local<String> name = String::NewSymbol("Widget");

	constructor = Persistent<FunctionTemplate>::New(tpl);
	// ObjectWrap uses the first internal field to store the wrapped pointer.
	constructor->InstanceTemplate()->SetInternalFieldCount(1);
	constructor->SetClassName(name);

	// Add all prototype methods, getters and setters here.
	NODE_SET_PROTOTYPE_METHOD(constructor, "resize", resize);
	NODE_SET_PROTOTYPE_METHOD(constructor, "show", show);

	// This has to be last, otherwise the properties won't show up on the
	// object in JavaScript.
	target->Set(name, constructor->GetFunction());
}

Widget::Widget(void): ObjectWrap() {};

Handle<Value> Widget::New(const Arguments& args) {
	HandleScope scope;

	// Creates a new instance object of this type and wraps it.
	Widget* obj = new Widget();

	obj->qwidget = new QWidget();
	//FIXME: Hay un problema con los punteros
	//qwidget->show(); //Anda
	//obj->qwidget->show(); //No Anda - Segmentation Fault

	obj->Wrap(args.This());

	return args.This();
}


Handle<Value> Widget::resize(const Arguments& args) {
	HandleScope scope;
	if (args.Length() != 2) {
		return ThrowException(Exception::TypeError(
			String::New("First two arguments must be numbers X Y")));
	}

	// Retrieves the pointer to the wrapped object instance.
	Widget* obj = ObjectWrap::Unwrap<Widget>(args.This());
	obj->qwidget->resize(args[0]->ToInteger()->Value(), args[1]->ToInteger()->Value());


	return scope.Close(Boolean::New(true));
}

Handle<Value> Widget::show(const Arguments& args) {
	HandleScope scope;

	// Retrieves the pointer to the wrapped object instance.
	Widget* obj = ObjectWrap::Unwrap<Widget>(args.This());

	obj->qwidget->show();

	return scope.Close(Boolean::New(true));
}
