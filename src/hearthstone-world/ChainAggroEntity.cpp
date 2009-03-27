#include "StdAfx.h"

ChainAggroEntity::ChainAggroEntity(CreaturePointer pOwner)
{
	AddAggroEntity(pOwner);
}

ChainAggroEntity::~ChainAggroEntity()
{

}

void ChainAggroEntity::AddAggroEntity(CreaturePointer pCreature)
{
	pCreature->GetAIInterface()->m_ChainAgroSet = this;
	m_agroEntitySet.insert(pCreature);
}

void ChainAggroEntity::RemoveAggroEntity(CreaturePointer pCreature)
{
	pCreature->GetAIInterface()->m_ChainAgroSet = NULL;
	m_agroEntitySet.erase(pCreature);

	// Oh noes, I am with the worms!
	if(m_agroEntitySet.size() == 0)
	{
		delete this;
	}
}

void ChainAggroEntity::Delete()
{
	set<CreaturePointer>::iterator itr = m_agroEntitySet.begin();
	for(; itr != m_agroEntitySet.end(); ++itr)
	{
		(*itr)->GetAIInterface()->m_ChainAgroSet = NULL;
	}
	delete this;
}

void ChainAggroEntity::EventEnterCombat(UnitPointer pTarget)
{
	set<CreaturePointer>::iterator itr = m_agroEntitySet.begin();
	for(; itr != m_agroEntitySet.end(); ++itr)
	{
		if( (*itr)->isDead() )
			continue;

		(*itr)->GetAIInterface()->AttackReaction( pTarget, 1 );
	}
}
