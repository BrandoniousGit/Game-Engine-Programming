#include <scripts/Scripts.h>

void PlayerScript::OnInitialize()
{
	transform->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
	dancing = false;
	movingUp = true;
	rotating = true;
}

void PlayerScript::OnTick()
{
	mat4 model(1.0f);
	vec3 rotation = transform->GetRotation();
	model = rotate(model, radians(rotation.y), vec3(0.0f, 1.0f, 0.0f));
	model = rotate(model, radians(rotation.x), vec3(1.0f, 0.0f, 0.0f));
	model = rotate(model, radians(rotation.z), vec3(0.0f, 0.0f, 1.0f));

	vec3 up = vec3(model * vec4(0, 1, 0, 1));
	vec3 down = vec3(model * vec4(0, -1, 0, 1));

	if (input->GetKey(Keys::F))
	{
		dancing = true;
		getComponent<AudioSource>()->PlaySound(getCore->GetCache()->load<AudioClip>("../resources/sounds/catloop.ogg"), 1.0f);
		startTime = (int)Time::GetTimeSeconds();
	}

	if ((int)Time::GetTimeSeconds() - 29 > startTime)
	{
		dancing = false;
	}

	if (dancing)
	{
		if (movingUp)
		{
			transform->AddPosition(up * 0.02f);
			if (transform->GetPosition().y > 0.25)
			{
				movingUp = !movingUp;
			}
		}
		if (!movingUp)
		{
			transform->AddPosition(down * 0.02f);
			if (transform->GetPosition().y < 0)
			{
				movingUp = !movingUp;
			}
		}
		if (rotating)
		{
			transform->AddRotation(vec3(2.5,0,0));
			if (transform->GetRotation().x > 30)
			{
				rotating = !rotating;
			}
		}
		if (!rotating)
		{
			transform->AddRotation(vec3(-2.5,0,0));
			if (transform->GetRotation().x < -30)
			{
				rotating = !rotating;
			}
		}
	}
	else
	{
		transform->SetPosition(vec3(0, 0, 0));
		transform->SetRotation(vec3(0, 0, 0));
	}
}
