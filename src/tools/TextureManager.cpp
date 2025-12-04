#include "TextureManager.hpp"

std::unordered_map<std::string, GLuint> TextureManager::cache;

GLuint TextureManager::Load(const std::string& path) {
  auto it = cache.find(path);
  if (it != cache.end()) {
    return it->second;
  }
  GLuint tex = LoadRaw(path.c_str());
  if (tex != 0) {
    cache[path] = tex;
  }
  return tex;
}

GLuint TextureManager::LoadRaw(const std::string &path) {
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (!surface) {
    std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    return 0;
  }
  SDL_Surface *conv = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_ABGR8888, 0);
  SDL_FreeSurface(surface);
  surface = conv;

  GLuint tex = 0;
  glGenTextures(1, &tex);
  glBindTexture(GL_TEXTURE_2D, tex);
  
  glTexImage2D(
    GL_TEXTURE_2D,
    0,
    GL_RGBA,
    surface->w,
    surface->h,
    0,
    GL_RGBA,
    GL_UNSIGNED_BYTE,
    surface->pixels
  );

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  SDL_FreeSurface(surface);
  return tex;
}

void TextureManager::Destroy(GLuint tex) {
  if (tex != 0) {
    glDeleteTextures(1, &tex);
  }
}

void TextureManager::DestroyAll() {
  for (const auto& pair : cache) {
    glDeleteTextures(1, &pair.second);
  }
  cache.clear();
}
