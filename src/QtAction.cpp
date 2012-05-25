#include "QtAction.moc"

void ActionSlot::printMe()
{
	fprintf(stderr, "Imprimir =========== %d\n", this->m_value);
}

int ActionSlot::getValue() {
	return this->m_value;
}
ActionSlot::ActionSlot(): QObject() {m_value = 0;};
