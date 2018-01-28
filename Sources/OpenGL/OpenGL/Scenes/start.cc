#include "start.h"
#include "..\application.h"
#include "..\Headers\canvas_components.h"
#include "bloom_scene.h"
#include "primitive_proc.h"
#include "path_finding2d.h"

Start::Start() {
	auto canvas = std::make_unique<Canvas::Canvas>();
	canvas->InitiateChild<Canvas::Image>("Image", "Resources/window.png");
	auto image = canvas->GetChild("Image");
	image->SetScaleValue(128.f);
	image->InitiateChild<Canvas::Text>("Txt1", "In Messsage Hello world");

	Canvas::Text&& txt_1{"OpenGL Tutorial Samples\n" "And dirty engine :)", glm::vec3{ 25, -25, 0 } };
	txt_1.SetOrigin(IOriginable::Origin::UP_LEFT);
	canvas->InitiateChild("Txt1", std::move(txt_1));

    std::string&& text = "A : Terrain Tesslation\n"
        "B : Flapping Carpet\n"
        "C : Bloom\n"
		"D : PathFinding2D";
	Canvas::Text&& txt_2{ std::move(text), glm::vec3{ 25, 0, 0 } }; {
		txt_2.SetOrigin(IOriginable::Origin::CENTER_LEFT);
		txt_2.SetFontSize(16);
	}
	canvas->InitiateChild("Txt2", std::move(txt_2));

	Canvas::Text&& txt_3{ "Copyright (c) 2018, Jongmin Yun All rights reserved.", {16, 16, 0} }; {
		txt_3.SetOrigin(IOriginable::Origin::DOWN_LEFT);
		txt_3.SetFontSize(12);
	}
	canvas->InitiateChild("Txt3", std::move(txt_3));

	//for (int i = 1; i <= 9; ++i) {
	//	Canvas::Text&& txt{ m_scene_name };
	//	txt.SetOrigin(static_cast<IOriginable::Origin>(i));
	//	txt.SetScaleValue(0.5f);
	//	txt.SetAlignment(IAlignable::Alignment::CENTER);

	//	std::string&& tag{ "txt" + std::to_string(i) };
	//	canvas->InitiateChild(std::move(tag), std::move(txt));
	//}

	InsertObject("Canvas", canvas);
}

void Start::HandleInput(GLFWwindow* const window) {
    if (DoesKeyPressed(window, GLFW_KEY_A)) {

    }
    else if (DoesKeyPressed(window, GLFW_KEY_B)) {
        Application::getInstance().ReplaceScene<PrimProc>();
    }
    else if (DoesKeyPressed(window, GLFW_KEY_C)) {
        Application::getInstance().ReplaceScene<BloomScene>();
    }
	else if (DoesKeyPressed(window, GLFW_KEY_D)) {
		Application::getInstance().ReplaceScene<PathFinding2D>();
	}

    Scene::HandleInput(window);
}

void Start::Draw() {
    glClearColor(.2f, .0f, .0f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::Draw();
}

void Start::Update() {
	Scene::Update();
}
