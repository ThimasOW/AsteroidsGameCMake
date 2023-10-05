#pragma once

#include "Engine/Component.h"
#include "chrono"

namespace ExampleGame {
	class ComponentController : public MyEngine::Component {
		const float ROT_SPEED = 60;
		const float MOVE_SPEED = 5;
		const float MOVE_AMOUNT = 170;

		glm::vec2 basePos;

		MyEngine::Engine* engine;
		MyEngine::GameObject* parent;

	public:
		glm::vec2 position;
		std::chrono::time_point<std::chrono::system_clock> start, end;
		bool isPlayer = false;
		float rotation;
		float velocity = 0;

		void Init() override;
		void Update(float) override;
		void KeyEvent(SDL_Event&) override;
		void ProcessInput(float);
		void CheckBounds();
		void Shoot(ComponentController&);
	};
}