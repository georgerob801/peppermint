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
	this->transform->setGameObject((void*)this);
}

GameObject::~GameObject() {
	// cout << "here (gameobject)" << endl;
	for (unsigned int i = 0; i < this->components.size(); i++) {
		delete this->components[i];
	}
	this->components.clear();

	// free memory
	vector<Component*>().swap(this->components);
}

void GameObject::prependComponent(Component* comp) {
	this->components.insert(this->components.begin(), comp);

	comp->setGameObject((void*)this);
}

void GameObject::addComponent(Component* comp) {
	vector<Component*>::iterator index = find(this->components.begin(), this->components.end(), comp);

	if (index != this->components.end()) {
		throw AlreadyHasComponentException();
	}

	this->components.push_back(comp);
	comp->setGameObject((void*)this);
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

	for (unsigned int i = 0; i < sizeof(void*); i++) {
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
	unsigned long long position = 0x00;

	unsigned int numComponents = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	this->components.reserve(numComponents);

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	if (this->serialisedID == nullptr) {
		throw peppermint::exceptions::serialisation::world::CorruptedFileException();
	}

	for (unsigned int i = 0; i < numComponents; i++) {
		this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));
		if (this->relatedSerialisedIDs[this->relatedSerialisedIDs.size() - 1] == nullptr) throw peppermint::exceptions::serialisation::world::CorruptedFileException();
		position += sizeof(void*);
	}
}