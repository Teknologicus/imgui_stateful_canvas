#ifndef IMGUI_STATEFUL_CANVAS_H
#define IMGUI_STATEFUL_CANVAS_H

#include "imgui.h"
#include <string>

namespace ImGui {
class ImStatefulCanvas {
  public:
    ImStatefulCanvas() = delete;
    ImStatefulCanvas(float width, float height);
    ImStatefulCanvas(float x, float y, float width, float height);
    ~ImStatefulCanvas() { clear(); }
    int line(const ImVec2 &p1, const ImVec2 &p2, ImU32 col, float thickness = 1.0f);
    int rect(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding = 0.0f,
             ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All, float thickness = 1.0f);
    int rectFilled(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding = 0.0f, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All);
    int rectFilledMultiColor(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left);
    int quad(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness = 1.0f);
    int quadFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col);
    int triangle(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col, float thickness = 1.0f);
    int triangleFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col);
    int circle(const ImVec2 &center, float radius, ImU32 col, int num_segments = 12, float thickness = 1.0f);
    int circleFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments = 12);
    int ngon(const ImVec2 &center, float radius, ImU32 col, int num_segments, float thickness = 1.0f);
    int ngonFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments);
    int text(const ImVec2 &pos, ImU32 col, const char *text_begin, const char *text_end = NULL);
    int text(const ImFont *font, float font_size, const ImVec2 &pos, ImU32 col,
             const char *text_begin, const char *text_end = NULL, float wrap_width = 0.0f, const ImVec4 *cpu_fine_clip_rect = NULL);
    int polyline(const ImVec2 *points, int num_points, ImU32 col, bool closed, float thickness = 1.0f);
    int convexPolyFilled(const ImVec2 *points, int num_points, ImU32 col); // Note: Anti-aliased filling requires points to be in clockwise order.
    int bezierCurve(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness = 1.0f, int num_segments = 0);
    int image(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0),
              const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = IM_COL32_WHITE);
    int imageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1 = ImVec2(0, 0),
                  const ImVec2& uv2 = ImVec2(1, 0), const ImVec2& uv3 = ImVec2(1, 1), const ImVec2& uv4 = ImVec2(0, 1), ImU32 col = IM_COL32_WHITE);
    int imageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col,
                     float rounding, ImDrawCornerFlags rounding_corners = ImDrawCornerFlags_All);
    void show(const char *label) const;
    void erase(int id);
    void clear();
    
  private:
    struct Primitive { virtual void show(ImDrawList *drawList, float x, float y) = 0; virtual ~Primitive() { } };
    struct Center { float center[2]; };
    struct Point { Point() { } Point(float x, float y) { p[0] = x; p[1] = y; } float p[2]; };
    struct Points2 { float p1[2], p2[2]; };
    struct Points3 { float p1[2], p2[2], p3[2]; };
    struct Points4 { float p1[2], p2[2], p3[2], p4[2]; };
    struct Points {
      Points(int size) { adjustedPoints = new ImVec2[size]; }
      virtual ~Points() { delete [] adjustedPoints; }
      ImVector<Point> points;
      ImVec2          *adjustedPoints;
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
    struct UV2 { float uv1[2], uv2[2]; };
    struct UV4 { float uv1[2], uv2[2], uv3[2], uv4[2]; };
    struct Line : Primitive, Points2, Color, Thickness { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Rect : Primitive, Points4, Color, Rounding, CornerFlags, Thickness { virtual void show(ImDrawList *drawList, float x, float y); };
    struct RectFilled : Primitive, Points4, Color, Rounding, CornerFlags { virtual void show(ImDrawList *drawList, float x, float y); };
    struct RectFilledMultiColor : Primitive, Points4, Color4 { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Quad : Primitive, Points4, Color, Thickness { virtual void show(ImDrawList *drawList, float x, float y); };
    struct QuadFilled : Primitive, Points4, Color { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Triangle : Primitive, Points3, Color, Thickness { virtual void show(ImDrawList *drawList, float x, float y); };
    struct TriangleFilled : Primitive, Points3, Color { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Circle : Primitive, Center, Radius, Color, Segments, Thickness { virtual void show(ImDrawList *drawList, float x, float y); };
    struct CircleFilled : Primitive, Center, Radius, Color, Segments { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Ngon : Primitive, Center, Radius, Color, Segments, Thickness { virtual void show(ImDrawList *drawList, float x, float y); };
    struct NgonFilled : Primitive, Center, Radius, Color, Segments { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Text : Primitive, Point, Color, String { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Text2 : Primitive, Point, Color, String {
      virtual void show(ImDrawList *drawList, float x, float y);
      const ImFont *font;
      float        fontSize;
      float        wrapWidth;
      const ImVec4 *cpuFineClipRect;
    };
    struct Polyline : Primitive, Points, Color, Thickness {
      Polyline(int size) : Points(size) { }
      virtual void show(ImDrawList *drawList, float x, float y);
      bool closed;
    };
    struct ConvexPolyFilled : Primitive, Points, Color {
      ConvexPolyFilled(int size) : Points(size) { }
      virtual void show(ImDrawList *drawList, float x, float y);
    };
    struct BezierCurve : Primitive, Points4, Color, Thickness, Segments { virtual void show(ImDrawList *drawList, float x, float y); };
    struct Image : Primitive, Texture, Points2, UV2, Color { virtual void show(ImDrawList *drawList, float x, float y); };
    struct ImageQuad : Primitive, Texture, Points4, UV4, Color { virtual void show(ImDrawList *drawList, float x, float y); };
    struct ImageRounded : Primitive, Texture, Points2, UV2, Color, Rounding, CornerFlags { virtual void show(ImDrawList *drawList, float x, float y); };
    typedef ImVector<Primitive *> DrawList;

  private:
    int addToDrawList(Primitive *primitive);
    static ImVec2 mkImVec2(const float p[2]) { return ImVec2(p[0], p[1]); }
    static ImVec2 mkAdjImVec2(const float p[2], float x, float y) { return ImVec2(p[0] + x, p[1] + y); }

  private:
    bool     useCursorPosition_;
    float    x_,
             y_,
             width_,
             height_;
    DrawList drawList_;
};
} // namespace ImGui

#endif