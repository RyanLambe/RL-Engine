#include "GameContext.h"

#include "Application.h"

namespace rl
{

    void GameContext::Setup()
    {
        library->RunFunctionVal<void>("GameSetup", (void*)Application::GetSharedPtr());
    }

    void GameContext::AddSystem(const std::string& system)
    {
        library->RunFunction<void>("AddSystem", system);
    }

    void GameContext::AddComponent(const std::string& component, Entity entity)
    {
        library->RunFunction<void>("AddComponent", component, entity);
    }

    void GameContext::RemoveComponent(const std::string& component, Entity entity)
    {
        library->RunFunction<void>("RemoveComponent", component, entity);
    }

    void* GameContext::GetComponent(const std::string& component, Entity entity)
    {
        return library->RunFunction<void*>("GetComponent", component, entity);
    }

    void GameContext::GetComponentValue(const VariableType& valType, const std::string& componentType,
                                        const std::string& varName, const Entity& entity, void* outBuf)
    {
        void* temp = library->RunFunction<void*>("GetValue" + ToStringUpper(valType), componentType, varName, entity);
        if (temp == nullptr)
            return;
        switch (valType)
        {
            case VariableType::Unknown:
                break;
            case VariableType::I8:
                *(i8*)outBuf = *std::bit_cast<i8*>(temp);
                break;
            case VariableType::I16:
                *(i16*)outBuf = *std::bit_cast<i16*>(temp);
                break;
            case VariableType::I32:
                *(i32*)outBuf = *std::bit_cast<i32*>(temp);
                break;
            case VariableType::I64:
                *(i64*)outBuf = *std::bit_cast<i64*>(temp);
                break;
            case VariableType::U8:
                *(u8*)outBuf = *(u8*)temp;
                break;
            case VariableType::U16:
                *(u16*)outBuf = *(u16*)temp;
                break;
            case VariableType::U32:
                *(u32*)outBuf = *(u32*)temp;
                break;
            case VariableType::U64:
                *(u64*)outBuf = *(u64*)temp;
                break;
            case VariableType::F32:
                *(f32*)outBuf = *(f32*)temp;
                break;
            case VariableType::F64:
                *(f64*)outBuf = *(f64*)temp;
                break;
            case VariableType::VEC2:
                *(Vec2*)outBuf = *(Vec2*)temp;
                break;
            case VariableType::VEC3:
                *(Vec3*)outBuf = *(Vec3*)temp;
                break;
            case VariableType::VEC4:
                *(Vec4*)outBuf = *(Vec4*)temp;
                break;
            case VariableType::QUAT:
                *(Quaternion*)outBuf = *(Quaternion*)temp;
                break;
        }
    }

    void GameContext::SetComponentValue(const VariableType& valType, const std::string& componentType,
                                        const std::string& varName, const Entity& entity, VariableData val)
    {
        switch (valType)
        {
            case VariableType::Unknown:
                break;
            case VariableType::I8:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity, val.I8);
                break;
            case VariableType::I16:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.I16);
                break;
            case VariableType::I32:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.I32);
                break;
            case VariableType::I64:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.I64);
                break;
            case VariableType::U8:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity, val.U8);
                break;
            case VariableType::U16:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.U16);
                break;
            case VariableType::U32:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.U32);
                break;
            case VariableType::U64:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.U64);
                break;
            case VariableType::F32:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.F32);
                break;
            case VariableType::F64:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.F64);
                break;
            case VariableType::VEC2:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.Vec2);
                break;
            case VariableType::VEC3:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.Vec3);
                break;
            case VariableType::VEC4:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.Vec4);
                break;
            case VariableType::QUAT:
                library->RunFunction<void>("SetValue" + ToStringUpper(valType), componentType, varName, entity,
                                           val.Quat);
                break;
        }
    }

    void GameContext::UpdateSceneWithComponentData(const std::string& component, Entity entity)
    {
        Quaternion quatTemp; // only used for quat properties

        for (auto& property : Scene::GetScene().GetEntityData(entity)->componentData[component])
        {
            switch (property.second.type)
            {
                case VariableType::Unknown:
                    return;
                case VariableType::I8:
                    property.second.data.I8 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.I8);
                    break;
                case VariableType::I16:
                    property.second.data.I16 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.I16);
                    break;
                case VariableType::I32:
                    property.second.data.I32 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.I32);
                    break;
                case VariableType::I64:
                    property.second.data.I64 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.I64);
                    break;
                case VariableType::U8:
                    property.second.data.U8 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.U8);
                    break;
                case VariableType::U16:
                    property.second.data.U16 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.U16);
                    break;
                case VariableType::U32:
                    property.second.data.U32 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.U32);
                    break;
                case VariableType::U64:
                    property.second.data.U64 = 0;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.U64);
                    break;
                case VariableType::F32:
                    property.second.data.F32 = 0.0f;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.F32);
                    break;
                case VariableType::F64:
                    property.second.data.F64 = 0.0f;
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.F64);
                    break;
                case VariableType::VEC2:
                    property.second.data.Vec2 = Vec2(0);
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.Vec2);
                    break;
                case VariableType::VEC3:
                    property.second.data.Vec3 = Vec3(0);
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.Vec3);
                    break;
                case VariableType::VEC4:
                    property.second.data.Vec4 = Vec4(0);
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.Vec4);
                    break;
                case VariableType::QUAT:
                    property.second.data.Quat = Quaternion(1, 0, 0, 0);
                    GetComponentValue(property.second.type, component, property.first, entity,
                                      &property.second.data.Quat);
                    break;
            }
        }
    }

    void GameContext::UpdateComponentWithSceneData(const std::string& component, Entity entity)
    {
        for (auto& property : Scene::GetScene().GetEntityData(entity)->componentData[component])
        {
            SetComponentValue(property.second.type, component, property.first, entity, property.second.data);
        }
    }
}