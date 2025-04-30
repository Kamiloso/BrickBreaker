#include "Texture.h"

map<string, sf::Texture> Texture::Textures;
void Texture::init()
{
	LoadTexture("Unbreakable", "Assets/Bricks/Unbreakable.png");
	LoadTexture("Spawn", "Assets/Bricks/Spawn.png");
	LoadTexture("SizeUp", "Assets/Bricks/SizeUp.png");
	LoadTexture("SizeDown", "Assets/Bricks/SizeDown.png");
	LoadTexture("SpeedUp", "Assets/Bricks/SpeedUp.png");
	LoadTexture("SlowDown", "Assets/Bricks/SlowDown.png");
	LoadTexture("Reverse", "Assets/Bricks/Reverse.png");
	LoadTexture("Fragile", "Assets/Bricks/Fragile.png");
	LoadTexture("Health1", "Assets/Bricks/Health1.png");
	LoadTexture("Health2", "Assets/Bricks/Health2.png");
	LoadTexture("Health3", "Assets/Bricks/Health3.png");
	LoadTexture("Health4", "Assets/Bricks/Health4.png");
}
void Texture::LoadTexture(const string& name, const string& path)
{
	sf::Texture texture;
	texture.loadFromFile(path);
	texture.setSmooth(true);
	Textures[name] = texture;
}

sf::Texture* Texture::GetTexture(const string& name)
{
	auto texture = Textures.find(name);
	return &texture->second;
}
