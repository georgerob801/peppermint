#ifndef PPMINT_COMPONENT_SCRIPT_COMPONENT_H
#define PPMINT_COMPONENT_SCRIPT_COMPONENT_H

#include <peppermint-preview/classes/game/Component.h>
#include <peppermint-preview/classes/Asset.h>

namespace peppermint {
	namespace game {
		namespace components {
			class ScriptComponent : public Component {
			public:
				ScriptComponent();

				virtual vector<byte> serialiseData() = 0;
				virtual void deserialiseData(vector<byte> bytes) = 0;
				virtual void makeConnections(vector<Asset*>* assets, vector<Component*>* components) = 0;

				vector<byte> serialise();
				void deserialise(vector<byte> bytes);

				unsigned long long deserialisedDataSize = 0;

				static const unsigned int scriptType = 0;

				static unsigned int getScriptType(vector<byte> bytes);

				inline virtual unsigned int getScriptType() = 0;
			};
		}
	}
}

#endif