#include "SP3.h"

SP3::SP3()
{

}

SP3::~SP3()
{

}

void SP3::Init()
{
	SceneBase::Init();
}

void SP3::Update(double dt)
{
	SceneBase::Update(dt);
}

void SP3::Render()
{
	SceneBase::Render();
	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0.f, m_screenWidth, 0.f, m_screenHeight, -10.f, 10.f);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera->position.x, camera->position.y, camera->position.z,
		camera->target.x, camera->target.y, camera->target.z,
		camera->up.x, camera->up.y, camera->up.z
		);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
}

void SP3::Exit()
{
	SceneBase::Exit();
}

// Renders