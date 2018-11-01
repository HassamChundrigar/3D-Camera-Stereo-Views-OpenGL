#include<glut.h>
#include<math.h>
using namespace std;
class point3D;
class vector3D
{
public:
	float dx, dy, dz;
	vector3D()
	{
		this->dx = 0;
		this->dy = 0;
		this->dz = 0;
	}
	vector3D(float dx, float dy, float dz)
	{
		this->dx = dx;
		this->dy = dy;
		this->dz = dz;
	}
	// Return magnitude of a vector
	float magnitude()
	{
		float magnitude = powf(dx*dx + dy*dy + dz*dz, 0.5);
		return magnitude;
	}
	// Convert a vector into unit vector
	void normalize()
	{
		float mag = magnitude();
		dx /= mag;
		dy /= mag;
		dz /= mag;
	}
	// Add two vectors
	void add(vector3D v)
	{
		this->dx += v.dx;
		this->dy += v.dy;
		this->dz += v.dz;
	}
	// Add vector and point, returns point
	point3D add(point3D P);

	// Subtract two vectors
	void subtract(vector3D v)
	{
		this->dx -= v.dx;
		this->dy -= v.dy;
		this->dz -= v.dz;
	}
	// Subtract point from vector, returns point
	point3D subtract(point3D P);

	// multiply vector by scalar
	void multiply(float scalar)
	{
		this->dx *= scalar;
		this->dy *= scalar;
		this->dz *= scalar;
	}
	// multiply vector by scalar
	void divide(float scalar)
	{
		this->dx /= scalar;
		this->dy /= scalar;
		this->dz /= scalar;
	}
	//Return Dot product of two vectors
	float dot(vector3D v)
	{
		float dot = dx*v.dx + dy*v.dy + dz*v.dz;
		return dot;
	}
	//Return Cross product of two vectors, gives new vector
	vector3D cross(vector3D v)
	{
		vector3D temp;
		temp.dx = dy*v.dz - v.dy*dz;
		temp.dy = -(dx*v.dz - dz*v.dx);
		temp.dz = (dx*v.dy - dy*v.dx);
		return temp;
	}
	// Returns angle (degree) between two vectors
	float angleBetween(vector3D v)
	{
		vector3D temp(dx, dy, dz);
		float angle = acos(temp.dot(v) / (temp.magnitude()*v.magnitude()));
		return angle *= 3.14 / 180;
	}
};
class point3D
{
public:
	float x, y, z;
	point3D()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	point3D(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	//Add two points and return vector
	vector3D add(point3D P)
	{
		vector3D temp(this->x + P.x, this->y + P.y, this->z + P.z);
		return temp;
	}
	//add vector in point and return new
	point3D add(vector3D v)
	{
		point3D temp;
		temp.x =x+ v.dx;
		temp.y =y+ v.dy;
		temp.z =z+ v.dz;
		return temp;
	}
	//sub two points and return vector
	vector3D sub(point3D P)
	{
		vector3D temp(this->x - P.x, this->y - P.y, this->z - P.z);
		return temp;
	}
	//add point in vector and return new point
	point3D sub(vector3D v)
	{
		point3D temp;
		temp.x = this->x - v.dx;
		temp.y = this->y - v.dy;
		temp.z = this->z - v.dz;
		return temp;

	}
};


point3D vector3D::add(point3D P)
{
	point3D temp;
	temp.x = dx + P.x;
	temp.y = dy + P.y;
	temp.z = dz + P.z;
	return temp;
}
point3D vector3D::subtract(point3D P)
{
	point3D temp;
	temp.x = dx - P.x;
	temp.y = dy - P.y;
	temp.z = dz - P.z;
	return temp;
}
