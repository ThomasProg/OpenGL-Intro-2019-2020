#ifndef _MESH_H_
#define _MESH_H_

#include <functional>

#include "macros.h"
#include "transform.h"

enum class E_MeshType : char
{
    E_EMPTY,
    E_CUBE,
    E_SPHERE,
    E_MAZE,
};

enum class E_VerticesType : char
{
    E_LINES,
    E_TRIANGLES,
    E_QUAD,
};

struct Mesh
{
private:
	void addQuad_triVersion(Vector3 a, Vector3 b, Vector3 c, Vector3 d)
	{
        addTriangle(a, b, c);

        addTriangle(a, c, d);
	}
	void addQuad_quadVersion(Vector3 a, Vector3 b, Vector3 c, Vector3 d)
	{
        triangles.emplace_back(vertices.size());
		vertices.emplace_back(a);
        triangles.emplace_back(vertices.size());
		vertices.emplace_back(b);
        triangles.emplace_back(vertices.size());
		vertices.emplace_back(c);
        triangles.emplace_back(vertices.size());
		vertices.emplace_back(d);
	}

public:
    bool bDraw = true;
	std::vector<Vector3> vertices;
	std::vector<unsigned int> triangles; //indices
    E_VerticesType typeOfVerticies = E_VerticesType::E_TRIANGLES;

    bool bShowEdges = false;

    S_Transform transform;

    bool bIsSphere = false;
    E_MeshType type = E_MeshType::E_EMPTY;

    Mesh() {}

    ~Mesh() {}

    void setMesh(E_MeshType type);

	void addTriangle(unsigned int a, unsigned int b, unsigned int c)
	{
		triangles.emplace_back(a);
		triangles.emplace_back(b);
		triangles.emplace_back(c);
	}

	void addTriangle(Vector3 a, Vector3 b, Vector3 c)
	{
        triangles.emplace_back(vertices.size());
		vertices.emplace_back(a);
        triangles.emplace_back(vertices.size());
		vertices.emplace_back(b);
        triangles.emplace_back(vertices.size());
		vertices.emplace_back(c);
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

	void addQuad(Vector3 a, Vector3 b, Vector3 c, Vector3 d)
	{
        switch (typeOfVerticies)
        {
            case E_VerticesType::E_TRIANGLES :
                addQuad_triVersion(a, b, c, d);
                break;

            case E_VerticesType::E_QUAD :
                addQuad_quadVersion(a, b, c, d);
                break;
            default:;
        }
	}

    void color(float x, float y, float z)
    {
            glColor3f((z + x)/40.f, (z + x)/40.f, (z + x)/40.f);
        if (bDraw)
        {
            // x=sin(x*PI + 14) + 1;
            // y=sin(y*PI + 3) + 1;
            // z=sin(z*PI + 60) + 1;
            // glColor3f(x/2, y/2, z/2);


        }
    }

    void useTransform()
    {
        transform.use();
    }
    
    void draw_triVersion()
    {
        if (bShowEdges)
            glBegin(GL_LINE_LOOP);
        else 
            glBegin(GL_TRIANGLES);
            
        Vector3 p1 = {0.f, 0.f, 0.f};
        if (type != E_MeshType::E_CUBE)
        for (unsigned int i = 0; i < triangles.size(); i+=3)
        {
            p1 = vertices.at(triangles.at(i));
            glTexCoord2d(0, 0);
            glVertex3d(p1.x, p1.y, p1.z);
            
            p1 = vertices.at(triangles.at(i+1));
            glTexCoord2d(0, 1);
            glVertex3d(p1.x, p1.y, p1.z);

            p1 = vertices.at(triangles.at(i+2));
            glTexCoord2d(1, 0);
            glVertex3d(p1.x, p1.y, p1.z);
        }
        else 
            for (unsigned int i = 0; i < triangles.size(); i+=6)
            {
                p1 = vertices.at(triangles.at(i));
                glTexCoord2d(0, 1);
                glVertex3d(p1.x, p1.y, p1.z);
                
                p1 = vertices.at(triangles.at(i+1));
                glTexCoord2d(0, 0);
                glVertex3d(p1.x, p1.y, p1.z);

                p1 = vertices.at(triangles.at(i+2));
                glTexCoord2d(1, 0);
                glVertex3d(p1.x, p1.y, p1.z);


                p1 = vertices.at(triangles.at(i+3));
                glTexCoord2d(0, 1);
                glVertex3d(p1.x, p1.y, p1.z);
                
                p1 = vertices.at(triangles.at(i+4));
                glTexCoord2d(1, 0);
                glVertex3d(p1.x, p1.y, p1.z);

                p1 = vertices.at(triangles.at(i+5));
                glTexCoord2d(1, 1);
                glVertex3d(p1.x, p1.y, p1.z);
            }

        glEnd();
    }

    void draw_quadVersion();
    
    void draw()
    {
        switch (typeOfVerticies)
        {
            case E_VerticesType::E_TRIANGLES :
                draw_triVersion();
                break;

            case E_VerticesType::E_QUAD :
                draw_quadVersion();
                break;
            default:;
        }
    }
};

#endif
