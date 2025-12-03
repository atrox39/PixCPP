#pragma once
#include<cstdint>
#include<vector>

class Canvas {
public:
  Canvas(int w = 32, int h = 32);
  void resize(int width, int height);
  void clear(uint32_t color = 0x000000FF);
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  const std::vector<uint32_t> &getPixels() const { return pixels; }
  std::vector<uint32_t> &setPixels() { return pixels; }
private:
  int width;
  int height;
  std::vector<uint32_t> pixels;
};
