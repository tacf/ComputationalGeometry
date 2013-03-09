/*
  point.h
  2013-03-08 pg22577@alunos.uminho.pt

  Purpose:
  - Representation of 2D points with integer coordinates.
  - Utility functions.

  Reference:
  - Computational Geometry in C (2nd ed)
    Joseph O'Rourke
*/
#ifndef POINT_H
#define POINT_H

#include <assert.h>
#include <stdlib.h>

typedef struct Point {
  int x;
  int y;
} * Point;

/* Returns (2 * A), where A is the area of the triangle abc.*/
int AreaTriangle (const Point a, const Point b, const Point c);

/* Returns 1 if c is strictly to the left of the line segment ab. */
int Left (const Point a, const Point b, const Point c);

/* Returns 1 if c is on or to the left of the line segment ab. */
int LeftOn (const Point a, const Point b, const Point c);

/* Returns 1 if c is on the line segment ab. */
int Collinear (const Point a, const Point b, const Point c);

/* Returns 1 if c lies on the closed line segment ab. */
int Between (const Point a, const Point b, const Point c);

/* Returns 1 if ab properly intersects cd.*/
int IntersectProperly (const Point a, const Point b, const Point c, const Point d);

/* Returns 1 if ab intersects cd, properly or improperly. */
int Intersect (const Point a, const Point b, const Point c, const Point d);

#endif /* POINT_H */
