#include <iostream>
#include "Application.hpp"
#include <vector>
#include <chrono>
#include <bitset>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"
#include <sstream>

Application* Application::instance = nullptr;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    Application::instance->GetCamera()->HandleMouseMovement(xposIn, yposIn);
}

void window_resize_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    Application::instance->GetCamera()->ResizeViewport(width, height);
}

Application::Application(const char* title)
{
    if (!glfwInit()) throw -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(1920, 1080, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw -1;
    }

    this->Window = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(this->Window, true);
    
    glfwMakeContextCurrent(window);
    ImGui_ImplOpenGL3_Init();

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetWindowSizeCallback(window, window_resize_callback);
    gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        throw -1;
    }

    glClearColor(0.2f, 0.2f, 0.215f, 1.0f);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);

    glfwSwapInterval(1);
    Application::instance = this;

    this->shader = new Shader("res/shader.frag", "res/shader.vert");
    this->camera = new Camera(70, 0.1f, 1000.0f);
    this->DeltaTime = 1.0/60.0;
}

void Application::Start()
{
    
    while (!glfwWindowShouldClose(this->Window) && this->Running)
    {
        auto t_start = std::chrono::high_resolution_clock::now();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::SetNextWindowPos({0, 0});
        ImGui::Begin("DEBUG", 0, ImGuiWindowFlags_AlwaysAutoResize);
        {
            std::stringstream ss;
            ss << (int)(this->DeltaTime * 1000);
            ss << " ms";
            
            glm::vec3 dir = this->camera->GetLookVector();
            glm::vec3 pos = this->camera->GetPosition();
            ImGui::Text(ss.str().c_str());

            std::stringstream lookDir;
            lookDir << "Look Direction: " << dir.x << ", " << dir.y << ", " << dir.z;
            ImGui::Text(lookDir.str().c_str());

            std::stringstream posStream;
            posStream << "Position: " << pos.x << ", " << pos.y << ", " << pos.z;
            ImGui::Text(posStream.str().c_str());

            ImGui::End();
        }

       
        this->Update();
        this->Render();

        auto t_end = std::chrono::high_resolution_clock::now();
        this->DeltaTime = std::chrono::duration<double, std::milli>(t_end-t_start).count() / 1000.0;


    }
}


void Application::Update()
{
    if (glfwGetKey(this->Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        this->Running = false;
    }

    this->camera->HandleInput();
    this->shader->UniformViewProjection(this->camera->GetViewProjection());

    if (glfwGetKey(this->Window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    {
        glfwSetInputMode(this->Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } else {
        glfwSetInputMode(this->Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}



void Application::Render()
{


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    this->shader->Use();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(this->Window);
    glfwPollEvents();
}

Application::~Application()
{
    delete this->camera;
    delete this->shader;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

double Application::GetDeltaTime() { return this->DeltaTime; }
GLFWwindow* Application::GetWindow() { return this->Window; }
Camera* Application::GetCamera() { return this->camera; }