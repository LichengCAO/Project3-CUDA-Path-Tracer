#pragma once

#include <string>
#include <vector>
#include <cuda_runtime.h>
#include "glm/glm.hpp"

#define BACKGROUND_COLOR (glm::vec3(0.0f))

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
};

struct Material {
    glm::vec3 color;
    struct {
        float exponent;
        glm::vec3 color;
    } specular;
    bool isScatterMedium;
    float hasReflective;
    float hasRefractive;
    float indexOfRefraction;
    float emittance;
    int textureId = -1;
    int bumpId = -1;
};

struct Camera {
    glm::ivec2 resolution;
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 view;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec2 fov;
    glm::vec2 pixelLength;
};

struct RenderState {
    Camera camera;
    unsigned int maxIterations;
    int traceDepth;
    std::vector<glm::vec3> image;
    std::string imageName;
};

struct PathSegment {
    Ray ray;
    glm::vec3 color;
    bool inScatterMedium = false;
    int pixelIndex;
    int remainingBounces;
};

// Use with a corresponding PathSegment to do:
// 1) color contribution computation
// 2) BSDF evaluation: generate a new ray
struct ShadeableIntersection {
  float t;
  int materialId;
  glm::vec3 surfaceNormal;
  glm::vec2 surfaceUV;
};

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv;
};

struct Triangle {
    Vertex v1;
    Vertex v2;
    Vertex v3;
    int meshId;
};

struct Mesh {
    int materialId;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transform;
    glm::mat4 inverseTransform;
    glm::mat4 invTranspose;
};