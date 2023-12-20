#ifndef PPMINT_SCRIPTS_TESTCOMPONENT_H
#define PPMINT_SCRIPTS_TESTCOMPONENT_H

#define TestComponent_SCRIPT_COMPONENT_INDEX 1

#include <peppermint/classes/game/components/ScriptComponent.h>

#include <peppermint/classes/game/GameObject.h>

#include <string>

namespace peppermint {
	namespace game {
		namespace components {
			class TestComponent : public ScriptComponent {
			public:
				void start();
				void loop();

				std::string message = "default message";

				GameObject* cam;
				vec3 originalOffset;

				
				// all below are required for normal function (in other words include them in a template)
				vector<byte> serialiseData();
				void deserialiseData(vector<byte> bytes);
				void makeConnections(vector<Asset*>* assets, vector<Component*>* components);

				static const unsigned int scriptType = TestComponent_SCRIPT_COMPONENT_INDEX;

				inline unsigned int getScriptType() { return TestComponent_SCRIPT_COMPONENT_INDEX; }
			};
		}
	}
}

#endif