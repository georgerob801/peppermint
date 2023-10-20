#include <peppermint/classes/rendering/RenderStack.h>

using namespace peppermint::rendering;

void RenderStack::processRenderItems() {
	while (this->renderItems.size() != 0) {
		this->renderItems[0].mesh->draw(this->renderItems[0].shader);
		this->renderItems.erase(this->renderItems.begin());
	}
}