#ifndef PPMINT_COMPONENT_H
#define PPMINT_COMPONENT_H

#include <peppermint/Serialisable.h>

namespace peppermint {
	namespace game {
		class Component : public Serialisable {
		public:
			virtual void start();
			virtual void awake();
			virtual void loop();

			enum ComponentType {
				COMPONENT,
				TRANSFORM,
				CAMERA,
				NAVIGABLE_MAP,
				PLAYER_CONTROLLER,
				BASIC_PLAYER_RENDERER,
				TILESET_RENDERER,
				RENDERER,
				ANIMATED_TILESET_RENDERER
			};

			Component* setGameObject(void* gameObject);
			void* getGameObject();

			void initialise();
			bool isInitialised();

			void disable();
			void enable();
			bool isEnabled();

			virtual vector<byte> serialise();
			void deserialise(vector<byte> bytes);

			unsigned int getType();
		private:
			void* gameObject = nullptr;
		protected:
			bool initialised = false;
			bool enabled = true;
			Component::ComponentType type;
		};
	}
}

#endif