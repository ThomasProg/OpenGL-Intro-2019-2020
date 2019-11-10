#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "macros.h"
#include "mesh.h"

//meridians = horizontalRotation subUnits
//parallels = verticalRotation subUnits
void UVSphere(unsigned int meridians, unsigned int parallels, Mesh &mesh)
{
    mesh.vertices.reserve(2 + meridians * (parallels - 1)); 
    mesh.triangles.reserve(2 * (meridians + 1) * (parallels - 1));

    {
        unsigned int a, b;
        for (unsigned int i = 0; i < meridians; ++i)
        {
            //pole 1
            a = i + 1;
            b = (i + 1) % meridians + 1;
            mesh.addTriangle(0, b, a);
        }
    }

	mesh.vertices.emplace_back(0.0f, 1.f, 0.0f);

    {
        double polar;
        double sinVertical;
        double cosVertical;
        unsigned int aStart;
        unsigned int bStart;
        double azimuth;
        double sinHorizontal;
        double cosHorizontal;
        double x;
        double y;
        double z;
        unsigned int a;
        unsigned int a1;
        unsigned int b;
        unsigned int b1;

        for (unsigned int j = 0; j < parallels - 1; ++j)
        {
            //optimization : outside of the last loop
            polar = M_PI * double(j+1) / double(parallels);
            sinVertical = std::sin(polar);
            cosVertical = std::cos(polar);

            aStart = j * meridians + 1;
            bStart = (j + 1) * meridians + 1;
            for (unsigned int i = 0; i < meridians; ++i)
            {
                azimuth = 2.0 * M_PI * double(i) / double(meridians);
                sinHorizontal = std::sin(azimuth);
                cosHorizontal = std::cos(azimuth);

                //any point is the combination of 2 angles
                x = sinVertical * cosHorizontal;
                y = cosVertical;
                z = sinVertical * sinHorizontal;
                //add vertice location
                mesh.vertices.emplace_back(x, y, z);

                if (j < parallels - 2)
                {
                    //sphere body triangle indices
                    a = aStart + i;
                    a1 = aStart + (i + 1) % meridians;
                    b = bStart + i;
                    b1 = bStart + (i + 1) % meridians;
                    mesh.addQuad(a, a1, b1, b);
                }
            }
        }
    }

    mesh.vertices.emplace_back(0.0f, -1.f, 0.0f);

    {
        unsigned int a;
        unsigned int b;

        //sphere poles triangle indices
        for (unsigned int i = 0; i < meridians; ++i)
        {
            //pole 2
            a = i + meridians * (parallels - 2) + 1;
            b = (i + 1) % meridians + meridians * (parallels - 2) + 1;
            mesh.addTriangle(mesh.vertices.size() - 1, a, b);
        }
    }
}

#endif