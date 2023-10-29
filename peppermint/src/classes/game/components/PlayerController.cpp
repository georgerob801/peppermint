#include <peppermint/classes/game/components/PlayerController.h>

#include <peppermint/managers/EngineManager.h>
#include <peppermint/managers/InputManager.h>
#include <peppermint/classes/game/GameObject.h>

using namespace peppermint::game::components;
using namespace peppermint::managers;

void PlayerController::loop() {
	GameObject* go = (GameObject*)this->getGameObject();
	this->updateInputStatus();

	this->attemptingCollidingMove = false;

	if (this->currentlyPressing.forward && !this->currentlyMoving.forward && !this->currentlyPressing.backward && !this->currentlyMoving.backward && !this->currentlyPressing.left && !this->currentlyMoving.left && !this->currentlyPressing.right && !this->currentlyMoving.right) {
		this->facing = UP;
		if (this->navMap == nullptr) {
			this->currentlyMoving.forward = true;
			this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
		} else {
			if (go->transform->position.y < this->navMap->height - 1 && this->navMap->isNavigable(std::round((int)go->transform->position.x), std::round((int)go->transform->position.y + 1))) {
				this->currentlyMoving.forward = true;
				this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
			} else {
				this->attemptingCollidingMove = true;
			}
		}
	}
	if (this->currentlyPressing.backward && !this->currentlyMoving.backward && !this->currentlyPressing.forward && !this->currentlyMoving.forward && !this->currentlyPressing.left && !this->currentlyMoving.left && !this->currentlyPressing.right && !this->currentlyMoving.right) {
		this->facing = DOWN;
		if (this->navMap == nullptr) {
			this->currentlyMoving.backward = true;
			this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
		} else {
			if (go->transform->position.y > 0 && this->navMap->isNavigable(std::round((int)go->transform->position.x), std::round((int)go->transform->position.y - 1))) {
				this->currentlyMoving.backward = true;
				this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
			} else {
				this->attemptingCollidingMove = true;
			}
		}
	}
	if (this->currentlyPressing.left && !this->currentlyMoving.left && !this->currentlyPressing.right && !this->currentlyMoving.right && !this->currentlyPressing.forward && !this->currentlyMoving.forward && !this->currentlyPressing.backward && !this->currentlyMoving.backward) {
		this->facing = LEFT;
		if (this->navMap == nullptr) {
			this->currentlyMoving.left = true;
			this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
		} else {
			if (go->transform->position.x > 0 && this->navMap->isNavigable(std::round((int)go->transform->position.x - 1), std::round((int)go->transform->position.y))) {
				this->currentlyMoving.left = true;
				this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
			} else {
				this->attemptingCollidingMove = true;
			}
		}
	}
	if (this->currentlyPressing.right && !this->currentlyMoving.right && !this->currentlyPressing.left && !this->currentlyMoving.left && !this->currentlyPressing.forward && !this->currentlyMoving.forward && !this->currentlyPressing.backward && !this->currentlyMoving.backward) {
		this->facing = RIGHT;
		if (this->navMap == nullptr) {
			this->currentlyMoving.right = true;
			this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
		} else {
			if (go->transform->position.x < this->navMap->width - 1 && this->navMap->isNavigable(std::round((int)go->transform->position.x + 1), std::round((int)go->transform->position.y))) {
				this->currentlyMoving.right = true;
				this->moveStartPosition = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
			} else {
				this->attemptingCollidingMove = true;
			}
		}
	}

	if (this->currentlyMoving.forward) {
		go->transform->position += vec3(0.0f, 1.0f, 0.0f) * this->speed * (float)EngineManager::deltaTime;
		if (go->transform->position.y >= this->moveStartPosition.y + 1.0f - this->snapRange) {
			go->transform->position.y = std::round(go->transform->position.y);
			this->currentlyMoving.forward = false;
		}
	}

	if (this->currentlyMoving.backward) {
		go->transform->position -= vec3(0.0f, 1.0f, 0.0f) * this->speed * (float)EngineManager::deltaTime;
		if (go->transform->position.y <= this->moveStartPosition.y - 1.0f + this->snapRange) {
			go->transform->position.y = std::round(go->transform->position.y);
			this->currentlyMoving.backward = false;
		}
	}

	if (this->currentlyMoving.left) {
		go->transform->position -= vec3(1.0f, 0.0f, 0.0f) * this->speed * (float)EngineManager::deltaTime;
		if (go->transform->position.x <= this->moveStartPosition.x - 1.0f + this->snapRange) {
			go->transform->position.x = std::round(go->transform->position.x);
			this->currentlyMoving.left = false;
		}
	}

	if (this->currentlyMoving.right) {
		go->transform->position += vec3(1.0f, 0.0f, 0.0f) * this->speed * (float)EngineManager::deltaTime;
		if (go->transform->position.x >= this->moveStartPosition.x + 1.0f - this->snapRange) {
			go->transform->position.x = std::round(go->transform->position.x);
			this->currentlyMoving.right = false;
		}
	}
}

void PlayerController::updateInputStatus() {
	if (InputManager::active(InputManager::FORWARD) && !this->currentlyPressing.forward) {
		this->currentlyPressing.forward = true;
	} else this->currentlyPressing.forward = false;
	if (InputManager::active(InputManager::BACKWARD) && !this->currentlyPressing.backward) {
		this->currentlyPressing.backward = true;
	} else this->currentlyPressing.backward = false;
	if (InputManager::active(InputManager::LEFT) && !this->currentlyPressing.left) {
		this->currentlyPressing.left = true;
	} else this->currentlyPressing.left = false;
	if (InputManager::active(InputManager::RIGHT) && !this->currentlyPressing.right) {
		this->currentlyPressing.right = true;
	} else this->currentlyPressing.right = false;
}

currentlyPressingStruct PlayerController::getActiveKeys() {
	currentlyPressingStruct out;
	if (InputManager::active(InputManager::FORWARD)) out.forward = true;
	if (InputManager::active(InputManager::BACKWARD)) out.backward = true;
	if (InputManager::active(InputManager::LEFT)) out.left = true;
	if (InputManager::active(InputManager::RIGHT)) out.right = true;

	return out;
}