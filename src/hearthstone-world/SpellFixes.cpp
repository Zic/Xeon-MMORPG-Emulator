/*
 * Aspire Hearthstone
 * Copyright (C) 2008 - 2009 AspireDev <http://www.aspiredev.org/>
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

#include "StdAfx.h"

//#define DUMP_SPELLS_SQL	1
//#define DUMP_CLASS_SPELLS	1
//#define DUMP_SPELL_RANKS_SQL	1

void CreateDummySpell(uint32 id)
{
	const char * name = "Dummy Trigger";
	SpellEntry * sp = new SpellEntry;
	memset(sp, 0, sizeof(SpellEntry));
	sp->Id = id;
	sp->Attributes = 384;
	sp->AttributesEx = 268435456;
	sp->Flags3 = 4;
	sp->CastingTimeIndex=1;
	sp->procChance=75;
	sp->rangeIndex=13;
	sp->EquippedItemClass=uint32(-1);
	sp->Effect[0]=SPELL_EFFECT_DUMMY;
	sp->EffectImplicitTargetA[0]=25;
	sp->NameHash=crc32((const unsigned char*)name, (unsigned int)strlen(name));
	sp->dmg_multiplier[0]=1.0f;
	sp->StanceBarOrder=-1;
	dbcSpell.SetRow(id,sp);
	sWorld.dummyspells.push_back(sp);
}
void DumpSpellsSQL()
{
	SpellEntry *sp;
	FILE *f;

	f = fopen("spell.sql", "w");
	if (f == NULL)
	{
		sLog.outString("Error while opening spell.sql: %s", strerror(errno));
		return;
	}

	fprintf(f, "drop table if exists spell;");
	fprintf(f, "create table spell(entry int4 unsigned primary key, "
			   "name varchar(255) not null, description text not null, "
			   "attr int4 unsigned not null, attrex int4 unsigned not null, "
			   "attrexb int4 unsigned not null, attrexc int4 unsigned not null, "
			   "attrexd int4 unsigned not null, attrexe int4 unsigned not null, "
			   "procchance int4 unsigned not null, procflags int4 unsigned not null, "
			   "intr int4 unsigned not null, auintr int4 unsigned not null, "
			   "grouptype0 int4 unsigned not null, grouptype1 int4 unsigned not null, "
			   "grouptype2 int4 unsigned not null, basepoints0 int4 unsigned not null, "
			   "basepoints1 int4 unsigned not null, basepoints2 int4 unsigned not null, "
			   "hasproc int1 unsigned not null);\n");

	for(uint32 x=0; x < (uint32)dbcSpell.GetNumRows(); x++)
	{
		sp = dbcSpell.LookupRow(x);
		char query[4096];
		char name[4096];
		char desc[4096];
		strcpy(name,sp->Name);
		strcpy(desc,sp->Description);
		for (int z=0;z<(int)strlen(name);z++) if (name[z] == '\'') name[z]=' ';
		for (int z=0;z<(int)strlen(desc);z++) if (desc[z] == '\'') desc[z]=' ';
		sprintf(query, "insert into spell(entry, name, description, attr, attrex, attrexb, "
				"attrexc, attrexd, attrexe, procchance, procflags, "
				"intr, auintr, grouptype0, "
				"grouptype1, grouptype2, basepoints0, "
				"basepoints1, basepoints2, hasproc) "
				"values(%u, '%s', '%s', %u, %u, %u, "
				"%u, %u, %u, %u, %u, "
				"%u, %u, 0x%x, "
				"0x%x, 0x%x, %u, "
				"%u, %u, %u);",
				sp->Id, name, desc, sp->Attributes, sp->AttributesEx, sp->Flags3, 
				sp->Flags4, sp->Flags5, sp->Flags6, sp->procChance, sp->procFlags, 
				sp->InterruptFlags, sp->AuraInterruptFlags, sp->SpellGroupType[0], 
				sp->SpellGroupType[1], sp->SpellGroupType[2], sp->EffectBasePoints[0], 
				sp->EffectBasePoints[1], sp->EffectBasePoints[2], 
				sp->EffectApplyAuraName[0]==42 ||sp->EffectApplyAuraName[1]==42 ||sp->EffectApplyAuraName[2]==42);
		fprintf(f, "%s\n", query);
	}
	fclose(f);
}

void DumpSpellRanksSQL()
{
	SpellEntry *sp;
	FILE *f;

	f = fopen("spell_ranks.sql", "w");
	if (f == NULL)
	{
		sLog.outString("Error while opening spell_ranks.sql: %s", strerror(errno));
		return;
	}

	fprintf(f, "drop table if exists spell_ranks;\n");
	fprintf(f, "create table spell_ranks(entry int4 unsigned primary key, namehash int4 unsigned not null, rank int4 unsigned not null);\n");

	for(uint32 x=0; x < (uint32)dbcSpell.GetNumRows(); x++)
	{
		char query[4096];
		unsigned int rank;

		sp = dbcSpell.LookupRow(x);
		rank = 0;
		sscanf( sp->Rank, "Rank %d", (unsigned int*)&rank);

		if( rank )
		{
			sprintf(query, "insert into spell_ranks(entry, namehash, rank) values(%u, 0x%X, %d);", sp->Id, sp->NameHash, rank);
			fprintf(f, "%s\n", query);
		}
	}
	fclose(f);
}

uint32 GetSpellClass(SpellEntry *sp)
{
	switch(sp->skilline)
	{
		case SKILL_ARMS:
		case SKILL_FURY:
		case SKILL_PROTECTION:
			return WARRIOR;
		case SKILL_HOLY2:
		case SKILL_PROTECTION2:
		case SKILL_RETRIBUTION:
			return PALADIN;
		case SKILL_BEAST_MASTERY:
		case SKILL_SURVIVAL:
		case SKILL_MARKSMANSHIP:
			return HUNTER;
		case SKILL_ASSASSINATION:
		case SKILL_COMBAT:
		case SKILL_SUBTLETY:
			return ROGUE;
		case SKILL_DISCIPLINE:
		case SKILL_HOLY:
		case SKILL_SHADOW:
			return PRIEST;
		case SKILL_ENHANCEMENT:
		case SKILL_RESTORATION:
		case SKILL_ELEMENTAL_COMBAT:
			return SHAMAN;
		case SKILL_FROST:
		case SKILL_FIRE:
		case SKILL_ARCANE:
			return MAGE;
		case SKILL_AFFLICTION:
		case SKILL_DEMONOLOGY:
		case SKILL_DESTRUCTION:
			return WARLOCK;
		case SKILL_RESTORATION2:
		case SKILL_BALANCE:
		case SKILL_FERAL_COMBAT:
			return DRUID;
		case SKILL_DK_FROST:
		case SKILL_UNHOLY:
		case SKILL_BLOOD:
			return DEATHKNIGHT;
	}

	return -1;
}

void _DumpClassSpells(FILE *f, uint32 _class)
{
	SpellEntry *sp;
	
	fprintf(f, "\t{ ");
	for(uint32 x=0; x < (uint32)dbcSpell.GetNumRows(); x++)
	{
		sp = dbcSpell.LookupRow(x);
		if (sp->talent_tree == 0 && GetSpellClass(sp) == _class)
			fprintf(f, "%d, ", sp->Id);
	}
	fprintf(f, " }, \n");
}

void DumpClassSpells()
{
	FILE *f;

	f = fopen("ClassSpells.h", "w");
	if (f == NULL)
	{
		sLog.outString("Error while opening ClassSpells.h: %s", strerror(errno));
		return;
	}

	fprintf(f, "/* ** Automatically Generated File ** */\n\n");
	fprintf(f, "static uint32 spellarray[DRUID+1][9999] = {\n");
	fprintf(f, "\t{ 0 }, \n");
	_DumpClassSpells(f, WARRIOR);
	_DumpClassSpells(f, PALADIN);
	_DumpClassSpells(f, HUNTER);
	_DumpClassSpells(f, ROGUE);
	_DumpClassSpells(f, PRIEST);
	_DumpClassSpells(f, DEATHKNIGHT);
	_DumpClassSpells(f, SHAMAN);
	_DumpClassSpells(f, MAGE);
	_DumpClassSpells(f, WARLOCK);
	_DumpClassSpells(f, DRUID);
	fprintf(f, "\t};\n");

	fclose(f);
}

void DumpTalentSpells()
{
	FILE *f;

	f = fopen("TalentSpells.csv", "w");
	if (f == NULL)
	{
		sLog.outString("Error while opening TalentSpells.csv: %s", strerror(errno));
		return;
	}

	for(uint32 i = 0 ;i < dbcTalent.GetNumRows(); i++)
	{
		TalentEntry *talent = dbcTalent.LookupRow(i);
		if(!talent)
			continue;
		for(uint32 rank = 0; rank < 5; rank++)
		{
			if(talent->RankID[rank] != 0)
				fprintf(f, "%d\n", talent->RankID[rank]); 
		}
		SpellEntry * sp = dbcSpell.LookupEntryForced(talent->RankID[0]);
		if(!sp)
			continue;
		for(uint32 k = 0; k < 3; ++k)
		{
			if(sp->Effect[k] == SPELL_EFFECT_LEARN_SPELL)
			{
				SpellEntry * sp2 = dbcSpell.LookupEntryForced(sp->EffectTriggerSpell[k]);
				if(!sp2) continue;
				for(uint32 j = 0; j < dbcSpell.GetNumRows(); j++)
				{
					SpellEntry * sp3 = dbcSpell.LookupRow(j);
					if(!sp3 || sp3->NameHash != sp2->NameHash)
						continue;
					fprintf(f, "%d\n", sp3->Id); 
				}
			}
		}
	}

	fclose(f);
}

// fills array 'arr' with integers in arguments and returns its new size. Last argument must be 0!
uint32 fill( uint32* arr, ... ){
	va_list vl;
	uint32 i;
	va_start( vl, arr );
	for( i = 0; i < 100; ++i ){
		arr[i] = va_arg( vl, uint32 );
		if(arr[i] == 0)
			break;
	}
	va_end( vl );
	return i;
}

// Generates SpellNameHashes.h
void GenerateNameHashesFile()
{
	const uint32 fieldSize = 81;
	const char* prefix = "SPELL_HASH_";
	uint32 prefixLen = strlen(prefix);
	DBCFile dbc;

	if( !dbc.open( "DBC/Spell.dbc" ) )
	{
		Log.Error("World", "Cannot find file ./DBC/Spell.dbc" );
		return;
	}
	uint32 cnt = (uint32)dbc.getRecordCount();
	uint32 namehash = 0;
	FILE * f = fopen("SpellNameHashes.h", "w");
	char spaces[fieldSize], namearray[fieldSize];
	strcpy(namearray, prefix);
	char* name = &namearray[prefixLen];
	for(int i=0;i<fieldSize-1;i++)
		spaces[i] = ' ';
	spaces[fieldSize-1] = 0;
	uint32 nameTextLen = 0, nameLen = 0;
	for(uint32 x=0; x < cnt; x++)
	{
		const char* nametext = dbc.getRecord(x).getString(139);
		nameTextLen = (unsigned int)strlen(nametext);
		strncpy(name, nametext, fieldSize-prefixLen-2);	// Cut it to fit in field size
		name[fieldSize-prefixLen-2] = 0; // in case nametext is too long and strncpy didn't copy the null
		nameLen = (unsigned int)strlen(name);
		for(uint32 i = 0;i<nameLen;i++)
		{
			if(name[i] >= 'a' && name[i] <= 'z')
				name[i] = toupper(name[i]);
			else if(!(name[i] >= '0' && name[i] <= '9') &&
				!(name[i] >= 'A' && name[i] <= 'Z'))
				name[i] = '_';
		}
		namehash = crc32((const unsigned char*)nametext, nameTextLen);
		int32 numSpaces = fieldSize-prefixLen-nameLen-1;
		if(numSpaces < 0)
			fprintf(f, "WTF");
		spaces[numSpaces] = 0;
		fprintf(f, "#define %s%s0x%08X\n", namearray, spaces, namehash);
		spaces[numSpaces] = ' ';
	}
	fclose(f);
}

// Copies effect number 'fromEffect' in 'fromSpell' to effect number 'toEffect' in 'toSpell'
void CopyEffect(SpellEntry *fromSpell, uint8 fromEffect, SpellEntry *toSpell, uint8 toEffect)
{
	if(!fromSpell || !toSpell || fromEffect > 2 || toEffect > 2)
		return;
	uint32 *from = fromSpell->Effect;
	uint32 *to = toSpell->Effect;
	// Copy 20 values starting at Effect
	for(uint8 index = 0;index < 20;index++)
	{
		to[index * 3 + toEffect] = from[index * 3 + fromEffect];
	}
}

void ApplySingleSpellFixes(SpellEntry *sp)
{
	if(sp != NULL)
	{
		switch(sp->Id)
		{
			// Spell 1455 Proc Chance (Life Tap Rank 2:
			case  1455:
				sp->procChance = 100;
				break;

			// Spell 1456 Proc Chance (Life Tap Rank 3:
			case  1456:
				sp->procChance = 100;
				break;
		
			// Spell 3391 Proc Chance (Thrash :
			case  3391:
				sp->procChance = 10;
				break;
			
			// Spell 8182 Proc Chance (Frost Resistance Rank 1:
			case  8182:
				sp->procChance = 100;
				break;
		
			// Spell 8185 Proc Chance (Fire Resistance Rank 1:
			case  8185:
				sp->procChance = 100;
				break;
		
			// Spell 10476 Proc Chance (Frost Resistance Rank 2:
			case  10476:
				sp->procChance = 100;
				break;
		
			// Spell 10477 Proc Chance (Frost Resistance Rank 3:
			case  10477:
				sp->procChance = 100;
				break;
		
			// Spell 10534 Proc Chance (Fire Resistance Rank 2:
			case  10534:
				sp->procChance = 100;
				break;
		
			// Spell 10535 Proc Chance (Fire Resistance Rank 3:
			case  10535:
				sp->procChance = 100;
				break;
		
			// Spell 11687 Proc Chance (Life Tap Rank 4:
			case  11687:
				sp->procChance = 100;
				break;
		
			// Spell 11688 Proc Chance (Life Tap Rank 5:
			case  11688:
				sp->procChance = 100;
				break;
		
			// Spell 11689 Proc Chance (Life Tap Rank 6:
			case  11689:
				sp->procChance = 100;
				break;
		
			// Spell 12284 Proc Chance (Mace Specialization Rank 1:
			case  12284:
				sp->procChance = 1;
				break;
		
			// Spell 12292 Proc Chance (Death Wish :
			case  12292:
				sp->procChance = 100;
				break;
		
			// Spell 12322 Proc Chance (Unbridled Wrath Rank 1:
			case  12322:
				sp->procChance = 8;
				break;
		
			// Spell 12701 Proc Chance (Mace Specialization Rank 2:
			case  12701:
				sp->procChance = 2;
				break;
		
			// Spell 12702 Proc Chance (Mace Specialization Rank 3:
			case  12702:
				sp->procChance = 3;
				break;
		
			// Spell 12703 Proc Chance (Mace Specialization Rank 4:
			case  12703:
				sp->procChance = 4;
				break;
		
			// Spell 12704 Proc Chance (Mace Specialization Rank 5:
			case  12704:
				sp->procChance = 6;
				break;
		
			// Spell 12999 Proc Chance (Unbridled Wrath Rank 2:
			case  12999:
				sp->procChance = 16;
				break;
		
			// Spell 13000 Proc Chance (Unbridled Wrath Rank 3:
			case  13000:
				sp->procChance = 24;
				break;
		
			// Spell 13001 Proc Chance (Unbridled Wrath Rank 4:
			case  13001:
				sp->procChance = 32;
				break;
		
			// Spell 13002 Proc Chance (Unbridled Wrath Rank 5:
			case  13002:
				sp->procChance = 40;
				break;
		
			// Spell 14076 Proc Chance (Dirty Tricks Rank 1:
			case  14076:
				sp->procChance = 30;
				break;
		
			// Spell 14094 Proc Chance (Dirty Tricks Rank 2:
			case  14094:
				sp->procChance = 60;
				break;
		
			// Spell 15494 Proc Chance (Fury of Forgewright :
			case  15494:
				sp->procChance = 10;
				break;
		
			// Spell 15600 Proc Chance (Hand of Justice :
			case  15600:
				sp->procChance = 2;
				break;
		
			// Spell 15601 Proc Chance (Hand of Justice :
			case  15601:
				sp->procChance = 10;
				break;
		
			// Spell 15642 Proc Chance (Ironfoe :
			case  15642:
				sp->procChance = 10;
				break;
		
			// Spell 16459 Proc Chance (Sword Specialization :
			case  16459:
				sp->procChance = 10;
				break;
		
			// Spell 16843 Proc Chance (Crimson Fury :
			case  16843:
				sp->procChance = 10;
				break;
		
			// Spell 18797 Proc Chance (Flurry Axe :
			case  18797:
				sp->procChance = 10;
				break;
		
			// Spell 18803 Proc Chance (Focus :
			case  18803:
				sp->procChance = 100;
				break;
		
			// Spell 19105 Proc Chance (MHTest01 Effect :
			case  19105:
				sp->procChance = 10;
				break;
		
			// Spell 19109 Proc Chance (MHTest02 Effect :
			case  19109:
				sp->procChance = 10;
				break;
		
			// Improved Wing Clip
			case  19228:
				{
				sp->procChance = 7;
				sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
				}break;
		
			// Improved Wing Clip
			case  19232:
				{
				sp->procChance = 14;
				sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
				}break;
		
			// Improved Wing Clip 
			case  19233:
				{
				sp->procChance = 20;
				sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
				}break;
		
			// Spell 21919 Proc Chance (Thrash :
			case  21919:
				sp->procChance = 10;
				break;
		
			// Spell 23158 Proc Chance (Concussive Shot Cooldown Reduction :
			case  23158:
				sp->procChance = 4;
				break;
		
			// Spell 26022 Proc Chance (Pursuit of Justice Rank 1:
			case  26022:
				sp->procChance = 100;
				break;
		
			// Spell 26023 Proc Chance (Pursuit of Justice Rank 2:
			case  26023:
				sp->procChance = 100;
				break;
		
			// Spell 27035 Proc Chance (Sword Specialization (OLD: :
			case  27035:
				sp->procChance = 10;
				break;
		
			// Spell 27521 Proc Chance (Mana Restore :
			case  27521:
				sp->procChance = 2;
				break;
		
			// Spell 27867 Proc Chance (Freeze :
			case  27867:
				sp->procChance = 2;
				break;
			
			// Elemental Focus
			case  16164:
				{
					sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
				}break;
			case  16246:
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
					sp->procCharges++; //	first	charge gets	lost when	it gets	procced
				}break;
			
			// Flametongue Weapon	-	10%	spd	coefficient
			case  10444:
				{	sp->fixed_dddhcoef = 0.1f;
				}break;
			
			//shaman - Stormstrike
			case  17364:
				{
					sp->procFlags=PROC_ON_SPELL_HIT_VICTIM;
				}break;

			//shaman - Improved Stormstrike
			case 51521:
			case 51522:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			
			//shaman - Hex
			case  51514:
				{
					// Damage	caused may interrupt the effect.
					sp->AuraInterruptFlags |=	AURA_INTERRUPT_ON_UNUSED2;
				}break;

			//shaman - Frozen Power
			case 63374:
			case 63373:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[1][0] = 0x80000000;	// frost shock
					sp->EffectSpellClassMask[1][1] = 0;
					sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1] = 63685;
				}break;

			//shaman - Ancestral Awakening
			case 51558:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
					sp->EffectTriggerSpell[0] = 52752;
				}break;
			case 52752:
				{
					sp->Dspell_coef_override = 0.0f;
					sp->spell_can_crit = false;
					sp->logsId = sp->Id;
				}break;
			case 974:
			case 32593:
			case 32594:
			case 49283:
			case 49284: //Earth Shield
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_REMOVEONUSE;
					sp->EffectTriggerSpell[0] = sp->Id;
				}break;
			// shaman	-	Maelstrom	Weapon
			case 51528:
			case 51529:
			case 51530:
			case 51531:
			case 51532:
				{
					sp->ProcsPerMinute = float(sp->RankNumber) * 2.5f;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
				}break;
			
			// Maelstorm proc	charge removal
			case  53817:	
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			
			// Astral	Shift
			case  52179:
				{
					sp->EffectAmplitude[0] = 0;
					sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
					sp->EffectMiscValue[0] = 127;
				}break;
			
			case 30824:
				{
					//this is so lame : shamanistic rage triggers a new spell which borrows it's stats from parent spell :S
					SpellEntry*  sp2 = dbcSpell.LookupEntryForced( 30823 );
					if( sp2 != NULL)
						sp->EffectBasePoints[0] = sp2->EffectBasePoints[0];
				}break;
			
			case 51479:
			case 51478:
			case 51474: // Astral Shift
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_SPELL_LAND_VICTIM;
					sp->EffectTriggerSpell[0]	=	52179;
					sp->Effect[1]	=	0;
					sp->EffectApplyAuraName[1] = 0;
				}break;
			
			case 51975:
				{
					// shaman	-	Poison Cleansing Totem
					SpellEntry*  sp2 = dbcSpell.LookupEntryForced( 58780 );
					if( sp2 != NULL)
					{
						sp->EffectRadiusIndex[0] = sp2->EffectRadiusIndex[0];	//30 yards
						sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY_IN_AREA;
					}
				}break;
			
			case 52025:
				{
					// shaman	-	Disease	Cleansing	Totem
					SpellEntry*  sp2 = dbcSpell.LookupEntryForced( 58780 );
					if( sp2 != NULL)
					{
						sp->EffectRadiusIndex[0] = sp2->EffectRadiusIndex[0];	//30 yards
						sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY_IN_AREA;
					}
				}break;
			
			// Fire	Nova Totem visual	fix
			case 8349:
			case 8502:
			case 8503:
			case 11306:
			case 11307:
			case 25535:
			case 25537:
			case 61650:
			case 61654:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	19823;
				}break;
			
			// Flurry
			case 12319:
			case 12971:
			case 12972:
			case 12973:
			case 12974:
			case 16256:
			case 16281:
			case 16282:
			case 16283:
			case 16284:
				{
					sp->procFlags	=	PROC_ON_CRIT_ATTACK;
				}break;
			
			// Flurry	proc
			case 12966:
			case 12967:
			case 12968:
			case 12969:
			case 12970:
			case 16257:
			case 16277:
			case 16278:
			case 16279:
			case 16280:
				{
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->procCharges++; //	first	charge gets	lost when	it gets	procced
				}break;
			
			// Shaman	Totem	items	fixes
			// Totem of	Survival,	Totem	of the Tundra
			case 46097:
			case 43860:
			case 43861:
			case 43862:
			case 60564:
			case 60571:
			case 60572:
			case 37575:
				{
					sp->EffectSpellClassMask[0][0] = 0x00100000	|	0x10000000 | 0x80000000; //Earth + Flame + Frost Shocks
					sp->EffectSpellClassMask[0][1] = 0x08000000;	// Wind	Shock
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
				}break;
			case 60567:
				{
					sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
				}break;
			
			// Totem of	Third	Wind
			case 46098:
			case 34138:
			case 42370:
			case 43728:
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[0][0] = 0x00000080;	// Lesser	Healing	Wave
				}break;
			
			// Totem of	the	Elemental	Plane
			case  60770:
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[0][0] = 0x00000001;	// Lightning Bolt
				}break;
			
			// Fathom-Brooch of	the	Tidewalker
			case  37247:	
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
					sp->proc_interval	=	45000;
				}break;
				
			//Warlock: Nether	Protection
			case  30299:
			case  30301:
			case  30302:
				{
					sp->procChance = 30;
					sp->proc_interval	=	13000;
				}break;
			
			//Warlock: Backlash
			case  34935:
			case  34938:
			case  34939:
				{
					sp->proc_interval	=	8000;
					sp->procFlags	|= PROC_ON_MELEE_ATTACK_VICTIM | PROC_TARGET_SELF;
				}break;
			
			case  34936:
				{
						sp->AuraInterruptFlags |=	AURA_INTERRUPT_ON_CAST_SPELL;
				}break;
			
			
			//Warlock: Demonic Knowledge
			case  35691:
			case  35692:
			case  35693:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_DONE;
					sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
					sp->Effect[1]	=	6;
					sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_DONE;
					sp->EffectBasePoints[1]	=	sp->EffectBasePoints[0];
					sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
					sp->Effect[2]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[2]	=	35696;
					sp->EffectImplicitTargetA[2] = EFF_TARGET_PET;
					sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
				}break;
			
			case  35696:
				{
					sp->Effect[0]	=	6; //making	this only	for	the	visible	effect
					sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY; //no	effect here
					sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			
				//Priest - Holy	Nova
			case 15237:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	23455;
				}break;
			case 15430:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	23458;
				}break;
			case 15431:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	23459;
				}break;
			case 27799:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	27803;
				}break;
			case 27800:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	27804;
				}break;
			case 27801:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	27805;
				}break;
			case 25331:
					{
						sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	25329;
					}break;
			case 48077:
					{
						sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	48075;
					}break;
			case 48078:
				{
					sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1]	=	48076;
				}break;
			// Replenishment
			case 57669:
			{
				sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
				sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
				sp->EffectImplicitTargetA[2] = EFF_TARGET_ALL_PARTY;
				sp->EffectImplicitTargetB[0] = 0;
				sp->EffectImplicitTargetB[1] = 0;
				sp->EffectImplicitTargetB[2] = 0;
			}break;				
			// Moroes' garrote targets a single	enemy	instead	of us
			case 37066:
				{
					sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
				}break;
			
			//Bloodlust	targets	sorounding party members instead of	us
			case 2825:
			//Heroism	targets	sorounding party members instead of	us
			case 32182:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_ATTACKSPEED;
					sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
					sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
					sp->EffectImplicitTargetA[2] = EFF_TARGET_ALL_PARTY;
					sp->EffectImplicitTargetB[0] = 0;
					sp->EffectImplicitTargetB[1] = 0;
					sp->EffectImplicitTargetB[2] = 0;
				}break;

			// Drums of	Panic	targets	sorounding creatures instead of	us
			case 35474:
				{
					sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
					sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
					sp->EffectImplicitTargetA[2] = 0;
					sp->EffectImplicitTargetB[0] = 0;
					sp->EffectImplicitTargetB[1] = 0;
					sp->EffectImplicitTargetB[2] = 0;
					sp->RequiredShapeShift = 0;
				}break;
		
			
			// Drums of	war	targets	sorounding party members instead of	us
			case 35475:
			// Symbol	of Hope	targets	sorounding party members instead of	us
			case 32548:
			// Drums of	Battle targets sorounding	party	members	instead	of us
			case 35476:
			// Drums of	Restoration	targets	sorounding party members instead of	us
			case 35478:
			// Drums of	Speed	targets	sorounding party members instead of	us
			case 35477:
				{
						sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
						sp->EffectImplicitTargetA[2] = 0;
						sp->EffectImplicitTargetB[0] = 0;
						sp->EffectImplicitTargetB[1] = 0;
						sp->EffectImplicitTargetB[2] = 0;
						sp->RequiredShapeShift = 0;
				}break;
		
			case 53007: // Penance
				{
					CopyEffect(dbcSpell.LookupEntry(54518), 0, sp, 0);
					CopyEffect(dbcSpell.LookupEntry(54518), 1, sp, 1);
					sp->EffectTriggerSpell[1] = 52985;
					sp->DurationIndex = dbcSpell.LookupEntry(54518)->DurationIndex;
				}break;
			case 52985: // Penance proc
				{
					sp->fixed_dddhcoef = 0.351f;	// needs check
				}break;

			//paladin	-	Reckoning
			case  20177:
			case  20179:
			case  20180:
			case  20181:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;
				}break;
			case  20182:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM | PROC_ON_BLOCK_VICTIM | PROC_TARGET_SELF;
 				}break;

		
			//paladin	-	Reckoning	Effect = proc	on proc
			case  20178:
				{
						sp->procChance = 100;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
				}break;

		
			//paladin	-	Judgement	of Wisdom
			case  20186:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
						sp->EffectTriggerSpell[0]	=	20268;
				}break;

			case  20354:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
						sp->EffectTriggerSpell[0]	=	20352;
				}break;

			case  20355:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
						sp->EffectTriggerSpell[0]	=	20353;
				}break;

			case  27164:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
						sp->EffectTriggerSpell[0]	=	27165;
				}break;

			case  20268:
			case  20352:
			case  20353:
			case  27165:
				{
						sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
				}break;

		
			//paladin	-	Judgement	of Light
			case  20185:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM;
						sp->EffectTriggerSpell[0]	=	20267;
				}break;

			case  20344:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM;
						sp->EffectTriggerSpell[0]	=	20341;
				}break;

			case  20345:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM;
						sp->EffectTriggerSpell[0]	=	20342;
				}break;

			case  20346:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM;
						sp->EffectTriggerSpell[0]	=	20343;
				}break;

			case  27162:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM;
						sp->EffectTriggerSpell[0]	=	27163;
				}break;

			case  20267:
			case  20341:
			case  20342:
			case  20343:
			case  27163:
				{
						sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
				}break;

			//Judgements - rebuff
			case 20184:
				{
					sp->RankNumber = 0;
				}break;
			//paladin	-	Eye	for	an Eye
			case  9799:
			case  25988:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT_VICTIM;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	25997;
				}break;
				
			//paladin	-	sanctified judgement
			case  31876:
			case  31877:
			case  31878:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	31930;
				}break;
		
			//paladin	-	Blessed	Life
			case  31828:
			case  31829:
			case  31830:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
						sp->EffectTriggerSpell[0]	=	31828;
				}break;

			//paladin	-	Light's	Grace
			case  31833:
			case  31835:
			case  31836:
				{
						sp->EffectSpellClassMask[0][0]=0x80000000;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;

			//Paladin - Sacred Cleansing
			case  53551:
			case  53552:
			case  53553:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectSpellClassMask[0][0] = 0x00001000;
						sp->EffectSpellClassMask[0][1] = 0x00001000;
						sp->EffectSpellClassMask[0][2] = 0x00001000;
				}break;
			
			//Paladin - Infusion of light
			case  53569:
			case  53576:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
				}break;
			case 53672:
			case 54149:
				{
					sp->AuraInterruptFlags	=	AURA_INTERRUPT_ON_CAST_SPELL;
				}break;
			//Paladin - Vindication
			case 9452:
			case 26016:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_ON_ANY_HOSTILE_ACTION;
						sp->procChance	=	30;
				}break;
			//Paladin - Art of War
			case 53486:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->EffectApplyAuraName[2]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[2]	=	53489;
				}break;
			case 53488:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->EffectApplyAuraName[2]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[2]	=	59578;
				}break;
			case 53489:
			case 59578:
				{
						 sp->AuraInterruptFlags	|= AURA_INTERRUPT_ON_CAST_SPELL;
				}break;

			//shaman - Lightning Overload	
			case  30675:	// rank	1
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	39805;//proc something (we will	owerride this)
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 4;
				}break;

			case  30678:	 //	rank 2
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	39805;//proc something (we will	owerride this)
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 8;
				}break;

			case  30679:	// rank	3
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	39805;//proc something (we will	owerride this)
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 12;
				}break;

			case  30680:	// rank	4
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	39805;//proc something (we will	owerride this)
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 16;
				}break;

			case  30681:	// rank	5
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	39805;//proc something (we will	owerride this)
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 20;
				}break;

			//shaman - Purge 
			case  370:
			case  8012:
			case  27626:
			case  33625:	
				{
						sp->DispelType = DISPEL_MAGIC;
				}break;

			case 57663: // Totem of Wrath
				{
					// doesn't work
					/*CopyEffect(dbcSpell.LookupEntry(30708), 0, sp, 2);
					sp->EffectImplicitTargetA[2] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
					sp->Effect[2] = SPELL_EFFECT_APPLY_AREA_AURA;*/
				}break;

		
			//Shaman - Eye of	the	Storm
			case  29062:
			case  29064:
			case  29065:
				{
						sp->procFlags	=	PROC_ON_CRIT_HIT_VICTIM;
				}break;
		
			//shaman - Elemental Devastation
			case  29179:
			case  29180:
			case  30160:
			//shaman - Ancestral healing
			case  16176:
			case  16235:
			case  16240:	
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
				}break;

			//shaman - Ancestral healing proc	spell
			case  16177:
			case  16236:
			case  16237:
				{
						sp->rangeIndex = 4;
				}break;

		
			//rogue	-	Find Weakness.
			case  31233:
			case  31239:
			case  31240:
			case  31241:
			case  31242:	
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;

			//rogue	-	Cheap	Shot
			case  1833: 
				{
						sp->Flags3 &=	~FLAGS3_REQ_BEHIND_TARGET;	//Doesn't	require	to be	behind target
				}break;
            case 1329: // (mutilate rank 1)
            case 34411: // 2
            case 34412: // 3
            case 34413: // 4
            case 48663: // 5
            case 48666: // 6
                {
						sp->Flags3 &=   ~FLAGS3_REQ_BEHIND_TARGET;  //Doesn't   require to be   behind target
                }break;

			//rogue	-	Camouflage.
			case  13975:
			case  14062:
			case  14063:
			case  14064:
			case  14065:	
				{
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			//rogue	-	Mace Specialization.
			case  13709:
			case  13800:
			case  13801:	
			case  13802:
			case  13803:	
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
		
				}break;
			//rogue	-	Shadowstep
			case  36563:	
				{
						sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
						sp->procFlags	=	0;
				}break;
		
			case  44373:
				{
						sp->procFlags	=	0;
				}break;
		
				 //priest	-	Holy Concentration
			case 34753:
			case 34859:
			case 34860:
				 {
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
						sp->procChance = 30;
				}break;

		
			case 34754:
				{
					 sp->AuraInterruptFlags	|= AURA_INTERRUPT_ON_CAST_SPELL;
				}break;

			//Priest:	Blessed	Recovery
			case 27811:
				{
						sp->EffectTriggerSpell[0]	=	27813;
						sp->procFlags	=	PROC_ON_CRIT_HIT_VICTIM;
						sp->procChance	=	100;
				}break;

			case 27815:
				{
						sp->EffectTriggerSpell[0]	=	27817;
						sp->procFlags	=	PROC_ON_CRIT_HIT_VICTIM;
						sp->procChance	=	100;
				}break;

			case 27816:
			{
						sp->EffectTriggerSpell[0]	=	27818;
						sp->procFlags	=	PROC_ON_CRIT_HIT_VICTIM;
						sp->procChance	=	100;
				}break;

			//priest-	Blessed	Resilience
			case  33142:
			case  33145:
			case  33146:
			//priest-	Focused	Will
			case  45234:
			case  45243:
			case  45244:
				{
						sp->procFlags	=	PROC_ON_CRIT_HIT_VICTIM;
				}break;
			//Priest:	Improved Vampiric Embrace (Rank1)
			case 27839:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;

				}break;
			//Paladin: Seal	of Wisdom
			case  20166:
				{
						sp->procChance = 12;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
				}break;

		
			//Druid: Feral Swiftness
			case  17002:
				{
						sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	24867;
				}break;

			case  24866:
				{
						sp->Effect[1]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	24864;
				}break;

			//Druid: Natural Perfection
			case  33881:
			case  33882:
			case  33883:
				{
						sp->procFlags	=	PROC_ON_CRIT_HIT_VICTIM;
				}break;

		
			//Druid: Frenzied	Regeneration
			case  22842:
			case  22895:
			case  22896:
			case  26999:
				{
						sp->Effect[0]	=	6;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	22845;
				}break;

			// Spell 16850 Proc Chance (Celestial Focus Rank 1:
			case  16850:
				{
						sp->procChance = 3;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			case  16923:	
				{
						sp->procChance = 6;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;

			case  16924:	
				{
						sp->procChance = 9;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;

		
			//paladin	-	seal of	blood
			case  31892:
			case  38008:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	31893;
				}break;

			//paladin	-	Spiritual	Attunement 
			case  31785:
			case  33776:
				{
						sp->procFlags	=	PROC_ON_SPELL_LAND_VICTIM | PROC_TARGET_SELF;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	31786;
				}break;


			//Druid: Leader	of the Pack
			case  24932:
					{
						sp->Effect[1]	=	0;
						sp->Effect[2]	=	0; //removing	strange	effects.
					}break;
		
			//Druid: Improved	Leader of	the	Pack
			case  34299:
					{
					sp->proc_interval	=	6000;//6 secs
					}break;
		
		
			//fix	for	the	right	Enchant	ID for Enchant Cloak - Major Resistance
			case  27962:
			case  36285:
					{
						sp->EffectMiscValue[0] = 2998;
					}break;
		
			//muhaha,	rewriting	Retaliation	spell	as old one :D
			case  20230:
					{
						sp->Effect[0]	=	6; //aura
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	22858; //evil	,	but	this is	good for us	:D
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM; //add procflag	here since this	was	not	processed	with the others	!
					}break;
		
		
			//"bloodthirst"	new	version	is ok	but	old	version	is wrong from	now	on :(
			case  23881:
					{
						sp->Effect[1]	=	64;	//cast on	us,	it is	good
						sp->EffectTriggerSpell[1]	=	23885; //evil	,	but	this is	good for us	:D
					}break;
		
			case  23892:
				{
						sp->Effect[1]	=	64;
						sp->EffectTriggerSpell[1]	=	23886; //evil	,	but	this is	good for us	:D
					}break;
		
			case  23893:
				{
						sp->Effect[1]	=	64;	//
						sp->EffectTriggerSpell[1]	=	23887; //evil	,	but	this is	good for us	:D
					}break;
		
			case  23894:
				{
						sp->Effect[1]	=	64;	//
						sp->EffectTriggerSpell[1]	=	23888; //evil	,	but	this is	good for us	:D
					}break;
		
			case  25251:
				{
						sp->Effect[1]	=	64;	//aura
						sp->EffectTriggerSpell[1]	=	25252; //evil	,	but	this is	good for us	:D
					}break;
		
			case  30335:
				{
						sp->Effect[1]	=	64;	//aura
						sp->EffectTriggerSpell[1]	=	30339; //evil	,	but	this is	good for us	:D
					}break;
		
		
			// Hunter	-	Master Tactician
			case  34506:
			case  34507:
			case  34508:
			case  34838:
			case  34839:
					{
						sp->procFlags	=	PROC_ON_RANGED_ATTACK	|	PROC_TARGET_SELF;
					}break;		
		
			// Hunter	-	Spirit Bond
			case  19578:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	19579;
					}break;
		
			case  20895:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	24529;
					}break;
		
			case  19579:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA; //we	should do	the	same for player	too	as we	did	for	pet
						sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
						sp->EffectBasePoints[1]	=	sp->EffectBasePoints[0];
						sp->EffectAmplitude[1] = sp->EffectAmplitude[0];
						sp->EffectDieSides[1]	=	sp->EffectDieSides[0];
					}break;
		
			case  24529:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA; //we	should do	the	same for player	too	as we	did	for	pet
						sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
						sp->EffectBasePoints[1]	=	sp->EffectBasePoints[0];
						sp->EffectAmplitude[1] = sp->EffectAmplitude[0];
						sp->EffectDieSides[1]	=	sp->EffectDieSides[0];
					}break;
		
		
			// Hunter	-	Animal Handler
			case  34453:
			case  34454:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HIT_CHANCE;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
					}break;
		
		
			// Hunter	-	Catlike	Reflexes
			case  34462:
			case  34464:
			case  34465:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
					}break;
		
		
			// Hunter	-	Serpent's	Swiftness
			case  34466:
			case  34467:
			case  34468:
			case  34469:
			case  34470:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	;
						sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
				}break;
		
			// Hunter	-	Ferocious	Inspiration
			case  34455:
			case  34459:
			case  34460:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->EffectTriggerSpell[0]	=	34456;
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
						sp->Effect[1]	=	0; //remove	this
				}break;
		
			// Hunter	-	Focused	Fire
			case  35029:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	35060;
				}break;
			case  35030:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	35061;
				}break;
			case  35060:
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET;
			case  35061:
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET;
		
			// Hunter	-	Thick	Hide
			case  19609:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE;	//we do	not	support	armor	rating for pets	yet	!
						sp->EffectBasePoints[0]	*= 10; //just	give it	a	little juice :P
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19610:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE;	//we do	not	support	armor	rating for pets	yet	!
						sp->EffectBasePoints[0]	*= 10; //just	give it	a	little juice :P
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
		
			// Hunter	-	Ferocity
			case  19612:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19599:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19600:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19601:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19602:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
		
			// Hunter	-	Bestial	Swiftness
			case  19596:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_SPEED;	
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
		
			// Hunter	-	Endurance	Training
			case  19583:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19584:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19585:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19586:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
			case  19587:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
		
			// Hunter	-	Thrill of	the	Hunt
			case  34497:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
						sp->procChance = sp->EffectBasePoints[0]+1;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	34720;
				}break;
			case  34498:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
						sp->procChance = sp->EffectBasePoints[0]+1;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	34720;
				}break;
			case  34499:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
						sp->procChance = sp->EffectBasePoints[0]+1;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	34720;
				}break;
		
			// Hunter	-	Expose Weakness
			case  34500:
			case  34502:
			case  34503:
						{
						sp->procFlags	=	PROC_ON_RANGED_CRIT_ATTACK | PROC_ON_SPELL_CRIT_HIT;
				}break;
		
			//Hunter - Frenzy
			case  19621:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	19615;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->procChance = sp->EffectBasePoints[0];
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
				}break;
			case  19622:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	19615;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->procChance = sp->EffectBasePoints[0];
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
				}break;
			case  19623:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	19615;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->procChance = sp->EffectBasePoints[0];
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
				}break;
			case  19624:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	19615;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->procChance = sp->EffectBasePoints[0];
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
				}break;
			case  19625:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	19615;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->procChance = sp->EffectBasePoints[0];
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
				}break;
		
			case 56641:
			case 34120:
			case 49051:
			case 49052: //Steady Shot cast time fix
				{
						sp->CastingTimeIndex = 5; // Set 2 sec cast time
				}break;

			case 61846:
			case 61847: // Aspect of the Dragonhawk
				{	// need to copy Mod Dodge Percent aura from a separate spell
					CopyEffect(dbcSpell.LookupEntryForced(61848), 0, sp, 2);
				}break;

			//Hunter - Unleashed Fury
			case  19616:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->EffectMiscValue[0] = 1;	//tweekign melee dmg
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
				}break;
			case  19617:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->EffectMiscValue[0] = 1;	//tweekign melee dmg
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
				}break;
			case  19618:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->EffectMiscValue[0] = 1;	//tweekign melee dmg
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
				}break;
			case  19619:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->EffectMiscValue[0] = 1;	//tweekign melee dmg
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
				}break;
			case  19620:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->EffectMiscValue[0] = 1;	//tweekign melee dmg
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
				}break;
		
			//Hunter : Pathfinding
			case  19559:
				{
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			case  19560:
				{
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			/*case  5131	);
					{
						sp->SpellGroupType = 2097152;*/		// 2.4.0-SPELL-NO-LONGER-EXISTS
		/*	case  13160:
						sp->SpellGroupType = 2097152;*/		// 2.4.0-SPELL-NO-LONGER-EXISTS
		
			//Hunter : Rapid Killing - might need	to add honor trigger too here. I'm guessing	you	receive	Xp too so	i'm	avoiding double	proc
			case  34948:
				{
						sp->procFlags	=	PROC_ON_GAIN_EXPIERIENCE | PROC_TARGET_SELF;
				}break;
			case  34949:
				{
						sp->procFlags	=	PROC_ON_GAIN_EXPIERIENCE | PROC_TARGET_SELF;
				}break;
		
			// Winter's	chill
			case 12579:
				{
						sp->c_is_flags |=	SPELL_FLAG_CANNOT_PROC_ON_SELF;
				}break;	
			// Mage	-	Invisibility part	2
			case  32612:
				{
				// cancel	spells
				// use mage	invisibility bool
						sp->Effect[0]	=	SPELL_EFFECT_SANCTUARY;
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
						sp->Effect[2]	=	0;
						sp->AuraInterruptFlags |=	AURA_INTERRUPT_ON_CAST_SPELL;	//The	effect is	cancelled	if you perform or	receive	any	actions
				}break;
			//Mage - Icy Veins
			case  12472:
				{
						sp->EffectMiscValue[1] = SMT_PROC_CHANCE;
				}break;
		
			//Mage - Wand	Specialization.	Not	the	forst	thing	we messed	up.	Blizz	uses attack	as magic and wandds	as weapons :S
			case  6057:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			case  6085:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
		
			//Priest - Wand	Specialization
			case  14524:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			case  14525:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			case  14526:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			case  14527:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
			case  14528:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
				}break;
		
			//Mage - Elemental Precision
			case  29438:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_COST;
				}break;
			case  29439:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_COST;
				}break;
			case  29440:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_COST;
				}break;
		
			//Mage - Arcane	Concentration
			case  11213:
			case  12574:
			case  12575:
			case  12576:
			case  12577:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
				}break;
		
			//Mage - ClearCasting	Effect 
			//Druid - Clearcasting Effect
			case  16870:
			case  12536:
				{
						sp->procCharges	=	2;
				}break;	
		
			//Mage - Arcane	Blast
			case  36032:
				{
						sp->procFlags	|=	PROC_TARGET_SELF;
						sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
				}break;
		
			//rogue	-	Seal Fate
			case  14186:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 20;
				}break;
			case  14190:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 40;
				}break;
			case  14193:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 60;
				}break;
			case  14194:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 80;
				}break;
			case  14195:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 100;
				}break;
		
		
			// druid - Nature's	Grace
			case  16880:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
						sp->procChance = 33;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	16886;
						sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
				}break;
		
			case  61345:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
						sp->procChance = 66;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	16886;
						sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
				}break;
		
			case  61346:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
						sp->procChance = 100;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	16886;
						sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
				}break;
		
			// Nature's	Grace
			case  16886:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 100;
						sp->procCharges++; //	first	charge gets	lost when	it gets	procced
				}break;
		
			//druid	-	Blood	Frenzy
			case  16954:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 100;
				}break;
			case  16952:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 50;
				}break;
		
			//druid	-	Primal Fury
			case  16961:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 100;
				}break;
			case  16958:
				{
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
						sp->procChance = 50;
				}break;
			//Druid - Earth and Moon
			case 48506:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	60431;
						sp->procChance	=	100;
				}break;
			case 48510:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	60432;
						sp->procChance	=	100;
				}break;
			case 48511:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	60433;
						sp->procChance	=	100;
				}break;
			//druid	-	Intensity
			case  17106:
				{
				 sp->EffectApplyAuraName[1]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
				 sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			case  17107:
				{
						sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
				 sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			case  17108:
				{
						sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			//Improved Sprint
			case  13743:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 50;
				}break;
			case  13875:
				{
						sp->procChance = 100;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			//warlock	-	 Seed	of Corruption
			case  27243:
				{
						sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	27285;
						sp->procFlags	=	PROC_ON_SPELL_HIT_VICTIM | PROC_ON_DIE;
						sp->procChance = 100;
				}break;
		
			//warlock	-	 soul	link
			case  19028:
				{
				//this is	for	the	trigger	effect
						sp->Effect[0]=SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[0] = SPELL_AURA_SPLIT_DAMAGE;
						sp->EffectMiscValue[0]=20;
				//sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		
				//this is	for	the	extra	5% dmg for caster	and	pet
						sp->Effect[1]	=	6;
						sp->EffectApplyAuraName[1] = 79;
						sp->EffectBasePoints[1]	=	4; //4+1=5
						sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
						sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET;
				}break;
		
			//warlock: Nightfall
			case  18094:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	17941;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 2;
						sp->EffectSpellClassMask[0][0]=0x0;
				}break;
			case  56218://Glyph of Corruption
			case  18095:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	17941;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 4;
						sp->EffectSpellClassMask[0][0]=0x0;
				}break;
			case 17941:
				{
						sp->AuraInterruptFlags	=	AURA_INTERRUPT_ON_CAST_SPELL;
				}break;
			//Warlock - Backdraft
			case 47258:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	54274;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 100;
						sp->procCharges	= 4;
						sp->EffectSpellClassMask[0][0]=0x00800000;
						sp->EffectSpellClassMask[0][1]=0x00800000;
				}break;
			case 47269:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	54276;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 100;
						sp->procCharges	= 4;
						sp->EffectSpellClassMask[0][0]=0x00800000;
						sp->EffectSpellClassMask[0][1]=0x00800000;
				}break;
			case 47260:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	54277;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 100;
						sp->procCharges	= 4;
						sp->EffectSpellClassMask[0][0]=0x00800000;
						sp->EffectSpellClassMask[0][1]=0x00800000;
				}break;
			//Warlock - Eradication
			case 47195:
			case 47196:
			case 47197:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	47274;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->proc_interval	=	30000;
				}break;
			
			//warlock: Empowered Corruption
			case  32381:
				{
						sp->EffectBasePoints[0]	*= 6;
				}break;
			case  32382:
				{
						sp->EffectBasePoints[0]	*= 6;
				}break;
			case  32383:
				{
						sp->EffectBasePoints[0]	*= 6;
				}break;
		
			//warlock: Improved	Enslave	Demon
			case  18821:
				{
						sp->EffectMiscValue[0]=SMT_SPELL_VALUE_PCT;
						sp->EffectBasePoints[0]	=	-(sp->EffectBasePoints[0]+2);
				}break;	
			//Mage - Improved	Blizzard
			case  11185:
				{		 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	12484;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			case  12487:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	12485;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			case  12488:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	12486;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			//mage - Combustion
			case  11129:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL | PROC_ON_SPELL_CRIT_HIT	|	PROC_TARGET_SELF;
						sp->procCharges	=	0;
						sp->c_is_flags |=	SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;
				}break;
		
			//mage - Master	of Elements
			case  29074:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	29077;
						sp->procFlags	=	uint32(PROC_ON_SPELL_CRIT_HIT|PROC_TARGET_SELF);
						sp->procChance = 100;
				}break;
			case  29075:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	29077;
						sp->procFlags	=	uint32(PROC_ON_SPELL_CRIT_HIT|PROC_TARGET_SELF);
						sp->procChance = 100;
				}break;
			case  29076:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	29077;
						sp->procFlags	=	uint32(PROC_ON_SPELL_CRIT_HIT|PROC_TARGET_SELF);
						sp->procChance = 100;
				}break;
		
			//mage:	Blazing	Speed
			case  31641:	
					{
						sp->EffectTriggerSpell[0]	=	31643;
				}break;
			case  31642:
				{
						sp->EffectTriggerSpell[0]	=	31643;
				}break;

			//mage talent	"frostbyte". we	make it	to be	dummy
			case  11071:
			case  12496:
			case  12497:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
				}break;

			//rogue-shiv ->	add	1	combo	point
			case  5938:
				{
						sp->Effect[1]=80;
						sp->Flags3 &=	~FLAGS3_REQ_BEHIND_TARGET;	//Doesn't	require	to be	behind target
				}break;
		
			//warlock	-	Demonic	Sacrifice
			case  18789:
			case  18790:
			case  18791:
			case  18792:
			case  35701:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_ON_PET;
				}break;

		
			//warlock	-	Demonic	Tactics
			case  30242:
				{
						sp->Effect[0]	=	0; //disble	this.	This is	just blizz crap. Pure	proove that	they suck	:P
						sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
						sp->EffectApplyAuraName[2] = SPELL_AURA_MOD_SPELL_CRIT_CHANCE; //lvl 1 has it	fucked up	:O
						sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
				}break;
			case  30245:
			case  30246:
			case  30247:
			case  30248:
				{
						sp->Effect[0]	=	0; //disble	this.	This is	just blizz crap. Pure	proove that	they suck	:P
						sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
						sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
				}break;
		
			//warlock	-	Demonic	Resilience
			case  30319:
			case  30320:
			case  30321:
				{
						sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
				}break;
		
			//warlock	-	Improved Imp
			case  18694:
			case  18695:
			case  18696:
			case  18705:
			case  18706:
			case  18707:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
		
			//warlock	-	Improved Succubus
			case  18754:
			case  18755:
			case  18756:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
				}break;
		
			//warlock	-	Fel	Intellect
			case  18731:
			case  18743:
			case  18744:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
						sp->EffectMiscValue[0] = 3;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
		
			//warlock	-	Fel	Stamina
			case  18748:
			case  18749:
			case  18750:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	;
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
						sp->EffectMiscValue[0] = 2;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;
		
			//warlock	-	Unholy Power
			case  18769:
			case  18770:
			case  18771:
			case  18772:
			case  18773:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	;
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				//this is	required since blizz uses	spells for melee attacks while we	use	fixed	functions
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
						sp->EffectMiscValue[1] = SCHOOL_NORMAL;
						sp->EffectBasePoints[1]	=	sp->EffectBasePoints[0]	;
				}break;
		
			//warlock	-	Master Demonologist	-	25 spells	here
			case  23785:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	|	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	23784;
				}break;
			case  23822:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	|	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	23830;
				}break;
			case  23823:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	|	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	23831;
				}break;
			case  23824:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	|	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	23832;
				}break;
			case  23825:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET	|	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	35708;
				}break;
			//and	the	rest
			case  23784:
			case  23830:
			case  23831:
			case  23832:
			case  35708:
				{
						sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;

			case  23759:
			case  23760:
			case  23761:
			case  23762:
			case  23826:
			case  23827:
			case  23828:
			case  23829:
			case  23833:
			case  23834:
			case  23835:
			case  23836:
			case  23837:
			case  23838:
			case  23839:
			case  23840:
			case  23841:
			case  23842:
			case  23843:
			case  23844:
				{
					sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET;
					sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
				}break;

			case  35702:
			case  35703:
			case  35704:
			case  35705:
			case  35706:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_EXPIREING_WITH_PET;
						sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
						sp->Effect[1]	=	0; //hacks,	we are handling	this in	another	way
				}break;
			//warlock	-	Improved Healthstone
			case  18692:
			case  18693:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
				}break;
		
			//warlock	-	Unstable Affliction
			case  30108:
			case  30404:
			case  30405:
				{
						sp->procFlags	=	PROC_ON_PRE_DISPELL_AURA_VICTIM	;
						sp->procChance = 100;
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	43523;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
				}break;
		
			//warlock	-	Improved Drain Soul
			case  18213:
			case  18372:
				{
						sp->procFlags	=	PROC_ON_TARGET_DIE | PROC_TARGET_SELF;
						sp->procChance = 100;
						sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	18371;
						sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
						sp->Effect[2]	=	0	;	//remove this	effect
				}break;
		
			//warlock	-	Shadow Embrace
			case  32385:
			case  32387:
			case  32392:
			case  32393:
			case  32394:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->Effect[1]	=	0	;	//remove this	effect ? Maybe remove	the	other	one	:P xD
				}break;
		
			//warlock	-	soul leech
			case 30293:
			case 30295:
			case 30296:
				{
					sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0]	=	30294;
					sp->procChance = sp->RankNumber * 10;
					sp->procFlags	=	PROC_ON_SPELL_LAND;
				}break;
		
			//warlock	-	Pyroclasm
			case  18073:
			case  18096:
				{
						sp->Effect[0]	=	0; //delete	this owerride	effect :P
						sp->EffectTriggerSpell[1]	=	18093; //trigger spell was wrong :P
						sp->procFlags	=	PROC_ON_ANY_HOSTILE_ACTION;
						sp->procChance = 26; //god,	save us	from fixed values	!
				}break;
		
			//Mage - Improved	Scorch
			case  11095:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance =33;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			case  12872:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;	
						sp->procChance =66;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			case  12873:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance =100;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			//Nature's Grasp
			case  16689:
				{
						sp->Effect[0]	=	6; 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	339; 
						sp->Effect[1]	=	0; 
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM	|	PROC_REMOVEONUSE;
						sp->AuraInterruptFlags = 0;	//we remove	it on	proc or	timeout
						sp->procChance = 100;
				}break;
			case  16810:
				{
						sp->Effect[0]	=	6; 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	1062;	
						sp->Effect[1]	=	0; 
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM	|	PROC_REMOVEONUSE;
						sp->AuraInterruptFlags = 0;	//we remove	it on	proc or	timeout
						sp->procChance = 100;
				}break;
			case  16811:
				{
						sp->Effect[0]	=	6; 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	5195;	
						sp->Effect[1]	=	0; 
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM	|	PROC_REMOVEONUSE;
						sp->AuraInterruptFlags = 0;	//we remove	it on	proc or	timeout
						sp->procChance = 100;
				}break;
			case  16812:
				{
						sp->Effect[0]	=	6; 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	5196;	
						sp->Effect[1]	=	0; 
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM	|	PROC_REMOVEONUSE;
						sp->AuraInterruptFlags = 0;	//we remove	it on	proc or	timeout
						sp->procChance = 100;
				}break;
			case  16813:
				{
						sp->Effect[0]	=	6; 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	9852;	
						sp->Effect[1]	=	0; 
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM	|	PROC_REMOVEONUSE;
						sp->AuraInterruptFlags = 0;	//we remove	it on	proc or	timeout
						sp->procChance = 100;
				}break;
			case  17329:
				{
						sp->Effect[0]	=	6; 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	9853;	
						sp->Effect[1]	=	0; 
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM	|	PROC_REMOVEONUSE;
						sp->AuraInterruptFlags = 0;	//we remove	it on	proc or	timeout
						sp->procChance = 100;
				}break;
			case  27009:
				{
						sp->Effect[0]	=	6; 
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	26989; 
						sp->Effect[1]	=	0; 
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM	|	PROC_REMOVEONUSE;
						sp->AuraInterruptFlags = 0;	//we remove	it on	proc or	timeout
						sp->procChance = 100;
				}break;
		
			//wrath	of air totem targets sorounding	creatures	instead	of us
			case  2895:
				{
						sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
						sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
						sp->EffectImplicitTargetA[2] = 0;
						sp->EffectImplicitTargetB[0] = 0;
						sp->EffectImplicitTargetB[1] = 0;
						sp->EffectImplicitTargetB[2] = 0;
				}break;
		
			//-----BLEED effects-----	(setting mech	to BLEED)
			//garrot
			case  703:
			case  8631:
			case  8632:
			case  8633:
			case  11289:
			case  11290:
			case  26839:
			case  26884:
			case  9007:
			case  9824:
			case  9826:
			case  27007:
			case  772:
			case  6546:
			case  6547:
			case  6548:
			case  11572:
			case  11573:
			case  11574:
			case  25208:
			case  1079:
			case  9492:
			case  9493:
			case  9752:
			case  9894:
			case  9896:
			case  27008:
			case  1943:
			case  8639:
			case  8640:
			case  11273:
			case  11274:
			case  11275:
			case  26867:
			case  1822:
			case  1823:
			case  1824:
			case  9904:
			case  27003:
			case  33745:
				{
						sp->MechanicsType	=	MECHANIC_BLEEDING;
				}break;

			//Druid: Natural Shapeshifter
			case  16833:
			case  16834:
			case  16835:
				{
						sp->DurationIndex	=	0;
				}break;

		
			//Priest - Inspiration proc	spell
			case  14893:
			case  15357:
			case  15359:
				{
						sp->rangeIndex = 4;
				}break;
		
			//Relentless Strikes
			case 14179:
			case 58422:
			case 58423:
			case 58424:
			case 58425:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;//proc	spell
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			//priest - surge of	light
			case  33150:
			case  33154:
				{
						sp->procFlags	=	uint32(PROC_ON_SPELL_CRIT_HIT_VICTIM | PROC_TARGET_SELF);
				}break;

			case  33151:
				{
						sp->AuraInterruptFlags = AURA_INTERRUPT_ON_CAST_SPELL;
				}break;
		
			//Seal of	Justice	-lowered proc	chance (experimental values	!)
			case  20164:
			case  31895:
				{
						sp->procChance = 20;
				}break;
	
			//make Berserking	a	simple spell 
			case  20554:
			case  26296:
			case  26297:
				{
						sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	26635;
				}break;
		
			//rogue	-	intiative
			case  13976:
			case  13979:
			case  13980:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procFlags	=	uint32(PROC_ON_CAST_SPELL|PROC_TARGET_SELF);
				}break;
		
			//this an	on equip item	spell(2824)	:	 ice arrow(29501)
			case  29501:
				{
						sp->procChance = 30;//some say it	is triggered every now and then
						sp->procFlags	=	PROC_ON_RANGED_ATTACK;
				}break;
		
			//warrior	-	second wind	should trigger on	self
			case  29841:
			case  29842:
				{
						sp->procFlags	|= PROC_TARGET_SELF;
				}break;

			// Improved Revenge
			case 12797:
			case 12799:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Glyph of Revenge
			case 58364:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[0][0]=0x0;
					sp->EffectSpellClassMask[0][1]=0x0;
				}break;
			// Glyph of Revenge Proc
			case 58363:
				{
					sp->AuraInterruptFlags  =   AURA_INTERRUPT_ON_CAST_SPELL;
				}break;
			
			//warrior	-	berserker	rage is	missing	1	effect = regenerate	rage
			case  18499:
				{
						sp->Effect[2]	=	6;
						sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[2]	=	37521; //not sure	if this	is the one.	In my	time this	adds 30	rage
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM	|	PROC_TARGET_SELF;
				}break;
		
			//warrior	-	improved berserker rage
			case  20500:
			case  20501:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
				}break;
		
			// warrior - Spell Reflection
			case  23920:
				{
						sp->procFlags	=	PROC_NULL; //	No need	to proc
				}break;

		
			// warrior - Titan's Grip
			case  46917:	// main	spell
				{
						SpellEntry * sp2 = dbcSpell.LookupEntryForced(	49152	);	// move	this aura	into main	spell
						if(sp != NULL)
						{
							sp->Effect[1] = sp2->Effect[0];
							sp->EffectApplyAuraName[1] = sp2->EffectApplyAuraName[0];
							sp->EffectMiscValue[1] = sp2->EffectMiscValue[0];
							sp->EffectSpellClassMask[1][0] = sp2->EffectSpellClassMask[0][0];
							sp->EffectSpellClassMask[1][1] = sp2->EffectSpellClassMask[0][1];
							sp->EffectSpellClassMask[1][2] = sp2->EffectSpellClassMask[0][2];
							sp->EffectBasePoints[1] = sp2->EffectBasePoints[0];
							sp->EffectDieSides[1]= sp2->EffectDieSides[0];
							sp->EffectBaseDice[1]= sp2->EffectBaseDice[0] ;
						}
				}break;
		
			// Charge	-	Changing from	dummy	for	the	power	regen
			case 100:
			case 6178:
			case 11578:
				{
					sp->Effect[1]	=	SPELL_EFFECT_ENERGIZE;
					sp->EffectMiscValue[1] = 1;
				}break;
		
			//warrior	-	Rampage
			case  30030:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
						sp->EffectTriggerSpell[0]	=	sp->EffectTriggerSpell[1];
				}break;
			case  30033:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
						sp->EffectTriggerSpell[0]	=	sp->EffectTriggerSpell[1];
				}break;

			// warrior - overpower r1
			case 7384:
			// warrior - overpower r2
			case 7887:
			// warrior - overpower r3
			case 11584:
			// warrior - overpower r4
			case 11585:
				{
						sp->Attributes |=	ATTRIBUTES_CANT_BE_DPB;
				}break;

		
			// warrior - heroic	fury
			case 60970:
				{
						sp->Effect[1]	=	3;
				}break;
		
			// priest	-	Reflective Shield
			case 33201:
			case 33202:
			case 33203:
			case 33204:
			case 33205:
				{
						sp->procFlags	=	PROC_ON_ABSORB;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	33619; //!!	WRONG	spell, we	will make	direct dmg here
				}break;

			case  20608:	//Reincarnation
					{
						for(uint32 i=0;i<8;i++)
						{
								if(sp->Reagent[i])
								{
									sp->Reagent[i] = 0;
									sp->ReagentCount[i]	=	0;
								}
						}
					}break;

			// druid - travel	form
			case 5419:
					{
						sp->Attributes |=	ATTRIBUTES_MOUNT_CASTABLE;
					}break;

			//Druid Eclipse
			case 48516:
					{
						sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	48517;//Damage Done by Wrath 20% more
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
						sp->procChance	=	33;
						sp->proc_interval	=	30000;
						sp->EffectApplyAuraName[1]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	48518;//Crit Chance of Starfire 30% more
						sp->EffectSpellClassMask[0][0]	=	0x0;
						sp->EffectSpellClassMask[0][1]	=	0x0;
					}break;
			case 48521:
					{
						sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	48517;//Damage Done by Wrath 20% more
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
						sp->procChance	=	66;
						sp->proc_interval	=	30000;
						sp->EffectApplyAuraName[1]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	48518;//Crit Chance of Starfire 30% more
						sp->EffectSpellClassMask[0][0]	=	0x0;
						sp->EffectSpellClassMask[0][1]	=	0x0;
					}break;
			case 48525:
					{
						sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	48517;//Damage Done by Wrath 20% more
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
						sp->procChance	=	100;
						sp->proc_interval	=	30000;
						sp->EffectApplyAuraName[1]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[1]	=	48518;//Crit Chance of Starfire 30% more
						sp->EffectSpellClassMask[0][0]	=	0x0;
						sp->EffectSpellClassMask[0][1]	=	0x0;
					}break;
			//Druid - Living Seed
			case 48496:
			case 48499:
			case 48500:
				{
					sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0]	=	48504;
					sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
					sp->procChance	=	100;
				}break;
			// druid - Naturalist
			case  17069:
			case  17070:
			case  17071:
			case  17072:
			case  17073:
				{
						sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
						sp->EffectMiscValue[1] = 1;	
				}break;
		
			// Druid:	Omen of	Clarity
			case  16864:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_ON_CAST_SPELL;
						sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->EffectTriggerSpell[0]	=	16870;
						sp->procChance = 6;
						sp->proc_interval	=	10000;
				}break;
		
			//Energized	
			case  43750:	
					{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
					}break;

		
			//Spell	Haste	Trinket
			case  33297:	
					{
						sp->procFlags	=	PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
					}break;
			case 57345: // Darkmoon Card: Greatness
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->proc_interval = 45000;
					sp->EffectTriggerSpell[0] = 60229;
				}break;
			// Mystical Skyfire Diamond
			case 32837:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Swordguard Embroidery
			case 55776:
				{
						sp->proc_interval	=	60000;
						sp->procFlags = PROC_ON_MELEE_ATTACK;
				}break;
			// Chuchu's Tiny Box of Horrors
			case 61618:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_MELEE_ATTACK;
				}break;		
			case 60063: // Sundial of the Exiled
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->proc_interval = 45000;
				}break;
			case 57351: // Darkmoon Card: Berserker!
				{
					sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK | PROC_ON_ANY_DAMAGE_VICTIM;;	// when you strike, or are struck in combat
				}break;
			case 60196:
				{
					sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
				}break;
			// Darkmoon Card: Death
			case 57352:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK | PROC_ON_CAST_SPELL;
				}break;
			case 60493: //Dying Curse
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->proc_interval = 45000;
				}break;
		
			// Ashtongue Talisman	of Shadows 
			case  40478:
			// Ashtongue Talisman	of Swiftness
			case  40485:
			// Ashtongue Talisman	of Valor
			case  40458:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;

		
			// Memento of	Tyrande
			case  37655:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 10;
						sp->proc_interval	=	45000;
				}break;
		
			// Ashtongue Talisman	of Insight
			case  40482:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
					}break;

		
			//Ashtongue	Talisman of	Equilibrium
			case  40442:
				{
						sp->Effect[0]	=	6;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 40;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectTriggerSpell[0]	=	40452;
						sp->maxstack = 1;
						sp->Effect[1]	=	6;
						sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 25;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectTriggerSpell[1]	=	40445;
						sp->maxstack = 1;
						sp->Effect[2]	=	6;
						sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 25;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectTriggerSpell[2]	=	40446;
						sp->maxstack = 1;
				}break;
		
			//Ashtongue	Talisman of	Acumen
			case  40438:
				{
						sp->Effect[0]	=	6;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 10;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectTriggerSpell[0]	=	40441;
						sp->maxstack = 1;
						sp->Effect[1]	=	6;
						sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 10;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectTriggerSpell[1]	=	40440;
						sp->maxstack = 1;
				}break;
		
			//Ashtongue	Talisman of	Lethality
			case  40460:
				{
						sp->Effect[0]	=	6;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 20;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectTriggerSpell[0]	=	40461;
						sp->maxstack = 1;
				}break;
		
			//Serpent-Coil Braid
			case  37447:
				{
						sp->Effect[0]	=	6;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 100;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->EffectTriggerSpell[0]	=	37445;
						sp->maxstack = 1;
				}break;
		
			//Item Set:	Malorne	Harness
			case  37306:
			case  37311:
			//Item Set:	Deathmantle
			case  37170:
				{
						sp->procChance = 4;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
				}break;
		
			//Item Set:	Netherblade
			case  37168:
				{
						sp->procChance = 15;
				//sp->procFlags	=	PROC_ON_CAST_SPELL;	Need new flag	-	PROC_ON_FINISH_MOVE;
				}break;
		
			//Item Set:	Tirisfal Regalia
			case  37443:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
				}break;
		
			//Item Set:	Avatar Regalia
			case  37600:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 6;
				}break;
		
			//Item Set:	Incarnate	Raiment
			case  37568:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			//Item Set:	Voidheart	Raiment
			case  37377:
				{
						sp->Effect[0]	=	6;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 5;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->proc_interval	=	20;
						sp->EffectTriggerSpell[0]	=	37379;
				}break;
			case  39437:
				{
						sp->Effect[0]	=	6;
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procChance = 5;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->proc_interval	=	20;
						sp->EffectTriggerSpell[0]	=	37378;
				}break;
		
			//Item Set:	Cataclysm	Raiment
			case  37227:
				{
						sp->proc_interval	=	60000;
						sp->procChance = 100;
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
				}break;
		
			//Item Set:	Cataclysm	Regalia
			case  37228:
				{
						sp->procChance = 7;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			case  37237:
				{
						sp->procChance = 25;
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
				}break;
		
			//Item Set:	Cataclysm	Harness
			case  37239:
				{
						sp->procChance = 2;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
				}break;
		
			//Item Set:	Cyclone	Regalia
			case  37213:
				{
						sp->procChance = 11;
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
				}break;
		
			//Item Set:	Lightbringer Battlegear
			case  38427:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
						sp->procChance = 20;
				}break;
		
			//Item Set:	Crystalforge Battlegear
			case  37195:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 6;
				}break;
		
			//Item Set:	Crystalforge Raiment
			case  37189:
				{
						sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
						sp->proc_interval	=	60000;
				}break;

			case  37188:
			//Item Set:	Crystalforge Armor
			case  37191:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			//Item Set:	Destroyer	Armor
			case  37525:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM;
						sp->procChance = 7;
				}break;
		
			//Item Set:	Destroyer	Battlegear
			case  37528:
			//Item Set:	Warbringer Armor
			case  37516:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
						sp->procChance = 100;
				}break;
		
			//Paladin	-	Improved Lay on	Hands
			case  20234:
			case  20235:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
		
			// Sudden	Death
			case 29724:
			case 29725:
			case 29723:
				{
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
				}break;
		
			// Taste for Blood
			case 56638:
			case 56637:
			case 56636:
				{
					sp->procFlags	=	PROC_ON_ANY_HOSTILE_ACTION;
				}break;
		
			// Ice Lance
			case 30455:
			case 42913:
			case 42914:
				{
					sp->Dspell_coef_override = 0.1429f;
				}break;
		
			// Flametongue weapon
			case 58792:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	58788;
				}break;
			case 58791:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	58787;
				}break;
			case 58784:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	58786;
				}break;
			case 16313:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	25488;
				}break;
			case 16312:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	16344;
				}break;
			case 16311:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	16343;
				}break;
			case 15569:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	10445;
				}break;
			case 15568:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	8029;
				}break;
			case 15567:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	8028;
				}break;
			case 10400:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->EffectTriggerSpell[0]	=	8026;
				}break;

			//windfury weapon
			case  33757:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
						sp->EffectTriggerSpell[0]	=	25504;
						sp->procChance = 20;
						sp->proc_interval	=	3000;
						sp->maxstack = 1;
						// Current proc system doesn't support common proc_interval for 2
						// procs making dual wielding WF overpowered. So it is disabled for now
						//sp->always_apply = true; //	so that	we can apply 2 wf	auras	while	dual-wielding
				}break;
		
			//for	test only
			//case  32796:
			//	{
			//{
				//printf("!!!!!!hash %u	\n",sp->NameHash);
				//sp->procChance=100;
				//SpellDuration	*sd=sSpellDuration.LookupEntryForced(sp->DurationIndex);
				//printf("iterruptflag %u, duration	%u",sp->AuraInterruptFlags,GetDuration(sd));
			//}
		
			//improoved	berserker	stance should	be triggered on	berserker	stance use
			//sp = sSpellStore.LookupEntryForced(12704);
			//	{	sp->procFlags	=	PROC_ON_CAST_SPECIFIC_SPELL;
		
			//sp = sSpellStore.LookupEntryForced(16280);
			//	{	printf("!!Interrupt	flags	%u interval	%u charges %u\n",sp->AuraInterruptFlags,sp->proc_interval,sp->procCharges);
			//sp = sSpellStore.LookupEntryForced(16284);
			//	{	printf("Interrupt	flags	%u\n",sp->AuraInterruptFlags);
		
			// dot heals
			case  38394:
				{
						sp->procFlags	=	1024;
					//sp->SpellGroupType = 6;
						sp->Dspell_coef_override = 0;
						sp->OTspell_coef_override	=	0;
				}break;
		
			// Citrine Pendant of	Golden Healing
			case  25608:
				{
						sp->Dspell_coef_override = 0;
						sp->OTspell_coef_override	=	0;
				}break;
		
			case  16972:
			case  16974:
			case  16975:
				{
					//fix	for	Predatory	Strikes
					uint32 mm	=	(1<<(FORM_BEAR-1))|(1<<(FORM_DIREBEAR-1))|(1<<(FORM_MOONKIN-1))|(1<<(FORM_CAT-1));
					sp->RequiredShapeShift = mm;
				}break;
		
			case  20134:
				{
						sp->procChance = 50;
				}break;
		
			/* aspect	of the pack	-	change to	AA */
			case  13159:
				{
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AREA_AURA;
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
				}break;

			/* aspect	of the cheetah - add proc	flags	*/
			case  5118:
					{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;;
				}break;

			
			case SPELL_RANGED_GENERAL:
			case SPELL_RANGED_THROW:
			case 26679:
			case 29436:
			case 37074:
			case 41182:
			case 41346:
				{
					if(	sp->RecoveryTime==0	&& sp->StartRecoveryTime ==	0	)
						sp->RecoveryTime = 1600;
				}break;

			case  SPELL_RANGED_WAND:
				{
						sp->Spell_Dmg_Type = SPELL_DMG_TYPE_RANGED;
						if(	sp->RecoveryTime==0	&& sp->StartRecoveryTime ==	0	)
							sp->RecoveryTime = 1600;
				}break;
		
			// Druid Trinket Living	Root of	the	Wildheart
			case  37336:
				{
						sp->Effect[0]	=	SPELL_EFFECT_DUMMY;//	oh noez, we	make it	DUMMY, no	other	way	to fix it	atm
				}break;

		
			/**********************************************************
			*	Misc stuff (questfixes etc)
			**********************************************************/
		
			case  30877:
				{
						sp->EffectImplicitTargetB[0]=0;
				}break;

		
			case 23179:
					{
						sp->EffectMiscValue[0] = 1434;
				}break;
		
			//////////////////////////////////////////////////////
			// CLASS-SPECIFIC	SPELL	FIXES						//
			//////////////////////////////////////////////////////
		
			/* Note: when	applying spell hackfixes,	please follow	a	template */
		
			//////////////////////////////////////////
			// WARRIOR								//
			//////////////////////////////////////////
			case 7405: //	Sunder Armor
			case 7386: //	Sunder Armor
			case 8380: //	Sunder Armor
			case 11596:	// Sunder	Armor
			case 11597:	// Sunder	Armor
			case 25225:	// Sunder	Armor
			case 30330:	// Mortal	Strike Ranks 
			case 25248:	// Mortal	Strike Ranks 
			case 21553:	// Mortal	Strike Ranks 
			case 21552:	// Mortal	Strike Ranks 
			case 21551:	// Mortal	Strike Ranks 
			case 12294:	// Mortal	Strike Ranks 
			case 16511:	// Hemo	Rank 1
			case 17347:	// Hemo	Rank 2
			case 17348:	// Hemo	Rank 3
			case 26864:	// Hemo	Rank 4
				{
						sp->Unique = true;
				}break;

			// Wrecking Crew
			case 46867:
			case 56611:
			case 56612:
			case 56613:
			case 56614:
				{
						sp->procFlags	=	 PROC_ON_CRIT_ATTACK;
				}break;
			// Enrage
			case 12317:
			case 13045:
			case 13046:
			case 13047:
			case 13048:
				{
						sp->procFlags	=	 PROC_ON_ANY_DAMAGE_VICTIM;
				}break;
			// Improved Defensive Stance (Missing Parry Flag)
			case 29593:
			case 29594:
				{
						sp->procFlags	=	 PROC_ON_BLOCK_VICTIM | PROC_ON_DODGE_VICTIM;
				}break;
			// Sword and Board
			case 46951:
			case 46952:
			case 46953:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Sword and Board Refresh
			case 50227:
				{
						sp->Effect[1]	=	3;
				}break;
			//////////////////////////////////////////
			// PALADIN								//
			//////////////////////////////////////////
		
			// Insert	paladin	spell	fixes	here
		
				// Seal	of Command - Holy	damage,	but	melee	mechanics	(crit	damage,	chance,	etc)
			case  20424:
				{
					sp->is_melee_spell = true;
				}break;

		
		
			//////////////////////////////////////////
			// HUNTER								//
			//////////////////////////////////////////

			//Hunter - Go for the Throat
			case 34950:
			case 34954:
				{
					sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
				}break;
			case 34952:
			case 34953:
				{
					sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				}break;

			//Mend Pet Fix - The spell used to be channeled pre-2.1. While Blizzard changed the spell cast to insta-cast, they never took out the interrupt flag
			case 136:
			case 3111:
			case 3661:
			case 3662:
			case 13542:
			case 13543:
			case 13544:
			case 27046:
				{
					sp->ChannelInterruptFlags = 0;
				}break;
			//End Mend Pet Fixes

			//Ranged Weapon Specialization
			case 19507: 
			case 19508:
			case 19509:
			case 19510:
			case 19511:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
					sp->EffectMiscValue[0] = 1;
				}break;
			//Two Handed Weapon Specialization and One Handed Weapon Specializacion
			//Warrior and Paladin and Death Knight - this will change on 3.1.0
			case 20111:
			case 20112:
			case 20113:
			case 12163:
			case 12711:
			case 12712:
			case 16538:
			case 16539:
			case 16540:
			case 16541:
			case 16542:
			case 20196:
			case 20197:
			case 20198:
			case 20199:
			case 20200:
			case 55107:
			case 55108:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
					sp->EffectMiscValue[0] = 2;
				}break;
			//Frost Trap
			case 13809:
				{
					sp->procFlags = PROC_ON_TRAP_TRIGGER;
					sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
					sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
					sp->Effect[2] = 0;  //stop strange effects
				}break;

			//Snakes from Snake Trap cast this, shouldn't stack
			case 25810:
			case 25809:
				{
					sp->maxstack = 1;
				}break;

			case  27065:
			case  20904:
			case  20903:
			case  20902:
			case  20901:
			case  20900:
			case  19434:
				{
						sp->Unique = true;
				}break;

			//Hunter : Explosive Trap
			case 13813:
				{
					sp->procFlags = PROC_ON_TRAP_TRIGGER;
					sp->EffectTriggerSpell[1] = 13812;
				}break;

			case 14316:
				{
					sp->procFlags = PROC_ON_TRAP_TRIGGER;
					sp->EffectTriggerSpell[1] = 14314;
				}break;

			case 14317:
				{	
					sp->procFlags = PROC_ON_TRAP_TRIGGER;
					sp->EffectTriggerSpell[1] = 14315;
				}break;

			case 27025:
				{
					sp->procFlags = PROC_ON_TRAP_TRIGGER;
					sp->EffectTriggerSpell[1] = 27026;
				}break;

				//Hunter : Entrapment
			case 19184:
			case 19387:
			case 19388:
				{
					sp->procFlags = PROC_ON_TRAP_TRIGGER;
				}break;
			// Improved Steady Shot
			case 53221:
			case 53222:
			case 53224:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[0][0] = 0x0;
					sp->EffectSpellClassMask[0][1] = 0x0;
				}break;
			//////////////////////////////////////////
			// ROGUE								//
			//////////////////////////////////////////
		
			// Let's hack	the	entire cheating	death	effect to	damage perc	resist ;)
			case 45182:	// Cheating	Death	buff
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
						sp->EffectMiscValue[0] = -90;
				}break;
		
			// Wound Poison	Stuff
			case 27189:	
			case 13224:	
			case 13223:	
			case 13222:	
			case 13218:	
				{
						sp->Unique = true;
				}break;

			// Killing Spree
			case 51690:
				{
					sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
					sp->Effect[1]	=	0;
					sp->Effect[2]	=	0;
					sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
				}break;
			// Focused Attacks
			case 51634:
			case 51635:
			case 51636:
				{
						sp->procFlags = PROC_ON_CRIT_ATTACK;
				}break;
			//////////////////////////////////////////
			// PRIEST								//
			//////////////////////////////////////////
		
			// Prayer	of mending (tricky one :()
			case 33076:
				{
				sp->Effect[0]	=	SPELL_EFFECT_TRIGGER_SPELL;
				sp->EffectTriggerSpell[0]	=	41635;
				sp->Effect[1]	=	SPELL_EFFECT_DUMMY;
				sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
				sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
				sp->EffectImplicitTargetB[0] = 0;
				sp->EffectImplicitTargetB[1] = 0;
				}break;
		
			// triggered spell,	this is	the	aura
			case 41635:
				{
				sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
				sp->EffectTriggerSpell[0]	=	41637;
				sp->procCharges	=	0;
				sp->procChance = 101;
				}break;
			// triggered on	hit, this	is the spell that	does the healing/jump
			case 41637:
				{
				sp->Effect[0]	=	SPELL_EFFECT_DUMMY;
				sp->EffectBasePoints[0]	=	5;
				sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
				sp->EffectImplicitTargetB[0] = 0;
				}break;	
			// Insert	priest spell fixes here
		
			//////////////////////////////////////////
			// SHAMAN								//
			//////////////////////////////////////////
			case 51466:
			case 51470: //Elemental Oath
				{
					sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
					sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_FLAT_MODIFIER;
					sp->EffectMiscValue[1] = SMT_LAST_EFFECT_BONUS;
					sp->EffectSpellClassMask[1][0] = 0;
					sp->EffectSpellClassMask[1][1] = 0x00004000; // Clearcasting
				}break;
			case 51562:
			case 51563:
			case 51564:
			case 51565:
			case 51566: // Tidal Waves
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[0][0] = 0x00000100;	// Chain heal
					sp->EffectSpellClassMask[0][1] = 0x00000000;
					sp->EffectSpellClassMask[0][2] = 0x00000010;	// Riptide
				}break;
			case 53390:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			case 51940:
			case 51989:
			case 52004:
			case 52005:
			case 52008: // Earthliving Weapon
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->procChance = 20;
				}break;
			case 51945:
			case 51990:
			case 51997:
			case 51998:
			case 51999:
			case 52000:
				{
					sp->logsId = sp->Id;
				}break; 
			case 55198:	// Tidal Force
				{
					sp->Effect[0] = SPELL_EFFECT_DUMMY;
					sp->EffectApplyAuraName[0] = 0;
					sp->EffectTriggerSpell[0] = 55166;
				}break;
			case 55166: 
				{
					sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
				}break;
			case 51525:
			case 51526:
			case 51527:	// Static Shock
				{
					sp->procFlags = PROC_ON_MELEE_ATTACK;
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0] = sp->Id;
				}break;
			case 16180:
			case 16196:
			case 16198: // Improved Water Shield
				{
					sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectSpellClassMask[0][0] = 0x000000C0; // Healing Wave and Lesser Healing Wave
					sp->EffectSpellClassMask[0][2] = 0x00000010; //Riptide
					sp->EffectTriggerSpell[0] = sp->Id;
				}break;
			case 16187:
			case 16205:
			case 16206:
			case 16207:
			case 16208: // Restorative Totems
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
					sp->EffectMiscValue[0] = SMT_DAMAGE_DONE;
					sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
				}break;
			case 31616: // Nature's Guardian
				{
					sp->logsId = sp->Id;
					sp->fixed_dddhcoef = 0.0f;
					sp->spell_can_crit = false;
				}break;
		
			//////////////////////////////////////////
			// MAGE								//
			//////////////////////////////////////////
		
			// Insert	mage spell fixes here
		
			//improved blink
			case  31570:
			case  31569:
				{
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;

		
		
			//////////////////////////////////////////
			// WARLOCK								//
			//////////////////////////////////////////
		
			// Insert	warlock	spell	fixes	here
		
			//////////////////////////////////////////
			// DRUID								//
			//////////////////////////////////////////
		
			// Insert	druid	spell	fixes	here
			case 22570:
			case 49802:	// Maim
				{
						sp->AuraInterruptFlags |=	AURA_INTERRUPT_ON_UNUSED2;
						sp->Attributes |=	ATTRIBUTES_STOP_ATTACK;
				}break;
			//Owlkin Frenzy
			case 48389:
			case 48392:
			case 48393:
				{
					sp->procFlags	=	PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
					sp->EffectSpellClassMask[0][0]	=	0x0;
				}break;
			// Infected Wounds
			case 48483:
			case 48484:
			case 48485:
				{
					sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_MELEE_ATTACK;
				}break;
			//////////////////////////////////////////
			// BOSSES								//
			//////////////////////////////////////////
		
			// Insert	boss spell fixes here
			
			// Dark	Glare
			case  26029:
				{
						sp->cone_width = 15.0f;	// 15	degree cone
				}break;
		
			// Commendation	of Kael'thas
			case  45057:
				{
						sp->proc_interval	=	30000;
				}break;
		
			// Recently	Dropped	Flag
			case  42792:
				{
						sp->c_is_flags |=	SPELL_FLAG_IS_FORCEDDEBUFF;
				}break;

		
			case  7712:
				{
						sp->Dspell_coef_override = 0.0f;
				}break;

		
			case  43958:
				{
						sp->Effect[0]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
						sp->DurationIndex	=	6; //	10 minutes.
						sp->c_is_flags |=	SPELL_FLAG_IS_FORCEDDEBUFF;
		
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
						sp->EffectMiscValue[1] = SMT_RESIST_DISPEL;
						sp->EffectBasePoints[1]	=	90;
				}break;
		
			// Recently	Dropped	Flag
			case 43869:
				{
						sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
						sp->c_is_flags |=	SPELL_FLAG_IS_FORCEDDEBUFF;
				}break;
		
			case 48978:
			case 61216:
				{
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
						sp->EffectMiscValue[1] = 1;
				}break;
		
			case 49390:
			case 61221:
				{
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
						sp->EffectMiscValue[1] = 2;
				}break;
		
			case 49391:
			case 61222:
				{
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
						sp->EffectMiscValue[1] = 3;
				}break;
		
			case 49392:
				{
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
						sp->EffectMiscValue[1] = 4;
				}break;
		
			case 49393:
				{
						sp->Effect[1]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
						sp->EffectMiscValue[1] = 5;
				}break;
		
			case 46910:
				{
						sp->EffectTriggerSpell[0]	=	56112;
						sp->procChance = 50;
						sp->procFlags	|= PROC_ON_MELEE_ATTACK;
				}break;
		
			case 46911:
				{
						sp->EffectTriggerSpell[0]	=	56112;
						sp->procChance = 100;
						sp->procFlags	|= PROC_ON_MELEE_ATTACK;
				}break;
		
			// Rogue:	Hunger for Blood!
			case 51662:
				{
						sp->Effect[1]	=	SPELL_EFFECT_DUMMY;
				}break;
		
			// Mage: Focus Magic
			case 54646:
				{
						sp->c_is_flags = SPELL_FLAG_ON_ONLY_ONE_TARGET;
				}break;
		
			// Mage: Hot Streak
			case 44445:
			case 44446:
			case 44448:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0]	=	48108;
					sp->procFlags	=	PROC_ON_SPELL_CRIT_HIT;
					sp->procChance = sp->RankNumber * 33;
					sp->EffectSpellClassMask[0][0] = 0x0;
				}break;

			case 1122:
					{
						sp->EffectBasePoints[0]	=	0;
				}break;

			case 1860:
			case 20719:
					{
						sp->Effect[0]	=	SPELL_EFFECT_DUMMY;
				}break;

			//Bloodsurge
			case 46915:
			case 46914:
			case 46913:
				{
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_CAST_SPELL;
				}break;		
		
		
			//Waylay			 
			case  51692:
			case  51696:
				{	 
						sp->procFlags	=	PROC_ON_CRIT_ATTACK;
				}break;

			// Cold	Blood
			case  14177:
				{	 
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;

			// priest	-	mind flay
			case 15407:
			case 17311:
			case 17312:
			case 17313:
			case 17314:
			case 18807:
			case 25387:
			case 48155:
			case 48156:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
					sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
					sp->logsId = 58381;
				}break;
			// Death and Decay
			case 43265:
			case 49936:
			case 49937:
			case 49938:
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
				}break;

		
			//Warlock	Chaos	bolt
			case 50796:
			case 59170:
			case 59171:
			case 59172:
				{
					sp->Attributes = ATTRIBUTES_IGNORE_INVULNERABILITY;
				}break;

			case 47245://warlock - Molten Core
			case 47246:
			case 47247:
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			//Force	debuff's	 
			// Hypothermia
			case  41425:	 
			// Forbearance
			case  25771:	 
			// Weakened	Soul
			case  6788:
				{
						sp->c_is_flags = SPELL_FLAG_IS_FORCEDDEBUFF;	 
				}break;

					// Death Knight	spell	fixes
			//Blade	Barrier
			case 49182:
			case 49500:
			case 49501:
			case 55225:
			case 55226:
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
					sp->procChance = 100;
				}break;
			case 51130:
			case 51129:
			case 51128:
			case 51127:
			case 51123:// Killing Machine
				{
					sp->procFlags	=	PROC_ON_MELEE_ATTACK;
					sp->ProcsPerMinute = sp->RankNumber;
				}break;
			case 49175:
			case 50031:
			case 51456:	// Improved Icy Touch
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
				}break;
			case 48743:	// Death Pact
				{
					sp->Effect[1] = SPELL_EFFECT_NULL;	// Incorrect targetting makes it kill everyone around
				}break;
			case 49143:
			case 51416:
			case 51417:
			case 51418:
			case 51419:
			case 55268: // Frost Strike
				{
					sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MAGIC;
				}
			case 55090:
			case 55265:
			case 55270:
			case 55271: // Scourge Strike
				{
					sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MAGIC;
				}
			case 58631: // Glyph of Icy Touch
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			case 1843:	// Disarm
				{
					sp->Effect[0] = 0;	// to prevent abuse at Arathi
				}break;
		
			case 31801: // Seal of Vengeance
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0] = 31803;
					sp->procFlags = PROC_ON_MELEE_ATTACK;
				}break;
			case 53736:	// Seal of Corruption
				{
					sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0] = 53742;
					sp->procFlags = PROC_ON_MELEE_ATTACK;
				}break;
			case 31803: // Holy Vengeance
			case 53742: // Blood Corruption
			case 53733:	// Judgement of Corruption
			case 31804: // Judgement of Vengeance
				{
					sp->Dspell_coef_override = 0.0f;
					sp->OTspell_coef_override	=	0.0f;
				}break;
		
		
			// Bone	Shield
			case  49222:
				{
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
						sp->proc_interval	=	3000;
				}break;
			// Shadow	of Death
			case  49157:
				{
						sp->Effect[0]	=	0;	// don't want	DKs	to be	always invincible
				}break;
		
			// Death Grip
			case  49576:
				{
						sp->FacingCasterFlags	=	0;
				}break;
		
			// Fiery Payback disable until it's	properly implemented
			case  44441:
			case  44440:
				{
						sp->Effect[0]	=	sp->Effect[1]	=	sp->Effect[2]	=	0;
				}break;
		
			// Item	procs
			// Lesser	Heroism	(Tenacious Earthstorm	Diamond)
			case  32844:
				{
						sp->procChance = 5;
						sp->procFlags	 = PROC_ON_MELEE_ATTACK;
				}break;
			// Lesser	Heroism	proc
			case  32845:
				{
						sp->Dspell_coef_override = 0.0f;
				}break;
		
			// Darkmoon	Card:	Heroism
			case  23689:
				{
						sp->ProcsPerMinute = 2.5f;
						sp->procFlags	 = PROC_ON_MELEE_ATTACK;
				}break;

			// Darkmoon	Card:	Maelstrom
			case  23686:
				{
						sp->ProcsPerMinute = 2.5f;
						sp->procFlags	 = PROC_ON_MELEE_ATTACK;
				}break;

			case 34587:
			// Lightning Strike	proc
			case  23687:
			// Lesser	Heroism	proc
			case  23682:
				{
						sp->Dspell_coef_override = 0.0f;
				}break;
			// dragonspine trophy
			case 34774:
				{
						sp->ProcsPerMinute = 1.5f;
						sp->proc_interval	=	20000;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
		
			// Romulo's	Poison Vial
			case 34586:
				{
						sp->ProcsPerMinute = 1.6f;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
		
			// madness of	the	betrayer
			case 40475:
				{
						sp->procChance = 50;
						sp->ProcsPerMinute = 1.0f;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
			
			// Band	of the Eternal Defender
			case 35077:
				{
						sp->proc_interval	=	55000;
						sp->procFlags	=	PROC_ON_ANY_DAMAGE_VICTIM;
				}break;
			// Band	of the Eternal Champion
			case 35080:
				{
						sp->proc_interval	=	55000;
						sp->procFlags	=	PROC_ON_MELEE_ATTACK;
				}break;
			// Band	of the Eternal Restorer
			case 35086:
			// Band	of the Eternal Sage
			case 35083:
				{
						sp->proc_interval	=	55000;
						sp->procFlags	=	PROC_ON_CAST_SPELL;
				}break;
			// Sonic Booster
			case 54707:
				{
						sp->ProcsPerMinute = 1.0f;
						sp->proc_interval	=	60000;
						sp->procFlags = PROC_ON_MELEE_ATTACK;
				}break;	
			// Meteorite Whetstone
			case 60301:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
			// Bandit's Insignia
			case 60442:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
			// Fury of the Five Flights
			case 60313:
				{
						sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
			// Grim Toll
			case 60436:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
			// Illustration of the Dragon Soul
			case 60485:
				{
						sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Soul of the Dead
			case 60537:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
				}break;
			// Anvil of Titans
			case 62115:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
			// Embrace of the Spider
			case 60490:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Flow of Knowledge
			case 62114:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Majestic Dragon Figurine
			case 60524:
				{
						sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Mirror of Truth
			case 33648:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_CRIT_ATTACK;
				}break;
			// Forge Ember
			case 60473:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			// Vestige of Haldor
			case 60306:
				{
						sp->proc_interval	=	45000;
						sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
				}break;
		
			// shadow	of death
			case 54223:
				{
						sp->Effect[2]	=	SPELL_EFFECT_APPLY_AURA;
						sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
						sp->Flags4 |=	CAN_PERSIST_AND_CASTED_WHILE_DEAD;
				}break;
			case 54749://Burning Determination
			case 54747:
				{
					sp->procFlags = PROC_ON_SPELL_LAND_VICTIM;
				}break;
			case 48266://blood presence
				{
					sp->EffectTriggerSpell[1] = 50475;
					sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION | PROC_ON_MELEE_ATTACK;
				}break;
			case 50475:
				{
					sp->Effect[0] = SPELL_EFFECT_NULL;
				}break;
			case 48263://Frost Presence
				{
					sp->AdditionalAura = 61261;
				}break;
			case 48265://Unholy Presence
				{
					sp->AdditionalAura = 49772;
				}break;
			case 56364:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
				}break;
			case 44443://Firestarter
			case 44442:
				{
					sp->procFlags = PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[0][0] = 0x0;
					sp->EffectSpellClassMask[0][1] = 0x0;
				}break;
			//Mage - Brain Freeze
			case 44546:
			case 44584:
			case 44549:
				{
					sp->procFlags	=	PROC_ON_CAST_SPELL;
					sp->EffectSpellClassMask[0][0] = 0x0;
					sp->EffectSpellClassMask[0][1] = 0x0;
				}break;
			case 54741:
				{
					sp->AuraInterruptFlags	=	AURA_INTERRUPT_ON_CAST_SPELL;
				}break;
			case 66:
				{
					sp->EffectTriggerSpell[0] = 32612;
				}break;
			case 56368:
				{
					sp->Effect[1] = sp->Effect[0];
					sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
				}break;
			case 48020:
				{
					sp->Effect[1] = SPELL_EFFECT_DUMMY;
				}break;
			case 48018:
				{
					sp->AdditionalAura = 62388;
					sp->EffectImplicitTargetA[0] = 1;
				}break;
			case 30708://Totem of Wrath
				{
					sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
				}break;
			//Noise Machine - Sonic Shield
			case 54808:
				{
					sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0]	=	55019;
					sp->procFlags	=	PROC_ON_MELEE_ATTACK_VICTIM;
					sp->proc_interval	=	60000;
					sp->procChance	=	50;
				}break;
			//Pendulum of Telluric Currents
			case 60482:
				{
					sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0]	=	60483;
					sp->procFlags	=	PROC_ON_CAST_SPELL;
					sp->procChance	=	15;
				}break;
			//Tears of Bitter Anguish
			case 58901:
				{
					sp->EffectApplyAuraName[0]	=	SPELL_AURA_PROC_TRIGGER_SPELL;
					sp->EffectTriggerSpell[0]	=	58904;
					sp->procFlags	=	PROC_ON_CRIT_ATTACK;
					sp->procChance	=	10;
				}break;
			// FIXES FOR WARLOCK GRIMOIRES BEGIN
			case 20270:// Imp spells
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7799;
				}break;
			case 20312:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7800;
				}break;
			case 20313:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7801;
				}break;
			case 20314:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7802;
				}break;
			case 20315:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11762;
				}break;
			case 20316:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11763;
				}break;
			case 20322:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 2947;
				}break;
			case 20323:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 8316;
				}break;
			case 20324:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 8317;
				}break;
			case 20326:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11770;
				}break;
			case 20327:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11771;
				}break;
			case 20329:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 4511;
				}break;
			case 27487:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27267;
				}break;
			case 27489:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27269;
				}break;
			case 47965:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47964;
				}break;
			case 47998:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47983;
				}break;
			// Voidwalker spells
			case 20317:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7809;
				}break;
			case 20377:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7810;
				}break;
			case 20378:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7811;
				}break;
			case 20379:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11774;
				}break;
			case 20380:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11775;
				}break;
			case 20381:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7812;
				}break;
			case 20382:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19438;
				}break;
			case 20383:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19440;
				}break;
			case 20384:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19441;
				}break;
			case 20385:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19442;
				}break;
			case 20386:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19443;
				}break;
			case 20387:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17767;
				}break;
			case 20388:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17850;
				}break;
			case 20389:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17851;
				}break;
			case 20390:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17852;
				}break;
			case 20391:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17853;
				}break;
			case 20392:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17854;
				}break;
			case 20393:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17735;
				}break;
			case 20394:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17750;
				}break;
			case 20395:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17751;
				}break;
			case 20396:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 17752;
				}break;
			case 27490:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27270;
				}break;
			case 27491:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27272;
				}break;
			case 27492:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27273;
				}break;
			case 27500:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27271;
				}break;
			case 33703:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 33701;
				}break;
			case 48000:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47984;
				}break;
			case 48001:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47985;
				}break;
			case 48002:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47986;
				}break;
			case 48003:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47987;
				}break;
			case 48004:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47988;
				}break;
			case 48005:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47989;
				}break;
			case 48006:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 47990;
				}break;
			// Succubus spells
			case 20398:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7815;
				}break;
			case 20399:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7816;
				}break;
			case 20400:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11778;
				}break;
			case 20401:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11779;
				}break;
			case 20402:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11780;
				}break;
			case 20403:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 6360;
				}break;
			case 20404:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7813;
				}break;
			case 20405:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11784;
				}break;
			case 20406:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 11785;
				}break;
			case 20407:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 6358;
				}break;
			case 20408:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 7870;
				}break;
			case 27493:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27274;
				}break;
			case 27494:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27275;
				}break;
			// Felhunter spells
			case 20426:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19731;
				}break;
			case 20427:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19734;
				}break;
			case 20428:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19736;
				}break;
			case 20429:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19478;
				}break;
			case 20430:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19655;
				}break;
			case 20431:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19656;
				}break;
			case 20432:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19660;
				}break;
			case 20433:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19244;
				}break;
			case 20434:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19647;
				}break;
			case 20435:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 19480;
				}break;
			case 27495:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27276;
				}break;
			case 27496:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27277;
				}break;
			case 27497:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 27280;
				}break;
			// Felguard spells
			case 30154:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 30151;
				}break;
			case 30199:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 30194;
				}break;
			case 30200:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 30198;
				}break;
			case 30214:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 30213;
				}break;
			case 30222:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 30219;
				}break;
			case 30224:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 30223;
				}break;
			case 32234:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 32233;
				}break;
			case 32852:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 32850;
				}break;
			case 33704:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 33698;
				}break;
			case 33705:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 33699;
				}break;
			case 33706:
				{
					sp->Effect[0] = SPELL_EFFECT_LEARN_PET_SPELL;
					sp->EffectTriggerSpell[0] = 33700;
				}break;
			// FIXES FOR WARLOCK GRIMOIRES END
			case 20578:
				sp->AuraInterruptFlags = AURA_INTERRUPT_ON_MOVEMENT|AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;
				break;
			// Learn Dual Talent Specialization
			case 63624:
				{
					sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
					sp->EffectTriggerSpell[1] = 63680;
				}break;	
			}
		}
	}
void ApplyNormalFixes()
{
	//Updating spell.dbc
	SpellEntry *sp;

	Log.Notice("World", "Processing %u spells...", dbcSpell.GetNumRows());
	uint32 cnt = (uint32)dbcSpell.GetNumRows();
	uint32 effect;

	map<uint32, uint32> talentSpells;
	map<uint32,uint32>::iterator talentSpellIterator;
	unsigned int i,j;
	for(i = 0; i < dbcTalent.GetNumRows(); ++i)
	{
		TalentEntry * tal = dbcTalent.LookupRow(i);
		for(j = 0; j < 5; ++j)
			if(tal->RankID[j] != 0)
				talentSpells.insert(make_pair(tal->RankID[j], tal->TalentTree));
	}

#ifdef DUMP_SPELLS_SQL
	DumpSpellsSQL();
#endif

	for(uint32 x=0; x < cnt; x++)
	{
		sp = dbcSpell.LookupRow(x);

		uint32 result = 0;

		uint32 type = 0;
		uint32 namehash = 0;

		sp->AdditionalAura = 0;
		sp->self_cast_only = false;
		sp->Unique = false;
		sp->apply_on_shapeshift_change = false;
		sp->always_apply = false;

		// hash the name
		//!!!!!!! representing all strings on 32 bits is dangerous. There is a chance to get same hash for a lot of strings ;)
		namehash = crc32((const unsigned char*)sp->Name, (unsigned int)strlen(sp->Name));
		sp->NameHash   = namehash; //need these set before we start processing spells

		float radius = 0.0f;
		if(sp->EffectRadiusIndex[0] != 0)
			radius=::GetRadius(dbcSpellRadius.LookupEntry(sp->EffectRadiusIndex[0]));
		
		if( sp->EffectRadiusIndex[1] != 0 )
			radius = std::max(radius,::GetRadius(dbcSpellRadius.LookupEntry(sp->EffectRadiusIndex[1])));

		if( sp->EffectRadiusIndex[2] != 0 )
			radius=std::max(::GetRadius(dbcSpellRadius.LookupEntry(sp->EffectRadiusIndex[2])),radius);

		radius=std::max(GetMaxRange(dbcSpellRange.LookupEntry(sp->rangeIndex)),radius);
		sp->base_range_or_radius = radius;
		sp->base_range_or_radius_sqr = radius*radius;
		sp->cone_width = 0.0f;
		sp->area_aura_update_interval = 1000;

		// NEW SCHOOLS AS OF 2.4.0:
		/* (bitwise)
		SCHOOL_NORMAL = 1,
		SCHOOL_HOLY   = 2,
		SCHOOL_FIRE   = 4,
		SCHOOL_NATURE = 8,
		SCHOOL_FROST  = 16,
		SCHOOL_SHADOW = 32,
		SCHOOL_ARCANE = 64
		*/

		for (i=0; i<8; i++)
		{
			if (sp->School & (1<<i))
			{
				sp->School = i;
				break;
			}
		}

		/*
		AURASTATE_FLAG_DODGE_BLOCK			= 1,		//1
		AURASTATE_FLAG_HEALTH20		     = 2,		//2
		AURASTATE_FLAG_BERSERK		      = 4,		//3
		AURASTATE_FLAG_JUDGEMENT		    = 16,       //5
		AURASTATE_FLAG_PARRY				= 64,       //7
		AURASTATE_FLAG_LASTKILLWITHHONOR    = 512,      //10
		AURASTATE_FLAG_CRITICAL		     = 1024,     //11
		AURASTATE_FLAG_HEALTH35		     = 4096,     //13
		AURASTATE_FLAG_IMMOLATE		     = 8192,     //14
		AURASTATE_FLAG_REJUVENATE		   = 16384,    //15 //where do i use this ?
		AURASTATE_FLAG_POISON		       = 32768,    //16
		*/

		// apply on shapeshift change
		if( sp->NameHash == SPELL_HASH_TRACK_HUMANOIDS )
			sp->apply_on_shapeshift_change = true;

		if( sp->NameHash == SPELL_HASH_BLOOD_FURY || sp->NameHash == SPELL_HASH_SHADOWSTEP )
			sp->always_apply = true;

		//there are some spells that change the "damage" value of 1 effect to another : devastate = bonus first then damage
		//this is a total bullshit so remove it when spell system supports effect overwriting
		for( uint32 col1_swap = 0; col1_swap < 2 ; col1_swap++ )
		{
			for( uint32 col2_swap = col1_swap ; col2_swap < 3 ; col2_swap++ )
			{
				if( sp->Effect[col1_swap] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE && sp->Effect[col2_swap] == SPELL_EFFECT_DUMMYMELEE )
				{
					uint32 temp;
					float ftemp;
					temp = sp->Effect[col1_swap];			sp->Effect[col1_swap] = sp->Effect[col2_swap] ;						sp->Effect[col2_swap] = temp;
					temp = sp->EffectDieSides[col1_swap];	sp->EffectDieSides[col1_swap] = sp->EffectDieSides[col2_swap] ;		sp->EffectDieSides[col2_swap] = temp;
					temp = sp->EffectBaseDice[col1_swap];	sp->EffectBaseDice[col1_swap] = sp->EffectBaseDice[col2_swap] ;		sp->EffectBaseDice[col2_swap] = temp;
					ftemp = sp->EffectDicePerLevel[col1_swap];			sp->EffectDicePerLevel[col1_swap] = sp->EffectDicePerLevel[col2_swap] ;				sp->EffectDicePerLevel[col2_swap] = ftemp;
					ftemp = sp->EffectRealPointsPerLevel[col1_swap];	sp->EffectRealPointsPerLevel[col1_swap] = sp->EffectRealPointsPerLevel[col2_swap] ;	sp->EffectRealPointsPerLevel[col2_swap] = ftemp;
					temp = sp->EffectBasePoints[col1_swap];	sp->EffectBasePoints[col1_swap] = sp->EffectBasePoints[col2_swap] ;	sp->EffectBasePoints[col2_swap] = temp;
					temp = sp->EffectMechanic[col1_swap];	sp->EffectMechanic[col1_swap] = sp->EffectMechanic[col2_swap] ;	sp->EffectMechanic[col2_swap] = temp;
					temp = sp->EffectImplicitTargetA[col1_swap];	sp->EffectImplicitTargetA[col1_swap] = sp->EffectImplicitTargetA[col2_swap] ;	sp->EffectImplicitTargetA[col2_swap] = temp;
					temp = sp->EffectImplicitTargetB[col1_swap];	sp->EffectImplicitTargetB[col1_swap] = sp->EffectImplicitTargetB[col2_swap] ;	sp->EffectImplicitTargetB[col2_swap] = temp;
					temp = sp->EffectRadiusIndex[col1_swap];	sp->EffectRadiusIndex[col1_swap] = sp->EffectRadiusIndex[col2_swap] ;	sp->EffectRadiusIndex[col2_swap] = temp;
					temp = sp->EffectApplyAuraName[col1_swap];	sp->EffectApplyAuraName[col1_swap] = sp->EffectApplyAuraName[col2_swap] ;	sp->EffectApplyAuraName[col2_swap] = temp;
					temp = sp->EffectAmplitude[col1_swap];		sp->EffectAmplitude[col1_swap] = sp->EffectAmplitude[col2_swap] ;	sp->EffectAmplitude[col2_swap] = temp;
					ftemp = sp->EffectMultipleValue[col1_swap];		sp->EffectMultipleValue[col1_swap] = sp->EffectMultipleValue[col2_swap] ;	sp->EffectMultipleValue[col2_swap] = ftemp;
					temp = sp->EffectChainTarget[col1_swap];	sp->EffectChainTarget[col1_swap] = sp->EffectChainTarget[col2_swap] ;	sp->EffectChainTarget[col2_swap] = temp;
					temp = sp->EffectSpellClassMask[col1_swap][0];	sp->EffectSpellClassMask[col1_swap][0] = sp->EffectSpellClassMask[col2_swap][0] ;	sp->EffectSpellClassMask[col2_swap][0] = temp;
					temp = sp->EffectSpellClassMask[col1_swap][1];	sp->EffectSpellClassMask[col1_swap][1] = sp->EffectSpellClassMask[col2_swap][1] ;	sp->EffectSpellClassMask[col2_swap][1] = temp;
					temp = sp->EffectSpellClassMask[col1_swap][2];	sp->EffectSpellClassMask[col1_swap][2] = sp->EffectSpellClassMask[col2_swap][2] ;	sp->EffectSpellClassMask[col2_swap][2] = temp;
					temp = sp->EffectMiscValue[col1_swap];		sp->EffectMiscValue[col1_swap] = sp->EffectMiscValue[col2_swap] ;	sp->EffectMiscValue[col2_swap] = temp;
					temp = sp->EffectTriggerSpell[col1_swap];	sp->EffectTriggerSpell[col1_swap] = sp->EffectTriggerSpell[col2_swap] ;	sp->EffectTriggerSpell[col2_swap] = temp;
					ftemp = sp->EffectPointsPerComboPoint[col1_swap];	sp->EffectPointsPerComboPoint[col1_swap] = sp->EffectPointsPerComboPoint[col2_swap] ;	sp->EffectPointsPerComboPoint[col2_swap] = ftemp;
				}
			}
		}
		for(uint32 b=0;b<3;++b)
		{
			if(sp->EffectTriggerSpell[b] != 0 && dbcSpell.LookupEntryForced(sp->EffectTriggerSpell[b]) == NULL)
			{
				/* proc spell referencing non-existant spell. create a dummy spell for use w/ it. */
				CreateDummySpell(sp->EffectTriggerSpell[b]);
			}
			/** Load teaching spells (used for hunters when learning pets wild abilities) */
			if(sp->Effect[b]==SPELL_EFFECT_LEARN_SPELL && sp->EffectImplicitTargetA[b]==EFF_TARGET_PET)
			{
				map<uint32,uint32>::iterator itr = sWorld.TeachingSpellMap.find(sp->EffectTriggerSpell[b]);
				if(itr == sWorld.TeachingSpellMap.end())
					sWorld.TeachingSpellMap.insert(make_pair(sp->EffectTriggerSpell[b],sp->Id));
			}

			if( sp->Attributes & ATTRIBUTES_ONLY_OUTDOORS && sp->EffectApplyAuraName[b] == SPELL_AURA_MOUNTED )
			{
				sp->Attributes &= ~ATTRIBUTES_ONLY_OUTDOORS;
			}
		}

		/*if(sp->self_cast_only && !(sp->Attributes&64))
			printf("SPELL SELF CAST ONLY: %s %u\n", sp->Name, sp->Id);*/

		if(!strcmp(sp->Name, "Hearthstone") || !strcmp(sp->Name, "Stuck") || !strcmp(sp->Name, "Astral Recall"))
			sp->self_cast_only = true;

		sp->proc_interval = 0;//trigger at each event
		sp->ProcsPerMinute = 0;
		sp->c_is_flags = 0;
		sp->spell_coef_flags = 0;
		sp->Dspell_coef_override = -1;
		sp->OTspell_coef_override = -1;
		sp->casttime_coef = 0;
		sp->fixed_dddhcoef = -1;
		sp->fixed_hotdotcoef = -1;
		sp->auraimmune_flag = 0;

		talentSpellIterator = talentSpells.find(sp->Id);
		if(talentSpellIterator == talentSpells.end())
			sp->talent_tree = 0;
		else
			sp->talent_tree = talentSpellIterator->second;

		skilllinespell *sk = objmgr.GetSpellSkill(sp->Id);
		sp->skilline = sk ? sk->skilline : 0;


		//judgement of command
		if( namehash == SPELL_HASH_JUDGEMENT_OF_COMMAND )		
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MAGIC;

		else if( namehash == SPELL_HASH_ARCANE_SHOT )		
			sp->c_is_flags |= SPELL_FLAG_IS_NOT_USING_DMG_BONUS;

		else if( namehash == SPELL_HASH_SERPENT_STING )		
			sp->c_is_flags |= SPELL_FLAG_IS_NOT_USING_DMG_BONUS;

		//Rogue: Posion time fix for 2.3
		if( strstr( sp->Name, "Crippling Poison") && sp->Effect[0] == 54 ) //I, II
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Mind-numbing Poison") && sp->Effect[0] == 54 ) //I,II,III
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Instant Poison") && sp->Effect[0] == 54 ) //I,II,III,IV,V,VI,VII    
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Deadly Poison") && sp->Effect[0] == 54 ) //I,II,III,IV,V,VI,VII
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Wound Poison") && sp->Effect[0] == 54 ) //I,II,III,IV,V
			sp->EffectBasePoints[0] = 3599;
		if( strstr( sp->Name, "Anesthetic Poison") && sp->Effect[0] == 54 ) //I
			sp->EffectBasePoints[0] = 3599;

		if( strstr( sp->Name, "Sharpen Blade") && sp->Effect[0] == 54 ) //All BS stones
		    sp->EffectBasePoints[0] = 3599;

		//these mostly do not mix so we can use else 
		// look for seal, etc in name
		if( strstr( sp->Name, "Seal"))
		    type |= SPELL_TYPE_SEAL;
		else if( strstr( sp->Name, "Blessing"))
		    type |= SPELL_TYPE_BLESSING;
		else if( strstr( sp->Name, "Curse"))
		    type |= SPELL_TYPE_CURSE;
		else if( strstr( sp->Name, "Aspect"))
		    type |= SPELL_TYPE_ASPECT;
		else if( strstr( sp->Name, "Sting") || strstr( sp->Name, "sting"))
		    type |= SPELL_TYPE_STING;
        else if( strstr( sp->Name, "Judgement"))
            type |= SPELL_TYPE_JUDGEMENT;
		// don't break armor items!
		else if(strcmp(sp->Name, "Armor") && strstr( sp->Name, "Armor") || strstr( sp->Name, "Demon Skin"))
		    type |= SPELL_TYPE_ARMOR;
		else if( strstr( sp->Name, "Aura"))
		    type |= SPELL_TYPE_AURA;
		else if( strstr( sp->Name, "Track")==sp->Name)
		    type |= SPELL_TYPE_TRACK;
		else if( namehash == SPELL_HASH_GIFT_OF_THE_WILD || namehash == SPELL_HASH_MARK_OF_THE_WILD )
		    type |= SPELL_TYPE_MARK_GIFT;
		else if( namehash == SPELL_HASH_IMMOLATION_TRAP || namehash == SPELL_HASH_FREEZING_TRAP || namehash == SPELL_HASH_FROST_TRAP || namehash == SPELL_HASH_EXPLOSIVE_TRAP || namehash == SPELL_HASH_SNAKE_TRAP )
		    type |= SPELL_TYPE_HUNTER_TRAP;
		else if( sp->EffectApplyAuraName[0] == SPELL_AURA_MOD_STAT && sp->EffectMiscValue[0] == 3 )
		    type |= SPELL_TYPE_MAGE_INTEL;
		else if( namehash == SPELL_HASH_AMPLIFY_MAGIC || namehash == SPELL_HASH_DAMPEN_MAGIC )
		    type |= SPELL_TYPE_MAGE_MAGI;
		else if( namehash == SPELL_HASH_FIRE_WARD || namehash == SPELL_HASH_FROST_WARD )
		    type |= SPELL_TYPE_MAGE_WARDS;
		else if( namehash == SPELL_HASH_SHADOW_PROTECTION || namehash == SPELL_HASH_PRAYER_OF_SHADOW_PROTECTION )
		    type |= SPELL_TYPE_PRIEST_SH_PPROT;
		else if( namehash == SPELL_HASH_WATER_SHIELD || namehash == SPELL_HASH_EARTH_SHIELD || namehash == SPELL_HASH_LIGHTNING_SHIELD )
		    type |= SPELL_TYPE_SHIELD;
		else if( namehash == SPELL_HASH_POWER_WORD__FORTITUDE || namehash == SPELL_HASH_PRAYER_OF_FORTITUDE )
		    type |= SPELL_TYPE_FORTITUDE;
		else if( namehash == SPELL_HASH_DIVINE_SPIRIT || namehash == SPELL_HASH_PRAYER_OF_SPIRIT )
		    type |= SPELL_TYPE_SPIRIT;
//		else if( strstr( sp->Name, "Curse of Weakness") || strstr( sp->Name, "Curse of Agony") || strstr( sp->Name, "Curse of Recklessness") || strstr( sp->Name, "Curse of Tongues") || strstr( sp->Name, "Curse of the Elements") || strstr( sp->Name, "Curse of Idiocy") || strstr( sp->Name, "Curse of Shadow") || strstr( sp->Name, "Curse of Doom"))
//		else if(namehash==4129426293 || namehash==885131426 || namehash==626036062 || namehash==3551228837 || namehash==2784647472 || namehash==776142553 || namehash==3407058720 || namehash==202747424)
//		else if( strstr( sp->Name, "Curse of "))
//		    type |= SPELL_TYPE_WARLOCK_CURSES;
		else if( strstr( sp->Name, "Immolate") || strstr( sp->Name, "Conflagrate"))
			type |= SPELL_TYPE_WARLOCK_IMMOLATE;
		else if( strstr( sp->Name, "Amplify Magic") || strstr( sp->Name, "Dampen Magic"))
			type |= SPELL_TYPE_MAGE_AMPL_DUMP;
		else if( strstr( sp->Description, "Battle Elixir"))
		    type |= SPELL_TYPE_ELIXIR_BATTLE;
		else if( strstr( sp->Description, "Guardian Elixir"))
		    type |= SPELL_TYPE_ELIXIR_GUARDIAN;
		else if( strstr( sp->Description, "Battle and Guardian elixir"))
		    type |= SPELL_TYPE_ELIXIR_FLASK;
		else if( namehash == SPELL_HASH_HUNTER_S_MARK )		// hunter's mark
			type |= SPELL_TYPE_HUNTER_MARK;
		else if( namehash == SPELL_HASH_COMMANDING_SHOUT || namehash == SPELL_HASH_BATTLE_SHOUT )
		    type |= SPELL_TYPE_WARRIOR_SHOUT;
		else if( ( namehash == SPELL_HASH_FROST_PRESENCE || namehash == SPELL_HASH_BLOOD_PRESENCE || namehash == SPELL_HASH_UNHOLY_PRESENCE ) &&
				 ( sp->Id != 61261 ) && ( sp->Id != 49772 ))
			type |= SPELL_TYPE_DK_PRESENCE;
		else if( strstr( sp->Description, "Finishing move")==sp->Description)
			sp->c_is_flags |= SPELL_FLAG_IS_FINISHING_MOVE;
		if( IsDamagingSpell( sp ) )
			sp->c_is_flags |= SPELL_FLAG_IS_DAMAGING;
		if( IsHealingSpell( sp ) )
			sp->c_is_flags |= SPELL_FLAG_IS_HEALING;
		if( IsTargetingStealthed( sp ) )
			sp->c_is_flags |= SPELL_FLAG_IS_TARGETINGSTEALTHED;
		if( IsFlyingSpell(sp) )
			sp->c_is_flags |= SPELL_FLAG_IS_FLYING;
		
		for(uint32 b = 0; b < 3; ++b)
		{
			if( sp->Effect[b] == SPELL_EFFECT_PERSISTENT_AREA_AURA )
			{
				/*if( sp->EffectImplicitTargetB[b] != 0 )
				printf("%s %s - A: %u, B: %u\n", sp->Name, sp->Rank, sp->EffectImplicitTargetA[b], sp->EffectImplicitTargetB[b]);*/

				sp->EffectImplicitTargetA[b] = EFF_TARGET_SELF;
				sp->EffectImplicitTargetB[b] = 0;
			}

			// 3.0.3 totemzzz
			if( sp->Effect[b] == SPELL_EFFECT_HEALTH_FUNNEL )
			{
				sp->Effect[b] = SPELL_EFFECT_APPLY_AREA_AURA;
			}
		}

		// parse rank text
		if( !sscanf( sp->Rank, "Rank %d", (unsigned int*)&sp->RankNumber) )
		{
			const char* ranktext = sp->Rank;
			uint32 rank = 0;

			//stupid spell ranking problem
			if( strstr( ranktext, "Apprentice"))
				rank = 1;
			else if( strstr( ranktext, "Journeyman"))
				rank = 2;
			else if( strstr( ranktext, "Expert"))
				rank = 3;
			else if( strstr( ranktext, "Artisan"))
				rank = 4;
			else if( strstr( ranktext, "Master"))
				rank = 5;
			else if( strstr( ranktext, "Grandmaster"))
				rank = 6;
			sp->RankNumber = rank;
		}

		if(sp->spellLevel==0)
		{
			uint32 new_level=sp->RankNumber;
			if(new_level!=0)
			{
				uint32 teachspell=0;
				if(sp->Effect[0]==SPELL_EFFECT_LEARN_SPELL)
					teachspell = sp->EffectTriggerSpell[0];
				else if(sp->Effect[1]==SPELL_EFFECT_LEARN_SPELL)
					teachspell = sp->EffectTriggerSpell[1];
				else if(sp->Effect[2]==SPELL_EFFECT_LEARN_SPELL)
					teachspell = sp->EffectTriggerSpell[2];
				if(teachspell)
				{
					SpellEntry *spellInfo;
					spellInfo = dbcSpell.LookupEntryForced(teachspell);
					spellInfo->spellLevel = new_level;
					sp->spellLevel = new_level;
				}
			}
		}

		/*FILE * f = fopen("C:\\spells.txt", "a");
		fprintf(f, "case 0x%08X:		// %s\n", namehash, sp->Name);
		fclose(f);*/

		// find diminishing status
		sp->DiminishStatus = GetDiminishingGroup(namehash);
		sp->buffIndexType=0;
		switch(namehash)
		{
		case SPELL_HASH_HUNTER_S_MARK:		// Hunter's mark
			sp->buffIndexType = SPELL_TYPE_INDEX_MARK;
			break;

		case SPELL_HASH_POLYMORPH:			// Polymorph
		case SPELL_HASH_POLYMORPH__CHICKEN:	// Polymorph: Chicken
		case SPELL_HASH_POLYMORPH__SHEEP:	// Polymorph: Sheep
			sp->buffIndexType = SPELL_TYPE_INDEX_POLYMORPH;
			break;

		case SPELL_HASH_FEAR:				// Fear
			sp->buffIndexType = SPELL_TYPE_INDEX_FEAR;
			break;

		case SPELL_HASH_SAP:				// Sap
			sp->buffIndexType = SPELL_TYPE_INDEX_SAP;
			break;

		case SPELL_HASH_SCARE_BEAST:		// Scare Beast
			sp->buffIndexType = SPELL_TYPE_INDEX_SCARE_BEAST;
			break;

		case SPELL_HASH_HIBERNATE:			// Hibernate
			sp->buffIndexType = SPELL_TYPE_INDEX_HIBERNATE;
			break;

		case SPELL_HASH_EARTH_SHIELD:		// Earth Shield
			sp->buffIndexType = SPELL_TYPE_INDEX_EARTH_SHIELD;
			break;

		case SPELL_HASH_CYCLONE:			// Cyclone
			sp->buffIndexType = SPELL_TYPE_INDEX_CYCLONE;
			break;

		case SPELL_HASH_BANISH:				// Banish
			sp->buffIndexType = SPELL_TYPE_INDEX_BANISH;
			break;

		//case SPELL_HASH_JUDGEMENT_OF_VENGEANCE:
		case SPELL_HASH_JUDGEMENT_OF_LIGHT:
		case SPELL_HASH_JUDGEMENT_OF_WISDOM:
		case SPELL_HASH_JUDGEMENT_OF_JUSTICE:
			sp->buffIndexType = SPELL_TYPE_INDEX_JUDGEMENT;
			break;

		case SPELL_HASH_REPENTANCE:
			sp->buffIndexType = SPELL_TYPE_INDEX_REPENTANCE;
			break;
		case SPELL_HASH_SLOW:
			sp->buffIndexType = SPELL_TYPE_INDEX_SLOW;
			break;
		}

		// HACK FIX: Break roots/fear on damage.. this needs to be fixed properly!
		uint32 z;
		if(!(sp->AuraInterruptFlags & AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN))
		{
			for(z = 0; z < 3; ++z) {
				if(sp->EffectApplyAuraName[z] == SPELL_AURA_MOD_FEAR ||
					sp->EffectApplyAuraName[z] == SPELL_AURA_MOD_ROOT)
				{
					sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_UNUSED2;
					break;
				}
			}
		}

		for(z = 0;z < 3; ++z)
		{
			if( ( sp->Effect[z] == SPELL_EFFECT_SCHOOL_DAMAGE && sp->Spell_Dmg_Type == SPELL_DMG_TYPE_MELEE ) || sp->Effect[z] == SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL || sp->Effect[z] == SPELL_EFFECT_WEAPON_DAMAGE || sp->Effect[z] == SPELL_EFFECT_WEAPON_PERCENT_DAMAGE || sp->Effect[z] == SPELL_EFFECT_DUMMYMELEE )
				sp->is_melee_spell = true;
			if( ( sp->Effect[z] == SPELL_EFFECT_SCHOOL_DAMAGE && sp->Spell_Dmg_Type == SPELL_DMG_TYPE_RANGED ) )
			{
				//sLog.outString( "Ranged Spell: %u [%s]" , sp->Id , sp->Name );
				sp->is_ranged_spell = true;
			}

			switch(sp->EffectImplicitTargetA[z])
			{
				case 6:
				case 22:
				case 24:
				case 25:
					sp->c_is_flags |= SPELL_FLAG_CAN_BE_REFLECTED;
					break;
			}

			if( sp->Effect[z] == SPELL_EFFECT_DISPEL )
				sp->c_is_flags |= SPELL_FLAG_IS_DISPEL_SPELL;

			if( sp->Effect[z] == SPELL_EFFECT_HEAL )
				sp->c_is_flags |= SPELL_FLAG_IS_HEALING_SPELL;

			if( sp->Effect[z] == SPELL_EFFECT_ENERGIZE )
				sp->c_is_flags |= SPELL_FLAG_IS_HEALING_MANA_SPELL;

		}

		// set extra properties
		sp->buffType   = type;

		uint32 pr=sp->procFlags;
		for(uint32 y=0;y < 3; y++)
		{
			// get the effect number from the spell
			effect = sp->Effect[y];

			if(effect==SPELL_EFFECT_APPLY_AURA)
			{
				uint32 aura = sp->EffectApplyAuraName[y];
				if( aura == SPELL_AURA_PROC_TRIGGER_SPELL ||
					aura == SPELL_AURA_PROC_TRIGGER_DAMAGE
					)//search for spellid in description
				{
					const char *p=sp->Description;
					while((p=strstr(p,"$")))
					{
						p++;
						//got $  -> check if spell
						if(*p>='0' && *p <='9')
						{//woot this is spell id
						
							result=atoi(p);
						}					
					}
					pr=0;

					char desc[4096];
					strcpy(desc,sp->Description);
					uint32 len = (uint32)strlen(desc);
					for(i = 0; i < len; ++i)
						desc[i] = tolower(desc[i]);
					//dirty code for procs, if any1 got any better idea-> u are welcome
					//139944 --- some magic number, it will trigger on all hits etc
						//for seems to be smth like custom check
					if( strstr( desc,"your ranged criticals"))
						pr|=PROC_ON_RANGED_CRIT_ATTACK;
					if( strstr( desc,"chance on hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"takes damage"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"attackers when hit"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"character strikes an enemy"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"strike you with a melee attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"target casts a spell"))
						pr|=PROC_ON_CAST_SPELL;
				    if( strstr( desc,"your harmful spells land"))
						pr|=PROC_ON_CAST_SPELL;
				    if( strstr( desc,"on spell critical hit"))
						pr|=PROC_ON_SPELL_CRIT_HIT;
				    if( strstr( desc,"spell critical strikes"))
						pr|=PROC_ON_SPELL_CRIT_HIT;
				    if( strstr( desc,"being able to resurrect"))
						pr|=PROC_ON_DIE;
					if( strstr( desc,"any damage caused"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"the next melee attack against the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"when successfully hit"))
						pr|=PROC_ON_MELEE_ATTACK ;
					if( strstr( desc,"an enemy on hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"when it hits"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"when successfully hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"on a successful hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"damage to attacker on hit"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"on a hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"strikes you with a melee attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"when caster takes damage"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"when the caster is using melee attacks"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"when struck in combat") || strstr(desc,"When struck in combat"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"successful melee attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"chance per attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"chance per hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"that strikes a party member"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"when hit by a melee attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"landing a melee critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( desc,"your critical strikes"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( desc,"whenever you deal ranged damage"))
						pr|=PROC_ON_RANGED_ATTACK;
//					if( strstr( desc,"whenever you deal melee damage"))
					if( strstr( desc,"you deal melee damage"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"your melee attacks"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"damage with your Sword"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"when struck in melee combat"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"any successful spell cast against the priest"))
						pr|=PROC_ON_SPELL_HIT_VICTIM;
					if( strstr( desc,"the next melee attack on the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"striking melee or ranged attackers"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM|PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( desc,"when damaging an enemy in melee"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"victim of a critical strike"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
					if( strstr( desc,"on successful melee or ranged attack"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
					if( strstr( desc,"enemy that strikes you in melee"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"after getting a critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( desc,"whenever damage is dealt to you"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"when ranged or melee damage is dealt"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
					if( strstr( desc,"damaging melee attacks"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"on melee or ranged attack"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
					if( strstr( desc,"on a melee swing"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"Chance on melee"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"spell criticals against you"))
						pr|=PROC_ON_SPELL_CRIT_HIT_VICTIM;
					if( strstr( desc,"after being struck by a melee or ranged critical hit"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
//					if( strstr( desc,"on a critical hit"))
					if( strstr( desc,"critical hit"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( desc,"strikes the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"a spell, melee or ranged attack hits the caster"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"after dealing a critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( desc,"each melee or ranged damage hit against the priest"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM|PROC_ON_RANGED_ATTACK_VICTIM;				
					if( strstr( desc, "a chance to deal additional"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc, "chance to get an extra attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc, "melee attacks has"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc, "any damage spell hits a target"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc, "giving each melee attack a chance"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc, "damage when hit"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM; //myabe melee damage ?
					if( strstr( desc, "gives your"))
					{
						if( strstr( desc, "melee"))
							pr|=PROC_ON_MELEE_ATTACK;
						else if( strstr( desc,"sinister strike, backstab, gouge and shiv"))
							pr|=PROC_ON_CAST_SPELL;
						else if( strstr( desc,"chance to daze the target"))
							pr|=PROC_ON_CAST_SPELL;
						else if( strstr( desc,"finishing moves"))
							pr|=PROC_ON_CAST_SPELL;
//						else if( strstr( desc,"shadow bolt, shadowburn, soul fire, incinerate, searing pain and conflagrate"))
//							pr|=PROC_ON_CAST_SPELL|PROC_TARGET_SELF;
						//we should find that specific spell (or group) on what we will trigger
						else pr|=PROC_ON_CAST_SPECIFIC_SPELL;
					}
					if( strstr( desc, "chance to add an additional combo") && strstr(desc, "critical") )
						pr|=PROC_ON_CRIT_ATTACK;
					else if( strstr( desc, "chance to add an additional combo"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc, "victim of a melee or ranged critical strike"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
					if( strstr( desc, "getting a critical effect from"))
						pr|=PROC_ON_SPELL_CRIT_HIT_VICTIM;
					if( strstr( desc, "damaging attack is taken"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc, "struck by a Stun or Immobilize"))
						pr|=PROC_ON_SPELL_HIT_VICTIM;
					if( strstr( desc, "melee critical strike"))
						pr|=PROC_ON_CRIT_ATTACK;
					if( strstr( sp->Name, "Bloodthirst"))
						pr|=PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
					if( strstr( desc, "experience or honor"))
						pr|=PROC_ON_GAIN_EXPIERIENCE;
					if( strstr( desc,"your next offensive ability"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"hit by a melee or ranged attack"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( desc,"enemy strikes the caster"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"melee and ranged attacks against you"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( desc,"when a block occurs"))
						pr|=PROC_ON_BLOCK_VICTIM;
					if( strstr( desc,"dealing a critical strike from a weapon swing, spell, or ability"))
						pr|=PROC_ON_CRIT_ATTACK|PROC_ON_SPELL_CRIT_HIT;
					if( strstr( desc,"dealing a critical strike from a weapon swing, spell, or ability"))
						pr|=PROC_ON_CRIT_ATTACK|PROC_ON_SPELL_CRIT_HIT;
					if( strstr( desc,"shadow bolt critical strikes increase shadow damage"))
						pr|=PROC_ON_SPELL_CRIT_HIT;
					if( strstr( desc,"next offensive ability"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"after being hit with a shadow or fire spell"))
						pr|=PROC_ON_SPELL_LAND_VICTIM;
					if( strstr( desc,"giving each melee attack"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"each strike has"))
						pr|=PROC_ON_MELEE_ATTACK;		
					if( strstr( desc,"your Fire damage spell hits"))
						pr|=PROC_ON_CAST_SPELL;		//this happens only on hit ;)
					if( strstr( desc,"corruption, curse of agony, siphon life and seed of corruption spells also cause"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"pain, mind flay and vampiric touch spells also cause"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"shadow damage spells have"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"on successful spellcast"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"your spell criticals have"))
						pr|=PROC_ON_SPELL_CRIT_HIT | PROC_ON_SPELL_CRIT_HIT_VICTIM;
					if( strstr( desc,"after dodging their attack"))
					{
						pr|=PROC_ON_DODGE_VICTIM;
						if( strstr( desc,"add a combo point"))
							pr|=PROC_TARGET_SELF;
					}
					if( strstr( desc,"fully resisting"))
						pr|=PROC_ON_RESIST_VICTIM;
					if( strstr( desc,"Your Shadow Word: Pain, Mind Flay and Vampiric Touch spells also cause the target"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"chance on spell hit"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"your spell casts have"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"chance on spell cast"))
						pr|=PROC_ON_CAST_SPELL;
					if( strstr( desc,"your melee and ranged attacks"))
						pr|=PROC_ON_MELEE_ATTACK|PROC_ON_RANGED_ATTACK;
//					if( strstr( desc,"chill effect to your Blizzard"))
//						pr|=PROC_ON_CAST_SPELL;	
					//////////////////////////////////////////////////
					//proc dmg flags
					//////////////////////////////////////////////////
					if( strstr( desc,"each attack blocked"))
						pr|=PROC_ON_BLOCK_VICTIM;
					if( strstr( desc,"into flame, causing an additional"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"victim of a critical melee strike"))
						pr|=PROC_ON_CRIT_HIT_VICTIM;
					if( strstr( desc,"damage to melee attackers"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"target blocks a melee attack"))
						pr|=PROC_ON_BLOCK_VICTIM;
					if( strstr( desc,"ranged and melee attacks to deal"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( desc,"damage on hit"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"chance on hit"))
						pr|=PROC_ON_MELEE_ATTACK;
					if( strstr( desc,"after being hit by any damaging attack"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"striking melee or ranged attackers"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM;
					if( strstr( desc,"damage to attackers when hit"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"striking melee attackers"))
						pr|=PROC_ON_MELEE_ATTACK_VICTIM;
					if( strstr( desc,"whenever the caster takes damage"))
						pr|=PROC_ON_ANY_DAMAGE_VICTIM;
					if( strstr( desc,"damage on every attack"))
						pr|=PROC_ON_MELEE_ATTACK | PROC_ON_RANGED_ATTACK;
					if( strstr( desc,"chance to reflect Fire spells"))
						pr|=PROC_ON_SPELL_HIT_VICTIM;
					if( strstr( desc,"hunter takes on the aspects of a hawk"))
						pr|=PROC_TARGET_SELF | PROC_ON_RANGED_ATTACK;
					if( strstr( desc,"successful auto shot attacks"))
						pr|=PROC_ON_AUTO_SHOT_HIT;
					if( strstr( desc,"after getting a critical effect from your"))
						pr=PROC_ON_SPELL_CRIT_HIT;
					if( strstr( desc, "with a melee weapon"))
						pr|=PROC_ON_MELEE_ATTACK;
//					if( strstr( desc,"Your critical strikes from Fire damage"))
//						pr|=PROC_ON_SPELL_CRIT_HIT;
				}//end "if procspellaura"
				//dirty fix to remove auras that should expire on event and they are not
//				else if(sp->procCharges>0)
//				{
					//there are at least 185 spells that should loose charge uppon some event.Be prepared to add more here !
					// ! watch it cause this might conflict with our custom modified spells like : lighning shield !

					//spells like : Presence of Mind,Nature's Swiftness, Inner Focus,Amplify Curse,Coup de Grace
					//SELECT * FROM dbc_spell where proc_charges!=0 and (effect_aura_1=108 or effect_aura_2=108 and effect_aura_3=108) and description!=""
//					if(aura == SPELL_AURA_ADD_PCT_MODIFIER)
//						sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_CAST_SPELL;
					//most of them probably already have these flags...not sure if we should add to all of them without checking
/*					if( strstr( desc, "melee"))
						sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_START_ATTACK;
					if( strstr( desc, "ranged"))
						sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_START_ATTACK;*/
//				}

				// Aura 109 fix
				if(sp->EffectApplyAuraName[y] == SPELL_AURA_ADD_TARGET_TRIGGER)
				{
					sp->EffectApplyAuraName[y] = SPELL_AURA_PROC_TRIGGER_SPELL;
					pr = PROC_ON_CAST_SPELL;
				}
			}//end "if aura"
		}//end "for each effect"
		sp->procFlags = pr;

		if( strstr( sp->Description, "Must remain seated"))
		{
			sp->RecoveryTime = 1000;
			sp->CategoryRecoveryTime = 1000;
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////
		// procintervals
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		//omg lighning shield trigger spell id's are all wrong ?
		//if you are bored you could make thiese by hand but i guess we might find other spells with this problem..and this way it's safe
		if( strstr( sp->Name, "Lightning Shield" ) && sp->EffectTriggerSpell[0] )
		{
			//check if we can find in the desription
			char *startofid = strstr(sp->Description, "for $");
			if( startofid )
			{
				startofid += strlen("for $");
				sp->EffectTriggerSpell[0] = atoi( startofid ); //get new lightning shield trigger id

				SpellEntry * triggerSpell = dbcSpell.LookupEntryForced( sp->EffectTriggerSpell[0] );
				if(triggerSpell)
					triggerSpell->Dspell_coef_override = 0.3f;
			}
			sp->proc_interval = 3000; //few seconds
		}
		//mage ignite talent should proc only on some chances
		else if( strstr( sp->Name, "Ignite") && sp->Id>=11119 && sp->Id<=12848 && sp->EffectApplyAuraName[0] == 4 )
		{
			//check if we can find in the desription
			char *startofid=strstr(sp->Description, "an additional ");
			if(startofid)
			{
				startofid += strlen("an additional ");
				sp->EffectBasePoints[0]=atoi(startofid); //get new value. This is actually level*8 ;)
			}
			sp->Effect[0] = 6; //aura
			sp->EffectApplyAuraName[0] = 42; //force him to use procspell effect
			sp->EffectTriggerSpell[0] = 12654; //evil , but this is good for us :D
			sp->procFlags = PROC_ON_SPELL_CRIT_HIT; //add procflag here since this was not processed with the others !
		}
		// Winter's Chill handled by frost school
		else if( strstr( sp->Name, "Winter's Chill"))
		{
			sp->School = 4;
		}
		// Blackout handled by Shadow school
		else if( strstr( sp->Name, "Blackout"))
		{
			sp->School = 5;
		}
#ifndef NEW_PROCFLAGS
		// Shadow Weaving
		else if( strstr( sp->Name, "Shadow Weaving"))
		{
			sp->School = 5;
			sp->EffectApplyAuraName[0] = 42;
			sp->procChance = sp->EffectBasePoints[0] + 1;
			sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
		}
#endif
		//this starts to be an issue for trigger spell id : Deep Wounds
		else if( strstr( sp->Name, "Deep Wounds") && sp->EffectTriggerSpell[0])
		{
			//check if we can find in the desription
			char *startofid=strstr(sp->Description, "over $");
			if(startofid)
			{
				startofid += strlen("over $");
				sp->EffectTriggerSpell[0] = atoi(startofid);
			}
		}
		else if( strstr( sp->Name, "Holy Shock"))
		{
			//check if we can find in the desription
			char *startofid=strstr(sp->Description, "causing $");
			if(startofid)
			{
				startofid += strlen("causing $");
				sp->EffectTriggerSpell[0] = atoi(startofid);
			}
			//check if we can find in the desription
			startofid=strstr(sp->Description, " or $");
			if(startofid)
			{
				startofid += strlen(" or $");
				sp->EffectTriggerSpell[1]=atoi(startofid);
			}
		}
		else if( strstr( sp->Name, "Touch of Weakness"))
		{
			//check if we can find in the desription
			char *startofid=strstr(sp->Description, "cause $");
			if(startofid)
			{
				startofid += strlen("cause $");
				sp->EffectTriggerSpell[0] = atoi(startofid);
				sp->EffectTriggerSpell[1]=sp->EffectTriggerSpell[0]; //later versions of this spell changed to eff[1] the aura
				sp->procFlags = uint32(PROC_ON_MELEE_ATTACK_VICTIM);
			}
		}
		else if( strstr( sp->Name, "Firestone Passive"))
		{
			//Enchants the main hand weapon with fire, granting each attack a chance to deal $17809s1 additional fire damage.
			//check if we can find in the desription
			char * startofid=strstr(sp->Description, "to deal $");
			if(startofid)
			{
				startofid += strlen("to deal $");
				sp->EffectTriggerSpell[0] = atoi(startofid);
				sp->EffectApplyAuraName[0] = 42;
				sp->procFlags = PROC_ON_MELEE_ATTACK;
				sp->procChance = 50;
			}
		}
		//some procs trigger at intervals
		else if(sp->NameHash == SPELL_HASH_WATER_SHIELD)
		{
			sp->proc_interval = 3000; //few seconds
			sp->procFlags |= PROC_TARGET_SELF;
		}
		else if(sp->NameHash == SPELL_HASH_EARTH_SHIELD)
			sp->proc_interval = 3000; //few seconds
		else if( strstr( sp->Name, "Shadowguard"))
			sp->proc_interval = 3000; //few seconds
		else if( strstr( sp->Name, "Poison Shield"))
			sp->proc_interval = 3000; //few seconds
		else if( strstr( sp->Name, "Infused Mushroom"))
			sp->proc_interval = 10000; //10 seconds
		else if( strstr( sp->Name, "Aviana's Purpose"))
			sp->proc_interval = 10000; //10 seconds
		//don't change to namehash since we are searching only a protion of the name
 		else if( strstr( sp->Name, "Crippling Poison"))
		{
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
		}
		else if( strstr( sp->Name, "Mind-Numbing Poison"))
		{
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
		}
		else if( strstr( sp->Name, "Instant Poison"))
		{
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
		}
		else if( strstr( sp->Name, "Deadly Poison"))
		{
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
		}
		else if( strstr( sp->Name, "Wound Poison"))
		{
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
		}
		else if( strstr( sp->Name, "Scorpid Poison") )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_POISON;
		}

		if( strstr( sp->Description, "cannot be resisted" ) )
			sp->c_is_flags |= SPELL_FLAG_IS_NOT_RESISTABLE;

		if( strstr( sp->Description, "pierces through all absorption effects" ) )
			sp->c_is_flags |= SPELL_FLAG_PIERCES_ABSORBTION_EFF;

		//Set Silencing spells mech.
				// Set default mechanics if we don't already have one
		if( !sp->MechanicsType )
		{
		    //Set Silencing spells mechanic.
		    if( sp->EffectApplyAuraName[0] == 27 ||
				sp->EffectApplyAuraName[1] == 27 ||
				sp->EffectApplyAuraName[2] == 27 )
				sp->MechanicsType = MECHANIC_SILENCED;

		    //Set Stunning spells mechanic.
		    if( sp->EffectApplyAuraName[0] == 12 ||
				sp->EffectApplyAuraName[1] == 12 ||
				sp->EffectApplyAuraName[2] == 12 )
				sp->MechanicsType = MECHANIC_STUNNED;

		    //Set Fearing spells mechanic
		    if( sp->EffectApplyAuraName[0] == 7 ||
				sp->EffectApplyAuraName[1] == 7 ||
				sp->EffectApplyAuraName[2] == 7 )
				sp->MechanicsType = MECHANIC_FLEEING;
		}

		// Sap, Gouge, Blehhhh
		if( sp->NameHash == SPELL_HASH_GOUGE ||
			sp->NameHash == SPELL_HASH_SAP ||
			sp->NameHash == SPELL_HASH_REPENTANCE ||
			sp->NameHash == SPELL_HASH_MAIM ||
			sp->NameHash == SPELL_HASH_GOBLIN_ROCKET_HELMET ||
			sp->NameHash == SPELL_HASH_RECKLESS_CHARGE)
			sp->MechanicsType = MECHANIC_INCAPACIPATED;

		if( sp->proc_interval != 0 )
			sp->procFlags |= PROC_REMOVEONUSE;

		// Seal of Command - Proc Chance
		if( sp->NameHash == SPELL_HASH_SEAL_OF_COMMAND )
		{
			sp->procChance = 25;
			sp->procFlags = PROC_ON_MELEE_ATTACK;
			sp->School = SCHOOL_HOLY; //the procspells of the original seal of command have fizical school instead of holy
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MAGIC; //heh, crazy spell uses melee/ranged/magic dmg type for 1 spell. Now which one is correct ?
		}

		//Seal of Jusice - Proc Chance
		if( sp->NameHash == SPELL_HASH_SEAL_OF_JUSTICE )
			sp->procChance = 25;

		/* Decapitate */
		if( sp->NameHash == SPELL_HASH_DECAPITATE )
			sp->procChance = 30;

		if( sp->NameHash == SPELL_HASH_DIVINE_SHIELD || sp->NameHash == SPELL_HASH_DIVINE_PROTECTION || sp->NameHash == SPELL_HASH_BLESSING_OF_PROTECTION )
			sp->MechanicsType = 25;

		if(sp->NameHash == SPELL_HASH_DRINK && sp->EffectBasePoints[0] == -1 &&
			sp->EffectApplyAuraName[1] == 226 && sp->EffectBasePoints[1] > 0)
		{
			sp->EffectBasePoints[0] = sp->EffectBasePoints[1];
			sp->Effect[1] = SPELL_EFFECT_NULL;
		}

		/* hackfix for this - FIX ME LATER - Burlex */
		if( namehash == SPELL_HASH_SEAL_FATE )
			sp->procFlags = 0;

		if(
			((sp->Attributes & ATTRIBUTES_TRIGGER_COOLDOWN) && (sp->AttributesEx & ATTRIBUTESEX_NOT_BREAK_STEALTH)) //rogue cold blood
			|| ((sp->Attributes & ATTRIBUTES_TRIGGER_COOLDOWN) && (!sp->AttributesEx || sp->AttributesEx & ATTRIBUTESEX_REMAIN_OOC))
			)
		{
			sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;
		}

		/////////////////////////////////////////////////////////////////
		//SPELL COEFFICIENT SETTINGS START
		//////////////////////////////////////////////////////////////////

		//Setting Cast Time Coefficient
		SpellCastTime *sd = dbcSpellCastTime.LookupEntry(sp->CastingTimeIndex);
		float castaff = float(GetCastTime(sd));
		if(castaff < 1500) castaff = 1500;
		else
			if(castaff > 7000) castaff = 7000;

		sp->casttime_coef = castaff / 3500;		 

		SpellEntry * spz;
		bool spcheck = false;

		//Flag for DoT and HoT
		for( uint8 i = 0 ; i < 3 ; i++ )
		{
			if (sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_DAMAGE ||
				sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_HEAL ||
				sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_LEECH )
			{
				sp->spell_coef_flags |= SPELL_FLAG_IS_DOT_OR_HOT_SPELL;
				break;
			}
		}

		//Flag for DD or DH
		for( uint8 i = 0 ; i < 3 ; i++ )
		{
			if ( sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_TRIGGER_SPELL && sp->EffectTriggerSpell[i] )
			{
				spz = dbcSpell.LookupEntry( sp->EffectTriggerSpell[i] );
				if( spz &&
					spz->Effect[i] == SPELL_EFFECT_SCHOOL_DAMAGE ||
					spz->Effect[i] == SPELL_EFFECT_HEAL
					) 
					spcheck = true;
			}
			if (sp->Effect[i] == SPELL_EFFECT_SCHOOL_DAMAGE ||
				sp->Effect[i] == SPELL_EFFECT_HEAL ||
				spcheck
				)
			{
				sp->spell_coef_flags |= SPELL_FLAG_IS_DD_OR_DH_SPELL;
				break;
			}
		}

		for(uint8 i = 0 ; i < 3; i++)
		{
			switch (sp->EffectImplicitTargetA[i])
			{
				//AoE
			case EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS:
			case EFF_TARGET_ALL_ENEMY_IN_AREA:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT:
			case EFF_TARGET_ALL_PARTY_AROUND_CASTER:
			case EFF_TARGET_ALL_ENEMIES_AROUND_CASTER:
			case EFF_TARGET_IN_FRONT_OF_CASTER:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_PARTY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_FRIENDLY_IN_AREA:
			case EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME:
			case EFF_TARGET_ALL_PARTY:
			case EFF_TARGET_LOCATION_INFRONT_CASTER:
			case EFF_TARGET_BEHIND_TARGET_LOCATION:
			case EFF_TARGET_LOCATION_INFRONT_CASTER_AT_RANGE:
				{
					sp->spell_coef_flags |= SPELL_FLAG_AOE_SPELL;
					break;
				}
			}	
		}

		for(uint8 i = 0 ; i < 3 ; i++)
		{
			switch (sp->EffectImplicitTargetB[i])
			{
				//AoE
			case EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS:
			case EFF_TARGET_ALL_ENEMY_IN_AREA:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT:
			case EFF_TARGET_ALL_PARTY_AROUND_CASTER:
			case EFF_TARGET_ALL_ENEMIES_AROUND_CASTER:
			case EFF_TARGET_IN_FRONT_OF_CASTER:
			case EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_PARTY_IN_AREA_CHANNELED:
			case EFF_TARGET_ALL_FRIENDLY_IN_AREA:
			case EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME:
			case EFF_TARGET_ALL_PARTY:
			case EFF_TARGET_LOCATION_INFRONT_CASTER:
			case EFF_TARGET_BEHIND_TARGET_LOCATION:
			case EFF_TARGET_LOCATION_INFRONT_CASTER_AT_RANGE:
				{
					sp->spell_coef_flags |= SPELL_FLAG_AOE_SPELL;
					break;
				}
			}	
			if(sp->Effect[i] == 0)
				continue;

			//Apply aura fixes
			if( sp->Effect[i] == SPELL_EFFECT_APPLY_AURA )
			{
				switch( sp->EffectApplyAuraName[i] )
				{
					case SPELL_AURA_MOD_CONFUSE: 
						sp->auraimmune_flag |= AURAIMMUNE_CONFUSE;break;
					case SPELL_AURA_MOD_CHARM: 
						sp->auraimmune_flag |= AURAIMMUNE_CHARM;break;
					case SPELL_AURA_MOD_FEAR: 
						sp->auraimmune_flag |= AURAIMMUNE_FEAR;break;
					case SPELL_AURA_MOD_STUN: 
						sp->auraimmune_flag |= AURAIMMUNE_STUN;break;
					case SPELL_AURA_MOD_PACIFY: 
						sp->auraimmune_flag |= AURAIMMUNE_PACIFY;break;
					case SPELL_AURA_MOD_ROOT: 
						sp->auraimmune_flag |= AURAIMMUNE_ROOT;break;
					case SPELL_AURA_MOD_SILENCE: 
						sp->auraimmune_flag |= AURAIMMUNE_SILENCE;break;
					case SPELL_AURA_MOD_INCREASE_SPEED: 
						sp->auraimmune_flag |= AURAIMMUNE_INCSPEED;break;
					case SPELL_AURA_MOD_DECREASE_SPEED: 
						sp->auraimmune_flag |= AURAIMMUNE_DECSPEED;break;
					case SPELL_AURA_TRANSFORM: 
						sp->auraimmune_flag |= AURAIMMUNE_TRANSFORM;break;
					case SPELL_AURA_MOD_TAUNT: 
						sp->auraimmune_flag |= AURAIMMUNE_TAUNT;break;
				}
			}
		}

		//Special Cases
		//Holy Light & Flash of Light
		if(sp->NameHash == SPELL_HASH_HOLY_LIGHT ||
			sp->NameHash == SPELL_HASH_FLASH_OF_LIGHT)
			sp->spell_coef_flags |= SPELL_FLAG_IS_DD_OR_DH_SPELL;

		if(sp->NameHash == SPELL_HASH_FIREBALL)
			sp->spell_coef_flags = SPELL_FLAG_IS_DD_OR_DH_SPELL;

		//Additional Effect (not healing or damaging)
		for( uint8 i = 0 ; i < 3 ; i++ )
		{
			if(sp->Effect[i] == 0)
				continue;

			switch (sp->Effect[i])
			{
			case SPELL_EFFECT_SCHOOL_DAMAGE:
			case SPELL_EFFECT_ENVIRONMENTAL_DAMAGE:
			case SPELL_EFFECT_HEALTH_LEECH:
			case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
			case SPELL_EFFECT_ADD_EXTRA_ATTACKS:
			case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
			case SPELL_EFFECT_POWER_BURN:
			case SPELL_EFFECT_ATTACK:
			case SPELL_EFFECT_HEAL:
			case SPELL_EFFECT_HEALTH_FUNNEL:
			case SPELL_EFFECT_HEAL_MAX_HEALTH:
			case SPELL_EFFECT_DUMMY:
				continue;
			}

			switch (sp->EffectApplyAuraName[i])
			{
			case SPELL_AURA_PERIODIC_DAMAGE:
			case SPELL_AURA_PROC_TRIGGER_DAMAGE:
			case SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
			case SPELL_AURA_POWER_BURN:
			case SPELL_AURA_PERIODIC_HEAL:
			case SPELL_AURA_MOD_INCREASE_HEALTH:
			case SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
			case SPELL_AURA_DUMMY:
				continue;
			}

			sp->spell_coef_flags |= SPELL_FLAG_ADITIONAL_EFFECT;
			break;

		}

		//Calculating fixed coeficients
		//Channeled spells
		if( sp->ChannelInterruptFlags != 0 )
		{
			float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
			if(Duration < 1500) Duration = 1500;
			else if(Duration > 7000) Duration = 7000;
			sp->fixed_hotdotcoef = (Duration / 3500.0f);

			if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
				sp->fixed_hotdotcoef *= 0.95f;
			if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
				sp->fixed_hotdotcoef *= 0.5f;
		}

		//Standard spells
		else if( (sp->spell_coef_flags & SPELL_FLAG_IS_DD_OR_DH_SPELL) && !(sp->spell_coef_flags & SPELL_FLAG_IS_DOT_OR_HOT_SPELL) )
		{
			sp->fixed_dddhcoef = sp->casttime_coef;
			if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
				sp->fixed_dddhcoef *= 0.95f;
			if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
				sp->fixed_dddhcoef *= 0.5f;
		}

		//Over-time spells
		else if( !(sp->spell_coef_flags & SPELL_FLAG_IS_DD_OR_DH_SPELL) && (sp->spell_coef_flags & SPELL_FLAG_IS_DOT_OR_HOT_SPELL) )
		{
			float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
			sp->fixed_hotdotcoef = (Duration / 15000.0f);

			if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
				sp->fixed_hotdotcoef *= 0.95f;
			if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
				sp->fixed_hotdotcoef *= 0.5f;

		}

		//Combined standard and over-time spells
		else if( sp->spell_coef_flags & SPELL_FLAG_IS_DD_DH_DOT_SPELL )
		{
			float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
			float Portion_to_Over_Time = (Duration / 15000.0f) / ((Duration / 15000.0f) + sp->casttime_coef );
			float Portion_to_Standard = 1.0f - Portion_to_Over_Time;

			sp->fixed_dddhcoef = sp->casttime_coef * Portion_to_Standard;
			sp->fixed_hotdotcoef = (Duration / 15000.0f) * Portion_to_Over_Time;

			if( sp->spell_coef_flags & SPELL_FLAG_ADITIONAL_EFFECT )
			{
				sp->fixed_dddhcoef *= 0.95f;
				sp->fixed_hotdotcoef *= 0.95f;
			}
			if( sp->spell_coef_flags & SPELL_FLAG_AOE_SPELL )
			{
				sp->fixed_dddhcoef *= 0.5f;
				sp->fixed_hotdotcoef *= 0.5f;
			}		
		}

		///	SPELLS CAN CRIT ///
		sp->spell_can_crit = true; // - except in special cases noted in this section

		if(sp->SpellFamilyName == 15)	// Death Knight
			sp->fixed_dddhcoef = sp->fixed_hotdotcoef = 0.0f; // Don't want to use SP coefficient for them

		// Spells Coefficient Exceptions based on http://www.wowwiki.com/Spell_power
		switch (sp->NameHash)
		{
		case SPELL_HASH_HOLY_FIRE:
			sp->fixed_dddhcoef = 0.575f;
			sp->fixed_hotdotcoef = 0.185f;
			break;
		case SPELL_HASH_REGROWTH:
			sp->fixed_dddhcoef = 0.3f;
			sp->fixed_hotdotcoef = 0.7f;
			break;
		case SPELL_HASH_CORRUPTION:
			sp->fixed_hotdotcoef = 0.93f;
			break;
		case SPELL_HASH_CURSE_OF_AGONY:
			sp->fixed_hotdotcoef = 1.2f;
			break;
		case SPELL_HASH_CURSE_OF_DOOM:
			sp->fixed_hotdotcoef = 2.0f;
			break;
		case SPELL_HASH_SHADOW_WORD__PAIN:
			sp->fixed_hotdotcoef = 1.1f;
			break;
		case SPELL_HASH_MIND_FLAY:
			sp->fixed_hotdotcoef = 0.57f;
			break;
		case SPELL_HASH_SOUL_FIRE:
			sp->fixed_hotdotcoef = 1.15f;
			break;
		case SPELL_HASH_PYROBLAST:
			sp->fixed_dddhcoef = 1.15f;
			sp->fixed_hotdotcoef = 0.05f;
			break;
		case SPELL_HASH_FROSTFIRE_BOLT:
			sp->fixed_dddhcoef = 0.8571f;
			break;
		case SPELL_HASH_DRAIN_SOUL:
			sp->fixed_hotdotcoef = 1.15f;
			break;
		case SPELL_HASH_LIFEBLOOM:
			sp->fixed_dddhcoef = 0.3544f;
			sp->fixed_hotdotcoef = 0.343f;
			break;
		case SPELL_HASH_RAIN_OF_FIRE:
			sp->fixed_dddhcoef = 0.083f;
			break;
		case SPELL_HASH_ARCANE_MISSILES:
			sp->fixed_dddhcoef = 0.2857f; // per second
			break;
		case SPELL_HASH_BLIZZARD:
			sp->fixed_dddhcoef = 0.1437f; // per tick
			break;
		case SPELL_HASH_POWER_WORD__SHIELD:
			sp->Dspell_coef_override = 0.8068f;
			break;

		// Death Knight Attack Power coefficients
		case SPELL_HASH_BLOOD_BOIL:
			sp->fixed_apcoef = 0.04f;
			break;
		case SPELL_HASH_BLOOD_PLAGUE:
			sp->fixed_apcoef = 0.055f;
			break;
		case SPELL_HASH_BLOODWORMS:
			sp->fixed_apcoef = 0.006f;
			break;
		case SPELL_HASH_CORPSE_EXPLOSION:
			sp->fixed_apcoef = 0.0475f;
			break;
		case SPELL_HASH_DEATH_AND_DECAY:
			sp->fixed_apcoef = 0.475f;	// Per whole duration
			break;
		case SPELL_HASH_DEATH_COIL:
			sp->fixed_apcoef = 0.15f;
			break;
		case SPELL_HASH_FROST_FEVER:
			sp->fixed_apcoef = 0.055f;
			break;
		case SPELL_HASH_HOWLING_BLAST:
			sp->fixed_apcoef = 0.1f;
			break;
		case SPELL_HASH_SUMMON_GARGOYLE:
		case SPELL_HASH_GARGOYLE_STRIKE:
			sp->fixed_apcoef = 0.4f;
			break;
		case SPELL_HASH_ICY_TOUCH:
			sp->fixed_apcoef = 0.1f;
			break;
		case SPELL_HASH_PESTILENCE:
			sp->fixed_apcoef = 0.04f;
			break;
		case SPELL_HASH_STRANGULATE:
			sp->fixed_apcoef = 0.06f;
			break;
		case SPELL_HASH_UNHOLY_BLIGHT:
			sp->fixed_apcoef = 0.013f;
			break;
		// Paladin coefficients
		case SPELL_HASH_AVENGER_S_SHIELD:
			sp->fixed_apcoef = 0.07f;
			sp->fixed_dddhcoef = 0.07f;
			break;
		}

		//////////////////////////////////////////////////////
		// CLASS-SPECIFIC SPELL FIXES						//
		//////////////////////////////////////////////////////

		/* Note: when applying spell hackfixes, please follow a template */

		//////////////////////////////////////////
		// WARRIOR								//
		//////////////////////////////////////////

		// Insert warrior spell fixes here
		if( sp->NameHash == SPELL_HASH_MORTAL_STRIKE)
			sp->maxstack = 1; // Healing reduction shouldn't stack

		//////////////////////////////////////////
		// PALADIN								//
		//////////////////////////////////////////

		// Insert paladin spell fixes here
			
		// Seal of Righteousness - cannot crit
		if( sp->NameHash == SPELL_HASH_SEAL_OF_RIGHTEOUSNESS )
			sp->spell_can_crit = false;

		//Seal of Light
		if( sp->NameHash == SPELL_HASH_SEAL_OF_LIGHT)
		{
			sp->Dspell_coef_override = 0.0f;
			sp->procChance = 45;	/* this will do */
		}

		if( sp->NameHash == SPELL_HASH_JUDGEMENTS_OF_THE_PURE )
			sp->procFlags = PROC_ON_CAST_SPELL;

		//////////////////////////////////////////
		// HUNTER								//
		//////////////////////////////////////////

		// Insert hunter spell fixes here
				
		
		// THESE FIXES ARE GROUPED FOR CODE CLEANLINESS.
		/*
		// Concussive Shot, Distracting Shot, Silencing Shot - ranged spells
		if( sp->NameHash == SPELL_HASH_CONCUSSIVE_SHOT || sp->NameHash == SPELL_HASH_DISTRACTING_SHOT || sp->NameHash == SPELL_HASH_SILENCING_SHOT || sp->NameHash == SPELL_HASH_SCATTER_SHOT || sp->NameHash == SPELL_HASH_TRANQUILIZING_SHOT )
			sp->is_ranged_spell = true;

		// All stings - ranged spells
		if( sp->NameHash == SPELL_HASH_SERPENT_STING || sp->NameHash == SPELL_HASH_SCORPID_STING || sp->NameHash == SPELL_HASH_VIPER_STING || sp->NameHash == SPELL_HASH_WYVERN STING )
			sp->is_ranged_spell = true;
		*/
		// come to think of it... anything *castable* requiring a ranged weapon is a ranged spell -.-
		// Note that talents etc also come under this, however it does not matter
		// if they get flagged as ranged spells because is_ranged_spell is only used for
		// differentiating between resistable and physically avoidable spells.
		if( sp->EquippedItemClass == 2 && sp->EquippedItemSubClass & 262156 ) // 4 + 8 + 262144 ( becomes item classes 2, 3 and 18 which correspond to bow, gun and crossbow respectively)
			sp->is_ranged_spell = true;

		if( sp->NameHash == SPELL_HASH_AIMED_SHOT)
			sp->maxstack = 1; // Healing reduction shouldn't stack

		if( sp->NameHash == SPELL_HASH_EXPLOSIVE_SHOT )
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;

		//////////////////////////////////////////
		// ROGUE								//
		//////////////////////////////////////////

		// Insert rogue spell fixes here
		if( sp->NameHash == SPELL_HASH_REMORSELESS_ATTACKS )
			sp->procFlags = PROC_ON_GAIN_EXPIERIENCE;

		if( sp->NameHash == SPELL_HASH_UNFAIR_ADVANTAGE )
			sp->procFlags = PROC_ON_DODGE_VICTIM;

		//////////////////////////////////////////
		// PRIEST								//
		//////////////////////////////////////////

		// Insert priest spell fixes here
		if( sp->NameHash == SPELL_HASH_BORROWED_TIME )
			sp->procFlags = PROC_ON_CAST_SPELL;

		if( sp->NameHash == SPELL_HASH_IMPROVED_SPIRIT_TAP )
			sp->procFlags = PROC_ON_CAST_SPELL;

		//////////////////////////////////////////
		// SHAMAN								//
		//////////////////////////////////////////

		// Insert shaman spell fixes here

		// Lightning Shield - cannot crit
		if( sp->NameHash == SPELL_HASH_LIGHTNING_SHIELD ) // not a mistake, the correct proc spell for lightning shield is also called lightning shield
			sp->spell_can_crit = false;

		// Frostbrand Weapon - 10% spd coefficient and 9ppm
		if( sp->NameHash == SPELL_HASH_FROSTBRAND_ATTACK )
			sp->Dspell_coef_override = 0.1f;

		if( sp->NameHash == SPELL_HASH_FROSTBRAND_WEAPON )
			sp->ProcsPerMinute = 9.0f;

		// Fire Nova - 21.4% spd coefficient
		if( sp->NameHash == SPELL_HASH_FIRE_NOVA )
			sp->Dspell_coef_override = 0.2142f;

		// Magma Totem - 10% spd coefficient
		if( sp->NameHash == SPELL_HASH_MAGMA_TOTEM )
			sp->Dspell_coef_override = 0.1f;

		// Searing Totem - 16.67% spd coefficient
		if( sp->NameHash == SPELL_HASH_ATTACK )
			sp->Dspell_coef_override = 0.1667f;

		// Healing Stream Totem - 4.5% healing coefficient
		if( sp->NameHash == SPELL_HASH_HEALING_STREAM_TOTEM )
			sp->Dspell_coef_override = 0.045f;

		// Earth Shield
		if( sp->NameHash == SPELL_HASH_EARTH_SHIELD) 
			sp->Dspell_coef_override = 0.2857f;

		// Nature's Guardian
		if( sp->NameHash == SPELL_HASH_NATURE_S_GUARDIAN )
		{
			sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_ANY_DAMAGE_VICTIM;
			sp->proc_interval = 5000;
			sp->EffectTriggerSpell[0] = 31616;
		}

		if(sp->NameHash == SPELL_HASH_WINDFURY_WEAPON || sp->NameHash == SPELL_HASH_FLAMETONGUE_WEAPON || sp->NameHash == SPELL_HASH_ROCKBITER_WEAPON ||
				sp->NameHash == SPELL_HASH_FROSTBRAND_WEAPON ||	sp->NameHash == SPELL_HASH_EARTHLIVING_WEAPON)
			sp->Flags3 |= FLAGS3_ENCHANT_OWN_ONLY;

		// Stoneclaw Totem
		if(sp->NameHash == SPELL_HASH_STONECLAW_TOTEM_PASSIVE)
			sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;

		// Flametongue Totem passive target fix
		if(sp->NameHash == SPELL_HASH_FLAMETONGUE_TOTEM && sp->Attributes & ATTRIBUTES_PASSIVE)
		{
			sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
			sp->EffectImplicitTargetB[0] = 0;
			sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
			sp->EffectImplicitTargetB[1] = 0;
		}

		// Unleashed Rage
		if(sp->NameHash == SPELL_HASH_UNLEASHED_RAGE)
			sp->procFlags = PROC_ON_CRIT_ATTACK;

		// Healing Stream
		if(sp->NameHash == SPELL_HASH_HEALING_STREAM_TOTEM && sp->Effect[0] == SPELL_EFFECT_DUMMY)
		{
			sp->EffectRadiusIndex[0] = 10; // 30 yards
			sp->Effect[0] = SPELL_EFFECT_HEAL;
			sp->logsId = 5394;
		}

		// Mana Spring
		if(sp->NameHash == SPELL_HASH_MANA_SPRING_TOTEM && sp->Effect[0] == SPELL_EFFECT_DUMMY)
		{
			sp->Effect[0] = SPELL_EFFECT_ENERGIZE;
			sp->EffectMiscValue[0] = POWER_TYPE_MANA;
			sp->logsId = 5675;
		}

		//////////////////////////////////////////
		// MAGE								//
		//////////////////////////////////////////

		// Insert mage spell fixes here

		// Hypothermia: undispellable
		if( sp->NameHash == SPELL_HASH_HYPOTHERMIA )
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;

		if( sp->NameHash == SPELL_HASH_IMPROVED_COUNTERSPELL )
		{
			sp->procFlags = PROC_ON_CAST_SPELL;
			sp->EffectSpellClassMask[0][0] = 0x00004000;	// Proc on counterspell only
		}

		if( sp->NameHash == SPELL_HASH_FROSTBITE )
		{
			sp->procFlags = PROC_NULL;
			sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_ROOT;
			sp->EffectTriggerSpell[0] = 12494;
			sp->School = SCHOOL_FROST;
			sp->c_is_flags |= SPELL_FLAG_CANNOT_PROC_ON_SELF;
		}

		//////////////////////////////////////////
		// WARLOCK								//
		//////////////////////////////////////////

		// Insert warlock spell fixes here

		//////////////////////////////////////////
		// DRUID								//
		//////////////////////////////////////////

		// Insert druid spell fixes here


		//////////////////////////////////////////
		// OTHER								//
		//////////////////////////////////////////
	}
	//Settings for special cases
	QueryResult * resultx = WorldDatabase.Query("SELECT * FROM spell_coef_override");
	if( resultx != NULL )
	{
		uint32 spellid;
		do 
		{
			Field * f;
			f = resultx->Fetch();
			spellid = f[0].GetUInt32();
			SpellEntry * sp = dbcSpell.LookupEntryForced( spellid );
			if( sp != NULL )
			{
				sp->Dspell_coef_override = f[2].GetFloat();
				sp->OTspell_coef_override = f[3].GetFloat();
			}
			else
			{
				if(Config.MainConfig.GetBoolDefault("Server", "CleanDatabase", false))
				{
					WorldDatabase.Query("DELETE FROM spell_coef_override where id = '%u'", spellid);
				}
				Log.Warning("SpellCoefOverride", "Has nonexistant spell %u.", spellid);
			}
			spellid = 0;
		} while( resultx->NextRow() );
		delete resultx;
	}

	//Fully loaded coefficients, we must share channeled coefficient to its triggered spells
	for(uint32 x=0; x < cnt; x++)
	{
		sp = dbcSpell.LookupRow(x);
		SpellEntry * spz;

		//Case SPELL_AURA_PERIODIC_TRIGGER_SPELL
		for( uint8 i = 0 ; i < 3 ; i++ )
		{
			if ( sp->EffectApplyAuraName[i] == SPELL_AURA_PERIODIC_TRIGGER_SPELL )
			{
				spz = dbcSpell.LookupEntry( sp->EffectTriggerSpell[i] );
				if( spz != NULL ) 
				{
					if( sp->Dspell_coef_override >= 0 )
						spz->Dspell_coef_override = sp->Dspell_coef_override;
					else
					{
						//we must set bonus per tick on triggered spells now (i.e. Arcane Missiles)
						if( sp->ChannelInterruptFlags != 0 )
						{
							float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
							float amp = float(sp->EffectAmplitude[i]);
							sp->fixed_dddhcoef = sp->fixed_hotdotcoef * amp / Duration;
						}			
						spz->fixed_dddhcoef = sp->fixed_dddhcoef;
					}

					if( sp->OTspell_coef_override >= 0 )
						spz->OTspell_coef_override = sp->OTspell_coef_override;
					else
					{
						//we must set bonus per tick on triggered spells now (i.e. Arcane Missiles)
						if( sp->ChannelInterruptFlags != 0 )
						{
							float Duration = float( GetDuration( dbcSpellDuration.LookupEntry( sp->DurationIndex ) ));
							float amp = float(sp->EffectAmplitude[i]);
							sp->fixed_hotdotcoef *= amp / Duration;
						}
						spz->fixed_hotdotcoef = sp->fixed_hotdotcoef;
					}
					break;
				}
			}
		}
		ApplySingleSpellFixes(sp);
	}
	for(list<SpellEntry*>::iterator itr = sWorld.dummyspells.begin(); itr != sWorld.dummyspells.end(); ++itr)
		ApplySingleSpellFixes(*itr);

	sp = dbcSpell.LookupEntryForced( 26659 );
	SpellEntry * sp2 = sp;
	sp2->Id = 62388;
	sp2->Name = "Dummy Shit";
	sp2->DurationIndex = 41;
	sp2->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	dbcSpell.SetRow(62388,sp2);

#ifdef DUMP_CLASS_SPELLS
	DumpClassSpells();
#endif
#ifdef DUMP_SPELL_RANKS_SQL
	DumpSpellRanksSQL();
#endif
#ifdef DUMP_TALENT_SPELLS
	DumpTalentSpells();
	exit(0);
#endif
}
