#ifndef PPMINT_COMPONENT_H
#define PPMINT_COMPONENT_H

#include <peppermint/Serialisable.h>
#include <peppermint/classes/game/Toggleable.hpp>

namespace peppermint {
	namespace game {
		class Component : public Serialisable, public Toggleable {
		public:
			/// <summary>
			/// Destroy this Component.
			/// </summary>
			virtual ~Component();
			/// <summary>
			/// Runs once when this Component is first activated in a world.
			/// </summary>
			virtual void start();
			/// <summary>
			/// Runs once when this Component is added to a world.
			/// </summary>
			virtual void awake();
			/// <summary>
			/// Runs once every frame.
			/// </summary>
			virtual void loop();

			/// <summary>
			/// Enum containing all types of built-in Components.
			/// </summary>
			enum ComponentType {
				COMPONENT,
				TRANSFORM,
				CAMERA,
				NAVIGABLE_MAP,
				PLAYER_CONTROLLER,
				BASIC_PLAYER_RENDERER,
				TILESET_RENDERER,
				RENDERER,
				ANIMATED_TILESET_RENDERER,
				WARP_TILE,
				SPRITE_RENDERER,
				SOUND_SOURCE,
				SOUND_LISTENER,
				TEXT_RENDERER
			};

			/// <summary>
			/// Sets the GameObject of this Component.
			/// </summary>
			/// <param name="gameObject">A generic pointer to the desired GameObject.</param>
			/// <returns>A pointer to this Component.</returns>
			Component* setGameObject(void* gameObject);
			/// <summary>
			/// Get a pointer to the GameObject this Component is attached to.
			/// </summary>
			/// <returns></returns>
			void* getGameObject();

			/// <summary>
			/// Initialise this Component.
			/// </summary>
			void initialise();
			/// <summary>
			/// Determing whether this Component 
			/// </summary>
			/// <returns></returns>
			bool isInitialised();

			virtual vector<byte> serialise();
			void deserialise(vector<byte> bytes);

			/// <summary>
			/// Get the type of this component.
			/// </summary>
			/// <returns>The type of this component.</returns>
			unsigned int getType();
		private:
			/// <summary>
			/// A pointer to the GameObject this Component is attached to.
			/// </summary>
			void* gameObject = nullptr;
		protected:
			/// <summary>
			/// Whether or not this Component has been initialised.
			/// </summary>
			bool initialised = false;
			/// <summary>
			/// The type of this Component.
			/// </summary>
			Component::ComponentType type;
		};
	}
}

#endif