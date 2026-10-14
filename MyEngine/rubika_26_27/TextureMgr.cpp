#include "TextureMgr.h"
#include <stdexcept>
#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>

#include "Globals.h"
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>


#include "Logger.h"


void TextureMgr::Init() {
    gData.DebugMgr->RegisterDebugableWindow("Textures", this);
}

void TextureMgr::Shut() {
    gData.DebugMgr->UnregisterDebugableWindow("Textures");
}

void TextureMgr::DrawDebug()
{
	for (auto& [name, data] : textures)
	{
		ImGui::PushID(name.c_str());
		if (ImGui::TreeNode(name.c_str()))
		{
			const AnimationData& a = data.animData;

			ImGui::Text("File : %s", data.file.string().c_str());
			ImGui::Text("Rect : (%d, %d) %dx%d", a.StartX, a.StartY, a.SizeX, a.SizeY);
			ImGui::Text("Sprites : %d (par ligne : %d) | %.2fs | inverse : %s",
				a.AnimationSpriteCount, a.SpriteOnLine,
				a.TimeBetweenAnimationInS, a.IsReverted ? "oui" : "non");

			if (data.sprite)
			{
				ImGui::Image(*data.sprite, sf::Vector2f(a.SizeX * 4.f, a.SizeY * 4.f));
			}

			ImGui::TreePop();
		}
		ImGui::PopID();
	}
}

bool TextureMgr::LoadTexture(const std::filesystem::path& path, std::string textType) {

	if (!IsValid(path)) {
		Logger::Error("the gived path is not valid");
		return false;
    }
    else {
        Logger::Info("The path is valid");
    }

	std::ifstream file(path);

	if (!file.is_open()) {
		Logger::Error("Can't open the metadata file");
		return false;
	}
    else {
        Logger::Info("The metadata is opened");
    }

	std::stringstream buffer;
	buffer << file.rdbuf();

	if (file.bad()) {
		Logger::Error("Failed to read the file");
		return false;
	}
    else {
        Logger::Info("The file can be readed");
    }

	std::string content = buffer.str();

	if (content.empty()){
		Logger::Error("The metadata file is empty");
		return false;
	}
    else {
        Logger::Info("The metadata is not empty");
    }

	rapidxml::xml_document<> doc;

	try
	{
		doc.parse<0>(&content[0]);
        Logger::Info("Try parse the xml");
	}
	catch (const rapidxml::parse_error&)
	{
		Logger::Error("Failed to parse the XML metadata");
		return false;
	}

	rapidxml::xml_node<>* root = doc.first_node(textType.c_str());

	std::filesystem::path imagePath;

	if (auto* fileAttr = root->first_attribute("file"))
	{
		imagePath = path.parent_path() / fileAttr->value();
	}
	else
	{
		for (const char* ext : { ".png", ".jpg", ".jpeg", ".bmp", ".tga" })
		{
			std::filesystem::path candidate = path;
			candidate.replace_extension(ext);

			if (std::filesystem::is_regular_file(candidate))
			{
				imagePath = candidate;
				break;
			}
		}
	}

	if (imagePath.empty() || !std::filesystem::is_regular_file(imagePath)) {
		Logger::Error("Texture image file not found next to the XML");
		return false;
	}

	/*const std::filesystem::path imagePath = path.parent_path() / fileAttr->value();

	if (!std::filesystem::is_regular_file(imagePath))
	{
		Logger::Error("Texture image file does not exist");
		return false;
	}*/

	auto readInt = [](rapidxml::xml_node<>* parent, const char* tag, int& out) -> bool
		{
			auto* n = parent->first_node(tag);
			if (!n) return false;
			try { out = std::stoi(n->value()); }
			catch (const std::exception&) { return false; }
			return true;
		};

	auto readFloat = [](rapidxml::xml_node<>* parent, const char* tag, float& out) -> bool
		{
			auto* n = parent->first_node(tag);
			if (!n) return false;
			try { out = std::stof(n->value()); }
			catch (const std::exception&) { return false; }
			return true;
		};

	for (rapidxml::xml_node<>* node = root->first_node("Animation");
		node;
		node = node->next_sibling("Animation"))
	{
		auto* nameAttr = node->first_attribute("Name");
		if (!nameAttr)
		{
			Logger::Error("Animation without a Name attribute");
			return false;
		}

		TextureData data;
		data.name = nameAttr->value();
		data.file = imagePath;

		AnimationData& a = data.animData;
		int reverted = 0;

		if (!readInt(node, "X", a.StartX) ||
			!readInt(node, "Y", a.StartY) ||
			!readInt(node, "SizeX", a.SizeX) ||
			!readInt(node, "SizeY", a.SizeY) ||
			!readInt(node, "OffsetX", a.OffsetX) ||
			!readInt(node, "OffsetY", a.OffsetY) ||
			!readInt(node, "SpriteNum", a.AnimationSpriteCount) ||
			!readInt(node, "SpritesOnLine", a.SpriteOnLine) ||
			!readInt(node, "Reverted", reverted) ||
			!readFloat(node, "TimeBetweenAnimation", a.TimeBetweenAnimationInS))
		{
			Logger::Error("Missing or invalid value in an Animation node");
			return false;
		}

		a.IsReverted = (reverted != 0);

		if (data.name.empty() || a.SizeX <= 0 || a.SizeY <= 0)
		{
			Logger::Error("Invalid texture metadata values");
			return false;
		}

		if (!data.Texture.loadFromFile(data.file))
		{
			Logger::Error("Failed to load texture image");
			return false;
		}

		auto [it, inserted] = textures.emplace(data.name, std::move(data));
		if (!inserted)
		{
			Logger::Error("Duplicate texture name");
			return false;
		}

		TextureData& stored = it->second;
		stored.sprite.emplace(stored.Texture);
		stored.sprite->setTextureRect(sf::IntRect(
			{ stored.animData.StartX, stored.animData.StartY },
			{ stored.animData.SizeX,  stored.animData.SizeY }));
	}

	if (textures.empty())
	{
		Logger::Error("No animation loaded from the metadata");
		return false;
	}

	return true;

}

const TextureData& TextureMgr::GetTextureData(const std::string& name) const{
    auto it = textures.find(name);

    if (it != textures.end()) {
        return it->second;
    }
    
    Logger::Error("No texture found");
    throw std::out_of_range("Texture not found: " + name);
}

bool TextureMgr::IsValid(const std::filesystem::path& path)
{
    if (!std::filesystem::exists(path)) {
        Logger::Error("the file does not exist");
        return false;
    }
    else {
        Logger::Info("The exist");
    }

    if (!std::filesystem::is_regular_file(path)) {
        Logger::Error("The file is not regular");
        return false;
    }
    else {
        Logger::Info("The file is valid");
    }
    return true;
}


