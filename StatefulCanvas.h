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
#include <string>
#include <assert.h>

namespace ImGui {

class StatefulCanvas {
  public: // data types
    typedef int draw_idx_t;
    struct Primitive;

  public:
    StatefulCanvas() = delete;
    StatefulCanvas(float width, float height);
    StatefulCanvas(float x, float y, float width, float height);
    ~StatefulCanvas() { clear(); }
    void size(float width, float height) { assert((width > 0) && (height > 0)); size_ = {width, height}; }
    void location(float x, float y) { useCursorPosition_ = false; location_ = {x, y}; }
    void z(int z) { z_ = z; } // control draw order (low z draws first) for following primitive add calls
    bool visible(draw_idx_t idx) const;
    void visible(draw_idx_t idx, bool state);
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
    draw_idx_t convexPolyFilled(const ImVec2 *points, int nPoints, ImU32 color); // Note: Anti-aliased filling requires points to be in clockwise order.
    draw_idx_t bezierCurve(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 color, float thickness = 1.0f, int nSegments = 0);
    draw_idx_t image(ImTextureID textureId, const ImVec2 &min, const ImVec2 &max, const ImVec2 &uvMin = ImVec2(0, 0), const ImVec2 &uvMax = ImVec2(1, 1),
                     ImU32 color = IM_COL32_WHITE);
    draw_idx_t imageQuad(ImTextureID textureId, const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &uv0 = ImVec2(0, 0),
                         const ImVec2 &uv1 = ImVec2(1, 0), const ImVec2 &uv2 = ImVec2(1, 1), const ImVec2 &uv3 = ImVec2(0, 1), ImU32 color = IM_COL32_WHITE);
    draw_idx_t imageRounded(ImTextureID textureId, const ImVec2 &min, const ImVec2 &max, const ImVec2 &uvMin, const ImVec2 &uvMax, ImU32 color,
                            float rounding, ImDrawCornerFlags roundingCorners = ImDrawCornerFlags_All);
    void draw(const char *label) const;
    void erase(draw_idx_t idx);
    void clear();
    Primitive* item(draw_idx_t idx) { assert((idx >= 0) && (idx < drawList_.size())); return drawList_[idx]; } // low-level mutator

  public: // data types
    struct Primitive {
      // methods
      Primitive() {
        z       = 0;
        visible = true;
      }
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) = 0;
      virtual ~Primitive() { }

      // data members
      int  z;
      bool visible;
    };
    struct Center { ImVec2 center; };
    struct Point { ImVec2 p; };
    struct Points2 { ImVec2 p0, p1; };
    struct Points3 { ImVec2 p0, p1, p2; };
    struct Points4 { ImVec2 p0, p1, p2, p3; };
    struct Points {
      // methods
      Points(int size) { adjustedPoints = new ImVec2[size]; }
      virtual ~Points() { delete [] adjustedPoints; }

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
    struct Line : Primitive, Points2, Color, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Rect : Primitive, Points2, Color, Rounding, CornerFlags, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct RectFilled : Primitive, Points2, Color, Rounding, CornerFlags { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct RectFilledMultiColor : Primitive, Points2, Color4 { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Quad : Primitive, Points4, Color, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct QuadFilled : Primitive, Points4, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Triangle : Primitive, Points3, Color, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct TriangleFilled : Primitive, Points3, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Circle : Primitive, Center, Radius, Color, Segments, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct CircleFilled : Primitive, Center, Radius, Color, Segments { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Ngon : Primitive, Center, Radius, Color, Segments, Thickness { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct NgonFilled : Primitive, Center, Radius, Color, Segments { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Text : Primitive, Point, Color, String { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Text2 : Primitive, Point, Color, String {
      // methods
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;

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

      // data members
      bool closed;
    };
    struct ConvexPolyFilled : Primitive, Points, Color {
      ConvexPolyFilled(int size) : Points(size) { }
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
    };
    struct BezierCurve : Primitive, Points4, Color, Thickness, Segments { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct Image : Primitive, Texture, Points2, UVs2, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct ImageQuad : Primitive, Texture, Points4, UVs4, Color { virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override; };
    struct ImageRounded : Primitive, Texture, Points2, UVs2, Color, Rounding, CornerFlags {
      virtual void draw(ImDrawList *drawList, const ImVec2 &loc) override;
    };

  private: // data types
    typedef ImVector<Primitive *> DrawList;

  private: // methods
    draw_idx_t addToDrawList(Primitive *primitive);

  private: // data members
    bool     useCursorPosition_;
    ImVec2   location_,
             size_;
    int      z_;
    DrawList drawList_;
};

} // namespace ImGui

#endif // STATEFUL_CANVAS_H
