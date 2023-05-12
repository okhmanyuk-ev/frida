#include "gameplay_screen.h"

using namespace PhoneInc;

GameplayScreen::GameplayScreen()
{
	auto player = std::make_shared<Scene::Sprite>();
	player->setTexture(TEXTURE("textures/player.png"));
	player->setAnchor({ 0.5f, 0.75f });
	player->setPivot(0.5f);
	player->setScale(2.0f);
	getContent()->attach(player);

	auto enemy = std::make_shared<Scene::Sprite>();
	enemy->setTexture(TEXTURE("textures/enemy.png"));
	enemy->setAnchor({ 0.5f, 0.25f });
	enemy->setPivot(0.5f);
	enemy->setScale(2.0f);
	getContent()->attach(enemy);

	player->runAction(Actions::Collection::RepeatInfinite([player] {
		auto dst_anchor_x = glm::linearRand(0.25f, 0.75f);
		auto duration = glm::linearRand(0.5f, 2.0f);
		return Actions::Collection::MakeSequence(
			Actions::Collection::ChangeHorizontalAnchor(player, dst_anchor_x, duration, Easing::CubicInOut)
		);
	}));

	enemy->runAction(Actions::Collection::RepeatInfinite([enemy] {
		auto dst_anchor_x = glm::linearRand(0.25f, 0.75f);
		auto duration = glm::linearRand(0.5f, 2.0f);
		return Actions::Collection::MakeSequence(
			Actions::Collection::ChangeHorizontalAnchor(enemy, dst_anchor_x, duration, Easing::CubicInOut)
		);
	}));
}
