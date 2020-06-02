//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2020 Jason Weiss
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifndef IMGUI_STATEFUL_CANVAS_H
#define IMGUI_STATEFUL_CANVAS_H

#include "imgui.h"
#include <string>

namespace ImGui {
class ImStatefulCanvas {
  public:
    typedef int DrawIdx;

  public:
    ImStatefulCanvas() = delete;
    ImStatefulCanvas(float width, float height);
    ImStatefulCanvas(float x, float y, float width, float height);
    ~ImStatefulCanvas() { clear(); }
    void setSize(float width, float height) { size_ = {width, height}; }
    void setLocation(float x, float y) { useCursorPosition_ = false; location_ = {x, y}; }
    void setZ(int z) { z_ = z; } // control draw order (low z draws first) for following primitive adds calls
    DrawIdx line(const ImVec2 &p1, const ImVec2 &p2, ImU32 col, float thickness = 1.0f);
    DrawIdx rect(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding = 0.0f,
                 ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All, float thickness = 1.0f);
    DrawIdx rectFilled(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding = 0.0f, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All);
    DrawIdx rectFilledMultiColor(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
    DrawIdx quad(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness = 1.0f);
    DrawIdx quadFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col);
    DrawIdx triangle(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col, float thickness = 1.0f);
    DrawIdx triangleFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col);
    DrawIdx circle(const ImVec2 &center, float radius, ImU32 col, int num_segments = 12, float thickness = 1.0f);
    DrawIdx circleFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments = 12);
    DrawIdx ngon(const ImVec2 &center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
    DrawIdx ngonFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments);
    DrawIdx text(const ImVec2 &pos, ImU32 col, const char *text_begin, const char *text_end = NULL);
    DrawIdx text(const ImFont *font, float font_size, const ImVec2 &pos, ImU32 col,
                 const char *text_begin, const char *text_end = NULL, float wrap_width = 0.0f, const ImVec4 *cpu_fine_clip_rect = NULL);
    DrawIdx polyline(const ImVec2 *points, int num_points, ImU32 col, bool closed, float thickness = 1.0f);
    DrawIdx convexPolyFilled(const ImVec2 *points, int num_points, ImU32 col); // Note: Anti-aliased filling requires points to be in clockwise order.
    DrawIdx bezierCurve(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness = 1.0f, int num_segments = 0);
    DrawIdx image(ImTextureID user_texture_id, const ImVec2 &p_min, const ImVec2 &p_max, const ImVec2 &uv_min = ImVec2(0, 0),
                  const ImVec2 &uv_max = ImVec2(1, 1), ImU32 col = IM_COL32_WHITE);
    DrawIdx imageQuad(ImTextureID user_texture_id, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, const ImVec2 &uv1 = ImVec2(0, 0),
                      const ImVec2 &uv2 = ImVec2(1, 0), const ImVec2 &uv3 = ImVec2(1, 1), const ImVec2 &uv4 = ImVec2(0, 1), ImU32 col = IM_COL32_WHITE);
    DrawIdx imageRounded(ImTextureID user_texture_id, const ImVec2 &p_min, const ImVec2 &p_max, const ImVec2 &uv_min, const ImVec2 &uv_max, ImU32 col,
                         float rounding, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All);
    void draw(const char *label) const;
    void erase(DrawIdx idx);
    void clear();
    
  private:
    struct Primitive { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) = 0; virtual ~Primitive() { } int z; };
    struct Center { ImVec2 center; };
    struct Point { ImVec2 p; };
    struct Points2 { ImVec2 p1, p2; };
    struct Points3 { ImVec2 p1, p2, p3; };
    struct Points4 { ImVec2 p1, p2, p3, p4; };
    struct Points {
      Points(int size) { adjustedPoints = new ImVec2[size]; }
      virtual ~Points() { delete [] adjustedPoints; }
      ImVector<ImVec2> points;
      ImVec2           *adjustedPoints;
    };
    struct Color { ImU32 color; };
    struct Color4 { ImU32 color1, color2, color3, color4; };
    struct Thickness { float thickness; };
    struct Rounding { float rounding; };
    struct Radius { float radius; };
    struct Segments { int segments; };
    struct String { std::string string; };
    struct CornerFlags { ImDrawCornerFlags cornerFlags; };
    struct Texture { ImTextureID textureId; };
    struct UV2 { ImVec2 uv1, uv2; };
    struct UV4 { ImVec2 uv1, uv2, uv3, uv4; };
    struct Line : Primitive, Points2, Color, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Rect : Primitive, Points4, Color, Rounding, CornerFlags, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct RectFilled : Primitive, Points4, Color, Rounding, CornerFlags { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct RectFilledMultiColor : Primitive, Points4, Color4 { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Quad : Primitive, Points4, Color, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct QuadFilled : Primitive, Points4, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Triangle : Primitive, Points3, Color, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct TriangleFilled : Primitive, Points3, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Circle : Primitive, Center, Radius, Color, Segments, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct CircleFilled : Primitive, Center, Radius, Color, Segments { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Ngon : Primitive, Center, Radius, Color, Segments, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct NgonFilled : Primitive, Center, Radius, Color, Segments { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Text : Primitive, Point, Color, String { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Text2 : Primitive, Point, Color, String {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc);
      const ImFont *font;
      float        fontSize;
      float        wrapWidth;
      const ImVec4 *cpuFineClipRect;
    };
    struct Polyline : Primitive, Points, Color, Thickness {
      Polyline(int size) : Points(size) { }
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc);
      bool closed;
    };
    struct ConvexPolyFilled : Primitive, Points, Color {
      ConvexPolyFilled(int size) : Points(size) { }
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc);
    };
    struct BezierCurve : Primitive, Points4, Color, Thickness, Segments { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct Image : Primitive, Texture, Points2, UV2, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct ImageQuad : Primitive, Texture, Points4, UV4, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    struct ImageRounded : Primitive, Texture, Points2, UV2, Color, Rounding, CornerFlags { virtual void draw(ImDrawList *drawList, const ImVec2 &loc); };
    typedef ImVector<Primitive *> DrawList;

  private:
    DrawIdx addToDrawList(Primitive *primitive);

  private:
    bool     useCursorPosition_;
    ImVec2   location_,
             size_;
    int      z_;
    DrawList drawList_;
};
} // namespace ImGui

#endif
