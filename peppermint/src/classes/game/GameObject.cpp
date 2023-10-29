#include <peppermint/classes/game/GameObject.h>

#include <peppermint/Exceptions.hpp>
#include <typeinfo>
#include <type_traits>

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