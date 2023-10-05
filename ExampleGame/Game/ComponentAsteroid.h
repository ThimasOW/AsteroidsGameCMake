#pragma once
#include "Engine/Component.h"

namespace ExampleGame {
	class ComponentAsteroid : public MyEngine::Component
	{
		const float ROT_SPEED = 60;
		const float MOVE_SPEED = 5;
		const float MOVE_AMOUNT = 170;

		glm::vec2 basePos;

		MyEngine::Engine* engine;
		MyEngine::GameObject* parent;

	public:
		float velocity;
		float rotation;

		void Init() override;
		void Update(float) override;
		void ProcessInput(float);
		void CheckBounds();
	};
}
