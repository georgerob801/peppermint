#ifndef PPMINT_SERIALISABLE_H
#define PPMINT_SERIALISABLE_H

#include <vector>

using namespace std;

namespace peppermint {
	class Serialisable {
	public:
		virtual vector<byte> serialise() = 0;
		virtual void deserialise(vector<byte>) = 0;
	protected:

	};
}

#endif