#ifndef PPMINT_RENDER_MANAGER_H
#define PPMINT_RENDER_MANAGER_H

#include <peppermint/classes/game/components/Camera.h>
#include <peppermint/classes/rendering/RenderQueue.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace peppermint::rendering;
using namespace peppermint::game::components;

using namespace glm;

namespace peppermint {
	namespace managers {
		/// <summary>
		/// Class to manage rendering.
		/// </summary>
		class RenderManager {
		public:
			/// <summary>
			/// The current status of this RenderManager.
			/// </summary>
			int status;

			/// <summary>
			/// The Camera Component currently in use by this RenderManager.
			/// </summary>
			Camera* activeCamera;

			/// <summary>
			/// The RenderQueue currently in use by this RenderManager.
			/// </summary>
			RenderQueue* activeRenderQueue;

			/// <summary>
			/// The shader to use when drawing the screen texture to the screen.
			/// </summary>
			Shader* screenShader;

			/// <summary>
			/// The colour to draw before all other render calls.
			/// </summary>
			vec4 backgroundColour;

			/// <summary>
			/// The index of this RenderManager's FBO.
			/// </summary>
			unsigned int FBO;

			/// <summary>
			/// Create a RenderManager.
			/// </summary>
			RenderManager();
			/// <summary>
			/// Destroy this RenderManager.
			/// </summary>
			~RenderManager();

			/// <summary>
			/// Render the next frame.
			/// </summary>
			void renderFrame();
			/// <summary>
			/// Set this RenderManager's active Camera.
			/// </summary>
			/// <param name="cam">The Camera Component to set.</param>
			void setCamera(Camera* cam);

			/// <summary>
			/// Setup this RenderManager's FBO.
			/// </summary>
			void setupFBO();

			/// <summary>
			/// Bind this RenderManager's FBO.
			/// </summary>
			void bindFBO();

			/// <summary>
			/// Get the index of this RenderManager's colour texture.
			/// </summary>
			/// <returns></returns>
			unsigned int getColourTex();

			/// <summary>
			/// Resize this RenderManager's attachments to match the current Window size.
			/// </summary>
			void resizeFBOAttachments();

			/// <summary>
			/// Clear any bound FBOs.
			/// </summary>
			static void unbindFBOs();
		private:
			unsigned int colourTex = NULL;
			unsigned int RBO = NULL;

			unsigned int fboVAO = NULL;
			unsigned int fboVBO = NULL;
		};
	}
}

#endif