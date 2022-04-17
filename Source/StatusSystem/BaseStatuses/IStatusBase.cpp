#include "IStatusBase.h"

void IStatusBase::OnTick_Implementation(const TScriptInterface<IStatusOwner>& statusOwner, float dt)
{
}

void IStatusBase::OnDie_Implementation(const TScriptInterface<IStatusOwner>& statusOwner)
{
}

void IStatusBase::ApplyDmg_Implementation(float damage)
{}
