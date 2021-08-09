#include "stdafx.h"
#include "define.h"
#include "Camera.h"

GLfloat Camera::GetRadian(GLfloat degree) {
	return degree * PI / 180.0f;
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat nearPlane, GLfloat farPlane, float fMovingSpeed, float fRotationSpeed)
	:m_fMovingSpeed(fMovingSpeed), 
	m_fRotaionSpped(fRotationSpeed), 

	m_RotVerticalCheck(0.0f), 
	
	m_isNewView(true), 
	m_isNewSkyView(true) {

	m_Position.x = posX; m_Position.y = posY; m_Position.z = 5.0f;
	m_Target.x = m_Position.x; m_Target.y = m_Position.y; m_Target.z = m_Position.z - 1.0f; //always start with horizontal view (easier to lock rotation view)
	m_VectorUp.x = 0.0f; m_VectorUp.y = 1.0f; m_VectorUp.z = 0.0f; //always (0, 1, 0)
	m_ZAxis = GetZAxis(); m_XAxis = GetXAxis(); m_YAxis = GetYAxis();
	m_ProjectionMatrix.SetOrthographic(left, right, bottom, top, nearPlane, farPlane);

	m_viewWidth = right - left;
	m_viewHeight = top - bottom;
}

Camera::~Camera() {

}

Vector3 Camera::GetXAxis() {
	return (m_VectorUp.Cross(m_ZAxis)).Normalize();
}

Vector3 Camera::GetYAxis() {
	return (m_ZAxis.Cross(m_XAxis)).Normalize();
}

Vector3 Camera::GetZAxis() {
	return (m_Position - m_Target).Normalize();
}

Matrix Camera::GetWorldMatrix() {
	Matrix worldMatrix;
	worldMatrix.m[0][0] = m_XAxis.x; worldMatrix.m[0][1] = m_XAxis.y; worldMatrix.m[0][2] = m_XAxis.z; worldMatrix.m[0][3] = 0.0f;
	worldMatrix.m[1][0] = m_YAxis.x; worldMatrix.m[1][1] = m_YAxis.y; worldMatrix.m[1][2] = m_YAxis.z; worldMatrix.m[1][3] = 0.0f;
	worldMatrix.m[2][0] = m_ZAxis.x; worldMatrix.m[2][1] = m_ZAxis.y; worldMatrix.m[2][2] = m_ZAxis.z; worldMatrix.m[2][3] = 0.0f;
	worldMatrix.m[3][0] = m_Position.x; worldMatrix.m[3][1] = m_Position.y; worldMatrix.m[3][2] = m_Position.z; worldMatrix.m[3][3] = 1.0f;
	return worldMatrix;
}

Matrix Camera::GetViewMatrix() {
	if (m_isNewView) {
		Matrix viewMatrix;
		viewMatrix.m[0][0] = m_XAxis.x; viewMatrix.m[0][1] = m_YAxis.x; viewMatrix.m[0][2] = m_ZAxis.x; viewMatrix.m[0][3] = 0.0f;
		viewMatrix.m[1][0] = m_XAxis.y; viewMatrix.m[1][1] = m_YAxis.y; viewMatrix.m[1][2] = m_ZAxis.y; viewMatrix.m[1][3] = 0.0f;
		viewMatrix.m[2][0] = m_XAxis.z; viewMatrix.m[2][1] = m_YAxis.z; viewMatrix.m[2][2] = m_ZAxis.z; viewMatrix.m[2][3] = 0.0f;
		viewMatrix.m[3][0] = -m_Position.Dot(m_XAxis); viewMatrix.m[3][1] = -m_Position.Dot(m_YAxis); 
		viewMatrix.m[3][2] = -m_Position.Dot(m_ZAxis); viewMatrix.m[3][3] = 1.0f;
		m_ViewMatrix = viewMatrix;
		m_isNewView = false;
	}
	
	return m_ViewMatrix;
}

Matrix Camera::GetSkyViewMatrix() {
	if (m_isNewSkyView) {
		Matrix viewMatrix;
		viewMatrix.m[0][0] = m_XAxis.x; viewMatrix.m[0][1] = m_YAxis.x; viewMatrix.m[0][2] = m_ZAxis.x; viewMatrix.m[0][3] = 0.0f;
		viewMatrix.m[1][0] = m_XAxis.y; viewMatrix.m[1][1] = m_YAxis.y; viewMatrix.m[1][2] = m_ZAxis.y; viewMatrix.m[1][3] = 0.0f;
		viewMatrix.m[2][0] = m_XAxis.z; viewMatrix.m[2][1] = m_YAxis.z; viewMatrix.m[2][2] = m_ZAxis.z; viewMatrix.m[2][3] = 0.0f;
		viewMatrix.m[3][0] = 0.0f;		viewMatrix.m[3][1] = 0.0f;		viewMatrix.m[3][2] = 0.0f;		viewMatrix.m[3][3] = 1.0f;
		m_SkyViewMatrix = viewMatrix;
		m_isNewSkyView = false;
	}

	return m_SkyViewMatrix;
}

Matrix Camera::GetProjectionMatrix() {
	return m_ProjectionMatrix;
}

Vector3 Camera::GetPosition() {
	return m_Position;
}

Vector2 Camera::GetViewScale()
{
	return Vector2(m_viewWidth,m_viewHeight);
}

void Camera::Update(float frameTime) {
	
}

void Camera::MoveForward(float frameTime) {
	Vector3 deltaMove = -GetZAxis() * frameTime * m_fMovingSpeed;
	m_Position += deltaMove;
	m_Target += deltaMove;
	m_isNewView = true;
}

void Camera::MoveBackward(float frameTime) {
	Vector3 deltaMove = GetZAxis() * frameTime * m_fMovingSpeed;
	m_Position += deltaMove;
	m_Target += deltaMove;
	m_isNewView = true;
}

void Camera::MoveUp(float frameTime)
{
	Vector3 deltaMove = GetYAxis() * frameTime * m_fMovingSpeed;
	m_Position += deltaMove;
	m_Target += deltaMove;
	m_isNewView = true;
}

void Camera::MoveDown(float frameTime)
{
	Vector3 deltaMove = -GetYAxis() * frameTime * m_fMovingSpeed;
	m_Position += deltaMove;
	m_Target += deltaMove;
	m_isNewView = true;
}

void Camera::MoveLeft(float frameTime) {
	Vector3 deltaMove = -GetXAxis() * frameTime * m_fMovingSpeed;
	m_Position += deltaMove;
	m_Target += deltaMove;
	m_isNewView = true;
}

void Camera::MoveRight(float frameTime) {
	Vector3 deltaMove = GetXAxis() * frameTime * m_fMovingSpeed;
	m_Position += deltaMove;
	m_Target += deltaMove;
	m_isNewView = true;
}

void Camera::RotationUp(float frameTime) {
	if (m_RotVerticalCheck + frameTime * m_fRotaionSpped < ROTATION_LOCK) {
		Matrix transform;
		Vector4 localTarget;
		localTarget.x = 0; localTarget.y = 0; localTarget.z = -(m_Position - m_Target).Length(), localTarget.w = 1.0f;
		Vector4 localNewTarget = localTarget * transform.SetRotationX(GetRadian(frameTime * m_fRotaionSpped));
		Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
		m_Target.x = worldNewTarget.x; m_Target.y = worldNewTarget.y; m_Target.z = worldNewTarget.z;
		m_ZAxis = GetZAxis(); m_XAxis = GetXAxis(); m_YAxis = GetYAxis();
		m_isNewView = true;
		m_isNewSkyView = true;
		m_RotVerticalCheck += frameTime * m_fRotaionSpped;
	}
}

void Camera::RotationDown(float frameTime) {
	if (m_RotVerticalCheck - frameTime * m_fRotaionSpped > -ROTATION_LOCK) {
		Matrix transform;
		Vector4 localTarget;
		localTarget.x = 0; localTarget.y = 0; localTarget.z = -(m_Position - m_Target).Length(), localTarget.w = 1.0f;
		Vector4 localNewTarget = localTarget * transform.SetRotationX(GetRadian(-frameTime * m_fRotaionSpped));
		Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
		m_Target.x = worldNewTarget.x; m_Target.y = worldNewTarget.y; m_Target.z = worldNewTarget.z;
		m_ZAxis = GetZAxis(); m_XAxis = GetXAxis(); m_YAxis = GetYAxis();
		m_isNewView = true;
		m_isNewSkyView = true;
		m_RotVerticalCheck -= frameTime * m_fRotaionSpped;
	}
}

void Camera::SetPosition(Vector3 pos)
{

	m_Position = Vector3(pos.x,pos.y,m_Position.z);
	m_Target = Vector3(pos.x, pos.y, m_Target.z);
	m_isNewView = true;

}

void Camera::RotationLeft(float frameTime) {
	Matrix transform;
	Vector4 localTarget = Vector4(0, 0, -(m_Position - m_Target).Length(), 1.0);
	Vector4 localYAxis = Vector4(0, 1, 0, 0);
	localYAxis = localYAxis * m_ViewMatrix;
	Vector4 localNewTarget = localTarget * transform.SetRotationAngleAxis(GetRadian(frameTime * m_fRotaionSpped), localYAxis.x, localYAxis.y, localYAxis.z);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_Target.x = worldNewTarget.x; m_Target.y = worldNewTarget.y; m_Target.z = worldNewTarget.z;
	m_ZAxis = GetZAxis(); m_XAxis = GetXAxis(); m_YAxis = GetYAxis();
	m_isNewView = true;
	m_isNewSkyView = true;
}

void Camera::RotationRight(float frameTime) {
	Matrix transform;
	Vector4 localTarget = Vector4(0, 0, -(m_Position - m_Target).Length(), 1.0);
	Vector4 localYAxis = Vector4(0, 1, 0, 0);
	localYAxis = localYAxis * m_ViewMatrix;
	Vector4 localNewTarget = localTarget * transform.SetRotationAngleAxis(GetRadian(-frameTime * m_fRotaionSpped), localYAxis.x, localYAxis.y, localYAxis.z);
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	m_Target.x = worldNewTarget.x; m_Target.y = worldNewTarget.y; m_Target.z = worldNewTarget.z;
	m_ZAxis = GetZAxis(); m_XAxis = GetXAxis(); m_YAxis = GetYAxis();
	m_isNewView = true;
	m_isNewSkyView = true;
}