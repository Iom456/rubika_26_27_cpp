#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "DebugMgr.h"
#include <optional>

#include <SFML/Graphics/Sprite.hpp>

#include <filesystem>
#include <string>
#include <map>

struct AnimationData
{
	int StartX = 0;
	int StartY = 0;
	int SizeX = 0;
	int SizeY = 0;
	int OffsetX = 0;
	int OffsetY = 0;
	int AnimationSpriteCount = 0;
	int SpriteOnLine = 0;
	bool IsReverted = false;
	float TimeBetweenAnimationInS = 0.f;
};

struct StaticTileData
{
	int StartX = 0;
	int StartY = 0;
	int SizeX = 0;
	int SizeY = 0;
	bool IsRevertedX = false;
	bool IsRevertedY = false;
};

struct TextureData
{
	TextureData() {};
	~TextureData() {};

	void Draw();

	sf::Texture Texture;
	std::optional<sf::Sprite> sprite;
	std::string name;
	std::filesystem::path file;

	AnimationData animData;
	StaticTileData tileData;
	
	// Container of AnimationData AnimationsData;
	// Container of StaticTileData StaticTilesData;

	friend class TextureMgr;
};

class TextureMgr final : public IDebugable
{
public:
	void Init();
	void Shut();

	void DrawDebug() override;
	bool LoadTexture(const std::filesystem::path& path, std::string textType);
	const TextureData& GetTextureData(const std::string& name) const;

private:
	bool IsValid(const std::filesystem::path& path);

	std::map<std::string, TextureData> textures;
};