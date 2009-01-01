#include "StdAfx.h"

ChainAggroEntity::ChainAggroEntity(Creature* pOwner)
{
	AddAggroEntity(pOwner);
}

ChainAggroEntity::~ChainAggroEntity()
{

}

void ChainAggroEntity::AddAggroEntity(Creature* pCreature)
{
	pCreature->GetAIInterface()->m_ChainAgroSet = this;
	m_agroEntitySet.insert(pCreature);
}

void ChainAggroEntity::RemoveAggroEntity(Creature* pCreature)
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
	set<Creature*>::iterator itr = m_agroEntitySet.begin();
	for(; itr != m_agroEntitySet.end(); ++itr)
	{
		(*itr)->GetAIInterface()->m_ChainAgroSet = NULL;
	}
	delete this;
}

void ChainAggroEntity::EventEnterCombat(Unit* pTarget)
{
	set<Creature*>::iterator itr = m_agroEntitySet.begin();
	for(; itr != m_agroEntitySet.end(); ++itr)
	{
		if( (*itr)->isDead() )
			continue;

		(*itr)->GetAIInterface()->AttackReaction( pTarget, 1 );
	}
}