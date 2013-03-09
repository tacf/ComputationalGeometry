#include "point.h"

static int intBetween (int a, int b, int c) {
  return a <= c && c <= b;
}

static int Equal (const Point a, const Point b) {
  return a->x == b->x && a->y == b->y;
}

int AreaTriangle (const Point a, const Point b, const Point c) {
  assert (NULL != a);
  assert (NULL != b);
  assert (NULL != c);
  return (b->x - a->x) * (c->y - a->y) - (c->x - a->x) * (b->y - a->y);
}

int Left (const Point a, const Point b, const Point c) {
  return 0 < AreaTriangle (a, b, c);
}

int LeftOn (const Point a, const Point b, const Point c) {
  return 0 <= AreaTriangle (a, b, c);
}

int Collinear (const Point a, const Point b, const Point c) {
  return 0 == AreaTriangle (a, b, c);
}

int Between (const Point a, const Point b, const Point c) {
  return
    Collinear (a, b, c) &&
    (a->x != b->x
     ? intBetween (a->x, b->x, c->x) || intBetween (b->x, a->x, c->x)
     : (a->y != b->y
        ? intBetween (a->y, b->y, c->y) || intBetween (b->y, a->y, c->y)
        : Equal (a, c)));
}

int IntersectProperly (const Point a, const Point b, const Point c, const Point d) {
  return
    !(Collinear (a, b, c) ||
      Collinear (a, b, d) ||
      Collinear (c, d, a) ||
      Collinear (c, d, b)) &&
    Left (a, b, c) != Left (a, b, d) &&
    Left (c, d, a) != Left (c, d, b);
}

int Intersect (const Point a, const Point b, const Point c, const Point d) {
  return
    IntersectProperly (a, b, c, d) ||
    Between (a, b, c) ||
    Between (a, b, d) ||
    Between (c, d, a) ||
    Between (c, d, b);
}
