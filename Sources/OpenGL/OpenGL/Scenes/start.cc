#include "start.h"
#include "..\application.h"
#include "..\GlobalObjects\Canvas\canvas.h"
#include "..\GlobalObjects\Canvas\image.h"
#include "..\GlobalObjects\Canvas\text.h"
#include "bloom_scene.h"
#include "primitive_proc.h"
#include "path_finding2d.h"

Start::Start() {
	glEnable(GL_DEPTH_TEST);

	auto canvas = std::make_unique<Canvas::Canvas>();
	canvas->InitiateChild<Canvas::Image>("Image", "Resources/window.png");
	auto image = canvas->GetChild("Image");

	using namespace std::string_literals;

	Canvas::Text&& txt_1{"OpenGL Tutorial Samples\n" "And dirty engine :)", glm::vec3{ 25, -25, 0 } };
	txt_1.SetOrigin(IOriginable::Origin::UP_LEFT);
	txt_1.SetScaleValue(0.5f);
	canvas->InitiateChild("Txt1", std::move(txt_1));

	objects[0] = std::move(canvas);
}

void Start::HandleInput(GLFWwindow* const window) {
    if (DoesKeyPressed(window, GLFW_KEY_A)) {

    }
    else if (DoesKeyPressed(window, GLFW_KEY_B)) {
        Application::getInstance().ReplaceScene((PrimProc*)nullptr);
    }
    else if (DoesKeyPressed(window, GLFW_KEY_C)) {
        Application::getInstance().ReplaceScene((BloomScene*)nullptr);
    }
	else if (DoesKeyPressed(window, GLFW_KEY_D)) {
		Application::getInstance().ReplaceScene((PathFinding2D*)nullptr);
	}

    Scene::HandleInput(window);
}

void Start::Draw() {
    glClearColor(.0f, .0f, .0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& object : objects) {
		object.second->Draw();
	}

    DrawText();
}

void Start::DrawText() {
    glDisable(GL_DEPTH_TEST);

    /** String rendering */
    //font.RenderText("OpenGL Tutorial Samples", { 25, 480 - 48 }, 1.f, { 1, 1, 1 });

  //  std::string text = "A : Terrain Tesslation\n"
  //      "B : Flapping Carpet\n"
  //      "C : Bloom\n"
		//"D : PathFinding2D";
  //  font.RenderText(text, { 25, 240 }, .5f, { 1, 1, 1 });

  //  std::string copyright = "Copyright (c) 2018, Jongmin Yun All rights reserved.";
  //  font.RenderText(copyright, { 16, 16 }, .25f, { 1, 1, 1 });

    glEnable(GL_DEPTH_TEST);
}

void Start::Update() {
}
