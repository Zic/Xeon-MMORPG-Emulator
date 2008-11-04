/*
 * Ascent MMORPG Server
 * Copyright (C) 2005-2008 Ascent Team <http://www.ascentemu.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __STRIKE_H
#define __STRIKE_H

class Striker : public ObjectPool< Striker >
{
public:
	Striker(){}
	Striker(Unit* pAttacker, Unit* pVictim, uint32 weapon_damage_type, SpellEntry* ability, int32 add_damage, int32 pct_dmg_mod, uint32 exclusive_damage, bool disable_proc, bool skip_hit_check );
	void Deal();
	uint32 GetSpellDidHitResult();
	~Striker(void);
private:
	void GetAttackerVictimSkills();
	void FillHitChances();
	Unit* pAttacker;
	Unit* pVictim;
	uint32 weapon_damage_type;
	SpellEntry* ability;
	int32 add_damage;
	int32 pct_dmg_mod;
	uint32 exclusive_damage;
	bool disable_proc;
	bool skip_hit_check;

	float vsk;
	float diffVcapped;
	float diffAcapped;
	uint32 SubClassSkill;

	float hitchance;
	float dodge;
	float parry;
	float block;

	bool backAttack;
};

#endif
