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

    Vector3 location = Vector3(0);
    Vector3 rotation = Vector3(0);
    Vector3 scale    = Vector3(1);

    bool bIsSphere = false;
    E_MeshType type = E_MeshType::E_EMPTY;

    unsigned int textureID = 0;

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
        glTranslatef(location.x, location.y, location.z);
        glScalef(scale.x, scale.y, scale.z);
        glRotatef(rotation.x, 1, 0, 0);
        glRotatef(rotation.y, 0, 1, 0);
        glRotatef(rotation.z, 0, 0, 1);
    }
    
    void setTexture(GLuint id)
    {
        glBindTexture(GL_TEXTURE_2D, id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

        if (id == 0)
        {
            float pixels[] = {
                0.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 0.0f
            };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels); 
        }
        if (id == 1)
        {
            float pixels[] = {
                1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,   1.0f, 0.0f, 0.0f
            };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels); 
        }
        if (id == 2)
        {
            float pixels[] = {
                0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 1.0f,
                1.0f, 1.0f, 1.0f,   0.0f, 1.0f, 0.0f
            };
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, pixels); 
        }
    }

    void draw()
    {
        //if (type == E_MeshType::E_CUBE)
        
            GLuint texture[3];
            glEnable(GL_TEXTURE_2D);
            glGenTextures(1, texture);
            //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            setTexture(textureID);
            glColor3f(1, 1, 1);

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

