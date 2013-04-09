/*
  giftWrap.c
  2013-04-08 pg22576@alunos.uminho.pt

  Purpose:
  - Calculate polygon convex hull using gift wrapping algorithm.

  Warnings:
  - Concerning the meta information associated with each vertex,
    it is assumed that sizeof (void *) == sizeof (int).

  Reference:
  - Computational Geometry in C (2nd)
    Joseph O'Rourke
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
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


double TwoVectorAngle (PolygonVertex a, PolygonVertex b, PolygonVertex c) {
  struct Point aP, bP, cP;
  double v1, v2;

  VertexPoint(a, &aP);
  VertexPoint(b, &bP);
  VertexPoint(c, &cP);
  v1 = (double)((aP.x - bP.x) + (aP.y - bP.y));
  v2 = (double)((cP.x - bP.x) + (cP.y - bP.y));
  return atan2(v1,v2);
}


PolygonVertex LowestPoint (Polygon p) {
  PolygonVertex i = SomeVertex (p);
  PolygonVertex v = i;
  PolygonVertex lm = i;
  PolygonVertex a;
  struct Point ptLM, pt;

  VertexPoint (v, &pt);
  VertexPoint (v, &ptLM);

  do {
    AdjacentVertices (v, &a, &v);
    VertexPoint (v, &pt);
    
    if (pt.y < ptLM.y) lm = v;
  } while (v != i);
  return lm;
}


int main (int argc, char ** argv) {
  Polygon p = ReadPolygonFile ();
  PolygonVertex a;
  struct Point lm;

#ifdef PSOUTPUT
  fprintf (stdout, "0.1 setlinewidth\n0 0 1 setrgbcolor\n");
  PrintPolygon (p);
  fprintf (stdout, "0.1 setlinewidth\n1 0 0 setrgbcolor\n");
#endif

  a = LowestPoint (p);
  VertexPoint (a, &lm);
  printf("Lowest Point (y axis): %d %d\n",lm.x, lm.y);

  PolygonVertex b, c ;
  AdjacentVertices(a, &b, &c);
  double testAngle = TwoVectorAngle (b, a, c);
  printf("Angle: %f\n", testAngle);

  return EXIT_SUCCESS;
}
