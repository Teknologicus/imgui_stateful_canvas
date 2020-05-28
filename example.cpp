#include "imgui/imgui_stateful_canvas.h"

// declaration
ImGui::ImStatefulCanvas *imCanvas;
float x0, y0, x1, y1;
int   id;
...
// start up
imCanvas = new ImGui::ImStatefulCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
x0 = 0; y0 = 0; x1 = 20; y1 = 20; id = -1;
...
// infrequent update
if (id != -1)
  imCanvas->erase(id);

id = imCanvas->line(ImVec2(x0, y0), ImVec2(x1, y1), 0xFF00FFFF);
...
// redraw
bool open = true;
ImGui::Begin("Drawing", &open);
imCanvas->show("Canvas");
ImGui::End();
