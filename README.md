ComputationalGeometry
=====================
March 2013, Xavier Pinho <pg22577@alunos.uminho.pt>.

Libraries
---------

### Representation of 2D points with integer coordinates

See `src/point.h`.

### Polygon manipulation library

See `src/polygon.h`.

Applications
------------

### Polygon triangulation in O(n^2)

See `src/triangulate.c`. For a usage example, try:

    ./triangulate < ../eg/i.18 > o.18.ps

![o.18.ps](/doc/o.18.png "Screenshot")

(`eg/i.18` was copied from [Ccode2.tar.gz] (http://cs.smith.edu/~orourke/CGCode/SecondEdition/Ccode2.tar.gz))

References
----------

  - Computational Geometry in C (2nd ed), Joseph O'Rourke.
