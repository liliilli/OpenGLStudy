#include "object.h"                     /*! Header file */
#include "impl\object_impl.h"           /*! ObjectImpl */
#include "..\Debugs\hierarchy_tree.h"   /*! ObjectTree */

#include <iostream>

Object::Object() {
	std::unique_ptr<ObjectImpl, ObjectImplDeleter> instance{ new ObjectImpl() };
	m_data = std::move(instance);
}

const glm::vec3& Object::GetLocalPosition() const noexcept {
    return m_data->GetLocalPosition();
}

const glm::vec3& Object::GetWorldPosition() const noexcept {
    return m_data->GetWorldPosition();
}

const glm::vec3& Object::GetParentPosition() const noexcept {
    return m_data->GetParentPosition();
}

const glm::vec3& Object::GetFinalPosition() const noexcept {
    return m_data->GetFinalPosition();
}

void Object::SetLocalPosition(const glm::vec3& position) noexcept {
	m_data->SetLocalPosition(position);
}

void Object::SetWorldPosition(const glm::vec3& world_position) {
	m_data->SetWorldPosition(world_position);
    PropagateParentPosition();
}

void Object::SetParentPosition(const glm::vec3& parent_position) {
	m_data->SetParentPosition(parent_position);
    PropagateParentPosition();
}

void Object::PropagateParentPosition() {
    for (auto& child : m_children) {
        auto& child_ptr = child.second;
        /*! If object is not empty and activated and permits succeeding positioning. */
        if (child_ptr && child_ptr->GetActive() && child_ptr->GetSucceedingPositionFlag())
            child_ptr->SetParentPosition(GetParentPosition());
    }
}

const float Object::GetRotationAngle() const noexcept {
    return m_data->GetRotationLocalAngle();
}

const glm::vec3& Object::GetRotationFactor() const noexcept {
    return m_data->GetRotationLocalFactor();
}

void Object::SetRotationAngle(const float angle_value) {
	m_data->SetRotationLocalAngle(angle_value);

    //for (auto& child : m_children) {
    //    auto& obj_ptr = child.second;
    //    /*! If child.second is not empty and activated and permits succeeding rotation */
    //    if (obj_ptr && obj_ptr->GetActive() && obj_ptr->GetSucceedingRotationFlag())
    //}
}

void Object::SetRotationFactor(const glm::vec3& factor) {
	m_data->SetRotationLocalFactor(factor);
}

const float Object::GetScaleValue() const noexcept {
    return m_data->GetScaleLocalValue();
}

const glm::vec3& Object::GetScaleFactor() const noexcept {
    return m_data->GetScaleLocalFactor();
}

void Object::SetScaleValue(const float scale_value) {
	m_data->SetScaleLocalValue(scale_value);
}

void Object::SetScaleFactor(const glm::vec3& factor) {
	m_data->SetScaleLocalFactor(factor);
}

const glm::mat4& Object::GetModelMatrix() const {
    return m_data->GetModelMatrix();
}

void Object::SetSucceedingPositionFlag(bool value) noexcept {
    m_data->SetSucceedingPositionFlag(value);
}

void Object::SetSucceedingRotationFlag(bool value) noexcept {
    m_data->SetSucceedingRotationFlag(value);
}

void Object::SetSucceedingScalingFlag(bool value) noexcept {
    m_data->SetSucceedingScalingFlag(value);
}

bool Object::GetSucceedingPositionFlag() const noexcept {
    return m_data->GetSucceedingPositionFlag();
}

bool Object::GetSucceedingRotationFlag() const noexcept {
    return m_data->GetSucceedingRotationFlag();
}

bool Object::GetSucceedingScalingFlag() const noexcept {
    return m_data->GetSucceedingScalingFlag();
}

std::vector<std::string> Object::GetChildrenNameList() const {
	std::vector<std::string> list(m_children.size());
	for (const auto& object_pair : m_children) {
        /*! emplace_back evades unnecessary temp instance. */
	    list.emplace_back(object_pair.first);
	}

	return list;
}

Object::object_map& Object::GetChildList() {
	 return m_children;
 }

Object::object_raw const Object::GetChild(const std::string& tag) {
    if (m_children.find(tag) == m_children.end()) return nullptr;
    return m_children.at(tag).get();
}

bool Object::DestroyChild(const std::string& child_name) {
    if (m_children.find(child_name) == m_children.end())
	    return false;

    m_children.erase(child_name);
    return true;
}

bool Object::GetActive() {
    return m_data->GetActive();
}

void Object::SetActive(const bool value) {
	m_data->SetActive(value);
}

void Object::SetTag(const std::string& tag_name) {
    m_data->SetTag(tag_name);
}

void Object::SetTag(const size_t tag_index) {
    m_data->SetTag(tag_index);
}

size_t Object::GetTagIndexOf() const {
    return m_data->GetTagIndexOf();
}

std::string Object::GetTagNameOf() const {
    return m_data->GetTagNameOf();
}

void Object::GetObjectTree(ObjectTree* const tree) {
	for (const auto& object : m_children) {
        if (object.second) {
            ObjectTree child; child.name = object.first;
            tree->children.push_back(std::move(child));
            object.second->GetObjectTree(&*tree->children.rbegin());
        }
	}
}

void ObjectImplDeleter::operator()(ObjectImpl* p) {
	delete p;
}
