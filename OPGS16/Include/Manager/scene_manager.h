#ifndef OPGS16_SYSTEM_MANAGER_PUBLIC_SCENE_MANAGER_H
#define OPGS16_SYSTEM_MANAGER_PUBLIC_SCENE_MANAGER_H

///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///
/// @file Manager/scene_manager.h
///
/// @author Jongmin Yun
///
/// @log
/// 2018-02-14 Create file.
/// 2018-03-04 Refactoring.
/// 2018-04-08 Add a macro, detach automatic initiation from push scene.
/// 2018-04-14 Collapsed inline function definitions to class body.
/// 2018-06-15 Refactoring.
///

#include <memory>

#include <Core/application.h>   /// ::opgs16::MApplication
#include <Element/scene.h>      /// ::opgs16::element::CScene

#include <Helper/template.h>    /// Type checking tempaltes

//!
//! Forward declaration.
//!

namespace opgs16::manager::scene::__ {

template <
  class TTy,
  typename = std::enable_if_t<IsCSceneBase<TTy>>
>
void PrivateReplaceScene();

}

//!
//! Implementation.
//!

///
/// @namespace scene
/// @brief Manager class manages game scene.
///
namespace opgs16::manager::scene {

/// Types
using TSceneStack = std::vector<std::unique_ptr<opgs16::element::CScene>>;

///
/// @brief
/// The method that adds scene to scene stack.
/// Add scene to scene stack stores scenes is paused, and move to top scene.
///
/// @tparam TTy
/// Type parameter is based on Scene, value must be nullptr to prevent
/// double initiation of scene.
///
template <
  class TTy,
  typename = std::enable_if_t<IsCSceneBase<TTy>>
>
void PushScene() {
  __::Get().push_back(std::make_unique<TTy>());
}

///
/// @brief
/// The method replace scene with top scene.
/// before actually replacing previous scene,
/// application have to go through purify resources,
/// to prevent unintentional memory leak and runtime errors.
///
/// @tparam TTy
///
template <
  class TTy,
  typename = std::enable_if_t<IsCSceneBase<TTy>>
>
void ReplaceScene() {
  entry::SetOnBeforeUpdateCallback(std::bind(&__::PrivateReplaceScene<TTy>));
}

///
/// @brief
/// The method removes top (present) scene.
/// If there is no scene, exit application automatically.
/// Otherwise all Update() and Rendering procedures delegates to previous scene.
///
void PopScene();

///
/// @brief Initiate top scene.
///
void InitiateTopScene();

///
/// @brief
/// @return
///
TSceneStack& GetLoadedSceneList() noexcept;

///
/// @brief Get top scene's pointer.
/// @return The pointer of top scene, if application has no scene return nullptr
///
element::CScene* PresentScene();

///
/// @brief
/// @return
///
bool Empty() noexcept;

} /// ::opgs16::manager::scene namespace

namespace opgs16::manager::scene::__ {

///
/// @brief
///
TSceneStack& Get();

///
/// @brief
/// Release all resource used in scene,
/// prevent runtime error and resource memory leak.
///
void ReleaseAllResources();

///
/// @brief
///
/// @tparam TTy
///
///
template <class TTy, typename>
void PrivateReplaceScene() {
  // Purify remain resources.
  ReleaseAllResources();

  // Pop present scene.
  Get().pop_back();

  // Push present scene.
  PushScene<TTy>();
  InitiateTopScene();
}

///
/// @brief
///
void PrivatePopScene();

} /// private internal namespace

#define M_REPLACE_SCENE(__scene_name__) \
opgs16::manager::scene::ReplaceScene<__scene_name__>()

#define M_PUSH_SCENE(__scene_name__, __automatical_initiate__) \
opgs16::manager::scene::PushScene<__scene_name__>(); \
if (__automatical_initiate__) opgs16::manager::scene::InitiateTopScene()

#define M_POP_SCENE() \
opgs16::manager::scene::PopScene();

#endif /// OPGS16_SYSTEM_MANAGER_SCENE_MANAGER_H
