#include "test_obj.h"   /*! Header file */

#include "..\..\..\System\Components\camera.h"         /*! component::Camera */
//#include "..\..\..\System\Manager\object_manager.h"    /*! ObjectManager */
#include "..\..\..\System\Manager\scene_manager.h"     /*! SceneManager */
#include "..\..\..\System\Shader\shader_wrapper.h"     /*! ShaderWrapper */
#include "..\Scripts\obj_script_1.h"    /*! ObjectScript1 */

TestObject1::TestObject1(const int i, const float size) :
    m_sprite_renderer{ "128_" + std::to_string(i) , "gQuad" } {
    SetScaleValue(size);

	auto& shader = m_sprite_renderer.GetWrapper();
	shader.InsertUniformValue<glm::mat4>("projection", glm::mat4{});
	shader.InsertUniformValue<float>("alpha", 0.0f);

    AddComponent<ObjectScript1>(*this);
}

void TestObject1::Render() {
    auto PVM =
        SceneManager::GetInstance().GetPresentScene()->GetMainCamera()->GetPV() *
        GetModelMatrix();

    auto& shader = m_sprite_renderer.GetWrapper();
    shader.ReplaceUniformValue<glm::mat4>("projection", PVM);
    shader.ReplaceUniformValue("alpha", 1.0f);
    m_sprite_renderer.RenderSprite();
}