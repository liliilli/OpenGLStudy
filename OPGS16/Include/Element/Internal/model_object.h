#ifndef OPGS16_ELEMENT_INTERNAL_MODEL_OBJECT_H
#define OPGS16_ELEMENT_INTERNAL_MODEL_OBJECT_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Element/Internal/model_object.h
///
/// @author Jongmin Yun
///
/// @log
/// 2018-06-12 Create file
///

#include <string>

#include <Element/Internal/mesh_object.h>

struct aiNode;
struct aiScene;

namespace opgs16::element {

///
/// @enum EModelMeshType
///
/// @brief
/// Classification type for meshes of each DModelObject.
/// If mesh is multiple, EModelMeshType must be Multiple or not.
///
enum class EModelMeshType {
  Single,
  Multiple
};

///
/// @class DModelObject
///
/// @brief
/// Model meshes which stores vertices container object.
///
class DModelObject {
public:
  explicit DModelObject() = default;
  explicit DModelObject(std::string& model_path);

  DModelObject(const DModelObject&) = default;
  DModelObject(DModelObject&&) = default;
  DModelObject& operator=(const DModelObject&) = default;
  DModelObject& operator=(DModelObject&&) = default;
  virtual ~DModelObject() = default;

  ///
  /// @brief Get model name.
  /// @return model name string.
  ///
  virtual std::string GetModelName() const noexcept;

  ///
  /// @brief Return meshes to be referenced.
  /// @return Meshes reference which had been generated by model file.
  ///
  inline const std::vector<DMeshObject>& GetMeshes() const noexcept {
    return m_meshes;
  }

protected:
  ///
  /// @brief
  ///
  ///
  /// @param[in] node
  /// @param[in] scene
  ///
  void ProcessNode(const aiNode& node, const aiScene& scene);

  // Each model directly stores mesh object information.
  std::vector<DMeshObject> m_meshes = {};

  // Not used yet.
  EModelMeshType m_model_mesh_type = EModelMeshType::Single;
  // Not used yet.
  std::string m_model_name = "";
  // Not used yet.
  std::string m_directory_path = "";
};

} /// ::opgs16::element

#endif /// OPGS16_ELEMENT_INTERNAL_MODEL_OBJECT_H