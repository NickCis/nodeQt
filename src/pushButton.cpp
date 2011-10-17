#include <node/v8.h>
#include <node/node.h>

#include <QPushButton>

#include "pushButton.hpp"
#include "Widget.hpp"

using namespace v8;


Persistent<FunctionTemplate> PushButton::constructor;

void PushButton::Init(Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	Local<String> name = String::NewSymbol("PushButton");

	constructor = Persistent<FunctionTemplate>::New(tpl);
	// ObjectWrap uses the first internal field to store the wrapped pointer.
	constructor->InstanceTemplate()->SetInternalFieldCount(1);
	constructor->SetClassName(name);

	// Add all prototype methods, getters and setters here.
	NODE_SET_PROTOTYPE_METHOD(constructor, "label", Label);
	NODE_SET_PROTOTYPE_METHOD(constructor, "resize", resize);
	NODE_SET_PROTOTYPE_METHOD(constructor, "show", show);

	// This has to be last, otherwise the properties won't show up on the
	// object in JavaScript.
	target->Set(name, constructor->GetFunction());
}

PushButton::PushButton(QString label): ObjectWrap(), ButtonLabel(label) {}


Handle<Value> PushButton::New(const Arguments& args) {
	HandleScope scope;
	if (args.Length() != 2) {
		return ThrowException(Exception::TypeError(
			String::New("First argument must be a string, second a widget")));
	}
	v8::String::AsciiValue v8Str(args[0]);
	char *cStr = (char*) malloc(strlen(*v8Str) + 1);
	strcpy(cStr, *v8Str);
	QString texto = cStr;

	// Creates a new instance object of this type and wraps it.
	//PushButton* obj = new PushButton(args[0]->ToString()->AsciiValue());
	Widget* parent = ObjectWrap::Unwrap<Widget>(args[1]->ToObject());
	PushButton* obj = new PushButton(texto);

	obj->qwidget = new QPushButton(texto, parent->qwidget);

	obj->Wrap(args.This());

	return args.This();
}


Handle<Value> PushButton::Label(const Arguments& args) {
	HandleScope scope;
	// Retrieves the pointer to the wrapped object instance.
	PushButton* obj = ObjectWrap::Unwrap<PushButton>(args.This());
	return scope.Close(String::New(obj->ButtonLabel));
}

Handle<Value> PushButton::resize(const Arguments& args) {
	HandleScope scope;
	if (args.Length() != 2) {
		return ThrowException(Exception::TypeError(
			String::New("First two arguments must be numbers X Y")));
	}

	// Retrieves the pointer to the wrapped object instance.
	PushButton* obj = ObjectWrap::Unwrap<PushButton>(args.This());
	obj->qwidget->resize(args[0]->ToInteger()->Value(), args[1]->ToInteger()->Value());
	return scope.Close(Boolean::New(true));
}

Handle<Value> PushButton::show(const Arguments& args) {
	HandleScope scope;
	// Retrieves the pointer to the wrapped object instance.
	PushButton* obj = ObjectWrap::Unwrap<PushButton>(args.This());
	obj->qwidget->show();
	return scope.Close(Boolean::New(true));
}
