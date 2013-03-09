/*
  triangulate.c
  2013-03-09 pg22577@alunos.uminho.pt

  Purpose:
  - Perform polygon triangulation.

  Features:
  - Complexity: O(n^3), where n is the total number of vertices.

  Details:
  - Proceeds by ear removal, testing one vertex at a time.

  Reference:
  - Computational Geometry in C (2nd ed)
    Joseph O'Rourke
*/
#include <stdlib.h>
#include <stdio.h>
#include "point.h"
#include "polygon.h"

void PrintDiagonal (const PolygonVertex a, const PolygonVertex b) {
  struct Point pta;
  struct Point ptb;
  VertexPoint (a, &pta);
  VertexPoint (b, &ptb);
  fprintf (stdout, "%d %d %d %d\n", pta.x, pta.y, ptb.x, ptb.y);
}

Polygon ReadPolygonFile (void) {
  struct Point pt;
  Polygon plg = NewPolygon ();

  if (NULL == plg) {
    fprintf (stderr, "Error: not enough memory.\n");
    exit (EXIT_FAILURE);
  }

  while (EOF != scanf ("%d %d", &pt.x, &pt.y))
    AppendVertex (plg, &pt);

  if (3 > PolygonSize (plg)) {
    fprintf (stderr, "Error: not enough vertices (%d).\n", PolygonSize (plg));
    exit (EXIT_FAILURE);
  }

  return plg;
}

int main (int argc, char ** argv) {
  Polygon p = ReadPolygonFile ();
  PolygonVertex a;
  PolygonVertex v = SomeVertex (p);
  PolygonVertex b;

  do {
    AdjacentVertices (v, &a, &b);

    if (IsDiagonal (p, a, b)) {
      PrintDiagonal (a, b);
      RemoveVertex (p, &v);
    }

    v = b;
  } while (3 < PolygonSize (p));
  
  exit (EXIT_SUCCESS);
}