#include "sre/SDLRenderer.hpp"
#include "sre/SpriteAtlas.hpp"
#include "Engine/MyEngine.h"
#include "Game/ComponentController.h"
#include "Game/ComponentRendererSprite.h"
#include "Game/ComponentAsteroid.h"

void InitGame();
void ProcessEvents(SDL_Event& event);
void Update(float deltaTime);
void Render();

MyEngine::Engine engine;

glm::vec2 window_size = glm::vec2(800, 600);
sre::SDLRenderer renderer;
sre::Camera camera;
std::shared_ptr<sre::SpriteAtlas> atlas;
std::string asteroidOptions[3] = {"Meteors/meteorBrown_big1.png", "Meteors/meteorGrey_med1.png", "Meteors/meteorGrey_tiny2.png"};

int main() {
	renderer.frameRender = Render;
	renderer.frameUpdate = Update;
	renderer.keyEvent = ProcessEvents;

	renderer.setWindowSize(window_size);
	renderer.init();
	camera.setWindowCoordinates();

	auto playerGameObject = engine.CreateGameObject("Player");
	auto componentController = std::shared_ptr<ExampleGame::ComponentController>(new ExampleGame::ComponentController());
	auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
	atlas = sre::SpriteAtlas::create("data/spritesheet.json", "data/spritesheet.png");
	playerGameObject->AddComponent(componentController);
	playerGameObject->AddComponent(componentRenderer);
	componentRenderer->sprite = atlas->get("playerShip1_red.png");
	componentController->isPlayer = true;

	InitGame();
	engine.Init();

	renderer.startEventLoop();
}

void InitGame() {
	for (int i = 0; i < 5; i++) {
		auto asteroid = engine.CreateGameObject("Asteroid");
		auto componentRenderer = std::make_shared<ExampleGame::ComponentRendererSprite>();
		auto componentAsteroid = std::make_shared<ExampleGame::ComponentAsteroid>();

		asteroid->AddComponent(componentRenderer);
		asteroid->AddComponent(componentAsteroid);

		componentRenderer->sprite = atlas->get(asteroidOptions[rand() % 3]);
	}
}

void ProcessEvents(SDL_Event& event) {
	engine.ProcessEvents(event);
}

void Update(float deltaTime) {
	engine.Update(deltaTime);
}

void Render() {
	engine.Render();
}