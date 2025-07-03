#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <directxmath.h>
#include <SimpleMath.h>

#include "Component.h"

#include "ResourceManager/Resources/TransformCBuffer.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


class TransformComponent :
    public Component
{
public:
    TransformComponent();
    TransformComponent(ID3D11Device* device);

    void SetupBuffer(ID3D11Device* device);

    // To-do ptr
    TransformCBuffer* transformBuffer;

    void Bind(ID3D11DeviceContext* context);

    ~TransformComponent() = default;

    // void Delete() override {};

    // Local Transforms
    Vector3 localOffset = { 0, 0, 0 };
    Vector3 localRotation = { 0, 0, 0 };
    Vector3 scaleFactor = { 1, 1, 1 };
    Matrix localCustomRotationMatrix = Matrix::Identity;

    void SetOffset(Vector3 newPosition);
    // Pitch (x-axis), Yaw (y-axis), Roll (z-axis)
    void SetLocalRotation(Vector3 newRotation);
    void SetLocalRotation(Quaternion rotQuaternion);
    void SetScaleFactor(float scaleFactor);
    void SetScaleFactor(Vector3 scaleFactor);

    void AddOffset(Vector3 moveVector);
    void LocalRotate(Vector3 pitchYawRoll);
    void LocalRotate(Quaternion rotQuaternion);
    void LocalRotate(Vector3 axis, float angle);
    void Scale(float newScaleFactor);
    void Scale(Vector3 newScaleFactor);

    Matrix GetOffsetMatrix();
    Matrix GetLocalRotationMatrix();
    Matrix GetScaleMatrix();

    Matrix GetLocalTransform();

    // Global Transforms
    Matrix worldMatrix;

    Matrix GetWorldMatrix();
    void SetWorldMatrix(Matrix newWorldMatrix);
    void TransformWorldMatrix(Matrix newTransform);
    Vector3 GetWorldPosition();
    void SetWorldPosition(Vector3 newPosition);
    
    // Full Transforms
    Matrix GetFullTransform();

    const std::type_info& getType() const override {
        return typeid(TransformComponent);
    }

    // Serialization
    std::string getTypeName() const override;

    void to_json(json& j) override;
    void from_json(ID3D11Device* device, const json& j) override;
};

inline void matrix_to_json(json& j, const Matrix& m) {
    j = json::array();
    for (int row = 0; row < 4; ++row) {
        json rowArr = json::array();
        for (int col = 0; col < 4; ++col) {
            rowArr.push_back(m(row, col));
        }
        j.push_back(rowArr);
    }
}

inline void matrix_from_json(const json& j, Matrix& m) {
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            m(row, col) = j.at(row).at(col).get<float>();
        }
    }
}