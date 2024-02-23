
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

#include "game/game.h"
#include "resource_manager.h"

#include "spdlog/spdlog.h"
#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/yaml.h"

#include <cstring>
#include <fstream>
#include <random>

// GLFW function declerations
void keyCallback(GLFWwindow *window, int key, int scancode,
				 int action, int mode);
void mouseButtonCallback(GLFWwindow *window, int button, int action,
						 int mode);

void framebufferSizeCallback(GLFWwindow *window, int width,
							 int height);

int WINDOW_WIDTH;
int WINDOW_HEIGHT;
std::string WINDOW_TITLE;

GameProject *game;

YAML::Node config;
std::mt19937 rnd(std::random_device{}());

void LoadConfig(const char *configFilename) {
	std::ifstream configFile(configFilename);
	config = YAML::Load(configFile);
	if (!config["debug"]["loglevel"]) {
		config["debug"]["loglevel"] = "info";
	}
	if (!config["window"]["width"]) {
		config["window"]["width"] = 800U;
	}
	if (!config["window"]["height"]) {
		config["window"]["height"] = 600U;
	}
	if (!config["window"]["title"]) {
		config["window"]["title"] = "Example";
	}
	WINDOW_WIDTH =
		static_cast<int>(config["window"]["width"].as<unsigned>());
	WINDOW_HEIGHT =
		static_cast<int>(config["window"]["height"].as<unsigned>());
	WINDOW_TITLE = config["window"]["title"].as<std::string>();
	spdlog::set_level(spdlog::level::from_str(
		config["debug"]["loglevel"].as<std::string>()));
}
void DumpConfig(const char *configFilename) {
	std::ofstream configFile(configFilename);
	YAML::Emitter dumper;
	dumper.SetIndent(2);
	dumper.SetMapFormat(YAML::Block);
	dumper << config;
	configFile << dumper.c_str();
}

auto main(int argc, const char *argv[]) -> int {
	LoadConfig(argc > 2 && strcmp(argv[1], "--config") == 0
				   ? argv[2]
				   : "config.yaml");
	game = new GameProject(WINDOW_WIDTH, WINDOW_HEIGHT);
	spdlog::info("Preload done.");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window =
		glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
						 WINDOW_TITLE.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);

	spdlog::info("Window Creation done.");

	if (gladLoadGLLoader(reinterpret_cast<GLADloadproc>(
			glfwGetProcAddress)) == 0) {
		return -1;
	}

	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);

	// OpenGL configuration
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	spdlog::info("OpenGL config done.");

	// Initialize game
	game->Init();
	spdlog::info("Game init done.");

	// DeltaTime variables
	GLfloat deltaTime = 0.0F;
	GLfloat lastFrame = 0.0F;
	while (glfwWindowShouldClose(window) == 0) {
		// Calculate delta time
		GLfloat currentFrame = static_cast<GLfloat>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();

		// deltaTime = 0.001f;
		// Manage user input
		game->ProcessInput(deltaTime);
		// spdlog::debug("Input done.");

		// Update Game state
		game->Update(deltaTime);
		// spdlog::debug("Update done.");

		// Render
		glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
		glClear(GL_COLOR_BUFFER_BIT);
		game->Render();

		glfwSwapBuffers(window);
		// spdlog::debug("Render done.");
	}
	game->CleanUp();

	DumpConfig(argc > 2 && strcmp(argv[1], "--config") == 0
				   ? argv[2]
				   : "config.yaml");

	glfwTerminate();
	return 0;
}

void keyCallback(GLFWwindow *window, int key, int scancode,
				 int action, int mode) {
	// When a user presses the escape key, we set the
	// WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			reinterpret_cast<Adapter *>(game->GetAdapter())
				->SetKeyPress(key);
		}
		else if (action == GLFW_RELEASE) {
			reinterpret_cast<Adapter *>(game->GetAdapter())
				->SetKeyUnPress(key);
		}
	}
}
void mouseButtonCallback(GLFWwindow *window, int button, int action,
						 int mode) {
	double x;
	double y;
	glfwGetCursorPos(window, &x, &y);
	if (button >= 0 && button < 1024) {
		if (action == GLFW_PRESS) {
			reinterpret_cast<Adapter *>(game->GetAdapter())
				->SetMouseButtonPress(button, x, y);
		}
		else if (action == GLFW_RELEASE) {
			reinterpret_cast<Adapter *>(game->GetAdapter())
				->SetMouseButtonUnPress(button, x, y);
		}
	}
}

void framebufferSizeCallback(GLFWwindow *window, int width,
							 int height) {
	// make sure the viewport matches the new window dimensions; note
	// that width and height will be significantly larger than
	// specified on retina displays.
	glViewport(0, 0, width, height);
}
