#ifndef PPMINT_GAME_OBJECT_H
#define PPMINT_GAME_OBJECT_H

#include <vector>
#include <peppermint-preview/classes/game/Component.h>
#include <peppermint-preview/classes/game/components/Transform.h>
#include <peppermint-preview/Serialisable.h>
#include <peppermint-preview/classes/game/Toggleable.hpp>

using namespace peppermint::game::components;

namespace peppermint {
	namespace game {
		/// <summary>
		/// Class for all objects that exist within a game.
		/// </summary>
		class GameObject : public Serialisable, public Toggleable {
		public:
			/// <summary>
			/// This GameObject's Transform Component.
			/// </summary>
			Transform* transform;

			/// <summary>
			/// A vector containing pointers to all of this GameObject's Components.
			/// </summary>
			std::vector<Component*> components;

			/// <summary>
			/// Create a GameObject. Please use WorldManager::createGameObject() instead.
			/// </summary>
			GameObject();
			/// <summary>
			/// Destroy this GameObject.
			/// </summary>
			~GameObject();

			/// <summary>
			/// Adds a component to this GameObject.
			/// </summary>
			/// <param name="comp">A pointer to the Component to add.</param>
			void addComponent(Component* comp);
			/// <summary>
			/// Prepends a component to this GameObject.
			/// </summary>
			/// <param name="comp">A pointer to the Component to prepend.</param>
			void prependComponent(Component* comp);

			/// <summary>
			/// Get a Component of a specific type.
			/// </summary>
			/// <typeparam name="T">The type of Component to get.</typeparam>
			/// <returns>The first Component of the type determined that belongs to this GameObject.</returns>
			template<class T> Component* getComponent();

			vector<byte> serialise();
			void deserialise(vector<byte> bytes);
		private:
		};
	}
}

#endif