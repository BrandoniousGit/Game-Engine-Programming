#include <scripts/Scripts.h>

void CameraScript::OnInitialize()
{
	//transform->SetRotation(vec3(-90, 0, 0));
	offset = vec3(0, 5, 0);
	player = getCore->GetEntityByName("Maxwell");
	ySens = 0.6f;
	xSens = 0.4f;
}

void CameraScript::OnTick()
{
	playerTransform = player->GetTransform()->GetPosition();
	transform->SetPosition(vec3(playerTransform + offset));
	if (input->mouseMotion)
	{
		input->mouseMotion = false;
		transform->AddRotation(vec3(-input->GetMousePos().y * ySens, -input->GetMousePos().x * xSens, 0));
	}

	if (transform->GetRotation().x >= 80)
	{
		transform->SetRotation(vec3(80, transform->GetRotation().y, transform->GetRotation().z));
	}
	if (transform->GetRotation().x <= 0)
	{
		transform->SetRotation(vec3(0, transform->GetRotation().y, transform->GetRotation().z));
	}

	if (input->GetKey(Keys::W))
	{
		transform->SetPosition(vec3(-0.2f, 0.0f, 0.0f));
	}
	if (input->GetKey(Keys::S))
	{
		transform->SetPosition(vec3(0.2f, 0.0f, 0.0f));
	}
	if (input->GetKey(Keys::A))
	{
		transform->SetPosition(vec3(-0.2f, 0.0f, 0.0f));
	}
	if (input->GetKey(Keys::D))
	{
		transform->SetPosition(vec3(0.2f, 0.0f, 0.0f));
	}
}