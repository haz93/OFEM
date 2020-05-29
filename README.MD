### Open Finite Element Method: Introduction
OFEM or Open FEM is a personal project of mine in my journey of studying FEM for structural engineering. It's basically a practical c++ implementation from textbook FEM derivations found in textbooks which are purely mathematical/theoritical on their own.
 
OFEM doesn't reinvent the wheel. it uses Eigen library to for underlying linear algebra calculations and sparse matrices implementation.
SFML, specifically SF::Graphics is used as a 2D graphics library for some basic drawing and interaction with mesh. This is to avoid getting into the hassle of learning openGL to write a 2D graphics engine from scratch.
 
Currently I've had time to implement only 2D plane-strain 3-noded triangle elements during COVID19 lockdown. Mutli-noded plane strain elements, 2D truss and beam elements should be added in the near future as these are fairly simple and I just need the free time to do so.
Future goals include implementing 2D plate/shell elements and possibly non-linear large deformations. Also migrating from SFML to a more mainstream option such as QTwidgets since SFML is not cross platform friendly and feature rich as QT.

## Usage
```
OFEM.exe <inputfile> <outputfile>
```
## Input
Input files must be in format of:
```
<poisson's ration> <modulus of elasticity>
<number of nodes>
<node x cord> <node y cord>
<number of elements>
<first node #> <second node #> <third node #>
<number of supports>
<node #> <2 for x constraint, 3 for both x&y constraints>
<number of loads>
<node #> <load in x> <load in y>
```
  
**Node numbering must start from 0, i.e. the first node has to have a 0 index when defining elements**
 
Sample input files are included the repository. As it is obvious from input parameters, OFEM does not include a meshing algorithm. You can draw whatever polygon you'd like analyzed on autocad, export nodes co ordinates and lines starting x and ys and ending x and ys into excel, format them into .node and .poly files and use them as inputs for a meshing tool such as [Triangles](https://www.cs.cmu.edu/~quake/triangle.html)
then use the output .node output and .ele files as input to OFEM after reformatting them.
 
This is obviously as gigantic hassle and will be changed in future releases.
## Output
Output files contains displacement vector. The model displays the original and displaced mesh along with a color contour of element stresses in x-direction. This is for debugging only and you can customize whatever output you want to see written to file by looking into engine.cpp and controlling what output window displays by modifying the call to the display instance. 

## Binary
[Windows x86_64](https://github.com/haz93/OFEM/releases/download/0.1/OFEM-0.1-test.zip)
