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
    for (auto& text : textures) {
        ImGui::PushID(text.first.c_str());
        if (ImGui::TreeNode(text.first.c_str())) {
            ImGui::Image(text.second.Texture);
        }
        ImGui::PopID();
    }
}

bool TextureMgr::LoadTexture(const std::filesystem::path& path, std::string textType) {

	if (!IsValid(path)) {
		Logger::Error("the gived path is not valid");
		return false;
	}

	std::ifstream file(path);

	if (!file.is_open()) {
		Logger::Error("Can't open the metadata file");
		return false;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	if (file.bad()) {
		Logger::Error("Failed to read the file");
		return false;
	}

	std::string content = buffer.str();

	if (content.empty()){
		Logger::Error("The metadata file is empty");
		return false;
	}

	rapidxml::xml_document<> doc;

	try
	{
		doc.parse<0>(&content[0]);
	}
	catch (const rapidxml::parse_error&)
	{
		Logger::Error("Failed to parse the XML metadata");
		return false;
	}

	rapidxml::xml_node<>* root = doc.first_node(textType.c_str());

	if (!root) {
		Logger::Error("missing first node type");
		return false;
	}

	for (rapidxml::xml_node<>* node = root->first_node(textType.c_str());
		node;
		node = node->next_sibling("texture")) {
        auto* nameAttr = node->first_attribute("name");
        auto* fileAttr = node->first_attribute("file");

        auto* rect = node->first_node("rect");

        if (!nameAttr || !fileAttr || !rect)
        {
            Logger::Error("Invalid texture metadata");
            return false;
        }

        auto* xAttr = rect->first_attribute("x");
        auto* yAttr = rect->first_attribute("y");
        auto* widthAttr = rect->first_attribute("width");
        auto* heightAttr = rect->first_attribute("height");

        if (!xAttr || !yAttr || !widthAttr || !heightAttr)
        {
            Logger::Error("Missing rectangle attributes");
            return false;
        }

        TextureData data;
        data.name = nameAttr->value();

        data.file = path.parent_path() / fileAttr->value();


        try
        {
            AnimationData newAnimData;
            newAnimData.StartX = std::stoi(xAttr->value());
            newAnimData.StartY = std::stoi(yAttr->value());
            newAnimData.SizeX = std::stoi(widthAttr->value());
            newAnimData.SizeY = std::stoi(heightAttr->value());
            data.animData = newAnimData;
        }
        catch (const std::exception&)
        {
            Logger::Error("Invalid rectangle values");
            return false;
        }

        if (data.name.empty() ||
            data.animData.SizeX <= 0 ||
            data.animData.SizeY <= 0)
        {
            Logger::Error("Invalid texture metadata values");
            return false;
        }

        if (!std::filesystem::is_regular_file(data.file))
        {
            Logger::Error("Texture image file does not exist");
            return false;
        }

        if (!textures.emplace(data.name, std::move(data)).second)
        {
            Logger::Error("Duplicate texture name");
            return false;
        }

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


