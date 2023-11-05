#ifndef PPMINT_SERIALISABLE_H
#define PPMINT_SERIALISABLE_H

#include <vector>

using namespace std;

namespace peppermint {
	class Serialisable {
	public:
		virtual vector<byte> serialise() = 0;
		virtual void deserialise(vector<byte>) = 0;

		void* serialisedID;
		vector<void*> relatedSerialisedIDs;

		unsigned long long getDeserialisedSize();
	protected:
		unsigned long long deserialisedSize = 0;
	};
}

#endif