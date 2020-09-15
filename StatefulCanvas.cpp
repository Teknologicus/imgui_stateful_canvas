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

#include "StatefulCanvas.h"

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
namespace ImGui {

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Points::move(float x, float y) {
  ImVec2 m(x, y);

  for (int i = 0; i < points.size(); ++i)
    points[i] += m;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::StatefulCanvas(float width, float height) {
  assert((width > 0) && (height > 0));
  useCursorPosition_ = true;
  location_          = {0, 0};
  size_              = {width, height};
  z_                 = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::StatefulCanvas(float x, float y, float width, float height) {
  assert((width > 0) && (height > 0));
  useCursorPosition_ = false;
  location_          = {x, y};
  size_              = {width, height};
  z_                 = 0;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
bool StatefulCanvas::visible(draw_idx_t idx) const {
  assert((idx >= 0) && (idx < drawList_.size()));
  Primitive *item = drawList_[idx];
  assert(item);
  return item->visible;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::visible(draw_idx_t idx, bool state) {
  assert((idx >= 0) && (idx < drawList_.size()));
  Primitive *item = drawList_[idx];
  assert(item);
  item->visible = state;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::line(const ImVec2 &p0, const ImVec2 &p1, ImU32 color, float thickness) {
  Line *line      = new Line;
  line->z         = z_;
  line->p0        = p0;
  line->p1        = p1;
  line->color     = color;
  line->thickness = thickness;
  return addToDrawList(line);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::rect(const ImVec2 &min, const ImVec2 &max, ImU32 color, float rounding, ImDrawCornerFlags roundingCorners,
                                                float thickness) {
  Rect *rect        = new Rect;
  rect->z           = z_;
  rect->p0          = min;
  rect->p1          = max;
  rect->color       = color;
  rect->rounding    = rounding;
  rect->cornerFlags = roundingCorners;
  rect->thickness   = thickness;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::rectFilled(const ImVec2 &min, const ImVec2 &max, ImU32 color, float rounding,
                                                      ImDrawCornerFlags roundingCorners) {
  RectFilled *rect  = new RectFilled;
  rect->z           = z_;
  rect->p0          = min;
  rect->p1          = max;
  rect->color       = color;
  rect->rounding    = rounding;
  rect->cornerFlags = roundingCorners;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::rectFilledMultiColor(const ImVec2 &min, const ImVec2 &max,
                                                                ImU32 colorUpperLeft, ImU32 colorUpperRight, ImU32 colorBottomRight, ImU32 colorBottomLeft) {
  RectFilledMultiColor *rect = new RectFilledMultiColor;
  rect->z                    = z_;
  rect->p0                   = min;
  rect->p1                   = max;
  rect->color0               = colorUpperLeft;
  rect->color1               = colorUpperRight;
  rect->color2               = colorBottomRight;
  rect->color3               = colorBottomLeft;
  return addToDrawList(rect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::quad(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 color, float thickness) {
  Quad *quad      = new Quad;
  quad->z         = z_;
  quad->p0        = p0;
  quad->p1        = p1;
  quad->p2        = p2;
  quad->p3        = p3;
  quad->color     = color;
  quad->thickness = thickness;
  return addToDrawList(quad);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::quadFilled(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 color) {
  QuadFilled *quad = new QuadFilled;
  quad->z          = z_;
  quad->p0         = p0;
  quad->p1         = p1;
  quad->p2         = p2;
  quad->p3         = p3;
  quad->color      = color;
  return addToDrawList(quad);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::triangle(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, ImU32 color, float thickness) {
  Triangle *tri  = new Triangle;
  tri->z         = z_;
  tri->p0        = p0;
  tri->p1        = p1;
  tri->p2        = p2;
  tri->color     = color;
  tri->thickness = thickness;
  return addToDrawList(tri);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::triangleFilled(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, ImU32 color) {
  TriangleFilled *tri = new TriangleFilled;
  tri->z              = z_;
  tri->p0             = p0;
  tri->p1             = p1;
  tri->p2             = p2;
  tri->color          = color;
  return addToDrawList(tri);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::circle(const ImVec2 &center, float radius, ImU32 color, int nSegments, float thickness) {
  Circle *circle    = new Circle;
  circle->z         = z_;
  circle->center    = center;
  circle->radius    = radius;
  circle->color     = color;
  circle->segments  = nSegments;
  circle->thickness = thickness;
  return addToDrawList(circle);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::circleFilled(const ImVec2 &center, float radius, ImU32 color, int nSegments) {
  CircleFilled *circle = new CircleFilled;
  circle->z            = z_;
  circle->center       = center;
  circle->radius       = radius;
  circle->color        = color;
  circle->segments     = nSegments;
  return addToDrawList(circle);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::ngon(const ImVec2 &center, float radius, ImU32 color, int nSegments, float thickness) {
  Ngon *ngon      = new Ngon;
  ngon->z         = z_;
  ngon->center    = center;
  ngon->radius    = radius;
  ngon->color     = color;
  ngon->segments  = nSegments;
  ngon->thickness = thickness;
  return addToDrawList(ngon);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::ngonFilled(const ImVec2 &center, float radius, ImU32 color, int nSegments) {
  NgonFilled *ngon = new NgonFilled;
  ngon->z          = z_;
  ngon->center     = center;
  ngon->radius     = radius;
  ngon->color      = color;
  ngon->segments   = nSegments;
  return addToDrawList(ngon);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::text(const ImVec2 &pos, ImU32 color, const char *textBegin, const char *textEnd) {
  Text *text   = new Text;
  text->z      = z_;
  text->p      = pos;
  text->color  = color;
  text->string = textEnd ? std::string(textBegin, textEnd - textBegin) : std::string(textBegin);
  return addToDrawList(text);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::text(const ImFont *font, float fontSize, const ImVec2 &pos, ImU32 color,
                                                const char *textBegin, const char *textEnd, float wrapWidth, const ImVec4 *cpuFineClipRect) {
  Text2 *text           = new Text2;
  text->z               = z_;
  text->p               = pos;
  text->color           = color;
  text->string          = textEnd ? std::string(textBegin, textEnd - textBegin) : textBegin;
  text->font            = font;
  text->fontSize        = fontSize;
  text->wrapWidth       = wrapWidth;
  text->cpuFineClipRect = cpuFineClipRect;
  return addToDrawList(text);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::polyline(const ImVec2 *points, int nPoints, ImU32 color, bool closed, float thickness) {
  Polyline *poly  = new Polyline(nPoints);
  poly->z         = z_;
  poly->color     = color;
  poly->thickness = thickness;
  poly->closed    = closed;

  for (int i = 0; i < nPoints; ++i)
    poly->points.push_back(points[i]);

  return addToDrawList(poly);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::convexPolyFilled(const ImVec2 *points, int nPoints, ImU32 color) {
  ConvexPolyFilled *poly = new ConvexPolyFilled(nPoints);
  poly->z                = z_;
  poly->color            = color;

  for (int i = 0; i < nPoints; ++i)
    poly->points.push_back(points[i]);

  return addToDrawList(poly);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::bezierCurve(const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3, ImU32 color, float thickness,
                                                       int nSegments) {
  BezierCurve *bezier = new BezierCurve;
  bezier->z           = z_;
  bezier->p0          = p0;
  bezier->p1          = p1;
  bezier->p2          = p2;
  bezier->p3          = p3;
  bezier->color       = color;
  bezier->thickness   = thickness;
  bezier->segments    = nSegments;
  return addToDrawList(bezier);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::image(ImTextureID textureId, const ImVec2 &min, const ImVec2 &max, const ImVec2 &uvMin,
                                                 const ImVec2 &uvMax, ImU32 color) {
  Image *image     = new Image;
  image->z         = z_;
  image->textureId = textureId;
  image->p0        = min;
  image->p1        = max;
  image->uv0       = uvMin;
  image->uv1       = uvMax;
  image->color     = color;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::imageQuad(ImTextureID textureId, const ImVec2 &p0, const ImVec2 &p1, const ImVec2 &p2, const ImVec2 &p3,
                                                     const ImVec2 &uv0, const ImVec2 &uv1, const ImVec2 &uv2, const ImVec2 &uv3, ImU32 color) {
  ImageQuad *image = new ImageQuad;
  image->z         = z_;
  image->textureId = textureId;
  image->p0        = p0;
  image->p1        = p1;
  image->p2        = p2;
  image->p3        = p3;
  image->uv0       = uv0;
  image->uv1       = uv1;
  image->uv2       = uv2;
  image->uv3       = uv3;
  image->color     = color;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::imageRounded(ImTextureID textureId, const ImVec2 &min, const ImVec2 &max,
                                                        const ImVec2 &uvMin, const ImVec2 &uvMax, ImU32 color, float rounding,
                                                        ImDrawCornerFlags roundingCorners) {
  ImageRounded *image = new ImageRounded;
  image->z            = z_;
  image->textureId    = textureId;
  image->p0           = min;
  image->p1           = max;
  image->uv0          = uvMin;
  image->uv1          = uvMax;
  image->color        = color;
  image->rounding     = rounding;
  image->cornerFlags  = roundingCorners;
  return addToDrawList(image);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::custom(Primitive *c) {
  c->z = z_;
  return addToDrawList(c);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::draw(const char *label, bool clip) const {
  if (drawList_.size() == 0)
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

  if (clip)
    drawList->PushClipRect(loc, loc + size_);

  int min = INT_MAX,
      max = INT_MIN;

  for (int i = 0; i < drawList_.size(); ++i) { // find zMin and zMax
    Primitive *primitive = drawList_[i];

    if (primitive) {
      int z = primitive->z + primitive->offsetZ;

      if (z < min)
        min = z;

      if (z > max)
        max = z;
    }
  }

  for (int z = min; z <= max; ++z) // poor performance with sparse z values -- designed for several, adjacent z layers on a canvas
    for (int i = 0; i < drawList_.size(); ++i) {
      Primitive *primitive = drawList_[i];

      if (primitive && primitive->visible && ((primitive->z + primitive->offsetZ) == z))
        primitive->draw(drawList, loc);
    }

  if (useCursorPosition_) {
    ItemSize(size_);
    ItemAdd(ImRect(window->DC.CursorPos, window->DC.CursorPos + size_), window->GetID(label));
  }

  if (clip)
    drawList->PopClipRect();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::erase(draw_idx_t idx) {
  assert((idx >= 0) && (idx < drawList_.size()) && drawList_[idx]);
  delete drawList_[idx];
  drawList_[idx] = nullptr;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::clear() {
  for (int i = 0; i < drawList_.size(); ++i)
    delete drawList_[i];

  drawList_.clear();
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
StatefulCanvas::draw_idx_t StatefulCanvas::addToDrawList(Primitive *primitive) {
  for (int i = 0; i < drawList_.size(); ++i)
    if (!drawList_[i]) {
      drawList_[i] = primitive;
      return i;
    }

  drawList_.push_back(primitive);
  return drawList_.size() - 1;
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Line::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddLine(p0 + offs, p1 + offs, color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Rect::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddRect(p0 + offs, p1 + offs, color, rounding, cornerFlags, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::RectFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddRectFilled(p0 + offs, p1 + offs, color, rounding, cornerFlags);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::RectFilledMultiColor::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddRectFilledMultiColor(p0 + offs, p1 + offs, color0, color1, color2, color3);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Quad::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddQuad(p0 + offs, p1 + offs, p2 + offs, p3 + offs, color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::QuadFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddQuadFilled(p0 + offs, p1 + offs, p2 + offs, p3 + offs, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Triangle::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddTriangle(p0 + offs, p1 + offs, p2 + offs, color, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::TriangleFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddTriangleFilled(p0 + offs, p1 + offs, p2 + offs, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Circle::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddCircle(center + offs, radius, color, segments, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::CircleFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddCircleFilled(center + offs, radius, color, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Ngon::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddNgon(center + offs, radius, color, segments, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::NgonFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddNgonFilled(center + offs, radius, color, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Text::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddText(p + offs, color, string.c_str());
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Text2::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddText(font, fontSize, p + offs, color, string.c_str(), nullptr, wrapWidth, cpuFineClipRect);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Polyline::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);

  for (int i = 0; i < points.Size; ++i)
    adjustedPoints[i] = points[i] + offs;

  drawList->AddPolyline(adjustedPoints, points.Size, color, closed, thickness);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::ConvexPolyFilled::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);

  for (int i = 0; i < points.Size; ++i)
    adjustedPoints[i] = points[i] + offs;

  drawList->AddConvexPolyFilled(adjustedPoints, points.Size, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::BezierCurve::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddBezierCurve(p0 + offs, p1 + offs, p2 + offs, p3 + offs, color, thickness, segments);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::Image::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddImage(textureId, p0 + offs, p1 + offs, uv0, uv1, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::ImageQuad::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddImageQuad(textureId, p0 + offs, p1 + offs, p2 + offs, p3 + offs, uv0, uv1, uv2, uv3, color);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
void StatefulCanvas::ImageRounded::draw(ImDrawList *drawList, const ImVec2 &loc) {
  ImVec2 offs;
  offset(loc, &offs);
  drawList->AddImageRounded(textureId, p0 + offs, p1 + offs, uv0, uv1, color, rounding, cornerFlags);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------------------
} // namespace ImGui
