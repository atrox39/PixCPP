#pragma once
#include<string>
#include<unordered_map>
#include<SDL2/SDL_opengl.h>

class TextureManager {
public:
  static GLuint LoadIcon(const char* path);
  static void Destroy(GLuint tex);
  static void DestroyAll();
private:
  static inline std::unordered_map<std::string, GLuint> cache;
};
