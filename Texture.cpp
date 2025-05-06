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

void Texture::LoadTexture(const string& name, const string& path, bool smooth)
{
	sf::Image original;
	if (!original.loadFromFile(path))
		return;

	sf::Image scaled;
	if (smooth)
		scaled = ScaleImageBilinear(original, original.getSize().x / 2, original.getSize().y / 2);
	else
		scaled = original;

	sf::Texture tex;
	tex.loadFromImage(scaled);
	tex.setSmooth(true);

	Textures[name] = tex;
}

const sf::Texture* Texture::GetTexture(const string& name)
{
	auto it = Textures.find(name);
	if (it != Textures.end())
		return &it->second;
	return nullptr;
}

// Texture smoothing by ChatGPT - works magically
sf::Image Texture::ScaleImageBilinear(const sf::Image& src, unsigned newWidth, unsigned newHeight)
{
	// Handle degenerate cases
	if (newWidth == 0 || newHeight == 0)
		return sf::Image{};

	sf::Vector2u srcSize = src.getSize();
	if (srcSize.x < 2 || srcSize.y < 2)
		return src; // No meaningful bilinear interpolation possible

	sf::Image result;
	result.create(newWidth, newHeight);

	// Use pixel centers for symmetric sampling
	float xRatio = static_cast<float>(srcSize.x) / newWidth;
	float yRatio = static_cast<float>(srcSize.y) / newHeight;

	auto lerp = [](float a, float b, float t) -> float {
		return a + (b - a) * t;
		};

	for (unsigned y = 0; y < newHeight; ++y)
	{
		for (unsigned x = 0; x < newWidth; ++x)
		{
			// Compute source coordinates relative to pixel centers
			float gx = (x + 0.5f) * xRatio - 0.5f;
			float gy = (y + 0.5f) * yRatio - 0.5f;

			int gxi = static_cast<int>(std::floor(gx));
			int gyi = static_cast<int>(std::floor(gy));

			// Clamp to valid range [0, size-2]
			if (gxi < 0) gxi = 0;
			if (gxi > static_cast<int>(srcSize.x) - 2) gxi = static_cast<int>(srcSize.x) - 2;
			if (gyi < 0) gyi = 0;
			if (gyi > static_cast<int>(srcSize.y) - 2) gyi = static_cast<int>(srcSize.y) - 2;

			float dx = gx - gxi;
			float dy = gy - gyi;

			// Fetch the four neighboring pixels
			sf::Color c00 = src.getPixel(gxi, gyi);
			sf::Color c10 = src.getPixel(gxi + 1, gyi);
			sf::Color c01 = src.getPixel(gxi, gyi + 1);
			sf::Color c11 = src.getPixel(gxi + 1, gyi + 1);

			// Interpolate each channel
			float red = lerp(lerp(c00.r, c10.r, dx), lerp(c01.r, c11.r, dx), dy);
			float green = lerp(lerp(c00.g, c10.g, dx), lerp(c01.g, c11.g, dx), dy);
			float blue = lerp(lerp(c00.b, c10.b, dx), lerp(c01.b, c11.b, dx), dy);
			float alpha = lerp(lerp(c00.a, c10.a, dx), lerp(c01.a, c11.a, dx), dy);

			// Round to nearest integer
			auto roundToUint8 = [](float v) -> sf::Uint8 {
				return static_cast<sf::Uint8>(std::round(v));
				};

			sf::Uint8 r = roundToUint8(red);
			sf::Uint8 g = roundToUint8(green);
			sf::Uint8 b = roundToUint8(blue);
			sf::Uint8 a = roundToUint8(alpha);

			// Optionally clear RGB when fully transparent
			if (a == 0)
				r = g = b = 0;

			result.setPixel(x, y, sf::Color(r, g, b, a));
		}
	}

	return result;
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
