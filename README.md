# ComputationalGeometry

[Computational Geometry](http://en.wikipedia.org/wiki/Computational_geometry) has to do with the study of algorithms for solving geometrical problems. Concerning this field, this repository is an attempt to provide a codebase able to support the implementation of some of its algorithms.

## Codebase

### Representation of 2D points with integer coordinates

See `src/point.h`.

### Polygon manipulation library

See `src/polygon.h`.

## Applications

### Polygon triangulation

Given is the **counterclockwise** sequence of vertices (one per line) that describe a simple polygon. Each vertex is represented by its coordinates. For instance (cf. `eg/i.18` from [Ccode2.tar.gz] (http://cs.smith.edu/~orourke/CGCode/SecondEdition/Ccode2.tar.gz)):

    0	0
    10	7
    12	3
    20	8
    13	17
    10	12
    12	14
    14	9
    8	10
    6	14
    10	15
    7	18
    0	16
    1	13
    3	15
    5	8
    -2	9
     5	5

Output `n-3` (`n` being the number of vertices) *diagonals* (line segments between two vertices) that witness a triangulation for such polygon. For instance:

    5 5 10 7
    10 7 20 8
    13 17 12 14
    13 17 14 9
    6 14 7 18
    0 16 3 15
    5 8 5 5
    5 8 10 7
    5 8 20 8
    20 8 14 9
    7 18 3 15
    5 8 14 9
    5 8 8 10
    5 8 6 14
    6 14 3 15

![o.18](/doc/o.18.png "Screenshot")

#### O(n^3) solution

See `app/tri3.c`. Usage example:
    
	./tri3 < ../eg/i.18

#### O(n^2) solution

See `app/tri2.c`. Usage example:

    ./tri2 < ../eg/i.18

## References

  - Computational Geometry in C (2nd ed), Joseph O'Rourke.
