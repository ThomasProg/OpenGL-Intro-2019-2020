#include "cube.h"
#include "mesh.h"

void Construct::cube(Mesh& mesh)
{
    //if (mesh.drawMode != GL_TRIANGLE_FAN)
    if (mesh.bShowEdges)
        glBegin(GL_LINE_LOOP);
    else 
        glBegin(GL_TRIANGLES);

    for (int i = -1; i < 2; i += 2)
    {
        mesh.addQuad(
            Vector3(i, -1, -1), 
            Vector3(i, -1, 1), 
            Vector3(i, 1, 1),
            Vector3(i, 1, -1));

        mesh.addQuad(
            Vector3(-1, i, -1), 
            Vector3(-1, i, 1), 
            Vector3(1, i, 1),
            Vector3(1, i, -1));

        mesh.addQuad(
            Vector3(-1, -1, i), 
            Vector3(-1, 1, i), 
            Vector3(1, 1, i),
            Vector3(1, -1, i));
    }

    glEnd();
}