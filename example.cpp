#include "imgui/imgui_stateful_canvas.h"

// declaration
ImGui::ImStatefulCanvas *imCanvas;
...
// start up
imCanvas = new ImGui::ImStatefulCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
...
// update
imCanvas->line(ImVec2(0, 0), ImVec2(20, 20), 0xFF00FFFF);
...
// redraw
bool open = true;
ImGui::Begin("Drawing", &open);
imCanvas->show("Canvas");
ImGui::End();
