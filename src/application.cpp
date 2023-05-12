#include "application.h"

using namespace PhoneInc;

Application::Application() : Shared::Application(PROJECT_NAME, { Flag::Audio, Flag::Scene })
{
	PLATFORM->setTitle(PRODUCT_NAME);
#if defined(PLATFORM_MAC)
	PLATFORM->resize(720, 1280);
#else
	PLATFORM->resize(360, 640);
#endif
#if defined(PLATFORM_WINDOWS)
	PLATFORM->rescale(1.5f);
#endif
	RENDERER->setVsync(true);

	// limit maximum time delta to avoid animation breaks
	FRAME->setTimeDeltaLimit(Clock::FromSeconds(1.0f / 30.0f));

	getScene()->getTimestepFixer().setEnabled(false);

	STATS->setAlignment(Shared::StatsSystem::Align::BottomRight);

	PLATFORM->initializeBilling({
		//{ "rubies.001", [this] { 
		//	addRubies(500);
		//} }
	});

	initializeScene();
}

Application::~Application()
{
}

void Application::onFrame()
{
	adaptToScreen(SCENE_MANAGER, { 1080.0f, 1920.0f });
}

void Application::adaptToScreen(std::shared_ptr<Scene::Node> node, const glm::vec2& dimensions)
{
	glm::vec2 size = { PLATFORM->getLogicalWidth(), PLATFORM->getLogicalHeight() };
	auto scale = size / dimensions;
	node->setScale(glm::min(scale.x, scale.y));
	node->setStretch(1.0f / node->getScale());
}

void Application::initializeScene()
{
	Scene::Sampler::DefaultSampler = skygfx::Sampler::Linear;

	PRECACHE_FONT_ALIAS("fonts/rubik/Rubik-Medium.ttf", "default");
	PRECACHE_FONT_ALIAS("fonts/rubik/Rubik-Bold.ttf", "default_bold");
	
	// prepare
			
	FONT("default")->setCustomVerticalOffset(-4.0f);
	FONT("default_bold")->setCustomVerticalOffset(-4.0f);

	Scene::Sprite::DefaultTexture = TEXTURE("textures/pink.png");
	Scene::Label::DefaultFont = FONT("default");

	// gameplay

	SCENE_MANAGER->switchScreen(std::make_shared<GameplayScreen>());
}
