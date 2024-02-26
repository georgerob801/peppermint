#ifndef CMPNT_HE_GO_SPIN_H
#define CMPNT_HE_GO_SPIN_H

#define HeGoSpin_SCRIPT_COMPONENT_INDEX 0

#include <peppermint/classes/game/components/ScriptComponent.h>
#include <peppermint/classes/game/components/Transform.h>

namespace peppermint {
	namespace game {
		namespace components {
			class HeGoSpin : public ScriptComponent {
			public:
				void start();
				void loop();


				Transform* toothless = nullptr;


				vector<byte> serialiseData();
				void deserialiseData(vector<byte> bytes);
				void makeConnections(vector<Asset*>* assets, vector<Component*>* components);

				static const unsigned int scriptType = HeGoSpin_SCRIPT_COMPONENT_INDEX;
				inline unsigned int getScriptType() { return HeGoSpin_SCRIPT_COMPONENT_INDEX; }
			};
		}
	}
}

#endif