#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Camera.hpp"
#include "Common.hpp"
#include "Mesh.hpp"
#include "BVH.h"
class Application {
    GLFWwindow* Window;
    bool Running;
    double DeltaTime;
    Camera* camera;
    Shader* shader;
    Mesh mesh;
    BVH* bvh;
public:
    static Application* instance;
    Application(const char* title);
    ~Application();
    void Start();
    void Update();
    void Render();
    double GetDeltaTime();
    Camera* GetCamera();
    GLFWwindow* GetWindow();
};