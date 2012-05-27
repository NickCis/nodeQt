#include "Widget.hpp"

using namespace v8;

Persistent<FunctionTemplate> Widget::constructor;

void Widget::Init(Handle<Object> target) {
	HandleScope scope;

	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	Local<String> name = GetName();

	tpl->SetClassName(name);
	// ObjectWrap uses the first internal field to store the wrapped pointer.
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	RegisterMethods(tpl);

	// This has to be last, otherwise the properties won't show up on the
	// object in JavaScript.
	constructor = Persistent<FunctionTemplate>::New(tpl);
	target->Set(name, constructor->GetFunction());
}

void Widget::RegisterMethods(Local<FunctionTemplate> tpl) {
	// Add all prototype methods, getters and setters here.
	NODE_SET_PROTOTYPE_METHOD(tpl, "resize", resize);
	NODE_SET_PROTOTYPE_METHOD(tpl, "show", show);
	NODE_SET_PROTOTYPE_METHOD(tpl, "ConnectDestroyed", ConnectDestroyed);
}

Local<String> Widget::GetName()
{
	Local<String> name = String::NewSymbol("Widget");
	return name;
}

Widget::Widget(): ObjectWrap()
{
	this->asDestroyed = NULL;
	this->qwidget = NULL;
};

Widget::~Widget()
{
	if (this->asDestroyed)
		delete this->asDestroyed;
	if(this->qwidget)
		delete this->qwidget;
};

Handle<Value> Widget::New(const Arguments& args) {
	HandleScope scope;

	// Creates a new instance object of this type and wraps it.
	Widget* obj = new Widget();

	obj->qwidget = new QWidget();

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
	Widget* obj = ObjectWrap::Unwrap<Widget>(args.This());

	obj->qwidget->show();
	return scope.Close(Boolean::New(true));
}

Handle<Value> Widget::ConnectDestroyed(const Arguments& args)
{
	HandleScope scope;
	Widget* obj = ObjectWrap::Unwrap<Widget>(args.This());

	if (!args[0]->IsFunction())
		return ThrowException(Exception::TypeError(String::New("Second argument must be a callback function")));

	// There's no ToFunction(), use a Cast instead.
	Local<Function> callback = Local<Function>::Cast(args[1]);
	if (! obj->asDestroyed)
		obj->asDestroyed = new ActionSlot();

	obj->asDestroyed->setCallback(callback);
	QObject::connect(obj->qwidget, SIGNAL(destroyed()), obj->asDestroyed, SLOT(callCallback()));
	return scope.Close(Boolean::New(true));
}
