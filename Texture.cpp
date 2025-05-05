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

const sf::Texture* Texture::GetTexture(const string& name)
{
	auto it = Textures.find(name);
	if (it != Textures.end())
		return &it->second;
	return nullptr;
}

sf::Color Texture::GetMainColor(const sf::Texture* const_texture_ptr)
{
	static std::map<const sf::Texture*, sf::Color> cache;

	// search in cache first
	auto it = cache.find(const_texture_ptr);
	if (it != cache.end()) {
		return it->second;
	}

	// texture -> image
	sf::Image image = const_texture_ptr->copyToImage();
	const unsigned width = image.getSize().x;
	const unsigned height = image.getSize().y;

	// store colors
	vector<sf::Color> colors;
	vector<int> occurences;

	for (unsigned x = 0; x < width; x++)
		for (unsigned y = 0; y < height; y++)
		{
			sf::Color pixel = image.getPixel(x, y);
			bool added = false;
			for (int i = 0; i < colors.size(); i++)
			{
				if (colors[i] == pixel)
				{
					occurences[i]++;
					added = true;
				}
			}
			if (!added)
			{
				colors.push_back(pixel);
				occurences.push_back(0);
			}
		}

	// find most frequent color
	int max_occurences = 0;
	sf::Color best_color = sf::Color::Black;
	for (int i = 0; i < colors.size(); i++)
	{
		if (occurences[i] > max_occurences)
		{
			max_occurences = occurences[i];
			best_color = colors[i];
		}
	}

	// cache and return
	cache[const_texture_ptr] = best_color;
	return best_color;
}
