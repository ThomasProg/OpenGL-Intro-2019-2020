#ifndef _MESH_H_
#define _MESH_H_

#include "macros.h"

struct Vector3
{
	double x, y, z;
	Vector3(double v) : x(v), y(v), z(v) {}
	Vector3(double ix, double iy, double iz) : x(ix), y(iy), z(iz) {}
	Vector3 operator +(const Vector3 &other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
	Vector3 operator -(const Vector3 &other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
	Vector3 operator *(const Vector3 &other) const { return Vector3(x * other.x, y * other.y, z * other.z); }
};

struct Mesh
{
    bool bDraw = true;
	std::vector<Vector3> vertices;
	std::vector<unsigned int> triangles;

    //GLenum drawMode = GL_TRIANGLE_FAN;
    bool showEdges = false;

	void addTriangle(unsigned int a, unsigned int b, unsigned int c)
	{
		triangles.emplace_back(a);
		triangles.emplace_back(b);
		triangles.emplace_back(c);
	}

	void addQuad(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
	{
		triangles.emplace_back(a);
		triangles.emplace_back(b);
		triangles.emplace_back(c);

		triangles.emplace_back(a);
		triangles.emplace_back(c);
		triangles.emplace_back(d);
	}

    void color(float x, float y, float z)
    {
        if (bDraw)
        {
            x=sin(x*PI) + 1;
            y=sin(y*PI) + 1;
            z=sin(z*PI) + 1;
            glColor3f(x/2, y/2, z/2);
        }
    }

    void draw()
    {
        if (showEdges)
            glBegin(GL_TRIANGLE_FAN);
        else
            glBegin(GL_LINE_LOOP);

        Vector3 p1 = {0.f, 0.f, 0.f};
        for (unsigned int i = 0; i < triangles.size(); i+=3)
        {
            p1 = vertices.at(triangles.at(i));
            color(p1.x, p1.y, p1.z);
            glVertex3d(p1.x, p1.y, p1.z);
            
            p1 = vertices.at(triangles.at(i+1));
            color(p1.x, p1.y, p1.z);
            glVertex3d(p1.x, p1.y, p1.z);

            p1 = vertices.at(triangles.at(i+2));
            color(p1.x, p1.y, p1.z);
            glVertex3d(p1.x, p1.y, p1.z);
        }
        glEnd();
    }
};

#endif