#include "Canvas.hpp"

Canvas::Canvas(int w, int h) : width(w), height(h), pixels(w * h, 0x000000FF) {
}

void Canvas::resize(int w, int h) {
  width = w;
  height = h;
  pixels.resize(w * h, 0x000000FF);
}

void Canvas::clear(uint32_t color) {
  std::fill(pixels.begin(), pixels.end(), color);
}
