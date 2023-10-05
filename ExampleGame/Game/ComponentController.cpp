#include "ComponentController.h"
#include "Component.h"
#include "sre/SDLRenderer.hpp"
#include "ComponentRendererSprite.h"
#include "Engine/MyEngine.h"
#include "chrono"

namespace ExampleGame {
	// Yes, I should not have reused this to make the lasers, but I am too deep in it now
	// I don't know how to delete the lasers when they're managed by GameObject in an list

	void ComponentController::Init() {
		engine = MyEngine::Engine::GetInstance();
		parent = GetGameObject();
		basePos = engine->GetScreenSize() / 2.f;

		parent->position = basePos;
		start = std::chrono::system_clock::now();
	}
	auto me = std::unique_ptr<ComponentController>();
	void ComponentController::Update(float deltaTime) {
		ProcessInput(deltaTime);

		end = std::chrono::system_clock::now();

		if (!isPlayer) {
			std::chrono::duration<double> elapsed_seconds = end - start;

			if (elapsed_seconds > std::chrono::duration<double>(1)) {
				// Imagine the lasers get destroyed here. RAII or something
			}
		}
	}

	void ComponentController::KeyEvent(SDL_Event& e) {
		if (isPlayer == false) return;

		switch (e.key.keysym.sym) {
		case SDLK_SPACE:
			Shoot(*this);
			break;

		case SDLK_w:
			velocity = -1;
			break;

		case SDLK_s:
			velocity = 1;
			break;

		case SDLK_a:
			rotation = 10;
			break;

		case SDLK_d:
			rotation = -10;
			break;
		}
	}

	void ComponentController::ProcessInput(float deltaTime) {
		parent->rotation += (rotation * ROT_SPEED) * deltaTime;

		// Moves player in it's relative forward vector
		parent->position.x += (MOVE_AMOUNT * cos(glm::radians(parent->rotation - 90)) * deltaTime) * velocity;
		parent->position.y += (MOVE_AMOUNT * sin(glm::radians(parent->rotation - 90)) * deltaTime) * velocity;

		if (isPlayer) {
			rotation = 0;
			velocity = 0;
			CheckBounds();
		}

	}

	void ComponentController::CheckBounds()
	{
		if (parent->position.x > engine->GetScreenSize().x) {
			parent->position.x = 0;
		}

		if (parent->position.x < 0) {
			parent->position.x = engine->GetScreenSize().x;
		}

		if (parent->position.y > engine->GetScreenSize().y) {
			parent->position.y = 0;
		}

		if (parent->position.y < 0) {
			parent->position.y = engine->GetScreenSize().y;
		}
	}

	void ComponentController::Shoot(ComponentController& c) {
		auto laser = engine->CreateGameObject("Laser");
		auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
		auto componentController = std::shared_ptr<ExampleGame::ComponentController>(new ExampleGame::ComponentController());

		laser->AddComponent(componentRenderer);
		laser->AddComponent(componentController);

		componentRenderer->sprite = engine->atlas->get("Lasers/laserRed01.png");
		componentController->Init();

		laser->position = c.parent->position;
		laser->rotation = c.parent->rotation;
		componentController->velocity = -1;
	}

}