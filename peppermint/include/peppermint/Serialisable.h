#ifndef PPMINT_SERIALISABLE_H
#define PPMINT_SERIALISABLE_H

#include <vector>

using namespace std;

namespace peppermint {
	class Serialisable {
	public:
		/// <summary>
		/// Serialise an object for writing to a file.
		/// </summary>
		/// <returns>A vector of bytes to be written to a file.</returns>
		virtual vector<byte> serialise() = 0;
		/// <summary>
		/// Read data from a vector of bytes into an object.
		/// </summary>
		/// <param name="bytes">The vector of bytes to be read.</param>
		virtual void deserialise(vector<byte> bytes) = 0;

		/// <summary>
		/// The serialised ID of an object.
		/// </summary>
		void* serialisedID;
		/// <summary>
		/// A vector containing the serialised IDs of objects related to this one.
		/// </summary>
		vector<void*> relatedSerialisedIDs;

		/// <summary>
		/// Get the size of the stored version of this object in bytes. (run after serialise())
		/// </summary>
		/// <returns>The size of this object in bytes when stored.</returns>
		unsigned long long getDeserialisedSize();

		void** getSerialisedID(void** in);
	protected:
		/// <summary>
		/// The calculated size in bytes of this object.
		/// </summary>
		unsigned long long deserialisedSize = 0;
	};
}

#endif