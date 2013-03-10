/*
  Details:
  - A polygon is represented by a circular doubly linked-list of vertices.
*/
#include "polygon.h"

struct PolygonVertex {
  struct Point Point;
  PolygonVertex Meta;
  struct PolygonVertex * Next;
  struct PolygonVertex * Prev;
};

struct Polygon {
  size_t Size;
  struct PolygonVertex * Vertices;
};

Polygon NewPolygon (void) {
  Polygon p = malloc (sizeof (struct Polygon));
  
  if (NULL == p)
    return NULL;

  p->Size = 0;

  return p;
}

void FreePolygon (Polygon * p) {
  PolygonVertex v;

  assert (NULL != p);

  while (NULL != (v = SomeVertex (*p)))
    RemoveVertex (*p, &v);

  assert ((*p)->Size == 0);

  free (*p);
  *p = NULL;
}

size_t PolygonSize (const Polygon p) {
  assert (NULL != p);
  return p->Size;
}

PolygonVertex SomeVertex (const Polygon p) {
  assert (NULL != p);
  return 0 < PolygonSize (p) ? p->Vertices : NULL;
}

PolygonVertex AppendVertexWithMeta (Polygon p, const struct Point * pt, PolygonVertexMeta * m) {
  PolygonVertex v = malloc (sizeof (struct PolygonVertex));

  if (NULL == v)
    return NULL;

  assert (NULL != pt);
  assert (NULL != m);

  v->Point.x = pt->x;
  v->Point.y = pt->y;
  v->Meta = *m;

  assert (NULL != p);

  if (0 == p->Size) {
    v->Next = v;
    v->Prev = v;
    p->Vertices = v;
  }
  else {
    v->Next = p->Vertices;
    v->Prev = p->Vertices->Prev;

    v->Prev->Next = v;
    v->Next->Prev = v;
  }

  p->Size++;

  return v;
}

PolygonVertex AppendVertex (Polygon p, const struct Point * pt) {
  PolygonVertexMeta n = NULL;
  return AppendVertexWithMeta (p, pt, &n);
}

void VertexPoint (const PolygonVertex v, struct Point * pt) {
  assert (NULL != v);
  assert (NULL != pt);

  pt->x = v->Point.x;
  pt->y = v->Point.y;
}

void VertexMeta (const PolygonVertex v, PolygonVertexMeta * m) {
  assert (NULL != v);
  assert (NULL != m);

  *m = v->Meta;
}

void UpdateVertexMeta (PolygonVertex v, PolygonVertexMeta * m) {
  assert (NULL != v);
  assert (NULL != m);

  v->Meta = *m;
}

void RemoveVertex (Polygon p, PolygonVertex * v) {
  assert (NULL != p);
  assert (NULL != v);
  assert (NULL != *v);

  (*v)->Prev->Next = (*v)->Next;
  (*v)->Next->Prev = (*v)->Prev;

  if (p->Vertices == *v)
    p->Vertices = p->Vertices->Next;

  p->Size--;

  free (*v);
  *v = NULL;
}

void AdjacentVertices (const PolygonVertex a, PolygonVertex * b, PolygonVertex * c){
  assert (NULL != a);
  assert (NULL != b);
  assert (NULL != c);

  *b = a->Prev;
  *c = a->Next;
}

int IsConvex (const PolygonVertex a) {
  assert (NULL != a);

  return LeftOn (&a->Point, &a->Next->Point, &a->Prev->Point);
}

static int InCone (const PolygonVertex a, const PolygonVertex b) {
  assert (NULL != a);
  assert (NULL != b);

  return
    IsConvex (a)
    ? (Left (&a->Point, &b->Point, &a->Prev->Point) &&
       Left (&b->Point, &a->Point, &a->Next->Point))
    : !(LeftOn (&a->Point, &b->Point, &a->Next->Point) &&
        LeftOn (&b->Point, &a->Point, &a->Prev->Point));
}

static int DiagonalIntOrExt (const Polygon p, const PolygonVertex a, const PolygonVertex b) {
  PolygonVertex v;

  assert (NULL != p);
  assert (NULL != a);
  assert (NULL != b);

  assert (0 < p->Size);
  v = p->Vertices;

  do {
    if (v != a &&
        v != b &&
        v->Next != a &&
        v->Next != b &&
        Intersect (&a->Point, &b->Point, &v->Point, &v->Next->Point))
      return 0;

    v = v->Next;
  } while (v != p->Vertices);

  return 1;
}

int IsDiagonal (const Polygon p, const PolygonVertex a, const PolygonVertex b) {
  assert (NULL != p);
  assert (NULL != a);
  assert (NULL != b);

  return
    InCone (a, b) &&
    InCone (b, a) &&
    DiagonalIntOrExt (p, a, b);
}
