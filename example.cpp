// NOTE: This is an outdated example which needs to be updated -- should still be useful for getting you started if you look at StatefulCanvas.h
#include "imgui/imgui_stateful_canvas.h"

// declaration
ImGui::ImStatefulCanvas *imCanvas;
float x0, y0, x1, y1;
ImGui::ImStatefulCanvas::DrawIdx lines[2];
...
// start up
imCanvas = new ImGui::ImStatefulCanvas(WINDOW_WIDTH, WINDOW_HEIGHT);
x0 = 0; y0 = 0; x1 = 20; y1 = 20; lines[0] = -1; lines[1] = -1;
...
// infrequent update
if (lines[0] != -1) {
  imCanvas->erase(lines[0]);
  imCanvas->erase(lines[1]);
  // or call imCanvas->clear() if you want to erase all primitives from canvas
}

imCanvas->setZ(1); // draw second
lines[0] = imCanvas->line(ImVec2(x0, y0), ImVec2(x1, y1), 0xFF00FFFF);
imCanvas->setZ(0); // draw first
lines[1] = imCanvas->line(ImVec2(x1, y0), ImVec2(x0, y1), 0xFFFF00FF);
...
// redraw
bool open = true;
ImGui::Begin("Drawing", &open);
imCanvas->draw("Canvas");
ImGui::End();
