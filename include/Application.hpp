#include "Shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "Camera.hpp"
#include "Common.hpp"
#include "Mesh.hpp"
#include "BVH.h"
#include "DemonstrationRenderer.hpp"
class Application {
    GLFWwindow* Window;
    bool Running;
    double DeltaTime;
    Camera* camera;
    Shader* shader;
    Mesh mesh;
    DemonstrationRenderer* demonstrationRenderer;
    BVH* bvh;
    bool drawModel = true;
    bool bvhDirty = false;
    float rayOrigin[3] = {0, 0, 8};
    float rayDirection[3] = {0, 0, -1};
    int currentFile = 0;
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