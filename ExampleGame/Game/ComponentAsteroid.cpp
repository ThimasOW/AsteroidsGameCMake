#include "ComponentAsteroid.h"
#include "sre/SDLRenderer.hpp"
#include "Engine/MyEngine.h"

namespace ExampleGame {
	void ComponentAsteroid::Init() {
		engine = MyEngine::Engine::GetInstance();
		parent = GetGameObject();
		basePos = engine->GetScreenSize() / 2.f;

		// Set initial random values
		parent->position = glm::vec2(rand() % (int)engine->GetScreenSize().x, rand() % (int)engine->GetScreenSize().y);
		parent->rotation = rand() % 360;

		float r = 0.2 + static_cast<float>(rand()) * static_cast<float>(1.0 - 0.2) / RAND_MAX;
		velocity = r;
	}

	void ComponentAsteroid::Update(float deltaTime) {
		ProcessInput(deltaTime);
	}
	void ComponentAsteroid::ProcessInput(float deltaTime) {
		parent->rotation += (rotation * ROT_SPEED) * deltaTime;

		// Move in relative forward vector
		parent->position.x += (MOVE_AMOUNT * cos(glm::radians(parent->rotation - 90)) * deltaTime) * velocity;
		parent->position.y += (MOVE_AMOUNT * sin(glm::radians(parent->rotation - 90)) * deltaTime) * velocity;

		CheckBounds();
	}

	void ComponentAsteroid::CheckBounds() {
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
}
