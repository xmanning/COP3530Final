# Problem

Cast a ray through a large 3D model and detect the hit point efficiently without iterating every triangle in the model.

# Solution

Use a BVH to divide the model and reduce the amount of triangles needed to check.

| Requirement              | Fulfilled by                          |
| ------------------------ | ------------------------------------- |
| Algorithm/Data Structure | Bounding Volume Hierarchy             |
| Algorithm/Data Structure | Ray-Triangle and Ray-Box intersection |
| 100,000 Datapoints       | Model with 100k+ Triangles            |
# Stack
We use GLFW & GLAD for rendering, IMGUI for UI, and GLM for basic math features such as `vec3`.

Project is built via CMake.

A prebuilt binary is provided as a release if building doesn't work for whatever reason.
