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
#include "point.h"
#include "polygon.h"

/* Comment the following line to suppress PostScript output. */
#define PSOUTPUT


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

void PrintLine (const PolygonVertex a, const PolygonVertex b) {
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

void PrintPolygon (const Polygon p) {
  PolygonVertex i = SomeVertex (p);
  PolygonVertex v = i;
  PolygonVertex a, lp;
  PolygonVertexMeta m;
  struct Point pt;

  VertexPoint (v, &pt);

#ifndef PSOUTPUT
  fprintf (stdout, "%d %d\n", pt.x, pt.y);
#else
  fprintf (stdout, ".00 .00 setlinewidth\n0 0 1 setrgbcolor\n");
  fprintf (stdout, "newpath\n");
#endif

  /* Draw Circles around Points or Output Points*/
  do {
    AdjacentVertices (v, &a, &v);
    VertexPoint (v, &pt);

#ifndef PSOUTPUT
    fprintf (stdout, "%d %d\n", pt.x, pt.y);
#else
    fprintf (stdout, "%d\t%d\t1  0  360\tarc\tstroke\n", pt.x, pt.y);
#endif

  } while (v != i);

#ifdef PSOUTPUT
  fprintf (stdout, "closepath\n");
#endif



  /* Draw Hull */
  a = LowestPoint(p);
  lp = a;
  do {
    VertexMeta(a, &m);
    if (m == NULL) v = lp;
    else v = (PolygonVertex) m;
    
    PrintLine(a,v);
    a = m;
  } while (v != lp);



#ifdef PSOUTPUT
  fprintf (stdout, "showpage\n");
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
    fprintf (stderr, "Error: not enough vertices (%d).\n", (int) PolygonSize (plg));
    exit (EXIT_FAILURE);
  }

  return plg;
}



int main (int argc, char ** argv) {
  Polygon p = ReadPolygonFile ();
  PolygonVertex lowestVertex, 
                prevVertex,
                nextVertex, 
                currentVertex,
                dummyVertex;
  Point a, b, c;


  /*Points From prevVertex, currentVertex and nextVertex respectively*/
  a = (Point) malloc(sizeof(struct Point));
  b = (Point) malloc(sizeof(struct Point));
  c = (Point) malloc(sizeof(struct Point));

  lowestVertex = LowestPoint (p);
  VertexPoint (lowestVertex, a);

  /* lowestVertex is the first Hull Vertex*/
  AdjacentVertices(lowestVertex, &dummyVertex, &nextVertex);
  currentVertex = nextVertex;
  AdjacentVertices (nextVertex, &prevVertex, &nextVertex);
  
  /*
   * prevVertex    -> last Known hull Vertex
   * currentVertex -> hull vertex candidate
   * nextVertex    -> next vertex from vertex set
   */

  do {

    /*Finds the next Hull Vertex*/
    while (nextVertex != currentVertex) {
      
      /*Select Points For AreaTriangle Calculation*/
        VertexPoint (prevVertex,    a);
        VertexPoint (currentVertex, b);
        VertexPoint (nextVertex,    c);

	/*If area below 0, Current Vertex is not a Hull Vertex*/
        if (AreaTriangle(a,b,c) < 0) {
            currentVertex = nextVertex;
            AdjacentVertices(currentVertex, &dummyVertex, &nextVertex);
        } else {
        AdjacentVertices(nextVertex, &dummyVertex, &nextVertex);
        }   
    }
    
    /*
     * Use vertex meta to store info about hull vertex
     */
    UpdateVertexMeta(
		     prevVertex, 
		    (PolygonVertexMeta) &currentVertex
		    );
    /* 
     * Select Hull Vertex Found as last hull Vertex found 
     * (prevVertex) and proceed to find next one
     */
    prevVertex = currentVertex;
    AdjacentVertices(prevVertex, &dummyVertex, &currentVertex);
    AdjacentVertices(currentVertex, &dummyVertex, &nextVertex);
  } while ( prevVertex != lowestVertex); 

#ifdef PSOUTPUT
  PrintPolygon (p);
#endif
  
  return EXIT_SUCCESS;
}
