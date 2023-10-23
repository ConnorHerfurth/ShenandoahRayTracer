# Hit
The Hit struct is used to represent the result of a ray cast against triangles in the scene.  It includes all the 
relevant information about the hit, including the distance along the ray, the U and V coordinates, the object that 
was hit, and the triangle that was hit on that object.

The Hit class is mostly used to encapsulate the information of the rays traced during the rendering process, but 
can also be used for casting against objects in simulations.

## Public Variables
- bool hit (Default: false) : Whether or not the Hit actually hit anything.  If false, the rest of the data can be considered garbage.
- float t : The distance along the ray that the hit occurred.
- float u : The distance along the U vector for the hit.
- float v : The distance along the V vector for the hit.
- int triangle_index : The index of the triangle that was hit within the ObjectHandler.  Used for calculating color within Materials.
- ObjectHandler* object (Default: nullptr) : The pointer to the object that was hit.

## Methods
- bool IsGreater(Hit h)
  - Checks to see if the hit is greater or less than another.  This is determined by looking at whether a hit occurred (if one has a hit and the other doesn't, then the one with the hit is greater) and if both are equal, then we look at the value of t, with the lower value of t being more significant.