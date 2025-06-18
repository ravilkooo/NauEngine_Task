#include "TransformComponent.h"

#include "TransformCBuffer.h"

TransformComponent::TransformComponent(ID3D11Device* device) {
    transformBuffer = new TransformCBuffer(device, this, 0u);
}

void TransformComponent::Bind(ID3D11DeviceContext* context) {
    transformBuffer->Bind(context);
}

void TransformComponent::SetPosition(Vector3 newPosition)
{
    position = newPosition;
}
void TransformComponent::SetRotation(Vector3 newRotation)
{
    rotation = newRotation;
}

void TransformComponent::SetRotation(Quaternion rotQuaternion)
{
    rotation = rotQuaternion.ToEuler();
}

void TransformComponent::SetScale(float newScaleFactor)
{
    scaleFactor = { newScaleFactor, newScaleFactor, newScaleFactor };
}

void TransformComponent::SetScale(Vector3 newScaleFactor)
{
    scaleFactor = newScaleFactor;
}

void TransformComponent::Translate(Vector3 moveVector)
{
    position += moveVector;
}

void TransformComponent::Rotate(Vector3 pitchYawRoll)
{
    rotation = rotation + pitchYawRoll;
}

void TransformComponent::Rotate(Quaternion rotQuaternion)
{
    rotation = (Quaternion::CreateFromYawPitchRoll(rotation) * rotQuaternion).ToEuler();
}

void TransformComponent::Scale(float newScaleFactor)
{
    scaleFactor = scaleFactor * newScaleFactor;
}

void TransformComponent::Scale(Vector3 newScaleFactor)
{
    scaleFactor = scaleFactor * newScaleFactor;
}

Matrix TransformComponent::GetTranslationMatrix()
{
    return Matrix::CreateTranslation(position);
}

Matrix TransformComponent::GetRotationMatrix()
{
    return Matrix::CreateFromYawPitchRoll(rotation);
}

Matrix TransformComponent::GetScaleMatrix()
{
    return Matrix::CreateScale(scaleFactor);
}

Matrix TransformComponent::GetFullTransform()
{
    return GetScaleMatrix() * GetRotationMatrix() * GetTranslationMatrix();
}

std::string TransformComponent::getTypeName() const
{
    return "TransformComponent";
}

void TransformComponent::to_json(json& j)
{
    j = json{
        {"position", {position.x, position.y, position.z}},
        {"rotation", {rotation.x, rotation.y, rotation.z}},
        {"scaleFactor", {scaleFactor.x, scaleFactor.y, scaleFactor.z}}
    };
}

void TransformComponent::from_json(const json& j)
{
}
