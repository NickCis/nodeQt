#include "pushButton.hpp"

using namespace v8;

void PushButton::Init(Handle<Object> target)
{
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

PushButton::PushButton(QString label): ButtonLabel(label)
{
	this->asClicked = NULL;
}

PushButton::~PushButton()
{
	fprintf(stderr, "I'm PushButton destroying, is it correct?\n");
	if (this->asClicked)
		delete this->asClicked;
};

void PushButton::RegisterMethods(Local<FunctionTemplate> tpl) {
	// Add all prototype methods, getters and setters here.
	Widget::RegisterMethods(tpl);
	NODE_SET_PROTOTYPE_METHOD(tpl, "Label", Label);
	NODE_SET_PROTOTYPE_METHOD(tpl, "ConnectClicked", ConnectClicked);
}

Local<String> PushButton::GetName()
{
	Local<String> name = String::NewSymbol("PushButton");
	return name;
}

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

Handle<Value> PushButton::ConnectClicked(const Arguments& args) {
	HandleScope scope;
	// Ensure that we got a callback. Generally, your functions should have
	// optional callbacks. In this case, you can declare an empty
	// Local<Function> handle and check for content before calling.

	PushButton* obj = ObjectWrap::Unwrap<PushButton>(args.This());

	if (!args[0]->IsFunction()) {
		return ThrowException(Exception::TypeError(
					String::New("Second argument must be a callback function")));
	}
	// There's no ToFunction(), use a Cast instead.
	Local<Function> callback = Local<Function>::Cast(args[0]);
	if (!obj->asClicked)
		obj->asClicked = new ActionSlot();
	obj->asClicked->setCallback(callback);
	QObject::connect(obj->qwidget, SIGNAL(clicked()), obj->asClicked, SLOT(callCallback()));
    return scope.Close(Undefined());
}
