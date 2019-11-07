#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

struct Vector3
{
	double x, y, z;
	Vector3(double v) : x(v), y(v), z(v) {}
	Vector3(double ix, double iy, double iz) : x(ix), y(iy), z(iz) {}
	Vector3 operator +(const Vector3 &other) const { return Vector3(x + other.x, y + other.y, z + other.z); }
	Vector3 operator -(const Vector3 &other) const { return Vector3(x - other.x, y - other.y, z - other.z); }
	Vector3 operator *(const Vector3 &other) const { return Vector3(x * other.x, y * other.y, z * other.z); }
	Vector3 operator /(const Vector3 &other) const { return Vector3(x / other.x, y / other.y, z / other.z); }
};

struct Vector3Int
{
    int x, y, z;
    Vector3Int(int ix, int iy, int iz) : x(ix), y(iy), z(iz) {}
	Vector3Int(double ix, double iy, double iz) : x(floor(ix)), y(floor(iy)), z(floor(iz)) {}
	Vector3Int(Vector3 v) : x(floor(v.x)), y(floor(v.y)), z(floor(v.z)) {}

    bool operator!=(Vector3Int& b)
    {
        return x != b.x || y != b.y || z != b.z;
    }

    bool operator==(Vector3Int& b)
    {
        return x == b.x && y == b.y && z == b.z;
    }    
};

struct vec2
{
	vec2() {}
    double x = 0.f, y = 0.f;
    vec2(double x, double y) : x(x), y(y) {}
    vec2 operator-(const vec2& v)
    {
        return vec2(x-v.x, y - v.y);
    }
    vec2 operator+(const vec2& v)
    {
        return vec2(x+v.x, y + v.y);
    }
    double length()
    {
        return sqrt(pow(x,2) + pow(y,2));
    }
    vec2 unit()
    {
        double len = length();
        if (len == 0)
            return vec2(1,0); 
        else
            return vec2(x/len, y/len);
    }
};

struct S_Transform
{
    Vector3 location = Vector3(0);
    Vector3 rotation = Vector3(0);
    Vector3 scale    = Vector3(1);

	//transform openGL matrix
	void use()
	{
		glRotatef(rotation.x, 1, 0, 0);
		glRotatef(rotation.y, 0, 1, 0);
		glRotatef(rotation.z, 0, 0, 1);
		glTranslatef(location.x, location.y, location.z);
		glScalef(scale.x, scale.y, scale.z);
	}
};

#endif