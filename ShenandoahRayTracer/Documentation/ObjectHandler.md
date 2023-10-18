# ObjectHandler
The ObjectHandler class is used to encapsulate the geometry and UV data of any object.  This allows for the renderer
to have multiple distinct objects, each with their own transform, present within one scene and having a consistent
method of accessing their data easily.

## High-Level View
In order to properly represent objects, we need to represent a few distinct things:
 - Vertices
 - UVs
 - Triangles
 - Triangle UVs

Firstly, vertices: vertices are, simply, points in 3D space.  Within the
ObjectHandler class, we represent this using an array.  While a class 
could have been used, these tend to be slower and take too much memory.  
Another option would have been a std::vector, and this is preferrable 
except for the fact that these are not necessarily GPU-compatible.
For these reasons, we use dynamic arrays and handle them using the 
constructors and destructors of the ObjectHandler, and perform vector operations on them using the static methods of the Vector3 class.

UVs are stored separately from vertices since they are also stored 
separately within .obj files, and the next step is to load .obj files 
into ObjectHandler.  This allows the same vertice in 3D space to have 
multiple different UV values for individual faces.  UVs are stored as an 
array of floating point values, with two values per UV.

Triangles are stored as an integer array representing indices within the 
vertices array.  This allows for vertices to be used multiple times for 
different triangles, which occurs extremely often in polygonal meshes.  
Doing this makes the program significantly more memory efficient.

Triangle UVs are similar to the triangles themselves in that they are an 
integer array representing indices within the UVs array, but the main 
difference is that each indice represents the UV of a specific vertice 
within the same triangle in the Triangles array.  For example, the first 
three numbers in the triangles array represent the vertices in the 
triangle *T*, while the same three numbers in the triangle uvs array 
represents the UV values for the same triangle *T*.

## How To Use
ObjectHandlers should be used to represent any geometry that is intended to move as one singular unit.  For example, characters, props, etc.  It is not, however, intended to represent an entire scene: a scene would best be represented currently with a vector of ObjectHandlers.