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

			Component* setGameObject(void* gameObject);
			void* getGameObject();

			void initialise();
			bool isInitialised();

			void disable();
			void enable();
			bool isEnabled();

			virtual vector<byte> serialise();
			void deserialise(vector<byte> bytes);

			void getType();
		private:
			void* gameObject = nullptr;
		protected:
			bool initialised = false;
			bool enabled = true;
			static const unsigned int type = 0x00;
		};
	}
}

#endif