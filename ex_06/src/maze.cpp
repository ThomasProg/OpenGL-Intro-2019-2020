#include "maze.h"

#include "mesh.h"

void Construct::maze(Mesh &mesh)
{
    // Vector3 mesh;
    Vector3 a (1.f, 0.f, 0.f);
    Vector3 b (0.f, 0.f, 0.f);
    Vector3 c (0.f, 0.f, 1.f);
    Vector3 d (1.f, 0.f, 1.f);
    mesh.addQuad(a, b, c, d);
}
 
int positiveModulo(int n, int modulo) //true mathematic version 
{
    n %= modulo;
    if (n < 0)
        n += modulo;
    return n;
}