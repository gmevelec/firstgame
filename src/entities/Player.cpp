#include "entities/Player.h"
#include "inputhandlers/KeyboardManager.h"

float	Player::gravity = -50;

Player::Player(TexturedModel model, glm::vec3 position, glm::vec3 rotation, float scale):
Entity(model, position, rotation, scale)
{
}

Player::~Player()
{
}

void		Player::move(std::vector<Terrain> terrains)
{
	if (KeyboardManager::key_pressed[KeyboardManager::key_actions["jump"]])
	{
		jump();
	}
	float distance = _runSpeed * MainGame::delta;

	float dx = (distance * sin(glm::radians(getRotation().y))) * (KeyboardManager::key_pressed[KeyboardManager::key_actions["forward"]] - KeyboardManager::key_pressed[KeyboardManager::key_actions["back"]]);
	float dz = (distance * cos(glm::radians(getRotation().y))) * (KeyboardManager::key_pressed[KeyboardManager::key_actions["forward"]] - KeyboardManager::key_pressed[KeyboardManager::key_actions["back"]]);

	increaseRotation(glm::vec3(0, (_turnSpeed * (KeyboardManager::key_pressed[KeyboardManager::key_actions["left"]] - KeyboardManager::key_pressed[KeyboardManager::key_actions["right"]])) * MainGame::delta, 0));
	increasePosition(glm::vec3(dx, 0, dz));
	_upwardsSpeed += gravity * MainGame::delta;
	increasePosition(glm::vec3(0, _upwardsSpeed * MainGame::delta, 0));
	float terrainHeight = Terrain::getTerrain(terrains, getPosition().x, getPosition().z).getHeightOfTerrain(getPosition().x, getPosition().z);
	if (getPosition().y < terrainHeight)
	{
		_upwardsSpeed = 0;
		_isInAir = false;
		setPosition(glm::vec3(getPosition().x, terrainHeight, getPosition().z));
	}
}

void		Player::jump()
{
	if (!_isInAir)
	{
		_upwardsSpeed = _jumpPower;
		_isInAir = true;	
	}
}
