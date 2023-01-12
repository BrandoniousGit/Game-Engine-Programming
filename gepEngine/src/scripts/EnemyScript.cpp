#include <scripts/Scripts.h>


void EnemyScript::OnInitialize()
{
	transform->SetPosition(vec3(0.0f, 0.3f, -3.0f));
	transform->SetScale(vec3(0.1f, 0.1f, 0.1f));
}

void EnemyScript::OnTick()
{
	if (input->GetKey(Keys::X))
	{
			
	}
}