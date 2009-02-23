/****************************************************************************
 *
 * SpellHandler Plugin
 * Copyright (c) 2007 Team Ascent
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0
 * License. To view a copy of this license, visit
 * http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to Creative Commons,
 * 543 Howard Street, 5th Floor, San Francisco, California, 94105, USA.
 *
 * EXCEPT TO THE EXTENT REQUIRED BY APPLICABLE LAW, IN NO EVENT WILL LICENSOR BE LIABLE TO YOU
 * ON ANY LEGAL THEORY FOR ANY SPECIAL, INCIDENTAL, CONSEQUENTIAL, PUNITIVE OR EXEMPLARY DAMAGES
 * ARISING OUT OF THIS LICENSE OR THE USE OF THE WORK, EVEN IF LICENSOR HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 */

#include "StdAfx.h"
#include "Setup.h"

/************************************************************************/
/* Spell Defs                                                           */
/************************************************************************/

bool RockbiterWeapon(uint32 i, SpellPointer pSpell)
{
    uint32 enchantment_entry = 0;
    switch(pSpell->m_spellInfo->RankNumber)
    {
    case 1:
        enchantment_entry = 36494;
        break;
    case 2:
        enchantment_entry = 36750;
        break;
    case 3:
        enchantment_entry = 36754;
        break;
    case 4:
        enchantment_entry = 36761;
        break;
    }

    if(!enchantment_entry || !pSpell->p_caster)
        return true;

    ItemPointer item = pSpell->p_caster->GetItemInterface()->GetInventoryItem(EQUIPMENT_SLOT_MAINHAND);
    EnchantEntry * enchant = dbcEnchant.LookupEntry(enchantment_entry);
    if(!item || !enchant)
        return true;

    int32 Slot = item->HasEnchantment(enchant->Id);
    if(Slot >= 0)
        item->ModifyEnchantmentTime(Slot, 1800);
    else
    {
		//check if enchantment slot 1 is taken. If there was no enchantment there function will quit
		item->RemoveEnchantment(1);
		//this will also apply bonuses for us
        Slot = item->AddEnchantment(enchant, 1800, false, true, false, 1);   // 5min
        if(Slot < 0) return true;
    }

    DEBUG_LOG("ShamanSpells.cpp", "Rockbiter Weapon Rank %u, enchant %u, slot %u", pSpell->m_spellInfo->RankNumber,
        enchantment_entry, Slot);
    
    return true;
}

void SetupShamanSpells(ScriptMgr * mgr)
{
    mgr->register_dummy_spell(8017, &RockbiterWeapon); // rank 1
    mgr->register_dummy_spell(8018, &RockbiterWeapon); // rank 2
    mgr->register_dummy_spell(8019, &RockbiterWeapon); // rank 3
    mgr->register_dummy_spell(10399, &RockbiterWeapon);// rank 4
}
