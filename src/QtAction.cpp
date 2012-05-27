#include "QtAction.moc"

using namespace v8;

ActionSlot::ActionSlot(): QObject() {};

ActionSlot::~ActionSlot()
{
	this->clearCallback();
}

void ActionSlot::clearCallback()
{
	if (this->callback.IsEmpty()) {
		this->callback.Dispose();
		this->callback.Clear();
	}

}
void ActionSlot::setCallback(Handle<Function> callback)
{
	this->clearCallback();
	this->callback = Persistent<Function>::New(callback);
	return;
}

Persistent<Function> ActionSlot::getCallback()
{
	return this->callback;
}

void ActionSlot::callCallback()
{
	HandleScope scope;
	const unsigned argc = 2;
	Local<Value> argv[argc] = {
		Local<Value>::New(Null()),
		Local<Value>::New(Integer::New(42))
	};
	this->callback->Call(Context::GetCurrent()->Global(), argc, argv);
}
