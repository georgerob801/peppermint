#ifndef PPMINT_COMPONENT_WALKABLE_MAP_H
#define PPMINT_COMPONENT_WALKABLE_MAP_H

#include <peppermint/classes/game/Component.h>
#include <peppermint/Exceptions.hpp>
#include <bitset>
#include <format>

#include <string>

namespace peppermint {
	namespace game {
		namespace components {
			class NavigableMap : public Component {
			public:
				unsigned int width = NULL;
				unsigned int height = NULL;

				bool navigableType = true;

				bool* data;

				NavigableMap(unsigned int width, unsigned int height) {
					this->width = width;
					this->height = height;
					this->data = new bool[this->width * this->height];

					this->type = Component::NAVIGABLE_MAP;

					for (unsigned int i = 0; i < this->width * this->height; i++) {
						this->data[i] = this->navigableType;
					}
				}

				~NavigableMap() {
					delete this->data;
				}

				void makeNavigable(unsigned int x, unsigned int y) {
					if (x >= this->width || y >= this->height) throw peppermint::exceptions::component::InvalidCoordinateException();

					unsigned int index = (this->width * y) + x;

					this->data[index] = this->navigableType;
				}

				void makeUnnavigable(unsigned int x, unsigned int y) {
					if (x >= this->width || y >= this->height) throw peppermint::exceptions::component::InvalidCoordinateException();

					unsigned int index = (this->width * y) + x;

					this->data[index] = !this->navigableType;
				}

				bool isNavigable(unsigned int x, unsigned int y) {
					if (x >= this->width || y >= this->height) throw peppermint::exceptions::component::InvalidCoordinateException();

					unsigned int index = (this->width * y) + x;

					return this->data[index] == this->navigableType;
				}

				vector<byte> serialise() {
					vector<byte> out;

					unsigned int e = this->type;
					byte* toAdd = (byte*)reinterpret_cast<char*>(&e);

					for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
						out.push_back(toAdd[i]);
					}

					void* id = this;
					byte* toAdd2 = (byte*)reinterpret_cast<char*>(&id);

					for (unsigned int i = 0; i < sizeof(void*); i++) {
						out.push_back(toAdd2[i]);
					}

					vector<byte*> uintsToAdd;

					uintsToAdd.push_back(reinterpret_cast<byte*>(&this->width));
					uintsToAdd.push_back(reinterpret_cast<byte*>(&this->height));
					
					for (unsigned int j = 0; j < uintsToAdd.size(); j++) {
						for (unsigned int i = 0; i < sizeof(unsigned int); i++) {
							out.push_back(uintsToAdd[j][i]);
						}
					}

					vector<byte*> boolsToAdd;
					boolsToAdd.push_back(reinterpret_cast<byte*>(&this->navigableType));

					for (unsigned int j = 0; j < boolsToAdd.size(); j++) {
						for (unsigned int i = 0; i < sizeof(bool); i++) {
							out.push_back(boolsToAdd[j][i]);
						}
					}

					// add the map data
					// compress bytes into bytes
					vector<unsigned char> compressedData;

					for (unsigned int i = 0; i < this->width * this->height; i++) {
						if (i % 8 == 0) compressedData.push_back(0b00000000);
						compressedData[i / 8] |= (((unsigned char)this->data[i]) << 7 - (i % 8));
					}

					
					for (unsigned int i = 0; i < compressedData.size(); i++) {
						byte* bytesToAdd = reinterpret_cast<byte*>(&compressedData[i]);
						for (unsigned int j = 0; j < sizeof(unsigned char); j++) {
							out.push_back(bytesToAdd[j]);
						}
					}


					//out += "Component:\n";
					//out += "Type: NavigableMap\n";
					//out += std::format("ID: {}\n", (void*)this);
					//out += "Data:\n";
					//out += std::format("ParentTileset: {}\n", (void*)this->parentTileset);
					//out += std::format("Width: {}\n", this->width);
					//out += std::format("Height: {}\n", this->height);
					//out += std::format("NavigableType: {}\n", this->navigableType);

					//std::string dataString = "";

					//for (unsigned int i = 0; i < this->width * this->height; i++) {
					//	dataString += this->data[i] == this->navigableType ? "1" : "0";
					//}

					//out += std::format("Data: {}\n", dataString);
						
					return out;
				}
				
				void deserialise(vector<byte> bytes) {
					unsigned long long position = 0x00;

					this->serialisedID = *reinterpret_cast<void**>(&bytes[position]);
					position += sizeof(void*);

					position += 2 * sizeof(unsigned int);

					this->navigableType = *reinterpret_cast<bool*>(&bytes[position]);
					position += sizeof(bool);

					for (unsigned int i = 0; i < this->width * this->height; i++) {
						byte valueB = bytes[position + (i / 8)];

						this->data[i] = ((unsigned char)valueB & (0b1 << (7 - (i % 8)))) != 0;
					}

					this->deserialisedSize = sizeof(void*) + (2 * sizeof(unsigned int)) + sizeof(bool) + ((int)ceil((float)(this->width * this->height) / 8.0f));
				}
			};
		}
	}
}

#endif