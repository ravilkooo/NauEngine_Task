#include "TransformComponent.h"

#include "ResourceManager/Resources/TransformCBuffer.h"


TransformComponent::TransformComponent()
{
    worldMatrix = XMMatrixIdentity();
}

TransformComponent::TransformComponent(ID3D11Device* device) {
    worldMatrix = XMMatrixIdentity();
    SetupBuffer(device);
}

void TransformComponent::SetupBuffer(ID3D11Device* device)
{
    transformBuffer = new TransformCBuffer(device, this, 0u);
}

void TransformComponent::Bind(ID3D11DeviceContext* context) {
    transformBuffer->Bind(context);
}

void TransformComponent::SetOffset(Vector3 newPosition)
{
    localOffset = newPosition;
}
void TransformComponent::SetLocalRotation(Vector3 newRotation)
{
    localRotation = newRotation;
}

void TransformComponent::SetLocalRotation(Quaternion rotQuaternion)
{
    localRotation = rotQuaternion.ToEuler();
}

void TransformComponent::SetScaleFactor(float newScaleFactor)
{
    scaleFactor = { newScaleFactor, newScaleFactor, newScaleFactor };
}

void TransformComponent::SetScaleFactor(Vector3 newScaleFactor)
{
    scaleFactor = newScaleFactor;
}

void TransformComponent::AddOffset(Vector3 moveVector)
{
    localOffset += moveVector;
}

void TransformComponent::LocalRotate(Vector3 pitchYawRoll)
{
    localRotation = localRotation + pitchYawRoll;
}

void TransformComponent::LocalRotate(Quaternion rotQuaternion)
{
    localRotation = (Quaternion::CreateFromYawPitchRoll(localRotation) * rotQuaternion).ToEuler();
}

void TransformComponent::LocalRotate(Vector3 axis, float angle)
{
    localCustomRotationMatrix *= Matrix::CreateFromAxisAngle(axis, angle);
}

void TransformComponent::Scale(float newScaleFactor)
{
    scaleFactor = scaleFactor * newScaleFactor;
}

void TransformComponent::Scale(Vector3 newScaleFactor)
{
    scaleFactor = scaleFactor * newScaleFactor;
}

Matrix TransformComponent::GetOffsetMatrix()
{
    return Matrix::CreateTranslation(localOffset);
}

Matrix TransformComponent::GetLocalRotationMatrix()
{
    return Matrix::CreateFromYawPitchRoll(localRotation);
}

Matrix TransformComponent::GetScaleMatrix()
{
    return Matrix::CreateScale(scaleFactor);
}

Matrix TransformComponent::GetLocalTransform()
{
    return GetScaleMatrix() * GetLocalRotationMatrix() * localCustomRotationMatrix * GetOffsetMatrix();
}

Matrix TransformComponent::GetWorldMatrix()
{
    return worldMatrix;
}

void TransformComponent::SetWorldMatrix(Matrix newWorldMatrix)
{
    worldMatrix = newWorldMatrix;
}

void TransformComponent::TransformWorldMatrix(Matrix newTransform)
{
    worldMatrix = worldMatrix * newTransform;
}

Vector3 TransformComponent::GetWorldPosition()
{
    // std::cout << worldMatrix._41 << ", " << worldMatrix._44 << "\n";
    return Vector3(
        worldMatrix._41 / worldMatrix._44,
        worldMatrix._42 / worldMatrix._44,
        worldMatrix._43 / worldMatrix._44);
}

void TransformComponent::SetWorldPosition(Vector3 newPosition)
{
    worldMatrix = worldMatrix * Matrix::CreateTranslation(-GetWorldPosition() + newPosition);
}

Matrix TransformComponent::GetFullTransform()
{
    return GetLocalTransform() * GetWorldMatrix();
}

std::string TransformComponent::getTypeName() const
{
    return "TransformComponent";
}

void TransformComponent::to_json(json& j)
{
    j = json{
        {"localOffset", {localOffset.x, localOffset.y, localOffset.z}},
        {"localRotation", {localRotation.x, localRotation.y, localRotation.z}},
        {"scaleFactor", {scaleFactor.x, scaleFactor.y, scaleFactor.z}}
    };
    json wMat;
    matrix_to_json(wMat, worldMatrix);
    j["worldMatrix"] = wMat;
}

void TransformComponent::from_json(ID3D11Device* device, const json& j)
{
    auto pos = j.at("localOffset");
    localOffset = { pos[0].get<float>(), pos[1].get<float>(), pos[2].get<float>() };

    auto rot = j.at("localRotation");
    localRotation = { rot[0].get<float>(), rot[1].get<float>(), rot[2].get<float>() };

    auto scale = j.at("scaleFactor");
    scaleFactor = { scale[0].get<float>(), scale[1].get<float>(), scale[2].get<float>() };

    auto wMat = j.at("worldMatrix");
    matrix_from_json(wMat, worldMatrix);

    SetupBuffer(device);
}
