//--------------------------------------------------------------------------------------------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2020 Jason Paul Weiss
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

#ifndef STATEFUL_CANVAS_H
#define STATEFUL_CANVAS_H

#include "imgui/imgui.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui/imgui_internal.h"
#include <string>
#include <type_traits>
#include <assert.h>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace ImGui {

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
class StatefulCanvas {
  public: // data types
    enum { DRAW_IDX_NONE = -1 };
    typedef int draw_idx_t;
    struct Primitive;

  public:
    StatefulCanvas() = delete;
    StatefulCanvas(float width, float height);
    StatefulCanvas(float x, float y, float width, float height);
    ~StatefulCanvas() { clear(); }
    void canvasSize(float width, float height) { assert((width > 0) && (height > 0)); size_ = {width, height}; }
    void canvasLocation(float x, float y) { useCursorPosition_ = false; location_ = {x, y}; }
    void pushZ(int z) { zStack_.push_back(z); } // push/pop draw order (low z draws first) for following primitive add calls
    void popZ() { assert(zStack_.size() > 0); zStack_.pop_back(); }
    void pushClipRect(const ImVec2 &min, const ImVec2 &max); // push/pop a clip rect for following primitive add calls
    void popClipRect();
    draw_idx_t line(const ImVec2 &p0, const ImVec2 &p1, ImU32 color, float thickness = 1.0f);
    draw_idx_t rect(const ImVec2 &min, const ImVec2 &max, ImU32 color, float rounding = 0.0f,
                    ImDrawCornerFlags roundingCorners = ImDrawCornerFlags_All, float thickness = 1.0f);
    draw_idx_t rectFilled(const ImVec2 &min, const ImVec2 &max, ImU32 color, float rounding = 0.0f, ImDrawCornerFlags roundingCorners = ImDrawCornerFlags_All);
    draw_idx_t rectFilledMultiColor(const ImVec2 &min, const ImVec2 &max, ImU32 colorUpperLeft, ImU32 colorUpperRight, ImU32 colorBottomRight,
                                    ImU32 colorBottomLeft);
    draw_idx_t quad(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 color, float thickness = 1.0f);
    draw_idx_t quadFilled(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 color);
    draw_idx_t triangle(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, ImU32 color, float thickness = 1.0f);
    draw_idx_t triangleFilled(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, ImU32 color);
    draw_idx_t circle(const ImVec2 &center, float radius, ImU32 color, int nSegments = 12, float thickness = 1.0f);
    draw_idx_t circleFilled(const ImVec2 &center, float radius, ImU32 color, int nSegments = 12);
    draw_idx_t ngon(const ImVec2 &center, float radius, ImU32 color, int nSegments, float thickness = 1.0f);
    draw_idx_t ngonFilled(const ImVec2 &center, float radius, ImU32 color, int nSegments);
    draw_idx_t text(const ImVec2 &pos, ImU32 color, const char *textBegin, const char *textEnd = nullptr);
    draw_idx_t text(const ImFont *font, float fontSize, const ImVec2 &pos, ImU32 color,
                    const char *textBegin, const char *textEnd = nullptr, float wrapWidth = 0.0f, const ImVec4 *cpuFineClipRect = nullptr);
    draw_idx_t polyline(const ImVec2 *points, int nPoints, ImU32 color, bool closed, float thickness = 1.0f);
    draw_idx_t convexPolyFilled(const ImVec2 *points, int nPoints, ImU32 color);
    draw_idx_t bezierCurve(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 color, float thickness = 1.0f, int nSegments = 0);
    draw_idx_t image(ImTextureID textureId, const ImVec2 &min, const ImVec2 &max, const ImVec2 &uvMin = ImVec2(0, 0), const ImVec2 &uvMax = ImVec2(1, 1),
                     ImU32 color = IM_COL32_WHITE);
    draw_idx_t imageQuad(ImTextureID textureId, const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &uv0 = ImVec2(0, 0),
                         const ImVec2 &uv1 = ImVec2(1, 0), const ImVec2 &uv2 = ImVec2(1, 1), const ImVec2 &uv3 = ImVec2(0, 1), ImU32 color = IM_COL32_WHITE);
    draw_idx_t imageRounded(ImTextureID textureId, const ImVec2 &min, const ImVec2 &max, const ImVec2 &uvMin, const ImVec2 &uvMax, ImU32 color,
                            float rounding, ImDrawCornerFlags roundingCorners = ImDrawCornerFlags_All);
    draw_idx_t custom(Primitive *c); // add custom object to draw list
    bool visible(draw_idx_t idx) const;
    void visible(draw_idx_t idx, bool state);
    void draw(const char *label, bool clip = true) const;
    void erase(draw_idx_t idx);
    void clear();
    template<typename T>
    T* item(draw_idx_t idx); // low-level mutator

  public: // data types
    struct Primitive {
      // methods
      Primitive() {
        z       = 0;
        offsetX = 0;
        offsetY = 0;
        offsetZ = 0;
        visible = true;
        clip    = false;
      }
      virtual ~Primitive() { }
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) = 0;
      virtual void moveTo(float x, float y) = 0;
      void dragAndDropStart(int z) { offsetZ = z; }
      void dragAndDropUpdate(float x, float y) { offsetX = x; offsetY = y; }
      void dragAndDropEnd() { offsetX = 0; offsetY = 0; offsetZ = 0; }
      void dragAndDropEnd(float x, float y) { offsetX = 0; offsetY = 0; offsetZ = 0; moveTo(x, y); }
      void offset(const ImVec2 &loc, ImVec2 *offset) const { *offset = loc; offset->x += offsetX; offset->y += offsetY; }

      // data members
      int    z,
             offsetZ; // offsets for client drag and drop functionality
      float  offsetX, offsetY;
      bool   visible,
             clip;
      ImVec4 clipRect;
    };
    struct Center {
      void move(float x, float y) { center += ImVec2(x, y); }
      ImVec2 center;
    };
    struct Point {
      void move(float x, float y) { p += ImVec2(x, y); }
      ImVec2 p;
    };
    struct Points2 {
      void move(float x, float y) { ImVec2 m(x, y); p0 += m; p1 += m; }
      ImVec2 p0, p1;
    };
    struct Points3 {
      void move(float x, float y) { ImVec2 m(x, y); p0 += m; p1 += m; p2 += m; }
      ImVec2 p0, p1, p2;
    };
    struct Points4 {
      void move(float x, float y) { ImVec2 m(x, y); p0 += m; p1 += m; p2 += m; p3 += m; }
      ImVec2 p0, p1, p2, p3;
    };
    struct Points {
      // methods
      Points(int size) { adjustedPoints = new ImVec2[size]; }
      virtual ~Points() { delete [] adjustedPoints; }
      void move(float x, float y);

      // data members
      ImVector<ImVec2> points;
      ImVec2           *adjustedPoints;
    };
    struct Color { ImU32 color; };
    struct Color4 { ImU32 color0, color1, color2, color3; };
    struct Thickness { float thickness; };
    struct Rounding { float rounding; };
    struct Radius { float radius; };
    struct Segments { int segments; };
    struct String { std::string string; };
    struct CornerFlags { ImDrawCornerFlags cornerFlags; };
    struct Texture { ImTextureID textureId; };
    struct UVs2 { ImVec2 uv0, uv1; };
    struct UVs4 { ImVec2 uv0, uv1, uv2, uv3; };
    struct Line : Primitive, Points2, Color, Thickness {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Rect : Primitive, Points2, Color, Rounding, CornerFlags, Thickness {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct RectFilled : Primitive, Points2, Color, Rounding, CornerFlags {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct RectFilledMultiColor : Primitive, Points2, Color4 {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Quad : Primitive, Points4, Color, Thickness {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct QuadFilled : Primitive, Points4, Color {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Triangle : Primitive, Points3, Color, Thickness {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct TriangleFilled : Primitive, Points3, Color {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Circle : Primitive, Center, Radius, Color, Segments, Thickness {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct CircleFilled : Primitive, Center, Radius, Color, Segments {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Ngon : Primitive, Center, Radius, Color, Segments, Thickness {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct NgonFilled : Primitive, Center, Radius, Color, Segments {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Text : Primitive, Point, Color, String {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Text2 : Primitive, Point, Color, String {
      // methods
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }

      // data members
      const ImFont *font;
      float        fontSize;
      float        wrapWidth;
      const ImVec4 *cpuFineClipRect;
    };
    struct Polyline : Primitive, Points, Color, Thickness {
      // methods
      Polyline(int size) : Points(size) { }
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }

      // data members
      bool closed;
    };
    struct ConvexPolyFilled : Primitive, Points, Color {
      ConvexPolyFilled(int size) : Points(size) { }
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct BezierCurve : Primitive, Points4, Color, Thickness, Segments {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct Image : Primitive, Texture, Points2, UVs2, Color {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct ImageQuad : Primitive, Texture, Points4, UVs4, Color {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };
    struct ImageRounded : Primitive, Texture, Points2, UVs2, Color, Rounding, CornerFlags {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
      virtual void moveTo(float x, float y) override { move(x, y); }
    };

  private: // data types
    typedef ImVector<Primitive *> DrawList;
    typedef ImVector<int>         ZStack;
    typedef ImVector<ImVec4>      ClipRectStack;

  private: // methods
    draw_idx_t addToDrawList(Primitive *primitive);
    int z() const { return zStack_.size() > 0 ? zStack_.back() : 0; }
    void addClipRect(Primitive *primitive) const;

  private: // data members
    bool          useCursorPosition_;
    ImVec2        location_,
                  size_;
    ZStack        zStack_;
    ClipRectStack clipRectStack_;
    DrawList      drawList_;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
template<typename T>
T* StatefulCanvas::item(draw_idx_t idx) {
  static_assert(std::is_base_of<StatefulCanvas::Primitive, T>::value);
  assert((idx >= 0) && (idx < drawList_.size()));
  return (T*)drawList_[idx];
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
} // namespace ImGui

#endif // STATEFUL_CANVAS_H
