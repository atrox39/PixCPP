#pragma once
#include <string>
#include "ui/Canvas.hpp"

struct FileData {
  std::string path = "";
  bool dirty = false;
};

extern FileData gFile;

bool LoadImageToCanvas(const std::string &path, Canvas &canvas);
