#include "Transform.h"

Transform::Transform()
{
   
}

glm::vec3 Transform::GetPosition() const
{
    return LocalPos;
}

void Transform::SetPosition(glm::vec3 position)
{
    LocalPos = position;
}

glm::quat Transform::GetRotation() const
{
    return LocalRot;
}

void Transform::SetRotation(glm::quat rotation)
{
    LocalRot = rotation;
}

glm::vec3 Transform::GetForward() const
{
    return glm::vec3();
}

void Transform::SetForward(glm::vec3 forward)
{
}

glm::mat4 Transform::LocalMat() const
{
    glm::mat4 trs = glm::translate(glm::mat4(1.0f), LocalPos);  // translation
    trs *= glm::toMat4(LocalRot);                               // rotation
    trs = glm::scale(trs, LocalScl);                            // scale
    return trs;
}
