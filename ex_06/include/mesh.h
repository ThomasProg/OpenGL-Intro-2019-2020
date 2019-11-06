#ifndef _MESH_H_
#define _MESH_H_

#include "macros.h"
#include "transform.h"

enum class E_MeshType : unsigned int
{
    E_EMPTY,
    E_CUBE,
    E_SPHERE
};

struct Mesh
{
    bool bDraw = true;
	std::vector<Vector3> vertices;
	std::vector<unsigned int> triangles;

    //GLenum drawMode = GL_TRIANGLE_FAN;
    bool bShowEdges = false;

    S_Transform transform;

    bool bIsSphere = false;
    E_MeshType type = E_MeshType::E_EMPTY;

    Mesh() {}

    ~Mesh() {}

    void set(E_MeshType type);

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
        addTriangle(a, b, c);

        addTriangle(a, c, d);
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

    void useTransform()
    {
        transform.use();
    }
    
    void draw()
    {
        //if (type == E_MeshType::E_CUBE)
        
            GLuint texture;
            glEnable(GL_TEXTURE_2D);
            glGenTextures(1, &texture);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

            float pixels[] = {
                0.3f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 0.3f, 0.0f, 0.0f,
                1.0f, 1.0f, 1.0f,   0.0f, 0.3f, 0.0f, 0.3f, 0.0f, 0.0f,
                1.0f, 1.0f, 1.0f,   0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 3.0f,
            };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 3, 3, 0, GL_RGB, GL_FLOAT, pixels);
        

        if (bShowEdges)
            glBegin(GL_LINE_LOOP);
        else 
            glBegin(GL_TRIANGLES);
            
        Vector3 p1 = {0.f, 0.f, 0.f};
        if (type != E_MeshType::E_CUBE)
        for (unsigned int i = 0; i < triangles.size(); i+=3)
        {
            p1 = vertices.at(triangles.at(i));
            //color(p1.x, p1.y, p1.z);
            glTexCoord2d(0, 0);
            glVertex3d(p1.x, p1.y, p1.z);
            
            p1 = vertices.at(triangles.at(i+1));
            //color(p1.x, p1.y, p1.z);
            glTexCoord2d(0, 1);
            glVertex3d(p1.x, p1.y, p1.z);

            p1 = vertices.at(triangles.at(i+2));
            //color(p1.x, p1.y, p1.z);
            glTexCoord2d(1, 0);
            glVertex3d(p1.x, p1.y, p1.z);
        }
        else 
            for (unsigned int i = 0; i < triangles.size(); i+=6)
            {
                p1 = vertices.at(triangles.at(i));
                //color(p1.x, p1.y, p1.z);
                glTexCoord2d(0, 1);
                glVertex3d(p1.x, p1.y, p1.z);
                
                p1 = vertices.at(triangles.at(i+1));
                //color(p1.x, p1.y, p1.z);
                glTexCoord2d(0, 0);
                glVertex3d(p1.x, p1.y, p1.z);

                p1 = vertices.at(triangles.at(i+2));
                //color(p1.x, p1.y, p1.z);
                glTexCoord2d(1, 0);
                glVertex3d(p1.x, p1.y, p1.z);



                p1 = vertices.at(triangles.at(i+3));
                //color(p1.x, p1.y, p1.z);
                glTexCoord2d(0, 1);
                glVertex3d(p1.x, p1.y, p1.z);
                
                p1 = vertices.at(triangles.at(i+4));
                //color(p1.x, p1.y, p1.z);
                glTexCoord2d(1, 0);
                glVertex3d(p1.x, p1.y, p1.z);

                p1 = vertices.at(triangles.at(i+5));
                //color(p1.x, p1.y, p1.z);
                glTexCoord2d(1, 1);
                glVertex3d(p1.x, p1.y, p1.z);
            }

        glEnd();

        //if (type == E_MeshType::E_CUBE)
        {
            glDisable(GL_TEXTURE_2D);
        }
    }
};

#endif

