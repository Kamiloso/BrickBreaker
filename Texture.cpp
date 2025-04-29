#include "Texture.h"

map<string, sf::Texture> Texture::Textures;
void Texture::init()
{
	LoadTexture("Unbreakable", "Unbreakable.png");
	LoadTexture("Spawn", "Spawn.png");
	LoadTexture("SizeUp", "SizeUp.png");
	LoadTexture("SizeDown", "SizeDown.png");
	LoadTexture("SpeedUp", "SpeedUp.png");
	LoadTexture("SlowDown", "SlowDown.png");
	LoadTexture("Reverse", "Reverse.png");
	LoadTexture("Fragile", "Fragile.png");
}
void Texture::LoadTexture(const string& name, const string& path)
{
	sf::Texture texture;
	texture.loadFromFile(path);
	Textures[name] = texture;
}

sf::Texture* Texture::GetTexture(const string& name)
{
	auto texture = Textures.find(name);
	return &texture->second;
}
