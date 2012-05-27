#include "Window.hpp"

using namespace v8;

void Window::RegisterMethods(Local<FunctionTemplate> tpl) {
	// Add all prototype methods, getters and setters here.
	NODE_SET_PROTOTYPE_METHOD(tpl, "ConnectClosed", ConnectClosed);
}

Local<String> Window::GetName()
{
	Local<String> name = String::NewSymbol("Window");
	return name;
}

Window::Window(): Widget()
{
	this->asClosed = NULL;
};

Window::~Window()
{
	if (this->asClosed)
		delete this->asClosed;
};

Handle<Value> Window::New(const Arguments& args) {
	HandleScope scope;

	// Creates a new instance object of this type and wraps it.
	Window* obj = new Window();

	obj->qwidget = new QWindow();

	obj->Wrap(args.This());
	return args.This();
}

Handle<Value> Widget::ConnectClosed(const Arguments& args)
{
	HandleScope scope;
	Window* obj = ObjectWrap::Unwrap<Window>(args.This());

	if (!args[0]->IsFunction())
		return ThrowException(Exception::TypeError(String::New("Second argument must be a callback function")));

	// There's no ToFunction(), use a Cast instead.
	Local<Function> callback = Local<Function>::Cast(args[1]);
	if (! obj->asClosed)
		obj->asClosed = new ActionSlot();

	obj->asClosed->setCallback(callback);
	QObject::connect(obj->qwidget, SIGNAL(closed()), obj->asClosed, SLOT(callCallback()));
	return scope.Close(Boolean::New(true));
}
