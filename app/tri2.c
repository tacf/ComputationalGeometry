/*
  tri2.c
  2013-03-19 pg22577@alunos.uminho.pt

  Purpose:
  - Perform polygon triangulation.

  Features:
  - Complexity: O(n^2), where n is the total number of vertices.

  Details:
  - Proceeds by ear removal.
    Each vertex comprises meta information indicating if it is
    an ear or not.
    Each time an ear is removed, it is only necessary to update
    its adjacent vertices earity status.

  Warnings:
  - Concerning the meta information associated with each vertex,
    it is assumed that sizeof (void *) == sizeof (int).

  Reference:
  - Computational Geometry in C (2nd)
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
    if (NULL == AppendVertex (plg, &pt)) {
      fprintf (stderr, "Error: not enough memory.\n");
      exit (EXIT_FAILURE);
    }

  if (3 > PolygonSize (plg)) {
    fprintf (stderr, "Error: not enough vertices (%d).\n", PolygonSize (plg));
    exit (EXIT_FAILURE);
  }

  return plg;
}

int EarityStatus (PolygonVertex v) {
  PolygonVertexMeta e;
  VertexMeta (v, &e);
  return (int) e;
}

void UpdateEarityStatus (PolygonVertex v, int e) {
  UpdateVertexMeta (v, (PolygonVertexMeta *) &e);
}

int CheckEarityStatus (Polygon p, PolygonVertex v) {
  PolygonVertex a;
  PolygonVertex b;
  AdjacentVertices (v, &a, &b);
  return IsDiagonal (p, a, b);
}

void MarkEars (Polygon p) {
  PolygonVertex i = SomeVertex (p);
  PolygonVertex v = i;
  PolygonVertex a;

  do {
    UpdateEarityStatus (v, CheckEarityStatus (p, v));
    AdjacentVertices (v, &a, &v);
  } while (v != i);
}

int main (int argc, char ** argv) {
  Polygon p = ReadPolygonFile ();
  PolygonVertex a;
  PolygonVertex v = SomeVertex (p);
  PolygonVertex b;

  MarkEars (p);

  do {
    AdjacentVertices (v, &a, &b);

    if (EarityStatus (v)) {
      PrintDiagonal (a, b);
      RemoveVertex (p, &v);
      UpdateEarityStatus (a, CheckEarityStatus (p, a));
      UpdateEarityStatus (b, CheckEarityStatus (p, b));
    }

    v = b;
  } while (3 < PolygonSize (p));

  return EXIT_SUCCESS;
}
