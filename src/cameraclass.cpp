#include "cameraclass.h"

CameraClass::CameraClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;

	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

}

CameraClass::CameraClass(const CameraClass&)
{
}

CameraClass::~CameraClass()
{
}

void CameraClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
	
}

void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

DirectX::XMFLOAT3 CameraClass::GetPosition()
{
	return DirectX::XMFLOAT3(m_positionX, m_positionY, m_positionZ);
}

DirectX::XMFLOAT3 CameraClass::GetRotation()
{
	return DirectX::XMFLOAT3(m_rotationX, m_rotationY, m_rotationZ);
}

void CameraClass::Render()
{
	DirectX::XMFLOAT3 up, position, lookAt;
	DirectX::XMVECTOR upVector, positionVector, lookAtVector;
	float yaw, pitch, roll;
	DirectX::XMMATRIX rotationMatrix;

	// Setup vector that points upwards
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	upVector = DirectX::XMLoadFloat3(&up);

	// Setup the position of camera in the world and load it into Vector
	position.x = m_positionX;
	position.y = m_positionY;
	position.z = m_positionZ;
	positionVector = XMLoadFloat3(&position);

	// Setup where the camera is looking at by default
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;
	lookAtVector = DirectX::XMLoadFloat3(&lookAt);

	pitch = m_rotationX * 0.0174532925f;
	yaw = m_rotationY * 0.0174532925f;
	roll = m_rotationZ * 0.0174532925f;
	
	// Create the rotation matrix from yaw pitch roll
	rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

	// Transform the lookAt and up vector bt the rotation matrix
	lookAtVector = DirectX::XMVector3TransformCoord(lookAtVector, rotationMatrix);
	upVector = DirectX::XMVector3TransformCoord(upVector, rotationMatrix);

	// Translate the rotate camera position to the location of Viewer;
	lookAtVector = DirectX::XMVectorAdd(positionVector, lookAtVector);

	// Finally create view Matrix from this updated positions
	m_viewMatrix = DirectX::XMMatrixLookAtLH(positionVector, lookAtVector, upVector);

	return;

}

void CameraClass::GetViewMatrix(DirectX::XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
	return;
}
