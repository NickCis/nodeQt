#include "QtAction.moc"

using namespace v8;

ActionSlot::ActionSlot(): QObject() {m_value = 0;};

void ActionSlot::printMe()
{
	fprintf(stderr, "Imprimir =========== %d\n", this->m_value);
}

int ActionSlot::getValue() {
	return this->m_value;
}

void ActionSlot::calleame()
{
	fprintf(stderr, "1CBB =========== \n");
	const unsigned argc = 2;
	fprintf(stderr, "2CBB =========== \n");
	Local<Value> argv[argc] = {
		Local<Value>::New(Null()),
		Local<Value>::New(Integer::New(42))
	};
	fprintf(stderr, "3CBB =========== \n");
	this->call->Call(Context::GetCurrent()->Global(), argc, argv);
	fprintf(stderr, "4CBB =========== \n");
}
