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

#include "imgui_stateful_canvas.h"
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"

namespace ImGui {
//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::ImStatefulCanvas(float width, float height) {
  useCursorPosition_ = true;
  location_          = {0, 0};
  size_              = {width, height};
  z_                 = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::ImStatefulCanvas(float x, float y, float width, float height) {
  useCursorPosition_ = false;
  location_          = {x, y};
  size_              = {width, height};
  z_                 = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::line(const ImVec2 &p1, const ImVec2 &p2, ImU32 col, float thickness) {
  Line *line = new Line;
  line->z         = z_;
  line->p1        = p1;
  line->p2        = p2;
  line->color     = col;
  line->thickness = thickness;
  return addToDrawList(line);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::rect(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding, ImDrawCornerFlags rounding_corners,
                                                 float thickness) {
  Rect *rect = new Rect;
  rect->z           = z_;
  rect->p1          = p_min;
  rect->p2          = p_max;
  rect->color       = col;
  rect->rounding    = rounding;
  rect->cornerFlags = rounding_corners;
  rect->thickness   = thickness;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::rectFilled(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding, 
                                                       ImDrawCornerFlags rounding_corners) {
  RectFilled *rect = new RectFilled;
  rect->z           = z_;
  rect->p1          = p_min;
  rect->p2          = p_max;
  rect->color       = col;
  rect->rounding    = rounding;
  rect->cornerFlags = rounding_corners;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::rectFilledMultiColor(const ImVec2 &p_min, const ImVec2 &p_max,
                                                                 ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left) {
  RectFilledMultiColor *rect = new RectFilledMultiColor;
  rect->z      = z_;
  rect->p1     = p_min;
  rect->p2     = p_max;
  rect->color1 = col_upr_left;
  rect->color2 = col_upr_right;
  rect->color3 = col_bot_right;
  rect->color4 = col_bot_left;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::quad(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness) {
  Quad *quad = new Quad;
  quad->z         = z_;
  quad->p1        = p1;
  quad->p2        = p2;
  quad->p3        = p3;
  quad->p4        = p4;
  quad->color     = col;
  quad->thickness = thickness;
  return addToDrawList(quad);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::quadFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col) {
  QuadFilled *quad = new QuadFilled;
  quad->z     = z_;
  quad->p1    = p1;
  quad->p2    = p2;
  quad->p3    = p3;
  quad->p4    = p4;
  quad->color = col;
  return addToDrawList(quad);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::triangle(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col, float thickness) {
  Triangle *tri = new Triangle;
  tri->z         = z_;
  tri->p1        = p1;
  tri->p2        = p2;
  tri->p3        = p3;
  tri->color     = col;
  tri->thickness = thickness;
  return addToDrawList(tri);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::triangleFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col) {
  TriangleFilled *tri = new TriangleFilled;
  tri->z     = z_;
  tri->p1    = p1;
  tri->p2    = p2;
  tri->p3    = p3;
  tri->color = col;
  return addToDrawList(tri);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::circle(const ImVec2 &center, float radius, ImU32 col, int num_segments, float thickness) {
  Circle *circle = new Circle;
  circle->z         = z_;
  circle->center    = center;
  circle->radius    = radius;
  circle->color     = col;
  circle->segments  = num_segments;
  circle->thickness = thickness;
  return addToDrawList(circle);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::circleFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments) {
  CircleFilled *circle = new CircleFilled;
  circle->z        = z_;
  circle->center   = center;
  circle->radius   = radius;
  circle->color    = col;
  circle->segments = num_segments;
  return addToDrawList(circle);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::ngon(const ImVec2 &center, float radius, ImU32 col, int num_segments, float thickness) {
  Ngon *ngon = new Ngon;
  ngon->z         = z_;
  ngon->center    = center;
  ngon->radius    = radius;
  ngon->color     = col;
  ngon->segments  = num_segments;
  ngon->thickness = thickness;
  return addToDrawList(ngon);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::ngonFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments) {
  NgonFilled *ngon = new NgonFilled;
  ngon->z        = z_;
  ngon->center   = center;
  ngon->radius   = radius;
  ngon->color    = col;
  ngon->segments = num_segments;
  return addToDrawList(ngon);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::text(const ImVec2 &pos, ImU32 col, const char *text_begin, const char *text_end) {
  Text *text = new Text;
  text->z      = z_;
  text->p      = pos;
  text->color  = col;
  text->string = text_end ? std::string(text_begin, text_end - text_begin) : std::string(text_begin);
  return addToDrawList(text);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::text(const ImFont *font, float font_size, const ImVec2 &pos, ImU32 col,
                                                 const char *text_begin, const char *text_end, float wrap_width, const ImVec4 *cpu_fine_clip_rect) {
  Text2 *text = new Text2;
  text->z               = z_;
  text->p               = pos;
  text->color           = col;
  text->string          = text_end ? std::string(text_begin, text_end - text_begin) : std::string(text_begin);
  text->font            = font;
  text->fontSize        = font_size;
  text->wrapWidth       = wrap_width;
  text->cpuFineClipRect = cpu_fine_clip_rect;
  return addToDrawList(text);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::polyline(const ImVec2 *points, int num_points, ImU32 col, bool closed, float thickness) {
  Polyline *poly = new Polyline(num_points);
  poly->z         = z_;
  poly->color     = col;
  poly->thickness = thickness;
  poly->closed    = closed;

  for (int i = 0; i < num_points; ++i)
    poly->points.push_back(points[i]);

  return addToDrawList(poly);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::convexPolyFilled(const ImVec2 *points, int num_points, ImU32 col) {
  ConvexPolyFilled *poly = new ConvexPolyFilled(num_points);
  poly->z     = z_;
  poly->color = col;

  for (int i = 0; i < num_points; ++i)
    poly->points.push_back(points[i]);

  return addToDrawList(poly);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::bezierCurve(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness,
                                                        int num_segments) {
  BezierCurve *bezier = new BezierCurve;
  bezier->z     = z_;
  bezier->p1    = p1;
  bezier->p2    = p2;
  bezier->p3    = p3;
  bezier->p4    = p4;
  bezier->color = col;
  bezier->thickness = thickness;
  bezier->segments = num_segments;
  return addToDrawList(bezier);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::image(ImTextureID user_texture_id, const ImVec2 &p_min, const ImVec2 &p_max, const ImVec2 &uv_min,
                                                  const ImVec2 &uv_max, ImU32 col) {
  Image *image = new Image;
  image->z         = z_;
  image->textureId = user_texture_id;
  image->p1        = p_min;
  image->p2        = p_max;
  image->uv1       = uv_min;
  image->uv2       = uv_max;
  image->color     = col;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::imageQuad(ImTextureID user_texture_id, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4,
                                                      const ImVec2 &uv1, const ImVec2 &uv2, const ImVec2 &uv3, const ImVec2 &uv4, ImU32 col) {
  ImageQuad *image = new ImageQuad;
  image->z         = z_;
  image->textureId = user_texture_id;
  image->p1        = p1;
  image->p2        = p2;
  image->p3        = p3;
  image->p4        = p4;
  image->uv1       = uv1;
  image->uv2       = uv2;
  image->uv3       = uv3;
  image->uv4       = uv4;
  image->color     = col;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::imageRounded(ImTextureID user_texture_id, const ImVec2 &p_min, const ImVec2 &p_max,
                                                         const ImVec2 &uv_min, const ImVec2 &uv_max, ImU32 col, float rounding,
                                                         ImDrawCornerFlags rounding_corners) {
  ImageRounded *image = new ImageRounded;
  image->z           = z_;
  image->textureId   = user_texture_id;
  image->p1          = p_min;
  image->p2          = p_max;
  image->uv1         = uv_min;
  image->uv2         = uv_max;
  image->color       = col;
  image->rounding    = rounding;
  image->cornerFlags = rounding_corners;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::draw(const char *label) const {
  if (drawList_.Size == 0)
    return;

  ImGuiWindow *window = ImGui::GetCurrentWindow();

  if (window->SkipItems)
    return;

  ImVec2 loc;
  
  if (useCursorPosition_)
    loc = window->DC.CursorPos;
  else
    loc = location_;

  ImDrawList *drawList = ImGui::GetWindowDrawList();
  drawList->PushClipRect(loc, loc + size_);

  int zMin = INT_MAX,
      zMax = INT_MIN;

  for (int i = 0; i < drawList_.Size; ++i) { // find zMin and zMax
    Primitive *primitive = drawList_[i];

    if (primitive) {
      if (primitive->z < zMin)
        zMin = primitive->z;

      if (primitive->z > zMax)
        zMax = primitive->z;
    }
  }

  for (int z = zMin; z <= zMax; ++z)
    for (int i = 0; i < drawList_.Size; ++i) {
      Primitive *primitive = drawList_[i];

      if (primitive && (primitive->z == z))
        primitive->draw(drawList, loc);
    }

  if (useCursorPosition_) {
    ItemSize(size_);
    ItemAdd(ImRect(window->DC.CursorPos, window->DC.CursorPos + size_), window->GetID(label));
  }

  drawList->PopClipRect();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::erase(DrawIdx idx) {
  delete drawList_[idx];
  drawList_[idx] = NULL;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::clear() {
  for (int i = 0; i < drawList_.Size; ++i)
    delete drawList_[i];

  drawList_.clear();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::DrawIdx ImStatefulCanvas::addToDrawList(Primitive *primitive) {
  for (int i = 0; i < drawList_.Size; ++i)
    if (!drawList_[i]) {
      drawList_[i] = primitive;
      return i;
    }
  
  drawList_.push_back(primitive);
  return drawList_.Size - 1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Line::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddLine(p1 + loc, p2 + loc, color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Rect::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddRect(p1 + loc, p2 + loc, color, rounding, cornerFlags, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::RectFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddRectFilled(p1 + loc, p2 + loc, color, rounding, cornerFlags);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::RectFilledMultiColor::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddRectFilledMultiColor(p1 + loc, p2 + loc, color1, color2, color3, color4);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Quad::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddQuad(p1 + loc, p2 + loc, p3 + loc, p4 + loc, color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::QuadFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddQuadFilled(p1 + loc, p2 + loc, p3 + loc, p4 + loc, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Triangle::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddTriangle(p1 + loc, p2 + loc, p3 + loc, color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::TriangleFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddTriangleFilled(p1 + loc, p2 + loc, p3 + loc, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Circle::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddCircle(center + loc, radius, color, segments, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::CircleFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddCircleFilled(center + loc, radius, color, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Ngon::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddNgon(center + loc, radius, color, segments, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::NgonFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddNgonFilled(center + loc, radius, color, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Text::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddText(p + loc, color, string.c_str());
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Text2::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddText(font, fontSize, p + loc, color, string.c_str(), NULL, wrapWidth, cpuFineClipRect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Polyline::draw(ImDrawList *drawList, const ImVec2 &loc) {
  for (int i = 0; i < points.Size; ++i)
    adjustedPoints[i] = points[i] + loc;

  drawList->AddPolyline(adjustedPoints, points.Size, color, closed, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::ConvexPolyFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  for (int i = 0; i < points.Size; ++i)
    adjustedPoints[i] = points[i] + loc;

  drawList->AddConvexPolyFilled(adjustedPoints, points.Size, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::BezierCurve::draw(ImDrawList *drawList, const ImVec2 &loc) {
  drawList->AddBezierCurve(p1 + loc, p2 + loc, p3 + loc, p4 + loc, color, thickness, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Image::draw(ImDrawList *drawList, const ImVec2 &loc) {
    drawList->AddImage(textureId, p1 + loc, p2 + loc, uv1, uv2, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::ImageQuad::draw(ImDrawList *drawList, const ImVec2 &loc) {
    drawList->AddImageQuad(textureId, p1 + loc, p2 + loc, p3 + loc, p4 + loc, uv1, uv2, uv3, uv4, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::ImageRounded::draw(ImDrawList *drawList, const ImVec2 &loc) {
    drawList->AddImageRounded(textureId, p1 + loc, p2 + loc, uv1, uv2, color, rounding, cornerFlags);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
} // namespace ImGui
