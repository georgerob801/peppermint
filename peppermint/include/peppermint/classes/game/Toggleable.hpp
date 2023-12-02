#ifndef PPMINT_TOGGLEABLE_H
#define PPMINT_TOGGLEABLE_H

namespace peppermint {
	namespace game {
		/// <summary>
		/// Interface for storing the state of toggleable things.
		/// </summary>
		class Toggleable {
		public:
			/// <summary>
			/// Enable this.
			/// </summary>
			void enable() {
				this->enabled = true;
			}

			/// <summary>
			/// Disable this.
			/// </summary>
			void disable() {
				this->enabled = false;
			}

			/// <summary>
			/// Determine whether this is enabled.
			/// </summary>
			/// <returns>True/false depending on whether this is enabled.</returns>
			bool isEnabled() {
				return this->enabled;
			}
		private:
			/// <summary>
			/// Whether this is enabled.
			/// </summary>
			bool enabled = true;
		};
	}
}

#endif