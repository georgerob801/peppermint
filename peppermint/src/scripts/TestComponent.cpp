#include <peppermint-preview/scripts/TestComponent.h>

#include <peppermint-preview/managers/LogManager.h>
#include <peppermint-preview/managers/EngineManager.h>

#include <peppermint-preview/classes/game/GameObject.h>

#include <peppermint-preview/classes/game/components/renderers/TextRenderer.h>
#include <peppermint-preview/classes/game/components/PlayerController.h>

using namespace peppermint::game::components;
using namespace peppermint::managers;

#include <format>

void TestComponent::start() {
	// is this thing on
	LogManager::warn("Start function called from test component!");

	// is storing stuff in files wotking
	LogManager::warn(std::format("Message: {}", this->message));

	// camera go circle
	this->cam = (GameObject*)EngineManager::getWM()->getFirstComponent<Camera>()->getGameObject();
	this->originalOffset = this->cam->transform->position;


	// create and put the text on the screen
	GameObject* go = EngineManager::getWM()->createGameObject();
	TextRenderer* tr = new TextRenderer();
	
	go->addComponent(tr);

	tr->fontFile = *find_if(EngineManager::assetManager->assets.begin(), EngineManager::assetManager->assets.end(), [](Asset* item) { return item->type == Asset::FONT; });
	tr->autoWrapX = true;
	tr->maxWidth = 6.8f;
	tr->setText("This was created on instantiation!");
	
	go->transform->parent = ((GameObject*)EngineManager::getWM()->getFirstComponent<PlayerController>()->getGameObject())->transform;

	go->transform->position.z = 2.0f;
	go->transform->position.x = 1.0f;
	go->transform->position.y = 1.0f;
}

void TestComponent::loop() {
	// CAMERA GO CIRCLEEEEEEE
	// this->cam->transform->position.x = originalOffset.x + sin(0.4f * glfwGetTime());
	// this->cam->transform->position.y = originalOffset.y + cos(0.4f * glfwGetTime());
}














vector<byte> TestComponent::serialiseData() {
	vector<byte> out;

	// length of message
	unsigned int numChars = this->message.length();
	byte* toAdd = reinterpret_cast<byte*>(&numChars);
	for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
		out.push_back(toAdd[i]);
	}

	// the actual message
	for (unsigned int i = 0; i < this->message.length(); i++) {
		char toProcess = this->message[i];
		toAdd = reinterpret_cast<byte*>(&toProcess);
		for (unsigned int i = 0; i < sizeof(char); i++) {
			out.push_back(toAdd[i]);
		}
	}

	return out;
}

void TestComponent::deserialiseData(vector<byte> bytes) {
	unsigned long long position = 0x00;

	unsigned int messageLength = *reinterpret_cast<unsigned int*>(&bytes[position]);
	position += sizeof(unsigned int);

	this->message = "";
	for (unsigned int i = 0; i < messageLength; i++) {
		this->message += *reinterpret_cast<char*>(&bytes[position]);
		position += sizeof(char);
	}

	this->deserialisedDataSize = position;
}

void TestComponent::makeConnections(vector<Asset*>* assets, vector<Component*>* components) {

}