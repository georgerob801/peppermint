// This file will be generated by the peppermint editor

#include <peppermint/scripts/ScriptTypes.hpp>

peppermint::game::components::ScriptComponent* peppermint::scripts::createScriptComponent(unsigned int scriptType, vector<byte> bytes) {
	peppermint::game::components::ScriptComponent* out;

	switch (scriptType) {
	case 1:
		out = new GET_SCRIPT_COMPONENT_TYPE(1);
		break;
	default:
		throw peppermint::exceptions::userScripts::UnknownScriptException();
	}

	out->deserialise(bytes);

	return out;
}