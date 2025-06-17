#pragma once
#include "Component.h"

#include <wrl.h>
#include <d3d11.h>
#include <directxmath.h>
#include <SimpleMath.h>

#include "TransformCBuffer.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


class TransformComponent :
    public Component
{
public:
    TransformComponent(ID3D11Device* device);

    // To-do ptr
    TransformCBuffer* transformBuffer;

    void Bind(ID3D11DeviceContext* context);

    ~TransformComponent() = default; // защищенный деструктор ? TO-DO: what is it ?

    // void Delete() override {};

    Vector3 position = { 0, 0, 0 };
    // Pitch (x-axis), Yaw (y-axis), Roll (z-axis)
    Vector3 rotation = { 0, 0, 0 };
    Vector3 scaleFactor = { 1, 1, 1 };

    const std::type_info& getType() const override {
        return typeid(TransformComponent);
    }

    void SetPosition(Vector3 newPosition);
    // Pitch (x-axis), Yaw (y-axis), Roll (z-axis)
    void SetRotation(Vector3 newRotation);
    void SetRotation(Quaternion rotQuaternion);
    void SetScale(float scaleFactor);
    void SetScale(Vector3 scaleFactor);

    void Translate(Vector3 moveVector);
    void Rotate(Vector3 pitchYawRoll);
    void Rotate(Quaternion rotQuaternion);
    void Scale(float newScaleFactor);
    void Scale(Vector3 newScaleFactor);

    Matrix GetTranslationMatrix();
    Matrix GetRotationMatrix();
    Matrix GetScaleMatrix();
    Matrix GetFullTransform();

    Vector3 SwapRotXYZToPitchYallRoll(Vector3 rot) { return { rot.y, rot.x, rot.x }; };
};

