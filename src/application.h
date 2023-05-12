#pragma once

#include <shared/all.h>
#include "screens/gameplay_screen.h"

namespace PhoneInc
{
	class Application : public Shared::Application,
		public Common::FrameSystem::Frameable
	{
	public:
		Application();
		~Application();

	private:
		void onFrame() override;
		void adaptToScreen(std::shared_ptr<Scene::Node> node, const glm::vec2& dimensions);

		void initializeScene();
	};
}
