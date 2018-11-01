#include<stdlib.h>
#include<glut.h>
#include<Windows.h>
#include"support.h"
using namespace std;
class camera3D
{
private:
	point3D eye, look;
	vector3D u, v, n, up;
	float viewAngle, aspect, nearDist, farDist;
public:
	void setModelViewMatrix()
	{
		float m[16];
		vector3D vec(-eye.x, -eye.y, -eye.z);
		m[0] = u.dx; m[4] = u.dy; m[8] = u.dz;  m[12] = vec.dot(u);
		m[1] = v.dx; m[5] = v.dy; m[9] = v.dz;  m[13] = vec.dot(v);
		m[2] = n.dx; m[6] = n.dy; m[10] = n.dz;  m[14] = vec.dot(n);
		m[3] = 0;    m[7] = 0;    m[11] = 0;     m[15] = 1;
		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(m);
	}

	void set(point3D eye, point3D look, vector3D up)
	{
		this->eye = eye;
		this->look = look;
		this->up = up;

		n = eye.sub(look);
		u = up.cross(n);
		n.normalize();
		u.normalize();
		v = n.cross(u);
		v.normalize();
		setModelViewMatrix();
	}
	void setShape(float viewAngle, float aspect, float nearDist, float farDist)
	{
		this->viewAngle = viewAngle;
		this->aspect = aspect;
		this->nearDist = nearDist;
		this->farDist = farDist;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(viewAngle, aspect, nearDist, farDist);
	}
	/*void roll(float angle)
	{
	float pi = 3.14159265;
	float cs = cos(pi/180*angle);
	float sn = sin(pi/180*angle);
	vector3D t=u;
	u.dx = cs*t.dx - sn*v.dx;
	u.dy = cs*t.dy - sn*v.dy;
	u.dz = cs*t.dz - sn*v.dz;
	v.dx = sn*t.dx + cs*v.dx;
	v.dy = sn*t.dy + cs*v.dy;
	v.dz = sn*t.dz + cs*v.dz;
	setModelViewMatrix();
	}
	void pitch(float angle)
	{
	float pi = 3.14159265;
	float cs = cos(pi / 180 * angle);
	float sn = sin(pi / 180 * angle);
	vector3D t = v;
	v.dx = cs*t.dx - sn*n.dx;
	v.dy = cs*t.dy - sn*n.dy;
	v.dz = cs*t.dz - sn*n.dz;
	n.dx = sn*t.dx + cs*n.dx;
	n.dy = sn*t.dy + cs*n.dy;
	n.dz = sn*t.dz + cs*n.dz;
	setModelViewMatrix();
	}
	void yaw(float angle)
	{
	float pi = 3.14159265;
	float cs = cos(pi / 180 * angle);
	float sn = sin(pi / 180 * angle);
	vector3D t = u;
	u.dx = cs*t.dx - sn*n.dx;
	u.dy = cs*t.dy - sn*n.dy;
	u.dz = cs*t.dz - sn*n.dz;
	n.dx = sn*t.dx + cs*n.dx;
	n.dy = sn*t.dy + cs*n.dy;
	n.dz = sn*t.dz + cs*n.dz;
	setModelViewMatrix();
	}
	void move(float delU, float delV, float delN)
	{
	eye.x += delU*u.dx + delV*v.dx + delN*n.dx;
	eye.y += delU*u.dy + delV*v.dy + delN*n.dy;
	eye.z += delU*u.dz + delV*v.dz + delN*n.dz;
	look.x += delU*u.dx + delV*v.dx + delN*n.dx;
	look.y += delU*u.dy + delV*v.dy + delN*n.dy;
	look.z += delU*u.dz + delV*v.dz + delN*n.dz;
	setModelViewMatrix();
	}*/
};
class stereoCam
{
private:
	point3D eye, look;
	vector3D u, v, n, up;
	camera3D leftCam, rightCam;
	float viewAngle, aspect, nearDist, farDist,eyeDistance,lookDist;
	void setCameras()
	{
		vector3D factor=u; factor.multiply(eyeDistance / 2);
		point3D rightEye(eye); rightEye = rightEye.add(factor);
		rightCam.set(rightEye, look, v); 
		factor.multiply(-1);
		point3D leftEye(eye); leftEye = leftEye.add(factor);
		leftCam.set(leftEye, look, v);
	}
	void setLook()
	{
		vector3D temp = n; temp.multiply(-lookDist);
		look = eye;
		look = look.add(temp);
	}
public:
	void set(point3D eye, point3D look, vector3D up,float eyeDistance)
	{
		this->eye = eye;
		this->look = look;
		this->up = up;
		this->eyeDistance = eyeDistance;
		n = eye.sub(look);
		u = up.cross(n);
		n.normalize();
		u.normalize();
		v = n.cross(u);
		v.normalize();
		lookDist = sqrt(pow(eye.x - look.x, 2) + pow(eye.y - look.y, 2) + pow(eye.z - look.z, 2));
		setCameras();
	}
	void setShape(float viewAngle, float aspect, float nearDist, float farDist)
	{
		this->viewAngle = viewAngle;
		this->aspect = aspect;
		this->nearDist = nearDist;
		this->farDist = farDist;
	}
	void roll(float angle)
	{
		float pi = 3.14159265;
		float cs = cos(pi / 180 * angle);
		float sn = sin(pi / 180 * angle);
		vector3D t = u;
		u.dx = cs*t.dx + sn*v.dx;
		u.dy = cs*t.dy + sn*v.dy;
		u.dz = cs*t.dz + sn*v.dz;
		v.dx = -sn*t.dx + cs*v.dx;
		v.dy = -sn*t.dy + cs*v.dy;
		v.dz = -sn*t.dz + cs*v.dz;
		up = v;
		setCameras();
	}
	void pitch(float angle)
	{
		float pi = 3.14159265;
		float cs = cos(pi / 180 * angle);
		float sn = sin(pi / 180 * angle);
		vector3D t = v;
		v.dx = cs*t.dx + sn*n.dx;
		v.dy = cs*t.dy + sn*n.dy;
		v.dz = cs*t.dz + sn*n.dz;
		up = v;
		n.dx = -sn*t.dx + cs*n.dx;
		n.dy = -sn*t.dy + cs*n.dy;
		n.dz = -sn*t.dz + cs*n.dz;
		setLook();
		setCameras();
	}
	void yaw(float angle)
	{
		float pi = 3.14159265;
		float cs = cos(pi / 180 * angle);
		float sn = sin(pi / 180 * angle);
		vector3D t = u;
		u.dx = cs*t.dx + sn*n.dx;
		u.dy = cs*t.dy + sn*n.dy;
		u.dz = cs*t.dz + sn*n.dz;
		n.dx = -sn*t.dx + cs*n.dx;
		n.dy = -sn*t.dy + cs*n.dy;
		n.dz = -sn*t.dz + cs*n.dz;
		setLook();
		setCameras();
	}
	void move(float delU, float delV, float delN)
	{
		eye.x += delU*u.dx + delV*v.dx + delN*n.dx;
		eye.y += delU*u.dy + delV*v.dy + delN*n.dy;
		eye.z += delU*u.dz + delV*v.dz + delN*n.dz;
		look.x += delU*u.dx + delV*v.dx + delN*n.dx;
		look.y += delU*u.dy + delV*v.dy + delN*n.dy;
		look.z += delU*u.dz + delV*v.dz + delN*n.dz;
		setCameras();
	}
	void setViewPortLeft()
	{
		float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		float screenRatio = windowWidth / windowHeight;
		float camPortRatio = aspect * 2;
		if (screenRatio > camPortRatio)
		{
			float percent = camPortRatio / screenRatio;
			percent = (1 - percent) / 2;
			float x = windowWidth*percent;
			glViewport(x, 0, (windowWidth*(1 - percent) - x)/2, windowHeight);
			leftCam.setShape(viewAngle, aspect, nearDist, farDist);
			leftCam.setModelViewMatrix();
		}
		else if (screenRatio < camPortRatio)
		{
			float percent = screenRatio / camPortRatio;
			percent = (1 - percent) / 2;
			float y = windowHeight*percent;
			glViewport(0, y, windowWidth/2, windowHeight*(1 - percent) - y);
			leftCam.setShape(viewAngle, aspect, nearDist, farDist);
			leftCam.setModelViewMatrix();
		}
		else if (screenRatio == camPortRatio)
		{
			glViewport(0, 0, windowWidth/2, windowHeight);
			leftCam.setModelViewMatrix();
		}
	}
	void setViewPortRight()
	{
		float windowWidth = glutGet(GLUT_WINDOW_WIDTH);
		float windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
		float screenRatio = windowWidth / windowHeight;
		float camPortRatio = aspect * 2;
		if (screenRatio > camPortRatio)
		{
			float percent = camPortRatio / screenRatio;
			percent = (1 - percent) / 2;
			float x = windowWidth*percent;
			glViewport(x + (windowWidth*(1 - percent) - x) / 2, 0, (windowWidth*(1 - percent) - x) / 2, windowHeight);
			rightCam.setShape(viewAngle, aspect, nearDist, farDist);
			rightCam.setModelViewMatrix();
		}
		else if (screenRatio < camPortRatio)
		{
			float percent = screenRatio / camPortRatio;
			percent = (1 - percent) / 2;
			float y = windowHeight*percent;
			glViewport(windowWidth / 2, y, windowWidth / 2, windowHeight*(1 - percent) - y);
			rightCam.setShape(viewAngle, aspect, nearDist, farDist);
			rightCam.setModelViewMatrix();
		}
		else if (screenRatio == camPortRatio)
		{
			glViewport(windowWidth / 2, 0, windowWidth / 2, windowHeight);
			rightCam.setModelViewMatrix();
		}
	}

};
