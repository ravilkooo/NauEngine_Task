#pragma once
#include <lua/lua.hpp>
#include <LuaBridge/LuaBridge.h>

#include "Scene.h"
#include "ECS/Components/TransformComponent.h"
#include "ECS/Components/LuaScriptComponent.h"

class ScriptingSystem {
public:
    void Update(Scene& scene, float deltaTime) {
        for (auto& entity : scene.entities) {
            if (entity->HasComponent<LuaScriptComponent>()) {
                auto& scriptComp = entity->GetComponent<LuaScriptComponent>();
                lua_State* L = luaL_newstate();
                luaL_openlibs(L);

                // Пробросить API управления TransformComponent
                RegisterTransformAPI(L, entity.get());

                // Загрузить и выполнить скрипт
                if (luaL_dofile(L, scriptComp.scriptFile.c_str()) != LUA_OK) {
                    std::cerr << lua_tostring(L, -1) << std::endl;
                }

                // Вызвать функцию update(dt)
                luabridge::LuaRef update = luabridge::getGlobal(L, "update");
                if (update.isFunction()) {
                    update(deltaTime);
                }

                lua_close(L);
            }
        }
    }

    void RegisterTransformAPI(lua_State* L, Entity* entity) {
        auto& transform = entity->GetComponent<TransformComponent>();
        luabridge::getGlobalNamespace(L)
            .beginNamespace("engine")
   
            .addFunction("get_position", [&transform]() {
            auto pos = transform.GetWorldPosition();
            return std::make_tuple(pos.x, pos.y, pos.z);
                })
            .addFunction("set_position", [&transform](float x, float y, float z) {
            transform.SetWorldPosition(Vector3(x, y, z));
                })
            .addFunction("rotate", [&transform](float axisX, float axisY, float axisZ, float angle) {
            // transform.rotation += {axisX * angle, axisY * angle, axisZ * angle};
                })
            .endNamespace();
    }
};
