#include <peppermint/classes/game/GameObject.h>

#include <peppermint/Exceptions.hpp>
#include <typeinfo>
#include <type_traits>
#include <format>

using namespace peppermint::game;
using namespace peppermint::exceptions::gameObject;

GameObject::GameObject() {
	this->transform = new Transform();
	this->components.push_back(transform);
}

GameObject::~GameObject() {
	for (int i = 0; i < this->components.size(); i++) {
		delete this->components[i];
	}
	delete &this->components;
	delete this->transform;
}

template <class T> Component* GameObject::addComponent() {
	if (!std::is_base_of(Component, T)) {
		throw IsNotComponentException();
	}

	for (int i = 0; i < this->components.size(); i++) {
		if (typeid(this->components[i]) == typeid(T)) {
			throw AlreadyHasComponentException();
		}
	}

	T* newComponent = new T();
	this->components.push_back(newComponent);

	return newComponent;
}

template<class T> Component* GameObject::getComponent() {
	if (!std::is_base_of(Component, T)) {
		throw IsNotComponentException();
	}

	for (int i = 0; i < this->components.size(); i++) {
		if (typeid(this->components[i] == typeid(T))) {
			return this->components[i];
		}
	}

	throw ComponentNotFoundException();
}

vector<byte> GameObject::serialise() {
	vector<byte> out;

	unsigned int numComponents = this->components.size();
	byte* componentsBytes = (byte*)static_cast<char*>(static_cast<void*>(&numComponents));

	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(componentsBytes[i]);
	}

	void* id = this;
	byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

	for (unsigned int i = 0; i < sizeof(id) / sizeof(byte); i++) {
		out.push_back(toAdd2[i]);
	}

	for (unsigned int i = 0; i < this->components.size(); i++) {
		/*byte* componentBytes = (byte*)static_cast<char*>(static_cast<void*>(this->components[i]));
		vector<byte> component = this->components[i]->serialise();
		out.insert(out.end(), component.begin(), component.end());*/

		byte* componentID = reinterpret_cast<byte*>(&this->components[i]);
		for (unsigned int j = 0; j < sizeof(void*); j++) {
			out.push_back(componentID[j]);
		}
	}

	//out += "GameObject:\n";
	//out += std::format("Components: {}\n", this->components.size());

	//for (unsigned int i = 0; i < this->components.size(); i++) {
	//	out += std::format("ID: {}\n", (void*)this->components[i]);
	//}

	return out;
}

void GameObject::deserialise(vector<byte> bytes) {

}