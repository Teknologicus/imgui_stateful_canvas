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
  x_                 = 0;
  y_                 = 0;
  width_             = width;
  height_            = height;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
ImStatefulCanvas::ImStatefulCanvas(float x, float y, float width, float height) {
  useCursorPosition_ = false;
  x_                 = x;
  y_                 = y;
  width_             = width;
  height_            = height;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::line(const ImVec2 &p1, const ImVec2 &p2, ImU32 col, float thickness) {
  Line *line = new Line;
  line->p1[0]     = p1.x;
  line->p1[1]     = p1.y;
  line->p2[0]     = p2.x;
  line->p2[1]     = p2.y;
  line->color     = col;
  line->thickness = thickness;
  return addToDrawList(line);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::rect(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding, ImDrawCornerFlags rounding_corners, float thickness) {
  Rect *rect = new Rect;
  rect->p1[0]       = p_min.x;
  rect->p1[1]       = p_min.y;
  rect->p2[0]       = p_max.x;
  rect->p2[1]       = p_max.y;
  rect->color       = col;
  rect->rounding    = rounding;
  rect->cornerFlags = rounding_corners;
  rect->thickness   = thickness;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::rectFilled(const ImVec2 &p_min, const ImVec2 &p_max, ImU32 col, float rounding, ImDrawCornerFlags rounding_corners) {
  RectFilled *rect = new RectFilled;
  rect->p1[0]       = p_min.x;
  rect->p1[1]       = p_min.y;
  rect->p2[0]       = p_max.x;
  rect->p2[1]       = p_max.y;
  rect->color       = col;
  rect->rounding    = rounding;
  rect->cornerFlags = rounding_corners;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::rectFilledMultiColor(const ImVec2 &p_min, const ImVec2 &p_max,
                                           ImU32 col_upr_left, ImU32 col_upr_right, ImU32 col_bot_right, ImU32 col_bot_left) {
  RectFilledMultiColor *rect = new RectFilledMultiColor;
  rect->p1[0]  = p_min.x;
  rect->p1[1]  = p_min.y;
  rect->p2[0]  = p_max.x;
  rect->p2[1]  = p_max.y;
  rect->color1 = col_upr_left;
  rect->color2 = col_upr_right;
  rect->color3 = col_bot_right;
  rect->color4 = col_bot_left;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::quad(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness) {
  Quad *quad = new Quad;
  quad->p1[0]     = p1.x;
  quad->p1[1]     = p1.y;
  quad->p2[0]     = p2.x;
  quad->p2[1]     = p2.y;
  quad->p3[0]     = p3.x;
  quad->p3[1]     = p3.y;
  quad->p4[0]     = p4.x;
  quad->p4[1]     = p4.y;
  quad->color     = col;
  quad->thickness = thickness;
  return addToDrawList(quad);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::quadFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col) {
  QuadFilled *quad = new QuadFilled;
  quad->p1[0] = p1.x;
  quad->p1[1] = p1.y;
  quad->p2[0] = p2.x;
  quad->p2[1] = p2.y;
  quad->p3[0] = p3.x;
  quad->p3[1] = p3.y;
  quad->p4[0] = p4.x;
  quad->p4[1] = p4.y;
  quad->color = col;
  return addToDrawList(quad);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::triangle(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col, float thickness) {
  Triangle *tri = new Triangle;
  tri->p1[0]     = p1.x;
  tri->p1[1]     = p1.y;
  tri->p2[0]     = p2.x;
  tri->p2[1]     = p2.y;
  tri->p3[0]     = p3.x;
  tri->p3[1]     = p3.y;
  tri->color     = col;
  tri->thickness = thickness;
  return addToDrawList(tri);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::triangleFilled(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 col) {
  TriangleFilled *tri = new TriangleFilled;
  tri->p1[0]     = p1.x;
  tri->p1[1]     = p1.y;
  tri->p2[0]     = p2.x;
  tri->p2[1]     = p2.y;
  tri->p3[0]     = p3.x;
  tri->p3[1]     = p3.y;
  tri->color     = col;
  return addToDrawList(tri);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::circle(const ImVec2 &center, float radius, ImU32 col, int num_segments, float thickness) {
  Circle *circle = new Circle;
  circle->center[0] = center.x;
  circle->center[1] = center.y;
  circle->radius    = radius;
  circle->color     = col;
  circle->segments  = num_segments;
  circle->thickness = thickness;
  return addToDrawList(circle);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::circleFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments) {
  CircleFilled *circle = new CircleFilled;
  circle->center[0] = center.x;
  circle->center[1] = center.y;
  circle->radius    = radius;
  circle->color     = col;
  circle->segments  = num_segments;
  return addToDrawList(circle);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::ngon(const ImVec2 &center, float radius, ImU32 col, int num_segments, float thickness) {
  Ngon *ngon = new Ngon;
  ngon->center[0] = center.x;
  ngon->center[1] = center.y;
  ngon->radius    = radius;
  ngon->color     = col;
  ngon->segments  = num_segments;
  ngon->thickness = thickness;
  return addToDrawList(ngon);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::ngonFilled(const ImVec2 &center, float radius, ImU32 col, int num_segments) {
  NgonFilled *ngon = new NgonFilled;
  ngon->center[0] = center.x;
  ngon->center[1] = center.y;
  ngon->radius    = radius;
  ngon->color     = col;
  ngon->segments  = num_segments;
  return addToDrawList(ngon);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::text(const ImVec2 &pos, ImU32 col, const char *text_begin, const char *text_end) {
  Text *text = new Text;
  text->p[0]   = pos.x;
  text->p[1]   = pos.y;
  text->color  = col;
  text->string = text_end ? std::string(text_begin, text_end - text_begin) : std::string(text_begin);
  return addToDrawList(text);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::text(const ImFont *font, float font_size, const ImVec2 &pos, ImU32 col,
                           const char *text_begin, const char *text_end, float wrap_width, const ImVec4 *cpu_fine_clip_rect) {
  Text2 *text = new Text2;
  text->p[0]            = pos.x;
  text->p[1]            = pos.y;
  text->color           = col;
  text->string          = text_end ? std::string(text_begin, text_end - text_begin) : std::string(text_begin);
  text->font            = font;
  text->fontSize        = font_size;
  text->wrapWidth       = wrap_width;
  text->cpuFineClipRect = cpu_fine_clip_rect;
  return addToDrawList(text);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::polyline(const ImVec2 *points, int num_points, ImU32 col, bool closed, float thickness) {
  Polyline *poly = new Polyline(num_points);
  poly->color     = col;
  poly->thickness = thickness;
  poly->closed    = closed;

  for (int i = 0; i < num_points; ++i) {
    const ImVec2 *p = &points[i];
    poly->points.push_back(Point(p->x, p->y));
  }

  return addToDrawList(poly);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::convexPolyFilled(const ImVec2 *points, int num_points, ImU32 col) {
  ConvexPolyFilled *poly = new ConvexPolyFilled(num_points);
  poly->color = col;

  for (int i = 0; i < num_points; ++i) {
    const ImVec2 *p = &points[i];
    poly->points.push_back(Point(p->x, p->y));
  }

  return addToDrawList(poly);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::bezierCurve(const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, const ImVec2 &p4, ImU32 col, float thickness, int num_segments) {
  BezierCurve *bezier = new BezierCurve;
  bezier->p1[0] = p1.x;
  bezier->p1[1] = p1.y;
  bezier->p2[0] = p2.x;
  bezier->p2[1] = p2.y;
  bezier->p3[0] = p3.x;
  bezier->p3[1] = p3.y;
  bezier->p4[0] = p4.x;
  bezier->p4[1] = p4.y;
  bezier->color = col;
  bezier->thickness = thickness;
  bezier->segments = num_segments;
  return addToDrawList(bezier);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::image(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max, ImU32 col) {
  Image *image = new Image;
  image->textureId = user_texture_id;
  image->p1[0]     = p_min.x;
  image->p1[1]     = p_min.y;
  image->p2[0]     = p_max.x;
  image->p2[1]     = p_max.y;
  image->uv1[0]    = uv_min.x;
  image->uv1[1]    = uv_min.y;
  image->uv2[0]    = uv_max.x;
  image->uv2[1]    = uv_max.y;
  image->color     = col;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::imageQuad(ImTextureID user_texture_id, const ImVec2& p1, const ImVec2& p2, const ImVec2& p3, const ImVec2& p4, const ImVec2& uv1,
                                const ImVec2& uv2, const ImVec2& uv3, const ImVec2& uv4, ImU32 col) {
  ImageQuad *image = new ImageQuad;
  image->textureId = user_texture_id;
  image->p1[0]     = p1.x;
  image->p1[1]     = p1.y;
  image->p2[0]     = p2.x;
  image->p2[1]     = p2.y;
  image->p3[0]     = p3.x;
  image->p3[1]     = p3.y;
  image->p4[0]     = p4.x;
  image->p4[1]     = p4.y;
  image->uv1[0]    = uv1.x;
  image->uv1[1]    = uv1.y;
  image->uv2[0]    = uv2.x;
  image->uv2[1]    = uv2.y;
  image->uv3[0]    = uv3.x;
  image->uv3[1]    = uv3.y;
  image->uv4[0]    = uv4.x;
  image->uv4[1]    = uv4.y;
  image->color     = col;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::imageRounded(ImTextureID user_texture_id, const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min, const ImVec2& uv_max,
                                   ImU32 col, float rounding, ImDrawCornerFlags rounding_corners) {
  ImageRounded *image = new ImageRounded;
  image->textureId   = user_texture_id;
  image->p1[0]       = p_min.x;
  image->p1[1]       = p_min.y;
  image->p2[0]       = p_max.x;
  image->p2[1]       = p_max.y;
  image->uv1[0]      = uv_min.x;
  image->uv1[1]      = uv_min.y;
  image->uv2[0]      = uv_max.x;
  image->uv2[1]      = uv_max.y;
  image->color       = col;
  image->rounding    = rounding;
  image->cornerFlags = rounding_corners;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::show(const char *label) const {
  ImGuiWindow *window = ImGui::GetCurrentWindow();

  if (window->SkipItems)
    return;

  float x,
        y;
  
  if (useCursorPosition_) {
    ImVec2 &pos = window->DC.CursorPos;
    x = pos.x;
    y = pos.y;
  } else {
    x = x_;
    y = y_;
  }

  ImDrawList *drawList = ImGui::GetWindowDrawList();
  drawList->PushClipRect(ImVec2(x, y), ImVec2(x + width_, y + height_));

  for (int i = 0; i < drawList_.Size; ++i) {
    Primitive *primitive = drawList_[i];

    if (primitive)
      primitive->show(drawList, x, y);
  }

  if (useCursorPosition_) {
    ImVec2 size(width_, height_);
    ItemSize(size);
    ItemAdd(ImRect(window->DC.CursorPos, window->DC.CursorPos + size), window->GetID(label));
  }

  drawList->PopClipRect();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::erase(int id) {
  delete drawList_[id];
  drawList_[id] = NULL;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::clear() {
  for (int i = 0; i < drawList_.Size; ++i)
    delete drawList_[i];

  drawList_.clear();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
int ImStatefulCanvas::addToDrawList(Primitive *primitive) {
  for (int i = 0; i < drawList_.Size; ++i)
    if (!drawList_[i]) {
      drawList_[i] = primitive;
      return i;
    }
  
  drawList_.push_back(primitive);
  return drawList_.Size - 1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Line::show(ImDrawList *drawList, float x, float y) {
  drawList->AddLine(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Rect::show(ImDrawList *drawList, float x, float y) {
  drawList->AddRect(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), color, rounding, cornerFlags, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::RectFilled::show(ImDrawList *drawList, float x, float y) {
  drawList->AddRectFilled(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), color, rounding, cornerFlags);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::RectFilledMultiColor::show(ImDrawList *drawList, float x, float y) {
  drawList->AddRectFilledMultiColor(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), color1, color2, color3, color4);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Quad::show(ImDrawList *drawList, float x, float y) {
  drawList->AddQuad(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkAdjImVec2(p3, x, y), mkAdjImVec2(p4, x, y), color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::QuadFilled::show(ImDrawList *drawList, float x, float y) {
  drawList->AddQuadFilled(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkAdjImVec2(p3, x, y), mkAdjImVec2(p4, x, y), color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Triangle::show(ImDrawList *drawList, float x, float y) {
  drawList->AddTriangle(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkAdjImVec2(p3, x, y), color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::TriangleFilled::show(ImDrawList *drawList, float x, float y) {
  drawList->AddTriangleFilled(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkAdjImVec2(p3, x, y), color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Circle::show(ImDrawList *drawList, float x, float y) {
  drawList->AddCircle(mkAdjImVec2(center, x, y), radius, color, segments, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::CircleFilled::show(ImDrawList *drawList, float x, float y) {
  drawList->AddCircleFilled(mkAdjImVec2(center, x, y), radius, color, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Ngon::show(ImDrawList *drawList, float x, float y) {
  drawList->AddNgon(mkAdjImVec2(center, x, y), radius, color, segments, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::NgonFilled::show(ImDrawList *drawList, float x, float y) {
  drawList->AddNgonFilled(mkAdjImVec2(center, x, y), radius, color, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Text::show(ImDrawList *drawList, float x, float y) {
  drawList->AddText(mkAdjImVec2(p, x, y), color, string.c_str());
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Text2::show(ImDrawList *drawList, float x, float y) {
  drawList->AddText(font, fontSize, mkAdjImVec2(p, x, y), color, string.c_str(), NULL, wrapWidth, cpuFineClipRect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Polyline::show(ImDrawList *drawList, float x, float y) {
  for (int i = 0; i < points.Size; ++i) {
    Point  *p = &points[i];
    ImVec2 *v = &adjustedPoints[i];
    v->x = p->p[0] + x;
    v->y = p->p[1] + y;
  }

  drawList->AddPolyline(adjustedPoints, points.Size, color, closed, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::ConvexPolyFilled::show(ImDrawList *drawList, float x, float y) {
  for (int i = 0; i < points.Size; ++i) {
    Point  *p = &points[i];
    ImVec2 *v = &adjustedPoints[i];
    v->x = p->p[0] + x;
    v->y = p->p[1] + y;
  }

  drawList->AddConvexPolyFilled(adjustedPoints, points.Size, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::BezierCurve::show(ImDrawList *drawList, float x, float y) {
  drawList->AddBezierCurve(mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkAdjImVec2(p3, x, y), mkAdjImVec2(p4, x, y), color, thickness, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::Image::show(ImDrawList *drawList, float x, float y) {
    drawList->AddImage(textureId, mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkImVec2(uv1), mkImVec2(uv2), color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::ImageQuad::show(ImDrawList *drawList, float x, float y) {
    drawList->AddImageQuad(textureId, mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkAdjImVec2(p3, x, y), mkAdjImVec2(p4, x, y),
                           mkImVec2(uv1), mkImVec2(uv2), mkImVec2(uv3), mkImVec2(uv4), color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void ImStatefulCanvas::ImageRounded::show(ImDrawList *drawList, float x, float y) {
    drawList->AddImageRounded(textureId, mkAdjImVec2(p1, x, y), mkAdjImVec2(p2, x, y), mkImVec2(uv1), mkImVec2(uv2), color, rounding, cornerFlags);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
} // namespace ImGui
