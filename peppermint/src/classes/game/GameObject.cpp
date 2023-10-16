#include <peppermint/classes/game/GameObject.h>

#include <peppermint/Exceptions.hpp>

using namespace peppermint::game;
using namespace peppermint::exceptions::gameObject;

GameObject::GameObject() {
	this->transform = new Transform();
}

GameObject::~GameObject() {
	for (int i = 0; i < this->components.size(); i++) {
		delete this->components[i];
	}
	delete &this->components;
	delete this->transform;
}

template <Component c> Component* GameObject::addComponent() {
	for (int i = 0; i < this->components.size(); i++) {
		if (typeid(this->components[i]) == typeid(c)) {
			throw AlreadyHasComponentException();
		}
	}
}

template<Component c> Component* GameObject::getComponent() {

}