/*
  tri3.c
  2013-03-21 pg22577@alunos.uminho.pt

  Purpose:
  - Perform polygon triangulation.

  Features:
  - Complexity: O(n^3), where n is the total number of vertices.
  - (Optional) PostScript output. See PSOUTPUT.

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

/* Comment the following line to suppress PostScript output. */
#define PSOUTPUT

void PrintPolygon (const Polygon p) {
  PolygonVertex i = SomeVertex (p);
  PolygonVertex v = i;
  PolygonVertex a;
  struct Point pt;

  VertexPoint (v, &pt);

#ifndef PSOUTPUT
  fprintf (stdout, "%d %d\n", pt.x, pt.y);
#else
  fprintf (stdout, "newpath\n%d %d moveto\n", pt.x, pt.y);
#endif

  do {
    AdjacentVertices (v, &a, &v);
    VertexPoint (v, &pt);

#ifndef PSOUTPUT
    fprintf (stdout, "%d %d\n", pt.x, pt.y);
#else
    fprintf (stdout, "%d %d lineto\n", pt.x, pt.y);
#endif

  } while (v != i);

#ifdef PSOUTPUT
  fprintf (stdout, "closepath stroke\n");
#endif
}

void PrintDiagonal (const PolygonVertex a, const PolygonVertex b) {
  struct Point pta;
  struct Point ptb;
  VertexPoint (a, &pta);
  VertexPoint (b, &ptb);

#ifdef PSOUTPUT
  fprintf (stdout, "newpath\n%d %d moveto\n%d %d lineto\nclosepath stroke\n", pta.x, pta.y, ptb.x, ptb.y);
#else
  fprintf (stdout, "%d %d %d %d\n", pta.x, pta.y, ptb.x, ptb.y);
#endif
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

int main (int argc, char ** argv) {
  Polygon p = ReadPolygonFile ();
  PolygonVertex a;
  PolygonVertex v = SomeVertex (p);
  PolygonVertex b;

#ifdef PSOUTPUT
  fprintf (stdout, "0.1 setlinewidth\n0 0 1 setrgbcolor\n");
  PrintPolygon (p);
  fprintf (stdout, "0.1 setlinewidth\n1 0 0 setrgbcolor\n");
#endif

  do {
    AdjacentVertices (v, &a, &b);
    
    if (IsDiagonal (p, a, b)) {
      PrintDiagonal (a, b);
      RemoveVertex (p, &v);
    }

    v = b;
  } while (3 < PolygonSize (p));

  return EXIT_SUCCESS;
}
