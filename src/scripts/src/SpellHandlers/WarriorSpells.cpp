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

/* Module info */
void SetupWarriorSpells(ScriptMgr * mgr)
{
#ifdef ASCENT_CORE
    /**** Execute ****/
    /* log isn't working */
    /*
      WORLD: got cast spell packet, spellId - 25236, data length = 9
      Spell::cast 25236, Unit: 2
      WORLD: Spell effect id = 3, damage = 925
      WORLD: Recvd CMSG_ATTACKSWING Message
      WORLD: Sent SMSG_ATTACKSTART
      Player::Update:  No valid current selection to attack, stopping attack
    */
    /**** Bloodrage ****/
    /* server debug when blood rages is cast */
    /*

    WORLD: got cast spell packet, spellId - 2687, data length = 6
    Spell::cast 2687, Unit: 2
    WORLD: Spell effect id = 30, damage = 100
    WORLD: Spell effect id = 64, damage = 1
    Spell::cast 29131, Unit: 2
    WORLD: Spell effect id = 6, damage = 10
    WORLD: Spell effect id = 6, damage = 1
    WORLD: target = 2 , Spell Aura id = 24, SpellId  = 29131, i = 0, apply = true
    WORLD: target = 2 , Spell Aura id = 94, SpellId  = 29131, i = 1, apply = true
    WORLD: target = 2 , Spell Aura id = 24, SpellId  = 29131, i = 0, apply = false
    WORLD: target = 2 , Spell Aura id = 94, SpellId  = 29131, i = 1, apply = false
    
    */
#endif
}
