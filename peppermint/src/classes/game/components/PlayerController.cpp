#include <peppermint/classes/game/components/PlayerController.h>

#include <peppermint/managers/EngineManager.h>
#include <peppermint/managers/InputManager.h>
#include <peppermint/classes/game/GameObject.h>

#include <format>

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

	if (this->navMap != nullptr) {
		if (go->transform->position.x < 0) go->transform->position.x = 0;
		if (go->transform->position.x >= this->navMap->width) go->transform->position.x = this->navMap->width - 1;
		if (go->transform->position.y < 0) go->transform->position.y = 0;
		if (go->transform->position.y >= this->navMap->height) go->transform->position.y = this->navMap->height - 1;

		while (!this->navMap->isNavigable((int)go->transform->position.x, (int)go->transform->position.y) && go->transform->position.x > 0 && go->transform->position.x < this->navMap->width - 1 && go->transform->position.y > 0 && go->transform->position.y < this->navMap->height - 1) {
			if (this->facing == UP) go->transform->position.y -= 1;
			if (this->facing == DOWN) go->transform->position.y += 1;
			if (this->facing == LEFT) go->transform->position.x += 1;
			if (this->facing == RIGHT) go->transform->position.x -= 1;
		}
	}

	if ((length(go->transform->position - this->lastLocation) >= 1.0f || this->facing != this->lastFacing) && this->navMap != nullptr) {
		unsigned int acWm = EngineManager::activeWorldManager;
		this->onChangeTile();
		if (EngineManager::activeWorldManager == acWm) this->lastLocation = vec3(std::round(go->transform->position.x), std::round(go->transform->position.y), std::round(go->transform->position.z));
	}

	this->lastFacing = this->facing;
}

void PlayerController::onChangeTile() {
	// check warp cooldown
	if (glfwGetTime() - lastWarp < warpCooldown) return;

	// check for warp tiles
	GameObject* go = (GameObject*)this->getGameObject();

	unsigned int x = (unsigned int)std::round(go->transform->position.x); // tileset positions
	unsigned int y = (unsigned int)std::round(go->transform->position.y);

	vector<WarpTile*>::iterator index = find_if(this->navMap->warpTiles.begin(), this->navMap->warpTiles.end(), [x, y, this](WarpTile* item) {
		GameObject* go = (GameObject*)item->getGameObject();

		if (!item->requiresFacing) return go->transform->position.x == x && go->transform->position.y == y;
		else return go->transform->position.x == x && go->transform->position.y == y && this->facing == (PlayerController::FACING)item->facingToGo;
	});

	// stop if no warp tile
	if (index >= this->navMap->warpTiles.end()) return;

	// switch to world
	unsigned int destination = (*index)->destinationWorld;

	// get things before they are deleted
	vec3 destCharPos = (*index)->destinationCharacterPosition;
	PlayerController::FACING facing = (PlayerController::FACING)((*index)->facingAtDestination);

	EngineManager::goToWorld(destination);


	// get first player controller + set position
	WorldManager* wm = EngineManager::worldManagers[EngineManager::activeWorldManager];

	PlayerController* pc = wm->getFirstComponent<PlayerController>();
	((GameObject*)pc->getGameObject())->transform->position = destCharPos;
	pc->facing = facing;
	pc->lastWarp = glfwGetTime();
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

vector<byte> PlayerController::serialise() {
	vector<byte> out;

	unsigned int e = this->type;
	byte* toAdd = (byte*)reinterpret_cast<char*>(&e);

	for (unsigned int i = 0; i < sizeof(unsigned int) / sizeof(byte); i++) {
		out.push_back(toAdd[i]);
	}

	void* id = this;
	byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

	for (unsigned int i = 0; i < sizeof(void*) / sizeof(byte); i++) {
		out.push_back(toAdd2[i]);
	}

	vector<byte*> floatsToAdd;

	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->speed));
	floatsToAdd.push_back(reinterpret_cast<byte*>(&this->snapRange));

	for (unsigned int i = 0; i < floatsToAdd.size(); i++) {
		for (unsigned int j = 0; j < sizeof(float); j++) {
			out.push_back(floatsToAdd[i][j]);
		}
	}

	byte* facing = reinterpret_cast<byte*>(&this->facing);
	out.push_back(facing[0]);

	byte* navMapB = reinterpret_cast<byte*>(&this->navMap);
	for (unsigned int i = 0; i < sizeof(void*); i++) {
		out.push_back(navMapB[i]);
	}

	return out;
}

void PlayerController::deserialise(vector<byte> bytes) {
	unsigned long long position = 0x00;

	this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
	position += sizeof(void*);

	this->speed = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);
	this->snapRange = *reinterpret_cast<float*>(&bytes[position]);
	position += sizeof(float);

	this->facing = (PlayerController::FACING)(*reinterpret_cast<unsigned char*>(&bytes[position]));
	position += sizeof(unsigned char);

	this->relatedSerialisedIDs.push_back(*reinterpret_cast<void**>(&bytes[position]));

	this->deserialisedSize = sizeof(void*) + (2 * sizeof(float) + sizeof(unsigned char) + sizeof(void*));
}