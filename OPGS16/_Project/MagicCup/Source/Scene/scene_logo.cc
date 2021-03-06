
///
/// @license BSD 2-Clause License
///
/// Copyright (c) 2018, Jongmin Yun(Neu.), All rights reserved.
/// If you want to read full statements, read LICENSE file.
///

/// Header file
#include "../../Include/Scene/scene_logo.h"

#include "../../Include/Object/Common/empty_canvas.h"
#include "../../Include/Internal/object_keyword.h"
#include "../../Include/Script/SceneGameLogo/script_logo_effect.h"
#include "../../Include/Script/SceneGameLogo/script_file_manage.h"
#include "../../Include/Object/Common/orthogonal_camera.h"

#include "../../Include/Object/Scoreboard/ui_scoreboard.h"

namespace magiccup {

void SceneLogo::Initiate() {
  this->SetBackgroundColor(opgs16::DColor::Black);

  auto canvas = CreateGameObject<magiccup::EmptyCanvas>(name::canvas);
  canvas->AddComponent<ScriptLogoEffect>(*canvas);
  canvas->AddComponent<ScriptFileManage>(*canvas);
}

} /// ::magiccup namespace