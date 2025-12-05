#include "App.hpp"
#include "core/MenuBar.hpp"
#include "core/Windows.hpp"
#include "ui/CanvasWindow.hpp"
#include "tools/TextureManager.hpp"

#include<imgui.h>
#include<backends/imgui_impl_sdl2.h>
#include<backends/imgui_impl_opengl3.h>

#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>
#include<SDL2/SDL_image.h>

#include<stdio.h>

GLuint textBrush = 0;
GLuint textEraser = 0;
GLuint textEyedropper = 0;
GLuint textLine = 0;

App::App() {}

App::~App() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  TextureManager::DestroyAll();

  if (gl_context) {
    SDL_GL_DeleteContext(gl_context);
    gl_context = nullptr;
  }
  if (window) {
    SDL_DestroyWindow(window);
    window = nullptr;
  }
  SDL_Quit();
}

void App::AllocateConsole() {
  #ifdef _WIN32
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
  #endif
}

bool App::init() {
  #ifdef Debug
    AllocateConsole();
  #endif
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
    printf("Error: %s\n", SDL_GetError());
    return false;
  }
  
  if (window) {
    #ifndef _WIN32
      SDL_Surface* icon = nullptr;
      icon = IMG_Load("assets/PixC++.png");
      if (icon) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
      } else {
        printf("Failed to load icon image: %s\n", SDL_GetError());
      }
    #endif
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  window = SDL_CreateWindow(
    "PixC++",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    1280,
    720,
    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
  );

  gl_context = SDL_GL_CreateContext(window);
  SDL_GL_MakeCurrent(window, gl_context);
  SDL_GL_SetSwapInterval(1);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
  io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

  ImGui::StyleColorsDark();

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    style.WindowRounding = 3.0f;
    style.Colors[ImGuiCol_WindowBg].w = 1.0f;
  }

  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init("#version 330");

  // Load tool icons
  textBrush = TextureManager::Load("assets/icons/brush.png");
  textEraser = TextureManager::Load("assets/icons/eraser.png");
  textEyedropper = TextureManager::Load("assets/icons/eyedropper.png");
  textLine = TextureManager::Load("assets/icons/line.png");

  return true;
}

void App::run() {
  while (running) {
    processEvent();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    {
      ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
      const ImGuiViewport *viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->WorkPos);
      ImGui::SetNextWindowSize(viewport->WorkSize);
      ImGui::SetNextWindowViewport(viewport->ID);
      window_flags |= ImGuiWindowFlags_NoTitleBar | 
        ImGuiWindowFlags_NoCollapse | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoMove;
      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

      ImGui::Begin("PixC++", nullptr, window_flags);
      ImGui::PopStyleVar(3);

      ImGuiID dockspace_id = ImGui::GetID("PixC++DockSpace");
      ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
      ImGui::End();
    }

    DrawCanvasWindow(canvas, toolState);

    DrawMenuBar(canvas);
    DrawToolsWindow(toolState);

    render();
  }
}

void App::processEvent() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    ImGui_ImplSDL2_ProcessEvent(&event);
    if (event.type == SDL_QUIT) {
      running = false;
    }
  }
}

void App::render() {
  ImGui::Render();
  glViewport(0, 0, (int) ImGui::GetIO().DisplaySize.x, (int) ImGui::GetIO().DisplaySize.y);
  glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  ImGuiIO &io = ImGui::GetIO();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
  }

  SDL_GL_SwapWindow(window);
}
