#include "Texture.h"

map<string, sf::Texture> Texture::Textures;
void Texture::init()
{
	LoadTexture("Unbreakable", "Assets/Bricks/Unbreakable.png");
	LoadTexture("Spawn", "Assets/Bricks/Spawn.png");
	LoadTexture("SizeUp", "Assets/Bricks/SizeUp.png");
	LoadTexture("SizeDown", "Assets/Bricks/SizeDown.png");
	LoadTexture("SizeUp2", "Assets/Bricks/SizeUp2.png");
	LoadTexture("SizeDown2", "Assets/Bricks/SizeDown2.png");
	LoadTexture("SpeedUp", "Assets/Bricks/SpeedUp.png");
	LoadTexture("SlowDown", "Assets/Bricks/SlowDown.png");
	LoadTexture("SpeedUp2", "Assets/Bricks/SpeedUp2.png");
	LoadTexture("SlowDown2", "Assets/Bricks/SlowDown2.png");
	LoadTexture("Reverse", "Assets/Bricks/Reverse.png");
	LoadTexture("Fragile", "Assets/Bricks/Fragile.png");
	LoadTexture("Health1", "Assets/Bricks/Health1.png");
	LoadTexture("Health2", "Assets/Bricks/Health2.png");
	LoadTexture("Health3", "Assets/Bricks/Health3.png");
	LoadTexture("Health4", "Assets/Bricks/Health4.png");
}

void Texture::LoadTexture(const string& name, const string& path, bool dont_smooth)
{
	sf::Texture texture;
	if (texture.loadFromFile(path))
	{
		texture.setSmooth(!dont_smooth);
		Textures[name] = texture;
	}
}

sf::Texture* Texture::GetTexture(const string& name)
{
	auto it = Textures.find(name);
	if (it != Textures.end())
		return &it->second;
	return nullptr;
}
