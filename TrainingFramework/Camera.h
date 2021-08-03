#pragma once

#include <GLES2/gl2.h>
#include "../Utilities/Math.h"

class Camera 
{
private:
	Vector3 m_Position;
	Vector3 m_Target;
	Vector3 m_VectorUp;
	Vector3 m_XAxis, m_YAxis, m_ZAxis;
	float m_fMovingSpeed, m_fRotaionSpped;
	Matrix m_ViewMatrix, m_SkyViewMatrix;
	Matrix m_ProjectionMatrix;
	float m_RotVerticalCheck;
	bool m_isNewView, m_isNewSkyView;

	Matrix GetWorldMatrix();
	GLfloat GetRadian(GLfloat degree);
	Vector3 GetXAxis();
	Vector3 GetYAxis();
	Vector3 GetZAxis();
public:
	/*
	bool m_isMoveLeft, m_isMoveRight;
	bool m_isMoveForward, m_isMoveBackward;
	bool m_isRotUp, m_isRotDown;
	bool m_isRotRight, m_isRotLeft;
	*/

	Camera(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane, float fMovingSpeed, float fRotationSpeed);
	~Camera();
	
	Vector3 GetPosition();
	Matrix GetViewMatrix();
	Matrix GetSkyViewMatrix();
	Matrix GetProjectionMatrix();

	void Update(float frameTime);
	void MoveLeft(float frameTime);
	void MoveRight(float frameTime);
	void MoveForward(float frameTime);
	void MoveBackward(float frameTime);
	void MoveUp(float frameTime);
	void MoveDown(float frameTime);
	void RotationLeft(float frameTime);
	void RotationRight(float frameTime);
	void RotationUp(float frameTime);
	void RotationDown(float frameTime);
};