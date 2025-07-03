#include "LuaScriptComponent.h"

std::string LuaScriptComponent::getTypeName() const
{
	return "LuaScriptComponent";
}

void LuaScriptComponent::to_json(json& j)
{
	j = json{
		{"luaScript", scriptFile.empty() ? "" : scriptFile}
	};
}

void LuaScriptComponent::from_json(ID3D11Device* device, const json& j)
{
	scriptFile = j.at("luaScript").get<std::string>();
}
