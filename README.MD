OFEM or Open FEM is a personal project of mine in my journey of studying FEM for structural engineering. It's basically a practical c++ impelmentation from textbook FEM derivations found in textbooks which are purely mathematical/theoritical.
OFEM doesn't reinvent the wheel. it uses Eigen Mathematics library to for underlying linear algebra calculations, storage of matrices and sparse matrices.
SFML, specifically SF::Graphics is used as a 2D graphics library for some basic drawing and interaction with mesh. This is to avoid getting into the hassle of learning openGL to write a 2D graphics engine from scratch.
Currently I've had time to implement 2D plane-strain 3-noded triangle elements. Mutli-noded plane strain elements, 2D truss and beam elements should be added in the near future as these are fairly simple and I just need the free time to do so.
Future goals include implementing 2D plate/shell elements and possibly non-linear large deformations. Also migrating from SFML to a more mainstream option such as QTwidgets since SFML is not cross platform friendly and feature rich as QT.

usage is OFEM.exe <inputfile.txt>

Input files must be in format of:

<poisson's ration> <modulus of elasticity>
<number of nodes>
<node x cord> <node y cord>
...
<number of elements>
<first node #> <second node #> <third node #>
... 
<number of supports>
<node #> <2 for x constraint, 3 for both x&y constraints>
...
<number of loads>
<node #> <load in x> <load in y>
  
Node numbering must start from 0, i.e. the first node has to have a 0 index.
Sample input files are included the repositery.
