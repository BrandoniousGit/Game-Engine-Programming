#include <scripts/Scripts.h>

void PlayerScript::OnInitialize()
{
	transform->SetPosition(vec3(0.0f, 0.0f, 0.0f));
	transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
}

void PlayerScript::OnTick()
{
	//if (input->GetKey(Keys::W))
	//{
	//	transform->AddPosition(vec3(0.0f, 0.0f, -0.2f));
	//}
	//if (input->GetKey(Keys::S))
	//{
	//	transform->AddPosition(vec3(0.0f, 0.0f, 0.2f));
	//}
	//if (input->GetKey(Keys::A))
	//{
	//	transform->AddPosition(vec3(-0.2f, 0.0f, 0.0f));
	//}
	//if (input->GetKey(Keys::D))
	//{
	//	transform->AddPosition(vec3(0.2f, 0.0f, 0.0f));
	//}
	if (input->GetKey(Keys::F))
	{
		getComponent<AudioSource>()->PlaySound(getCore->GetCache()->load<AudioClip>("../resources/sounds/funkytown.ogg"), 1.0f);
	}
}
