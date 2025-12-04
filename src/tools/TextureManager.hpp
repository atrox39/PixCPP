#pragma once
#include<iostream>
#include<string>
#include<unordered_map>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_opengl.h>

class TextureManager {
public:
  static GLuint Load(const std::string &path);
  static void Destroy(GLuint tex);
  static void DestroyAll();
private:
  static std::unordered_map<std::string, GLuint> cache;
  static GLuint LoadRaw(const std::string &path);
};
