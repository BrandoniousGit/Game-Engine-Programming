#include <scripts/Scripts.h>

void CameraScript::OnInitialize()
{
	//transform->SetRotation(vec3(-90, 0, 0));
	offset = vec3(0, 5, 0);
	player = getCore->GetEntityByName("Maxwell");
	ySens = 0.2f;
	xSens = 0.35f;
	moveSpeed = 0.1f;
}

void CameraScript::OnTick()
{
	playerTransform = player->GetTransform()->GetPosition();
	//transform->SetPosition(vec3(playerTransform + offset));
	if (input->mouseMotion)
	{
		input->mouseMotion = false;
		transform->AddRotation(vec3(-input->GetMousePos().y * ySens, -input->GetMousePos().x * xSens, 0));
	}

	if (transform->GetRotation().x > 80)
	{
		transform->SetRotation(vec3(80, transform->GetRotation().y, transform->GetRotation().z));
	}
	if (transform->GetRotation().x < -80)
	{
		transform->SetRotation(vec3(-80, transform->GetRotation().y, transform->GetRotation().z));
	}

	mat4 model(1.0f);
	vec3 rotation = transform->GetRotation();
	model = rotate(model, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	model = rotate(model, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	model = rotate(model, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

	if (input->GetKey(Keys::W))
	{
		vec3 forward = vec3(model * vec4(0, 0, -1, 1));

		transform->AddPosition(forward * moveSpeed);
	}
	if (input->GetKey(Keys::S))
	{
		vec3 backward = vec3(model * vec4(0, 0, 1, 1));

		transform->AddPosition(backward * moveSpeed);
	}
	if (input->GetKey(Keys::A))
	{
		vec3 left = vec3(model * vec4(-1, 0, 0, 1));

		transform->AddPosition(left * moveSpeed);
	}
	if (input->GetKey(Keys::D))
	{
		vec3 right = vec3(model * vec4(1, 0, 0, 1));

		transform->AddPosition(right * moveSpeed);
	}
	//transform->SetPosition(vec3(transform->GetPosition().x, 0, transform->GetPosition().z));
}