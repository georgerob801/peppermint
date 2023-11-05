#include <peppermint/Serialisable.h>

using namespace peppermint;

unsigned long long Serialisable::getDeserialisedSize() {
	return this->deserialisedSize;
}