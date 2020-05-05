#include <chrono>

#define GLFW_INCLUDE_VULKAN
#include <Libraries/GLFW/glfw3.h>

#include "Logger.hpp"

#include "GulgEngine/GulgEngine.hpp"
#include "Vulkan/VulkanDevice.hpp"
#include "Systems/RenderSystem.hpp"

GLFWwindow* initGLFW(const uint32_t width, const uint32_t height) {
    
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, "Gulg Engine v0.1", NULL, NULL);

    if(window == nullptr){

        const char* errorMessage;
        int code = glfwGetError(&errorMessage);
        Logger::write("GLFW error: " + std::to_string(code) + '\n' + errorMessage + '\n' + "GulgEngine can't create a window, glfw error.", LogType::Error);
        return nullptr;
    }

    return window;
}

void quitProgram(GLFWwindow* window) {

    glfwDestroyWindow(window);
    glfwTerminate();
    Logger::closeFile();
}

int main() {

    const uint32_t windowWidth{800}, windowHeight{800};
    if(!Logger::openFile("log.txt")) { std::cout << "WARNING: can't use Logger !" << std::endl; }
    Logger::setMaxCharacters(100);

    GLFWwindow* window{initGLFW(windowWidth, windowHeight)};

    Gg::GulgEngine engine;

    std::shared_ptr<Device> device;

    try { device = createVulkanDevice(window, windowWidth, windowHeight); }

    catch(const std::exception &e) {

        Logger::write(e.what(), LogType::Error);
        quitProgram(window);
        return -1;
    }


    Mesh mesh;

    try { mesh = loadFromFile("Datas/Mesh/TestMesh"); }

    catch(const std::exception &e) {

        device->clean();
        Logger::write(e.what(), LogType::Error);
        quitProgram(window);
        return -1;
    }


    std::shared_ptr<Gg::Component::MeshRenderer> renderer;

    try {  

        renderer = std::make_shared<Gg::Component::MeshRenderer>(device);
        renderer->loadFromMesh(mesh);
    }

    catch(const std::exception &e) {

        device->clean();
        Logger::write(e.what(), LogType::Error);
        quitProgram(window);
        return -1;
    }
   
    

    Gg::Systems::RenderSystem renderSystem{engine, device};

    Gg::Entity meshEntity = engine.getNewEntity();
    engine.addComponentToEntity(meshEntity, Gg::ComponentType::MainMeshRenderer, renderer);
    renderSystem.addEntity(meshEntity);


    // Main loop

    bool haveToStop{false};
    if(window == nullptr) { haveToStop = true; }

    std::chrono::time_point<std::chrono::system_clock> oldTime { std::chrono::system_clock::now() };

    uint32_t elapsedTime{0};
    const uint32_t nbImagePerSecond{60};
    const uint32_t timePerFrame{1'000'000/nbImagePerSecond};

   
    while (!haveToStop) {

        // Input
        glfwPollEvents();
        if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { haveToStop = true; }

        elapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now()-oldTime).count();
        oldTime = std::chrono::system_clock::now();

        if(elapsedTime >= timePerFrame) {

            elapsedTime -= timePerFrame;

            //Update



            //Draw

            renderSystem.apply();
        }
    }

    vkDeviceWaitIdle(device->logicalDevice);

    renderer->clean();
    device->clean();
    quitProgram(window);

    return 0;
}