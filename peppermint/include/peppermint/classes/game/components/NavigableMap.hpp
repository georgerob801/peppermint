#ifndef PPMINT_COMPONENT_WALKABLE_MAP_H
#define PPMINT_COMPONENT_WALKABLE_MAP_H

#include <peppermint/classes/game/Component.h>
#include <peppermint/classes/rendering/Tileset.h>
#include <peppermint/Exceptions.hpp>
#include <bitset>

using namespace peppermint::rendering;

namespace peppermint {
	namespace game {
		namespace components {
			class NavigableMap : public Component {
			public:
				Tileset* parentTileset = nullptr;

				unsigned int width = NULL;
				unsigned int height = NULL;

				bool navigableType = true;

				bool* data;

				NavigableMap(unsigned int width, unsigned int height) {
					this->width = width;
					this->height = height;
					this->data = new bool[this->width * this->height];

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
			};
		}
	}
}

#endif