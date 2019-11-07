#include "cube.h"
#include "mesh.h"

void Construct::cube(Mesh& mesh)
{
    //if (mesh.drawMode != GL_TRIANGLE_FAN)
    // if (mesh.bShowEdges)
    //     glBegin(GL_LINE_LOOP);
    // else 
    //     glBegin(GL_TRIANGLES);

    for (float i = -0.5; i < 1; i++)
    {
        mesh.addQuad(
            Vector3(i, -0.5, -0.5), 
            Vector3(i, -0.5, 0.5), 
            Vector3(i, 0.5, 0.5),
            Vector3(i, 0.5, -0.5));

        mesh.addQuad(
            Vector3(-0.5, i, -0.5), 
            Vector3(-0.5, i, 0.5), 
            Vector3(0.5, i, 0.5),
            Vector3(0.5, i, -0.5));

        mesh.addQuad(
            Vector3(-0.5, -0.5, i), 
            Vector3(-0.5, 0.5, i), 
            Vector3(0.5, 0.5, i),
            Vector3(0.5, -0.5, i));
    }

    //glEnd();
}