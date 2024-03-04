#include <peppermint/Serialisable.h>

using namespace peppermint;

unsigned long long Serialisable::getDeserialisedSize() {
	return this->deserialisedSize;
}

void** Serialisable::getSerialisedID(void** in) {
	(*in) = this != nullptr ? this->serialisedID == nullptr ? this : this->serialisedID : nullptr;
	return in;
}