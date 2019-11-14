#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

struct vector3D
{
	float x, y, z;
    vector3D() {}
	vector3D(float v) : x(v), y(v), z(v) {}
	vector3D(float ix, float iy, float iz) : x(ix), y(iy), z(iz) {}
	vector3D operator +(const vector3D &other) const { return vector3D(x + other.x, y + other.y, z + other.z); }
	vector3D operator -(const vector3D &other) const { return vector3D(x - other.x, y - other.y, z - other.z); }
	vector3D operator *(const vector3D &other) const { return vector3D(x * other.x, y * other.y, z * other.z); }
	vector3D operator /(const vector3D &other) const { return vector3D(x / other.x, y / other.y, z / other.z); }

	vector3D operator /(float f) const { return vector3D(x / f, y / f, z / f); }
};

struct Vector3Int
{
    int x, y, z;
    Vector3Int(int ix, int iy, int iz) : x(ix), y(iy), z(iz) {}
	Vector3Int(float ix, float iy, float iz) : x(floor(ix)), y(floor(iy)), z(floor(iz)) {}
	Vector3Int(vector3D v) : x(floor(v.x)), y(floor(v.y)), z(floor(v.z)) {}

    bool operator!=(const Vector3Int& b) const
    {
        return x != b.x || y != b.y || z != b.z;
    }

    bool operator==(const Vector3Int& b) const
    {
        return x == b.x && y == b.y && z == b.z;
    }    

    Vector3Int operator%(const int& b) const
    {
        return Vector3Int(x % b, y % b, z % b);
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
    vector3D location = vector3D(0);
    vector3D rotation = vector3D(0);
    vector3D scale    = vector3D(1);

	//transform openGL matrix
	// void use()
	// {
	// 	glRotatef(rotation.x, 1, 0, 0);
	// 	glRotatef(rotation.y, 0, 1, 0);
	// 	glRotatef(rotation.z, 0, 0, 1);
	// 	glTranslatef(location.x, location.y, location.z);
	// 	glScalef(scale.x, scale.y, scale.z);
	// }
};

#endif