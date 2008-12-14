/*
 * Aspire Hearthstone
 * Copyright (C) 2008 AspireDev <http://www.aspiredev.org/>
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

enum SUMMON_TYPE
{
    SUMMON_TYPE_POSSESSED = 65,
    SUMMON_TYPE_GUARDIAN = 61,
    SUMMON_TYPE_WILD = 64,
    SUMMON_TYPE_DEMON = 66,
    SUMMON_TYPE_TOTEM_1 = 63,
    SUMMON_TYPE_TOTEM_2 = 81,
    SUMMON_TYPE_TOTEM_3 = 82,
    SUMMON_TYPE_TOTEM_4 = 83,
    SUMMON_TYPE_SUMMON = 67,
    SUMMON_TYPE_CRITTER = 41,
    SUMMON_TYPE_CREATE_TOTEM = 121,
};

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
	sp->Effect[0]=3;
	sp->EffectImplicitTargetA[0]=25;
	sp->NameHash=crc32((const unsigned char*)name, (unsigned int)strlen(name));
	sp->dmg_multiplier[0]=1.0f;
	sp->StanceBarOrder=-1;
	dbcSpell.SetRow(id,sp);
	sWorld.dummyspells.push_back(sp);
}

void Apply112SpellFixes()
{
	SpellEntry * sp;
	// Spell 1455 Proc Chance (Life Tap Rank 2)
	sp = dbcSpell.LookupEntryForced(1455);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 1456 Proc Chance (Life Tap Rank 3)
	sp = dbcSpell.LookupEntryForced(1456);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 3391 Proc Chance (Thrash )
	sp = dbcSpell.LookupEntryForced(3391);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 8033 Proc Chance (Frostbrand Weapon Rank 1)
	sp = dbcSpell.LookupEntryForced(8033);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 8034 Proc Chance (Frostbrand Attack Rank 1)
	sp = dbcSpell.LookupEntryForced(8034);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 8037 Proc Chance (Frostbrand Attack Rank 2)
	sp = dbcSpell.LookupEntryForced(8037);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 8182 Proc Chance (Frost Resistance Rank 1)
	sp = dbcSpell.LookupEntryForced(8182);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 8185 Proc Chance (Fire Resistance Rank 1)
	sp = dbcSpell.LookupEntryForced(8185);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 8516 Proc Chance (Windfury Totem Rank 1)
	sp = dbcSpell.LookupEntryForced(8516);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 10456 Proc Chance (Frostbrand Weapon Rank 3)
	sp = dbcSpell.LookupEntryForced(10456);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 10458 Proc Chance (Frostbrand Attack Rank 3)
	sp = dbcSpell.LookupEntryForced(10458);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 10476 Proc Chance (Frost Resistance Rank 2)
	sp = dbcSpell.LookupEntryForced(10476);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 10477 Proc Chance (Frost Resistance Rank 3)
	sp = dbcSpell.LookupEntryForced(10477);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 10534 Proc Chance (Fire Resistance Rank 2)
	sp = dbcSpell.LookupEntryForced(10534);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 10535 Proc Chance (Fire Resistance Rank 3)
	sp = dbcSpell.LookupEntryForced(10535);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 10608 Proc Chance (Windfury Totem Rank 2)
	sp = dbcSpell.LookupEntryForced(10608);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 10610 Proc Chance (Windfury Totem Rank 3)
	sp = dbcSpell.LookupEntryForced(10610);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 11687 Proc Chance (Life Tap Rank 4)
	sp = dbcSpell.LookupEntryForced(11687);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 11688 Proc Chance (Life Tap Rank 5)
	sp = dbcSpell.LookupEntryForced(11688);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 11689 Proc Chance (Life Tap Rank 6)
	sp = dbcSpell.LookupEntryForced(11689);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 12284 Proc Chance (Mace Specialization Rank 1)
	sp = dbcSpell.LookupEntryForced(12284);
	if(sp != NULL)
		sp->procChance = 1;

	// Spell 12292 Proc Chance (Death Wish )
	sp = dbcSpell.LookupEntryForced(12292);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 12322 Proc Chance (Unbridled Wrath Rank 1)
	sp = dbcSpell.LookupEntryForced(12322);
	if(sp != NULL)
		sp->procChance = 8;

	// Spell 12701 Proc Chance (Mace Specialization Rank 2)
	sp = dbcSpell.LookupEntryForced(12701);
	if(sp != NULL)
		sp->procChance = 2;

	// Spell 12702 Proc Chance (Mace Specialization Rank 3)
	sp = dbcSpell.LookupEntryForced(12702);
	if(sp != NULL)
		sp->procChance = 3;

	// Spell 12703 Proc Chance (Mace Specialization Rank 4)
	sp = dbcSpell.LookupEntryForced(12703);
	if(sp != NULL)
		sp->procChance = 4;

	// Spell 12704 Proc Chance (Mace Specialization Rank 5)
	sp = dbcSpell.LookupEntryForced(12704);
	if(sp != NULL)
		sp->procChance = 6;

	// Spell 12999 Proc Chance (Unbridled Wrath Rank 2)
	sp = dbcSpell.LookupEntryForced(12999);
	if(sp != NULL)
		sp->procChance = 16;

	// Spell 13000 Proc Chance (Unbridled Wrath Rank 3)
	sp = dbcSpell.LookupEntryForced(13000);
	if(sp != NULL)
		sp->procChance = 24;

	// Spell 13001 Proc Chance (Unbridled Wrath Rank 4)
	sp = dbcSpell.LookupEntryForced(13001);
	if(sp != NULL)
		sp->procChance = 32;

	// Spell 13002 Proc Chance (Unbridled Wrath Rank 5)
	sp = dbcSpell.LookupEntryForced(13002);
	if(sp != NULL)
		sp->procChance = 40;

	// Spell 14076 Proc Chance (Dirty Tricks Rank 1)
	sp = dbcSpell.LookupEntryForced(14076);
	if(sp != NULL)
		sp->procChance = 30;

	// Spell 14094 Proc Chance (Dirty Tricks Rank 2)
	sp = dbcSpell.LookupEntryForced(14094);
	if(sp != NULL)
		sp->procChance = 60;

	// Spell 15494 Proc Chance (Fury of Forgewright )
	sp = dbcSpell.LookupEntryForced(15494);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 15600 Proc Chance (Hand of Justice )
	sp = dbcSpell.LookupEntryForced(15600);
	if(sp != NULL)
		sp->procChance = 2;

	// Spell 15601 Proc Chance (Hand of Justice )
	sp = dbcSpell.LookupEntryForced(15601);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 15642 Proc Chance (Ironfoe )
	sp = dbcSpell.LookupEntryForced(15642);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 16352 Proc Chance (Frostbrand Attack Rank 4)
	sp = dbcSpell.LookupEntryForced(16352);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 16353 Proc Chance (Frostbrand Attack Rank 5)
	sp = dbcSpell.LookupEntryForced(16353);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 16355 Proc Chance (Frostbrand Weapon Rank 4)
	sp = dbcSpell.LookupEntryForced(16355);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 16356 Proc Chance (Frostbrand Weapon Rank 5)
	sp = dbcSpell.LookupEntryForced(16356);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 16459 Proc Chance (Sword Specialization )
	sp = dbcSpell.LookupEntryForced(16459);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 16843 Proc Chance (Crimson Fury )
	sp = dbcSpell.LookupEntryForced(16843);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 16850 Proc Chance (Celestial Focus Rank 1)
	sp = dbcSpell.LookupEntryForced(16850);
	if(sp != NULL)
		sp->procChance = 3;

	// Spell 16923 Proc Chance (Celestial Focus Rank 2)
	sp = dbcSpell.LookupEntryForced(16923);
	if(sp != NULL)
		sp->procChance = 6;

	// Spell 16924 Proc Chance (Celestial Focus Rank 3)
	sp = dbcSpell.LookupEntryForced(16924);
	if(sp != NULL)
		sp->procChance = 9;

	// Spell 18797 Proc Chance (Flurry Axe )
	sp = dbcSpell.LookupEntryForced(18797);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 18803 Proc Chance (Focus )
	sp = dbcSpell.LookupEntryForced(18803);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 19105 Proc Chance (MHTest01 Effect )
	sp = dbcSpell.LookupEntryForced(19105);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 19109 Proc Chance (MHTest02 Effect )
	sp = dbcSpell.LookupEntryForced(19109);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 19184 Proc Chance (Entrapment Rank 1)
	sp = dbcSpell.LookupEntryForced(19184);
	if(sp != NULL)
		sp->procChance = 5;

	// Spell 19228 Proc Chance (Improved Wing Clip Rank 1)
	sp = dbcSpell.LookupEntryForced(19228);
	if(sp != NULL)
		sp->procChance = 4;

	// Spell 19232 Proc Chance (Improved Wing Clip Rank 2)
	sp = dbcSpell.LookupEntryForced(19232);
	if(sp != NULL)
		sp->procChance = 8;

	// Spell 19233 Proc Chance (Improved Wing Clip Rank 3)
	sp = dbcSpell.LookupEntryForced(19233);
	if(sp != NULL)
		sp->procChance = 12;

	// Spell 19387 Proc Chance (Entrapment Rank 2)
	sp = dbcSpell.LookupEntryForced(19387);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 19388 Proc Chance (Entrapment Rank 3)
	sp = dbcSpell.LookupEntryForced(19388);
	if(sp != NULL)
		sp->procChance = 15;

	// Spell 20178 Proc Chance (Reckoning )
	sp = dbcSpell.LookupEntryForced(20178);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 21919 Proc Chance (Thrash )
	sp = dbcSpell.LookupEntryForced(21919);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 23158 Proc Chance (Concussive Shot Cooldown Reduction )
	sp = dbcSpell.LookupEntryForced(23158);
	if(sp != NULL)
		sp->procChance = 4;

	// Spell 26022 Proc Chance (Pursuit of Justice Rank 1)
	sp = dbcSpell.LookupEntryForced(26022);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 26023 Proc Chance (Pursuit of Justice Rank 2)
	sp = dbcSpell.LookupEntryForced(26023);
	if(sp != NULL)
		sp->procChance = 100;

	// Spell 27035 Proc Chance (Sword Specialization (OLD) )
	sp = dbcSpell.LookupEntryForced(27035);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 27521 Proc Chance (Mana Restore )
	sp = dbcSpell.LookupEntryForced(27521);
	if(sp != NULL)
		sp->procChance = 2;

	// Spell 27867 Proc Chance (Freeze )
	sp = dbcSpell.LookupEntryForced(27867);
	if(sp != NULL)
		sp->procChance = 2;

	// Spell 25500 Proc Chance (Frostbrand Weapon Rank 6)
	sp = dbcSpell.LookupEntryForced(25500);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 25501 Proc Chance (Frostbrand Attack Rank 6)
	sp = dbcSpell.LookupEntryForced(25501);
	if(sp != NULL)
		sp->procChance = 10;

	// Spell 38617 Proc Chance (Frostbrand Attack )
	sp = dbcSpell.LookupEntryForced(38617);
	if(sp != NULL)
		sp->procChance = 10;
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

void ApplyNormalFixes()
{
	//Updating spell.dbc
	SpellEntry *sp;
	uint32 ids[100], ranks;

	Log.Notice("World", "Processing %u spells...", dbcSpell.GetNumRows());
	Apply112SpellFixes();

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

		uint32 rank = 0;
		uint32 type = 0;
		uint32 namehash = 0;

		sp->self_cast_only = false;
		sp->Unique = false;
		sp->apply_on_shapeshift_change = false;
		sp->always_apply = false;
		sp->procs_per_minute = 0.0f;

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
		AURASTATE_FLAG_DODGE_BLOCK			= 1,        //1
		AURASTATE_FLAG_HEALTH20             = 2,        //2
		AURASTATE_FLAG_BERSERK              = 4,        //3
		AURASTATE_FLAG_JUDGEMENT            = 16,       //5
		AURASTATE_FLAG_PARRY                = 64,       //7
		AURASTATE_FLAG_LASTKILLWITHHONOR    = 512,      //10
		AURASTATE_FLAG_CRITICAL             = 1024,     //11
		AURASTATE_FLAG_HEALTH35             = 4096,     //13
		AURASTATE_FLAG_IMMOLATE             = 8192,     //14
		AURASTATE_FLAG_REJUVENATE           = 16384,    //15 //where do i use this ?
		AURASTATE_FLAG_POISON               = 32768,    //16
		*/

		// New 2.4.3 summon types
        for(uint8 i = 0; i<3; i++)
        {
            if(!sp->EffectMiscValueB[i])
                continue;

            switch(sp->EffectMiscValueB[i])
            {
                case SUMMON_TYPE_POSSESSED: sp->Effect[i] = SPELL_EFFECT_SUMMON_POSSESSED; break;
                case SUMMON_TYPE_GUARDIAN: sp->Effect[i] = SPELL_EFFECT_SUMMON_GUARDIAN; break;
                case SUMMON_TYPE_WILD: sp->Effect[i] = SPELL_EFFECT_SUMMON_WILD; break;
                case SUMMON_TYPE_DEMON: sp->Effect[i] = SPELL_EFFECT_SUMMON_DEMON; break;
                case SUMMON_TYPE_TOTEM_1: sp->Effect[i] = SPELL_EFFECT_SUMMON_TOTEM_SLOT1; break;
                case SUMMON_TYPE_TOTEM_2: sp->Effect[i] = SPELL_EFFECT_SUMMON_TOTEM_SLOT2; break;
                case SUMMON_TYPE_TOTEM_4: sp->Effect[i] = SPELL_EFFECT_SUMMON_TOTEM_SLOT4; break;
                case SUMMON_TYPE_CRITTER: sp->Effect[i] = SPELL_EFFECT_SUMMON_CRITTER; break;
                case SUMMON_TYPE_TOTEM_3: sp->Effect[i] = SPELL_EFFECT_SUMMON_TOTEM_SLOT3; break;
                //case SUMMON_TYPE_CREATE_TOTEM: sp->Effect[i] = SPELL_EFFECT_SUMMON_TOTEM; break;
            }
        }

		// apply on shapeshift change
		if( sp->NameHash == SPELL_HASH_TRACK_HUMANOIDS )
			sp->apply_on_shapeshift_change = true;

		if( sp->NameHash == SPELL_HASH_BLOOD_FURY || sp->NameHash == SPELL_HASH_SHADOWSTEP )
			sp->always_apply = true;

		//there are some spells that change the "damage" value of 1 effect to another : devastate = bonus first then damage
		//this is a total bullshit so remove it when spell system supports effect overwriting
		for( uint32 col1_swap = 0; col1_swap < 2 ; col1_swap++ )
			for( uint32 col2_swap = col1_swap ; col2_swap < 3 ; col2_swap++ )
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

			// fill in more here
			/*switch( sp->EffectImplicitTargetA[b] )
			{
			case 1:
			case 9:
				sp->self_cast_only = true;
				break;
			}

			// fill in more here too
			switch( sp->EffectImplicitTargetB[b] )
			{
			case 1:
			case 9:
				sp->self_cast_only = true;
				break;
			}*/
		}

		/*if(sp->self_cast_only && !(sp->Attributes&64))
			printf("SPELL SELF CAST ONLY: %s %u\n", sp->Name, sp->Id);*/

		if(!strcmp(sp->Name, "Hearthstone") || !strcmp(sp->Name, "Stuck") || !strcmp(sp->Name, "Astral Recall"))
			sp->self_cast_only = true;

		sp->proc_interval = 0;//trigger at each event
		sp->c_is_flags = 0;
		sp->spell_coef_flags = 0;
		sp->Dspell_coef_override = -1;
		sp->OTspell_coef_override = -1;
		sp->casttime_coef = 0;
		sp->fixed_dddhcoef = -1;
		sp->fixed_hotdotcoef = -1;

		talentSpellIterator = talentSpells.find(sp->Id);
		if(talentSpellIterator == talentSpells.end())
			sp->talent_tree = 0;
		else
			sp->talent_tree = talentSpellIterator->second;

		skilllinespell *sk = objmgr.GetSpellSkill(sp->Id);
		sp->skilline = sk ? sk->skilline : 0;

		// parse rank text
		if( !sscanf( sp->Rank, "Rank %d", (unsigned int*)&rank) )
			rank = 0;

		// Inback hacky fix
		if (strstr(sp->Description, "Must be behind the target") ||
		    strstr(sp->Description, "and behind the target"))
			sp->FacingCasterFlags = FACING_FLAG_INBACK;

		//seal of light 
		if( namehash == SPELL_HASH_SEAL_OF_LIGHT )			
			sp->procChance = 45;	/* this will do */

		//seal of command
		else if( namehash == SPELL_HASH_SEAL_OF_COMMAND )		
			sp->Spell_Dmg_Type = SPELL_DMG_TYPE_MAGIC;

		//judgement of command
		else if( namehash == SPELL_HASH_JUDGEMENT_OF_COMMAND )		
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
		{
            type |= SPELL_TYPE_SEAL;
		}
        else if( strstr( sp->Name, "Blessing"))
            type |= SPELL_TYPE_BLESSING;
        else if( strstr( sp->Name, "Curse"))
            type |= SPELL_TYPE_CURSE;
        else if( strstr( sp->Name, "Aspect"))
            type |= SPELL_TYPE_ASPECT;
        else if( strstr( sp->Name, "Sting") || strstr( sp->Name, "sting"))
            type |= SPELL_TYPE_STING;
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
		else if( namehash == SPELL_HASH_ARCANE_INTELLECT || namehash == SPELL_HASH_ARCANE_BRILLIANCE )
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
//            type |= SPELL_TYPE_WARLOCK_CURSES;
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
		else if( namehash == SPELL_HASH_FROST_PRESENCE || namehash == SPELL_HASH_BLOOD_PRESENCE || namehash == SPELL_HASH_UNHOLY_PRESENCE )
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

			if( b > 0 && sp->Effect[b] == SPELL_EFFECT_SUMMON && sp->EffectApplyAuraName[b - 1] == SPELL_AURA_MOUNTED )
				sp->Effect[b] = 0; // temp fix.
		}

		//stupid spell ranking problem
		if(sp->spellLevel==0)
		{
			uint32 new_level=0;
			if( strstr( sp->Name, "Apprentice "))
				new_level = 1;
			else if( strstr( sp->Name, "Journeyman "))
				new_level = 2;
			else if( strstr( sp->Name, "Expert "))
				new_level = 3;
			else if( strstr( sp->Name, "Artisan "))
				new_level = 4;
			else if( strstr( sp->Name, "Master "))
				new_level = 5;
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

//		removed by Zack Earth shield stacks 10 times. Current code does not support it
//		case SPELL_HASH_EARTH_SHIELD:		// Earth Shield
//			sp->buffIndexType = SPELL_TYPE_INDEX_EARTH_SHIELD;
//			break;

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
		}

		// PROCS PERMINUTE
		switch( namehash )
		{
		case SPELL_HASH_MAGTHERIDON_MELEE_TRINKET:
			sp->procs_per_minute = 1.5f;
			break; // dragonspine trophy
		case SPELL_HASH_ROMULO_S_POISON:
			sp->procs_per_minute = 1.5f;
			break; // romulo's
		case SPELL_HASH_BLACK_TEMPLE_MELEE_TRINKET:
			sp->procs_per_minute = 1.0f;
			break; // madness of the betrayer
		case SPELL_HASH_BAND_OF_THE_ETERNAL_CHAMPION:
			sp->proc_interval = 30;
			break;
		case SPELL_HASH_BAND_OF_THE_ETERNAL_DEFENDER:
			sp->proc_interval = 30;
			break;
		case SPELL_HASH_BAND_OF_THE_ETERNAL_RESTORER:
			sp->proc_interval = 30;
			break;
		case SPELL_HASH_BAND_OF_THE_ETERNAL_SAGE:
			sp->proc_interval = 30;
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
		sp->RankNumber = rank;

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
		//more triggered spell ids are wrong. I think blizz is trying to outsmart us :S
		else if( strstr( sp->Name, "Nature's Guardian"))
		{
			sp->EffectTriggerSpell[0] = 31616;
			sp->proc_interval = 5000;
		}
		//Chain Heal all ranks %50 heal value (49 + 1)
		else if( strstr( sp->Name, "Chain Heal"))
		{
			sp->EffectDieSides[0] = 49;
		}
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
		else if( strstr( sp->Name, "Water Shield"))
		{
			sp->proc_interval = 3000; //few seconds
			sp->procFlags |= PROC_TARGET_SELF;
		}
		else if( strstr( sp->Name, "Earth Shield"))
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
	}


	/////////////////////////////////////////////////////////////////
	//SPELL COEFFICIENT SETTINGS START
	//////////////////////////////////////////////////////////////////

	for(uint32 x=0; x < cnt; x++)
	{
		sp = dbcSpell.LookupRow(x);

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
		}

		//Special Cases
		//Holy Light & Flash of Light
		if(sp->NameHash == SPELL_HASH_HOLY_LIGHT ||
			sp->NameHash == SPELL_HASH_FLASH_OF_LIGHT)
			sp->spell_coef_flags |= SPELL_FLAG_IS_DD_OR_DH_SPELL;

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


		//////////////////////////////////////////////////////
		// CLASS-SPECIFIC SPELL FIXES						//
		//////////////////////////////////////////////////////

		/* Note: when applying spell hackfixes, please follow a template */

		//////////////////////////////////////////
		// WARRIOR								//
		//////////////////////////////////////////

		// Insert warrior spell fixes here

		//////////////////////////////////////////
		// PALADIN								//
		//////////////////////////////////////////

		// Insert paladin spell fixes here
			
			// Seal of Righteousness - cannot crit
			if( sp->NameHash == SPELL_HASH_SEAL_OF_RIGHTEOUSNESS )
				sp->spell_can_crit = false;

		//////////////////////////////////////////
		// HUNTER								//
		//////////////////////////////////////////

		// Insert hunter spell fixes here
		//Hunter - Go for the Throat
		sp = dbcSpell.LookupEntryForced( 34950 );
		if( sp != NULL )
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;

		sp = dbcSpell.LookupEntryForced( 34954 );
		if( sp != NULL )
			sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;

		sp = dbcSpell.LookupEntryForced( 34952 );
		if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;

		sp = dbcSpell.LookupEntryForced( 34953 );
		if( sp != NULL )
			sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
				
		
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
			{
				sp->is_ranged_spell = true;
			}

		//////////////////////////////////////////
		// ROGUE								//
		//////////////////////////////////////////

		// Insert rogue spell fixes here

		//////////////////////////////////////////
		// PRIEST								//
		//////////////////////////////////////////

		// Insert priest spell fixes here

		//////////////////////////////////////////
		// SHAMAN								//
		//////////////////////////////////////////

		// Insert shaman spell fixes here

			// Lightning Shield - cannot crit
			if( sp->NameHash == SPELL_HASH_LIGHTNING_SHIELD ) // not a mistake, the correct proc spell for lightning shield is also called lightning shield
				sp->spell_can_crit = false;

		//////////////////////////////////////////
		// MAGE								//
		//////////////////////////////////////////

		// Insert mage spell fixes here

		// Hypothermia: undispellable
		if( sp->NameHash == SPELL_HASH_HYPOTHERMIA )
			sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;

		// Winter's chill
		sp = dbcSpell.LookupEntryForced(12579);
		if( sp != NULL )
			sp->c_is_flags |= SPELL_FLAG_CANNOT_PROC_ON_SELF;


		//////////////////////////////////////////
		// WARLOCK								//
		//////////////////////////////////////////

		// Insert warlock spell fixes here

		//////////////////////////////////////////
		// DRUID								//
		//////////////////////////////////////////

		// Insert druid spell fixes here


	}

	//Settings for special cases
	QueryResult * resultx = WorldDatabase.Query("SELECT * FROM spell_coef_override");
	if( resultx != NULL )
	{
		do 
		{
			Field * f;
			f = resultx->Fetch();
			SpellEntry * sp = dbcSpell.LookupEntryForced( f[0].GetUInt32() );
			if( sp != NULL )
			{
				sp->Dspell_coef_override = f[2].GetFloat();
				sp->OTspell_coef_override = f[3].GetFloat();
			}
			else
				Log.Warning("SpellCoefOverride", "Has nonexistant spell %u.", f[0].GetUInt32());
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
	}	

	/////////////////////////////////////////////////////////////////
	//SPELL COEFFICIENT SETTINGS END
	/////////////////////////////////////////////////////////////////

	//this is so lame : shamanistic rage triggers a new spell which borrows it's stats from parent spell :S
	SpellEntry*  parentsp = dbcSpell.LookupEntryForced( 30823 );
	SpellEntry* triggersp = dbcSpell.LookupEntryForced( 30824 );

	if( parentsp != NULL && triggersp != NULL )
		triggersp->EffectBasePoints[0] = parentsp->EffectBasePoints[0];

	/// Elemental Focus
	sp = dbcSpell.LookupEntryForced( 16164 );
	if( sp != NULL && sp->Id == 16164 )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

	//remove stormstrike effect 0
	sp = dbcSpell.LookupEntryForced( 17364 );
	if( sp != NULL && sp->Id == 17364 )
		sp->Effect[0] = 0;

	//Warlock: Nether Protection
	sp = dbcSpell.LookupEntryForced( 30299 );
	if (sp != NULL)
	{
		sp->procChance = 10;
		sp->proc_interval = 13000;
	}
	sp = dbcSpell.LookupEntryForced( 30301 );
	if (sp != NULL)
	{
		sp->procChance = 20;
		sp->proc_interval = 13000;
	}
	sp = dbcSpell.LookupEntryForced( 30302 );
	if (sp != NULL)
	{
		sp->procChance = 30;
		sp->proc_interval = 13000;
	}

	//Warlock: Backlash
	sp = dbcSpell.LookupEntryForced( 34935 );
	if (sp != NULL)
	{
		sp->proc_interval = 8000;
		sp->procFlags |= PROC_ON_MELEE_ATTACK_VICTIM | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 34938 );
	if (sp != NULL)
	{
		sp->proc_interval = 8000;
		sp->procFlags |= PROC_ON_MELEE_ATTACK_VICTIM | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 34939 );
	if (sp != NULL)
	{
		sp->proc_interval = 8000;
		sp->procFlags |= PROC_ON_MELEE_ATTACK_VICTIM | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 34936 );
	if (sp != NULL)
	{
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_CAST_SPELL;
	}

	//Warlock: Demonic Knowledge
    sp = dbcSpell.LookupEntryForced( 35691 );
    if( sp != NULL )
	{
        sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
        sp->Effect[1] = 6;
        sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_DONE;
        sp->EffectBasePoints[1] = sp->EffectBasePoints[0];
		sp->EffectImplicitTargetA[1]= EFF_TARGET_PET;
        sp->Effect[2] = SPELL_EFFECT_TRIGGER_SPELL;
        sp->EffectTriggerSpell[2] = 35696;
		sp->EffectImplicitTargetA[2]=EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
    }
    sp = dbcSpell.LookupEntryForced( 35692 );
    if( sp != NULL )
	{
        sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
        sp->Effect[1] = 6;
        sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_DONE;
        sp->EffectBasePoints[1] = sp->EffectBasePoints[0];
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
        sp->Effect[2] = SPELL_EFFECT_TRIGGER_SPELL;
        sp->EffectTriggerSpell[2] = 35696;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
    }
    sp = dbcSpell.LookupEntryForced( 35693 );
    if( sp != NULL )
	{
        sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
        sp->Effect[1] = 6;
        sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_DONE;
        sp->EffectBasePoints[1] = sp->EffectBasePoints[0];
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
        sp->Effect[2] = SPELL_EFFECT_TRIGGER_SPELL;
        sp->EffectTriggerSpell[2] = 35696;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
    }
    sp = dbcSpell.LookupEntryForced( 35696 );
    if( sp != NULL )
	{
        sp->Effect[0] = 6; //making this only for the visible effect
        sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY; //no effect here
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

    //Priest - Holy Nova
    sp = dbcSpell.LookupEntryForced( 15237 );
    if( sp != NULL )
    {
        sp->Effect[1] = 64;
        sp->EffectTriggerSpell[1] = 23455;
    }
    sp = dbcSpell.LookupEntryForced( 15430 );
    if( sp != NULL )
    {
        sp->Effect[1] = 64;
        sp->EffectTriggerSpell[1] = 23458;
    }
    sp = dbcSpell.LookupEntryForced( 15431 );
    if( sp != NULL )
    {
        sp->Effect[1] = 64;
        sp->EffectTriggerSpell[1] = 23459;
    }
    sp = dbcSpell.LookupEntryForced( 27799 );
    if( sp != NULL )
    {
        sp->Effect[1] = 64;
        sp->EffectTriggerSpell[1] = 27803;
    }
    sp = dbcSpell.LookupEntryForced( 27800 );
    if( sp != NULL )
    {
        sp->Effect[1] = 64;
        sp->EffectTriggerSpell[1] = 27804;
    }
    sp = dbcSpell.LookupEntryForced( 27801 );
    if( sp != NULL )
    {
        sp->Effect[1] = 64;
        sp->EffectTriggerSpell[1] = 27805;
    }
    sp = dbcSpell.LookupEntryForced( 25331 );
    if( sp != NULL )
    {
        sp->Effect[1] = 64;
        sp->EffectTriggerSpell[1] = 25329;
    }

	sp = dbcSpell.LookupEntryForced( 30427 );
	if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_DUMMY;
	}

	// Moroes' garrote targets a single enemy instead of us
	sp = dbcSpell.LookupEntryForced( 37066 );
    if( sp != NULL )
    {
        sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
    }

	//Bloodlust targets sorounding party members instead of us
	sp = dbcSpell.LookupEntryForced( 2825 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}

	//Heroism targets sorounding party members instead of us
	sp = dbcSpell.LookupEntryForced( 32182 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}
	// Drums of war targets sorounding party members instead of us
	sp = dbcSpell.LookupEntryForced( 35475 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}

	// Symbol of Hope targets sorounding party members instead of us
	sp = dbcSpell.LookupEntryForced( 32548 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}

	// Drums of Battle targets sorounding party members instead of us
	sp = dbcSpell.LookupEntryForced( 35476 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}

	// Drums of Panic targets sorounding creatures instead of us
	sp = dbcSpell.LookupEntryForced( 35474 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_ENEMIES_AROUND_CASTER;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}

	// Drums of Restoration targets sorounding party members instead of us
	sp = dbcSpell.LookupEntryForced( 35478 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}
	// Drums of Speed targets sorounding party members instead of us
	sp = dbcSpell.LookupEntryForced( 35477 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_ALL_PARTY;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}

	sp = dbcSpell.LookupEntryForced( 34774 );
	if( sp != NULL ) //dragonspine trophy proc
	{
		sp->procChance = 6;
	}

	//paladin - Blessing of Light. Changed to scripted because it needs to mod target and should not influence holy nova
	sp = dbcSpell.LookupEntryForced( 19977 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 19978 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 19979 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 27144 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	}
	sp = dbcSpell.LookupEntryForced( 32770 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
	}

	//paladin - Seal of Vengeance
	sp = dbcSpell.LookupEntryForced( 31801 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
        sp->EffectTriggerSpell[0] = 31803;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}

	//paladin - Reckoning
	sp = dbcSpell.LookupEntryForced( 20177 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 20179 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 20180 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 20181 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 20182 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;

	//paladin - Reckoning Effect = proc on proc
	sp = dbcSpell.LookupEntryForced( 20178 );
	if( sp != NULL )
	{
		sp->procChance = 100;
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
	}

	//paladin - Judgement of Wisdom
	sp = dbcSpell.LookupEntryForced( 20186 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
        sp->EffectTriggerSpell[0] = 20268;
	}
	sp = dbcSpell.LookupEntryForced( 20354 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
        sp->EffectTriggerSpell[0] = 20352;
	}
	sp = dbcSpell.LookupEntryForced( 20355 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
        sp->EffectTriggerSpell[0] = 20353;
	}
	sp = dbcSpell.LookupEntryForced( 27164 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
        sp->EffectTriggerSpell[0] = 27165;
	}
	sp = dbcSpell.LookupEntryForced( 20268 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 20352 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 20353 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 27165 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;

	//paladin - Judgement of Light
	sp = dbcSpell.LookupEntryForced( 20185 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
        sp->EffectTriggerSpell[0] = 20267;
	}
	sp = dbcSpell.LookupEntryForced( 20344 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
        sp->EffectTriggerSpell[0] = 20341;
	}
	sp = dbcSpell.LookupEntryForced( 20345 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
        sp->EffectTriggerSpell[0] = 20342;
	}
	sp = dbcSpell.LookupEntryForced( 20346 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
        sp->EffectTriggerSpell[0] = 20343;
	}
	sp = dbcSpell.LookupEntryForced( 27162 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
        sp->EffectTriggerSpell[0] = 27163;
	}
	sp = dbcSpell.LookupEntryForced( 20267 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 20341 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 20342 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 20343 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;
	sp = dbcSpell.LookupEntryForced( 27163 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SINGLE_ENEMY;

	//paladin - Eye for an Eye
	sp = dbcSpell.LookupEntryForced( 9799 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
        sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
        sp->EffectTriggerSpell[0] = 25997;
	}
	sp = dbcSpell.LookupEntryForced( 25988 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT_VICTIM;
        sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
        sp->EffectTriggerSpell[0] = 25997;
	}

	//paladin - sanctified judgement
	sp = dbcSpell.LookupEntryForced( 31876 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
        sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
        sp->EffectTriggerSpell[0] = 31930;
	}
	sp = dbcSpell.LookupEntryForced( 31877 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
        sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
        sp->EffectTriggerSpell[0] = 31930;
	}
	sp = dbcSpell.LookupEntryForced( 31878 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
        sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
        sp->EffectTriggerSpell[0] = 31930;
		//sp->procChance=100;
	}

	//paladin - Blessed Life
	sp = dbcSpell.LookupEntryForced( 31828 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
        sp->EffectTriggerSpell[0] = 31828;
	}
	sp = dbcSpell.LookupEntryForced( 31829 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
        sp->EffectTriggerSpell[0] = 31828;
	}
	sp = dbcSpell.LookupEntryForced( 31830 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
        sp->EffectTriggerSpell[0] = 31828;
	}

	//paladin - Light's Grace
	sp = dbcSpell.LookupEntryForced( 31833 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 31835 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 31836 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	//shaman - Lightning Overload 
	sp = dbcSpell.LookupEntryForced( 30675 ); // rank 1
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 39805;//proc something (we will owerride this)
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 4;
	}
	sp = dbcSpell.LookupEntryForced( 30678 );  // rank 2
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 39805;//proc something (we will owerride this)
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 8;
	}
	sp = dbcSpell.LookupEntryForced( 30679 ); // rank 3
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 39805;//proc something (we will owerride this)
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 12;
	}
	sp = dbcSpell.LookupEntryForced( 30680 ); // rank 4
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 39805;//proc something (we will owerride this)
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 16;
	}
	sp = dbcSpell.LookupEntryForced( 30681 );	// rank 5
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 39805;//proc something (we will owerride this)
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 20;
	}

	//shaman - Purge 
	sp = dbcSpell.LookupEntryForced( 370 ); 
	if( sp != NULL )
		sp->DispelType = DISPEL_MAGIC;
	sp = dbcSpell.LookupEntryForced( 8012 ); 
	if( sp != NULL )
		sp->DispelType = DISPEL_MAGIC;
	sp = dbcSpell.LookupEntryForced( 27626 ); 
	if( sp != NULL )
		sp->DispelType = DISPEL_MAGIC;
	sp = dbcSpell.LookupEntryForced( 33625 ); 
	if( sp != NULL )
		sp->DispelType = DISPEL_MAGIC;

	//Shaman - Eye of the Storm
	sp = dbcSpell.LookupEntryForced( 29062 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 29064 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 29065 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;

	//Shaman - Shamanistic Focus
	sp = dbcSpell.LookupEntryForced( 43338 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->EffectTriggerSpell[0] = 43339;
		sp->procChance = 100;
		sp->maxstack = 1;
	}

	//Shaman focused
	sp = dbcSpell.LookupEntryForced( 43339 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectMiscValue[0] = SMT_COST;
	}

	//shaman - Healing Way
	sp = dbcSpell.LookupEntryForced( 29202 ); 
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 29205 ); 
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 29206 ); 
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}

	//shaman - Elemental Devastation
	sp = dbcSpell.LookupEntryForced( 29179 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	sp = dbcSpell.LookupEntryForced( 29180 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	sp = dbcSpell.LookupEntryForced( 30160 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

	//shaman - Ancestral healing
	sp = dbcSpell.LookupEntryForced( 16176 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	sp = dbcSpell.LookupEntryForced( 16235 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	sp = dbcSpell.LookupEntryForced( 16240 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

    //shaman - Ancestral healing proc spell
    sp = dbcSpell.LookupEntryForced( 16177 );
    if( sp != NULL )
        sp->rangeIndex = 4;
    sp = dbcSpell.LookupEntryForced( 16236 );
    if( sp != NULL )
        sp->rangeIndex = 4;
    sp = dbcSpell.LookupEntryForced( 16237 );
    if( sp != NULL )
        sp->rangeIndex = 4;

	//rogue - Find Weakness.
	sp = dbcSpell.LookupEntryForced( 31233 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 31239 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 31240 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 31241 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 31242 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	
	//rogue - Camouflage.
	sp = dbcSpell.LookupEntryForced( 13975 ); 
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14062 ); 
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14063 ); 
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14064 ); 
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14065 ); 
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}

	//rogue - Vanish : Second Trigger Spell
	sp = dbcSpell.LookupEntryForced( 18461 );
	if( sp != NULL )
		sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;

	// rogue - shadowstep
	sp = dbcSpell.LookupEntryForced( 36554 );
	if( sp != NULL )
		sp->AttributesEx |= ATTRIBUTESEX_NOT_BREAK_STEALTH;

	//rogue - Mace Specialization.
	sp = dbcSpell.LookupEntryForced( 13709 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	sp = dbcSpell.LookupEntryForced( 13800 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	sp = dbcSpell.LookupEntryForced( 13801 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	sp = dbcSpell.LookupEntryForced( 13802 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	sp = dbcSpell.LookupEntryForced( 13803 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK;

	//rogue - Shadowstep
	sp = dbcSpell.LookupEntryForced( 36563 ); 
	if( sp != NULL )
	{
		sp->EffectMiscValue[1] = SMT_MISC_EFFECT;
		sp->procFlags = 0;
	}

	sp = dbcSpell.LookupEntryForced( 44373 );
	if( sp != NULL )
		sp->procFlags = 0;

     //priest - Holy Concentration
     sp = dbcSpell.LookupEntryForced( 34753 );
     if (sp != NULL)
	 {
          sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		  sp->procChance = 30;
	 }
     sp = dbcSpell.LookupEntryForced( 34859 );
     if (sp != NULL)
	 {
	     sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		 sp->procChance = 30;
	 }
     sp = dbcSpell.LookupEntryForced( 34860 );
     if (sp != NULL)
	 {
          sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		  sp->procChance = 30;
	 }

	 sp = dbcSpell.LookupEntryForced( 34754 );
	 if( sp != NULL)
		 sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_CAST_SPELL;

	//Priest: Blessed Recovery
	sp = dbcSpell.LookupEntryForced(27811);
	if(sp != NULL)
	{
		sp->EffectTriggerSpell[0] = 27813;
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	}
	sp = dbcSpell.LookupEntryForced(27815);
	if(sp != NULL)
	{
		sp->EffectTriggerSpell[0] = 27817;
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	}
	sp = dbcSpell.LookupEntryForced(27816);
	if(sp != NULL)
	{
		sp->EffectTriggerSpell[0] = 27818;
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	}
	//priest- Blessed Resilience
	sp = dbcSpell.LookupEntryForced( 33142 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 33145 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 33146 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;

	//priest- Focused Will
	sp = dbcSpell.LookupEntryForced( 45234 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 45243 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 45244 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;

	//Priest: Shadowguard
	sp = dbcSpell.LookupEntryForced( 18137 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 3000; //every 3 seconds
		sp->EffectTriggerSpell[0] = 28377;
	}
	sp = dbcSpell.LookupEntryForced( 19308 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 3000; //every 3 seconds
		sp->EffectTriggerSpell[0] = 28378;
	}
	sp = dbcSpell.LookupEntryForced( 19309 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 3000; //every 3 seconds
		sp->EffectTriggerSpell[0] = 28379;
	}
	sp = dbcSpell.LookupEntryForced( 19310 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 3000; //every 3 seconds
		sp->EffectTriggerSpell[0] = 28380;
	}
	sp = dbcSpell.LookupEntryForced( 19311 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 3000; //every 3 seconds
		sp->EffectTriggerSpell[0] = 28381;
	}
	sp = dbcSpell.LookupEntryForced( 19312 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 3000; //every 3 seconds
		sp->EffectTriggerSpell[0] = 28382;
	}
	sp = dbcSpell.LookupEntryForced( 25477 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_RANGED_ATTACK_VICTIM | PROC_ON_MELEE_ATTACK_VICTIM;
		sp->proc_interval = 3000; //every 3 seconds
		sp->EffectTriggerSpell[0] = 28385;
	}

	//Paladin: Seal of Wisdom
	sp = dbcSpell.LookupEntryForced( 20166 );
	if( sp != NULL )
	{
		sp->procChance = 12;
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	}

	//Druid: Feral Swiftness
	sp = dbcSpell.LookupEntryForced( 17002 );
	if ( sp != NULL )
	{
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 24867;
	}
	sp = dbcSpell.LookupEntryForced( 24866 );
	if ( sp != NULL )
	{
		sp->Effect[1] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 24864;
	}

	//Druid: Natural Perfection
	sp = dbcSpell.LookupEntryForced( 33881 );
	if ( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 33882 );
	if ( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;
	sp = dbcSpell.LookupEntryForced( 33883 );
	if ( sp != NULL )
		sp->procFlags = PROC_ON_CRIT_HIT_VICTIM;

	//Druid: Frenzied Regeneration
	sp = dbcSpell.LookupEntryForced( 22842 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 22845;
	}
	sp = dbcSpell.LookupEntryForced( 22895 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 22845;
	}
	sp = dbcSpell.LookupEntryForced( 22896 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 22845;
	}
	sp = dbcSpell.LookupEntryForced( 26999 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 22845;
	}

	//Druid - Celestial Focus
	sp = dbcSpell.LookupEntryForced( 16850 ); 
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 16923 ); 
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 16924 ); 
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//paladin - seal of blood
	sp = dbcSpell.LookupEntryForced( 31892 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 31893;
	}
	sp = dbcSpell.LookupEntryForced( 38008 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 31893;
	}

	//paladin - Spiritual Attunement 
	sp = dbcSpell.LookupEntryForced( 31785 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_TARGET_SELF ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 31786;
	}
	sp = dbcSpell.LookupEntryForced( 33776 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_TARGET_SELF;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 31786;
	}

	//Druid: Leader of the Pack
	sp = dbcSpell.LookupEntryForced( 24932 );
	if( sp != NULL )
	{
		sp->Effect[1] = 0;
		sp->Effect[2] = 0; //removing strange effects.
	}

	//Druid: Improved Leader of the Pack
	sp = dbcSpell.LookupEntryForced( 34299 );
	if( sp != NULL )
		sp->proc_interval = 6000;//6 secs

	//fix for the right Enchant ID for Enchant Cloak - Major Resistance
	sp = dbcSpell.LookupEntryForced( 27962 );
	if( sp != NULL )
		sp->EffectMiscValue[0] = 2998;
	sp = dbcSpell.LookupEntryForced( 36285 );
	if( sp != NULL )
		sp->EffectMiscValue[0] = 2998;

	//muhaha, rewriting Retaliation spell as old one :D
	sp = dbcSpell.LookupEntryForced( 20230 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; //aura
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 22858; //evil , but this is good for us :D
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM; //add procflag here since this was not processed with the others !
	}

	//"bloodthirst" new version is ok but old version is wrong from now on :(
	sp = dbcSpell.LookupEntryForced( 23881 );
	if( sp != NULL )
	{
		sp->Effect[1] = 64; //cast on us, it is good
		sp->EffectTriggerSpell[1] = 23885; //evil , but this is good for us :D
	}
	sp = dbcSpell.LookupEntryForced( 23892 );
	if( sp != NULL )
	{
		sp->Effect[1] = 64;
		sp->EffectTriggerSpell[1] = 23886; //evil , but this is good for us :D
	}
	sp = dbcSpell.LookupEntryForced( 23893 );
	if( sp != NULL )
	{
		sp->Effect[1] = 64; //
		sp->EffectTriggerSpell[1] = 23887; //evil , but this is good for us :D
	}
	sp = dbcSpell.LookupEntryForced( 23894 );
	if( sp != NULL )
	{
		sp->Effect[1] = 64; //
		sp->EffectTriggerSpell[1] = 23888; //evil , but this is good for us :D
	}
	sp = dbcSpell.LookupEntryForced( 25251 );
	if( sp != NULL )
	{
		sp->Effect[1] = 64; //aura
		sp->EffectTriggerSpell[1] = 25252; //evil , but this is good for us :D
	}
	sp = dbcSpell.LookupEntryForced( 30335 );
	if( sp != NULL )
	{
		sp->Effect[1] = 64; //aura
		sp->EffectTriggerSpell[1] = 30339; //evil , but this is good for us :D
	}

	// Hunter - Master Tactician
	sp = dbcSpell.LookupEntryForced( 34506 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 34507 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 34508 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 34838 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 34839 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_ATTACK | PROC_TARGET_SELF;

	// Hunter - Spirit Bond
	sp = dbcSpell.LookupEntryForced( 19578 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 19579;
	}
	sp = dbcSpell.LookupEntryForced( 20895 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 24529;
	}
	sp = dbcSpell.LookupEntryForced( 19579 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA; //we should do the same for player too as we did for pet
		sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0];
		sp->EffectAmplitude[1] = sp->EffectAmplitude[0];
		sp->EffectDieSides[1] = sp->EffectDieSides[0];
	}
	sp = dbcSpell.LookupEntryForced( 24529 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA; //we should do the same for player too as we did for pet
		sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0];
		sp->EffectAmplitude[1] = sp->EffectAmplitude[0];
		sp->EffectDieSides[1] = sp->EffectDieSides[0];
	}

	// Hunter - Animal Handler
	sp = dbcSpell.LookupEntryForced( 34453 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HIT_CHANCE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 34454 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HIT_CHANCE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}

	// Hunter - Catlike Reflexes
	sp = dbcSpell.LookupEntryForced( 34462 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 34464 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 34465 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[1] = sp->EffectApplyAuraName[0];
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}

	// Hunter - Serpent's Swiftness
	sp = dbcSpell.LookupEntryForced( 34466 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 34467 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 34468 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 34469 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 34470 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_HASTE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}

	// Hunter - Ferocious Inspiration
	sp = dbcSpell.LookupEntryForced( 34455 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectTriggerSpell[0] = 34456;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF; //maybe target master ?
		sp->Effect[1] = 0; //remove this
	}
	sp = dbcSpell.LookupEntryForced( 34459 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectTriggerSpell[0] = 34456;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF; 
		sp->Effect[1] = 0; //remove this
	}
	sp = dbcSpell.LookupEntryForced( 34460 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectTriggerSpell[0] = 34456;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->Effect[1] = 0; //remove this
	}

	// Hunter - Focused Fire
	sp = dbcSpell.LookupEntryForced( 35029 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 35060;
	}
	sp = dbcSpell.LookupEntryForced( 35030 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 35061;
	}
	sp = dbcSpell.LookupEntryForced( 35060 );
	if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
	sp = dbcSpell.LookupEntryForced( 35061 );
	if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;

	// Hunter - Thick Hide
	sp = dbcSpell.LookupEntryForced( 19609 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE; //we do not support armor rating for pets yet !
		sp->EffectBasePoints[0] *= 10; //just give it a little juice :P
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19610 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE; //we do not support armor rating for pets yet !
		sp->EffectBasePoints[0] *= 10; //just give it a little juice :P
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19612 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_RESISTANCE; //we do not support armor rating for pets yet !
		sp->EffectBasePoints[0] *= 10; //just give it a little juice :P
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	// Hunter - Ferocity
	sp = dbcSpell.LookupEntryForced( 19612 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19599 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19600 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19601 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19602 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_CRIT_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	// Hunter - Bestial Swiftness
	sp = dbcSpell.LookupEntryForced( 19596 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_SPEED; 
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	// Hunter - Endurance Training
	sp = dbcSpell.LookupEntryForced( 19583 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19584 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19585 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19586 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19587 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	// Hunter - Thrill of the Hunt
	sp = dbcSpell.LookupEntryForced( 34497 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->procChance = sp->EffectBasePoints[0]+1;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34720;
	}
	sp = dbcSpell.LookupEntryForced( 34498 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->procChance = sp->EffectBasePoints[0]+1;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34720;
	}
	sp = dbcSpell.LookupEntryForced( 34499 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->procChance = sp->EffectBasePoints[0]+1;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 34720;
	}

	// Hunter - Expose Weakness
	sp = dbcSpell.LookupEntryForced( 34500 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
	sp = dbcSpell.LookupEntryForced( 34502 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;
	sp = dbcSpell.LookupEntryForced( 34503 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_RANGED_CRIT_ATTACK;

	//Hunter - Frenzy
	sp = dbcSpell.LookupEntryForced( 19621 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 19615;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->procChance = sp->EffectBasePoints[0];
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 19622 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 19615;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->procChance = sp->EffectBasePoints[0];
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 19623 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 19615;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->procChance = sp->EffectBasePoints[0];
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 19624 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 19615;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->procChance = sp->EffectBasePoints[0];
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 19625 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 19615;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->procChance = sp->EffectBasePoints[0];
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | PROC_TARGET_SELF;
	}

	//Hunter - Unleashed Fury
	sp = dbcSpell.LookupEntryForced( 19616 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectMiscValue[0] = 1; //tweekign melee dmg
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19617 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectMiscValue[0] = 1; //tweekign melee dmg
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19618 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectMiscValue[0] = 1; //tweekign melee dmg
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19619 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectMiscValue[0] = 1; //tweekign melee dmg
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
	}
	sp = dbcSpell.LookupEntryForced( 19620 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectMiscValue[0] = 1; //tweekign melee dmg
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET | SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET;
	}

	//Hunter : Pathfinding
	sp = dbcSpell.LookupEntryForced( 19559 );
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 19560 );
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	/*sp = dbcSpell.LookupEntryForced( 5131 );
	if( sp != NULL )
		sp->SpellGroupType = 2097152;*/		// 2.4.0-SPELL-NO-LONGER-EXISTS
/*	sp = dbcSpell.LookupEntryForced( 13160 );
	if( sp != NULL )
		sp->SpellGroupType = 2097152;*/		// 2.4.0-SPELL-NO-LONGER-EXISTS

	//Hunter : Rapid Killing - might need to add honor trigger too here. I'm guessing you receive Xp too so i'm avoiding double proc
	sp = dbcSpell.LookupEntryForced( 34948 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_GAIN_EXPIERIENCE | PROC_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 34949 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_GAIN_EXPIERIENCE | PROC_TARGET_SELF;
	}

	// Mage - Invisibility 
	sp = dbcSpell.LookupEntryForced( 66 );
	if( sp != NULL )
	{
		// make a new dummy effect for it
		sp->Effect[2] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[2] = SPELL_AURA_DUMMY;
	}

	// Mage - Invisibility part 2
	sp = dbcSpell.LookupEntryForced( 32612 );
	if( sp != NULL )
	{
		// cancel spells
		// use mage invisibility bool
		sp->Effect[0] = SPELL_EFFECT_SANCTUARY;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->Effect[2] = 0;
	}

	//Mage - Icy Veins
	sp = dbcSpell.LookupEntryForced( 12472 );
	if( sp != NULL )
	{
		sp->EffectMiscValue[1] = SMT_TRIGGER;
	}

	//Mage - Wand Specialization. Not the forst thing we messed up. Blizz uses attack as magic and wandds as weapons :S
	sp = dbcSpell.LookupEntryForced( 6057 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 6085 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}

	//Priest - Wand Specialization
	sp = dbcSpell.LookupEntryForced( 14524 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14525 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14526 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14527 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 14528 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}

	//Mage - Elemental Precision
	sp = dbcSpell.LookupEntryForced( 29438 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
	}
	sp = dbcSpell.LookupEntryForced( 29439 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
	}
	sp = dbcSpell.LookupEntryForced( 29440 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_COST;
	}

	//Mage - Arcane Concentration
	sp = dbcSpell.LookupEntryForced( 11213 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 12574 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 12575 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 12576 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 12577 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
		//sp->procChance = 100;
	}

	//Mage - ClearCasting Effect
	sp = dbcSpell.LookupEntryForced( 12536 );
	if( sp != NULL )
	{
		sp->procCharges = 2;
	}	

	//Mage - Arcane Blast
	sp = dbcSpell.LookupEntryForced( 30451 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 36032;
		sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;
	}

	//rogue - Seal Fate
	sp = dbcSpell.LookupEntryForced( 14186 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 20;
	}
	sp = dbcSpell.LookupEntryForced( 14190 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 40;
	}
	sp = dbcSpell.LookupEntryForced( 14193 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 60;
	}
	sp = dbcSpell.LookupEntryForced( 14194 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 80;
	}
	sp = dbcSpell.LookupEntryForced( 14195 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 100;
	}


	// druid - Nature's Grace
	sp = dbcSpell.LookupEntryForced( 16880 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->procChance = 33;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 16886;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}

	sp = dbcSpell.LookupEntryForced( 61345 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->procChance = 66;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 16886;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}

	sp = dbcSpell.LookupEntryForced( 61346 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->procChance = 100;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 16886;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}

	sp = dbcSpell.LookupEntryForced( 16886 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
		sp->procCharges = 2; // i know.. hacky.. but first charge gets lost when it gets procced
	}

	//druid - Blood Frenzy
	sp = dbcSpell.LookupEntryForced( 16954 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 16952 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 50;
	}

	//druid - Primal Fury
	sp = dbcSpell.LookupEntryForced( 16961 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 16958 );
	if( sp != NULL ) 
	{
		sp->procFlags = PROC_ON_CRIT_ATTACK;
		sp->procChance = 50;
	}

	//druid - Intensity
	sp = dbcSpell.LookupEntryForced( 17106 );
	if( sp != NULL )
	{
	   sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
	   sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 17107 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		 sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 17108 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//Improved Sprint
	sp = dbcSpell.LookupEntryForced( 13743 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 50;
	}
	sp = dbcSpell.LookupEntryForced( 13875 );
	if( sp != NULL )
	{
		sp->procChance = 100;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//warlock -  Seed of Corruption
	sp = dbcSpell.LookupEntryForced( 27243 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 27285;
		sp->procFlags = PROC_ON_SPELL_HIT_VICTIM | PROC_ON_DIE;
		sp->procChance = 100;
	}

	//warlock -  soul link
	sp = dbcSpell.LookupEntryForced( 19028 );
	if( sp != NULL )
	{
		//this is for the trigger effect
		sp->Effect[0]=SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_SPLIT_DAMAGE;
		sp->EffectMiscValue[0]=20;
		//sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;

		//this is for the extra 5% dmg for caster and pet
		sp->Effect[1] = 6;
		sp->EffectApplyAuraName[1] = 79;
		sp->EffectBasePoints[1] = 4; //4+1=5
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
	}

	//warlock: Nightfall
	sp = dbcSpell.LookupEntryForced( 18094 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 17941;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 2;
	}
	sp = dbcSpell.LookupEntryForced( 18095 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 17941;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 4;
	}

	//warlock: Empowered Corruption
	sp = dbcSpell.LookupEntryForced( 32381 );
	if( sp != NULL )
	{
		sp->EffectBasePoints[0] *= 6;
	}
	sp = dbcSpell.LookupEntryForced( 32382 );
	if( sp != NULL )
	{
		sp->EffectBasePoints[0] *= 6;
	}
	sp = dbcSpell.LookupEntryForced( 32383 );
	if( sp != NULL )
	{
		sp->EffectBasePoints[0] *= 6;
	}

	//warlock: Improved Enslave Demon
	sp = dbcSpell.LookupEntryForced( 18821 );
	if( sp != NULL )
	{
		sp->EffectMiscValue[0]=SMT_SPELL_VALUE_PCT;
		sp->EffectBasePoints[0] = -(sp->EffectBasePoints[0]+2);
	}

	//mage : Empowered Arcane Missiles
	sp = dbcSpell.LookupEntryForced( 31579 );
	if( sp != NULL )
	{
		sp->EffectBasePoints[0] *= 5; //heh B thinks he is smart by adding this to description ? If it doesn;t work std then it still needs to made by hand
	}
	sp = dbcSpell.LookupEntryForced( 31582 );
	if( sp != NULL )
	{
		sp->EffectBasePoints[0] *= 5; //heh B thinks he is smart by adding this to description ? If it doesn;t work std then it still needs to made by hand
	}
	sp = dbcSpell.LookupEntryForced( 31583 );
	if( sp != NULL )
	{
		sp->EffectBasePoints[0] *= 5; //heh B thinks he is smart by adding this to description ? If it doesn;t work std then it still needs to made by hand
	}

	//Mage - Improved Blizzard
	sp = dbcSpell.LookupEntryForced( 11185 );
	if( sp != NULL )
	{    
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 12484;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 12487 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 12485;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 12488 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 12486;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//mage - Combustion
	sp = dbcSpell.LookupEntryForced( 11129 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_ON_SPELL_CRIT_HIT | PROC_TARGET_SELF;
		sp->procCharges = 0;
		sp->c_is_flags |= SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE;
	}

	//mage - Master of Elements
	sp = dbcSpell.LookupEntryForced( 29074 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 29077;
		sp->procFlags = uint32(PROC_ON_SPELL_CRIT_HIT|PROC_TARGET_SELF);
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 29075 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 29077;
		sp->procFlags = uint32(PROC_ON_SPELL_CRIT_HIT|PROC_TARGET_SELF);
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 29076 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 29077;
		sp->procFlags = uint32(PROC_ON_SPELL_CRIT_HIT|PROC_TARGET_SELF);
		sp->procChance = 100;
	}

	//mage: Blazing Speed
	sp = dbcSpell.LookupEntryForced( 31641 ); 
	if( sp != NULL )
		sp->EffectTriggerSpell[0] = 31643;
	sp = dbcSpell.LookupEntryForced( 31642 );
	if( sp != NULL )
		sp->EffectTriggerSpell[0] = 31643;

	//mage talent "frostbyte". we make it to be dummy
	sp = dbcSpell.LookupEntryForced( 11071 );
	if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	sp = dbcSpell.LookupEntryForced( 12496 );
	if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	sp = dbcSpell.LookupEntryForced( 12497 );
	if( sp != NULL )
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	//rogue-shiv -> add 1 combo point
	sp = dbcSpell.LookupEntryForced( 5938 );
	if( sp != NULL )
		sp->Effect[1]=80;

	//warlock - Demonic Sacrifice
	sp = dbcSpell.LookupEntryForced( 18789 );
	if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
	sp = dbcSpell.LookupEntryForced( 18790 );
	if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
	sp = dbcSpell.LookupEntryForced( 18791 );
	if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
	sp = dbcSpell.LookupEntryForced( 18792 );
	if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;
	sp = dbcSpell.LookupEntryForced( 35701 );
	if( sp != NULL )
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_ON_PET;

	//warlock - Demonic Tactics
	sp = dbcSpell.LookupEntryForced( 30242 );
	if( sp != NULL )
	{
		sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
		sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
		sp->EffectApplyAuraName[2] = SPELL_AURA_MOD_SPELL_CRIT_CHANCE; //lvl 1 has it fucked up :O
		sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}
	sp = dbcSpell.LookupEntryForced( 30245 );
	if( sp != NULL )
	{
		sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
		sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
		sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}
	sp = dbcSpell.LookupEntryForced( 30246 );
	if( sp != NULL )
	{
		sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
		sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
		sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}
	sp = dbcSpell.LookupEntryForced( 30247 );
	if( sp != NULL )
	{
		sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
		sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
		sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}
	sp = dbcSpell.LookupEntryForced( 30248 );
	if( sp != NULL )
	{
		sp->Effect[0] = 0; //disble this. This is just blizz crap. Pure proove that they suck :P
		sp->EffectImplicitTargetB[1] = EFF_TARGET_PET;
		sp->EffectImplicitTargetB[2] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}

	//warlock - Demonic Resilience
	sp = dbcSpell.LookupEntryForced( 30319 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}
	sp = dbcSpell.LookupEntryForced( 30320 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}
	sp = dbcSpell.LookupEntryForced( 30321 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER ;
	}

	//warlock - Improved Imp
	sp = dbcSpell.LookupEntryForced( 18694 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18695 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18696 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	//warlock - Improved Voidwalker
	sp = dbcSpell.LookupEntryForced( 18705 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18706 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18707 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	//warlock - Improved Succubus
	sp = dbcSpell.LookupEntryForced( 18754 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18755 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18756 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
	}

	//warlock - Fel Intellect
	sp = dbcSpell.LookupEntryForced( 18731 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
		sp->EffectMiscValue[0] = 3;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18743 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
		sp->EffectMiscValue[0] = 3;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18744 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
		sp->EffectMiscValue[0] = 3;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	//warlock - Fel Stamina
	sp = dbcSpell.LookupEntryForced( 18748 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
		sp->EffectMiscValue[0] = 2;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18749 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
		sp->EffectMiscValue[0] = 2;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}
	sp = dbcSpell.LookupEntryForced( 18750 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_PERCENT_STAT;
		sp->EffectMiscValue[0] = 2;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	}

	//warlock - Demonic Tactics
	sp = dbcSpell.LookupEntryForced( 30242 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		//this is required since blizz uses spells for melee attacks while we use fixed functions
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectMiscValue[1] = SCHOOL_NORMAL;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0] ;
	}

	//warlock - Unholy Power
	sp = dbcSpell.LookupEntryForced( 18769 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		//this is required since blizz uses spells for melee attacks while we use fixed functions
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectMiscValue[1] = SCHOOL_NORMAL;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0] ;
	}
	sp = dbcSpell.LookupEntryForced( 18770 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		//this is required since blizz uses spells for melee attacks while we use fixed functions
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectMiscValue[1] = SCHOOL_NORMAL;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0] ;
	}
	sp = dbcSpell.LookupEntryForced( 18771 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		//this is required since blizz uses spells for melee attacks while we use fixed functions
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectMiscValue[1] = SCHOOL_NORMAL;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0] ;
	}
	sp = dbcSpell.LookupEntryForced( 18772 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		//this is required since blizz uses spells for melee attacks while we use fixed functions
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectMiscValue[1] = SCHOOL_NORMAL;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0] ;
	}
	sp = dbcSpell.LookupEntryForced( 18773 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET ;
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
		//this is required since blizz uses spells for melee attacks while we use fixed functions
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_PET;
		sp->EffectMiscValue[1] = SCHOOL_NORMAL;
		sp->EffectBasePoints[1] = sp->EffectBasePoints[0] ;
	}

	//warlock - Master Demonologist - 25 spells here
	sp = dbcSpell.LookupEntryForced( 23785 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 23784;
	}
	sp = dbcSpell.LookupEntryForced( 23822 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 23830;
	}
	sp = dbcSpell.LookupEntryForced( 23823 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 23831;
	}
	sp = dbcSpell.LookupEntryForced( 23824 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 23832;
	}
	sp = dbcSpell.LookupEntryForced( 23825 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET | SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 35708;
	}
	//and the rest
	sp = dbcSpell.LookupEntryForced( 23784 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	sp = dbcSpell.LookupEntryForced( 23830 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	sp = dbcSpell.LookupEntryForced( 23831 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	sp = dbcSpell.LookupEntryForced( 23832 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	sp = dbcSpell.LookupEntryForced( 35708 );
	if( sp != NULL )
		sp->EffectImplicitTargetA[0] = EFF_TARGET_PET;
	sp = dbcSpell.LookupEntryForced( 23759 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	sp = dbcSpell.LookupEntryForced( 23760 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	sp = dbcSpell.LookupEntryForced( 23761 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	sp = dbcSpell.LookupEntryForced( 23762 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	sp = dbcSpell.LookupEntryForced( 23826 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	sp = dbcSpell.LookupEntryForced( 23827 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	sp = dbcSpell.LookupEntryForced( 23828 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	sp = dbcSpell.LookupEntryForced( 23829 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
	}
	for(uint32 i=23833;i<=23844;i++)
	{
		sp = dbcSpell.LookupEntryForced( i );
		if( sp != NULL )
		{
			sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
			sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		}
	}
	sp = dbcSpell.LookupEntryForced( 35702 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->Effect[1] = 0; //hacks, we are handling this in another way
	}
	sp = dbcSpell.LookupEntryForced( 35703 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->Effect[1] = 0; //hacks, we are handling this in another way
	}
	sp = dbcSpell.LookupEntryForced( 35704 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->Effect[1] = 0; //hacks, we are handling this in another way
	}
	sp = dbcSpell.LookupEntryForced( 35705 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->Effect[1] = 0; //hacks, we are handling this in another way
	}
	sp = dbcSpell.LookupEntryForced( 35706 );
	if( sp != NULL )
	{
		sp->c_is_flags |= SPELL_FLAG_IS_EXPIREING_WITH_PET;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->Effect[1] = 0; //hacks, we are handling this in another way
	}
	//warlock - Improved Healthstone
	sp = dbcSpell.LookupEntryForced( 18692 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
	}
	sp = dbcSpell.LookupEntryForced( 18693 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
	}

	//warlock - Unstable Affliction
	sp = dbcSpell.LookupEntryForced( 30108 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM ;
		sp->procChance = 100;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 43523;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
	}
	sp = dbcSpell.LookupEntryForced( 30404 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM ;
		sp->procChance = 100;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 43523;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
	}
	sp = dbcSpell.LookupEntryForced( 30405 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_PRE_DISPELL_AURA_VICTIM ;
		sp->procChance = 100;
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[1] = 43523;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SINGLE_FRIEND;
	}

	//warlock - Improved Drain Soul
	sp = dbcSpell.LookupEntryForced( 18213 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_TARGET_DIE | PROC_TARGET_SELF;
		sp->procChance = 100;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 18371;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->Effect[2] = 0 ; //remove this effect
	}
	sp = dbcSpell.LookupEntryForced( 18372 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_TARGET_DIE | PROC_TARGET_SELF;
		sp->procChance = 100;
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 18371;
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->Effect[2] = 0 ; //remove this effect
	}

	//warlock - Shadow Embrace
	sp = dbcSpell.LookupEntryForced( 32385 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->Effect[1] = 0 ; //remove this effect ? Maybe remove the other one :P xD
	}
	sp = dbcSpell.LookupEntryForced( 32387 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->Effect[1] = 0 ; //remove this effect ? Maybe remove the other one :P xD
	}
	sp = dbcSpell.LookupEntryForced( 32392 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->Effect[1] = 0 ; //remove this effect ? Maybe remove the other one :P xD
	}
	sp = dbcSpell.LookupEntryForced( 32393 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->Effect[1] = 0 ; //remove this effect ? Maybe remove the other one :P xD
	}
	sp = dbcSpell.LookupEntryForced( 32394 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->Effect[1] = 0 ; //remove this effect ? Maybe remove the other one :P xD
	}

	//warlock - soul leech
	sp = dbcSpell.LookupEntryForced( 30293 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; //aura
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 30294;
		sp->procFlags = uint32(PROC_ON_CAST_SPELL|PROC_TARGET_SELF);
	}
	sp = dbcSpell.LookupEntryForced( 30295 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; //aura
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 30294;
		sp->procFlags = uint32(PROC_ON_CAST_SPELL|PROC_TARGET_SELF);
	}
	sp = dbcSpell.LookupEntryForced( 30296 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; //aura
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 30294;
		sp->procFlags = uint32(PROC_ON_CAST_SPELL|PROC_TARGET_SELF);
	}

	//warlock - Pyroclasm
	sp = dbcSpell.LookupEntryForced( 18073 );
	if( sp != NULL )
	{
		sp->Effect[0] = 0; //delete this owerride effect :P
		sp->EffectTriggerSpell[1] = 18093; //trigger spell was wrong :P
		sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION;
		sp->procChance = 13; //god, save us from fixed values !
	}
	sp = dbcSpell.LookupEntryForced( 18096 );
	if( sp != NULL )
	{
		sp->Effect[0] = 0; //delete this owerride effect :P
		sp->EffectTriggerSpell[1] = 18093; //trigger spell was wrong :P
		sp->procFlags = PROC_ON_ANY_HOSTILE_ACTION;
		sp->procChance = 26; //god, save us from fixed values !
	}

	//Mage - Improved Scorch
	sp = dbcSpell.LookupEntryForced( 11095 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance =33;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 12872 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL; 
		sp->procChance =66;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 12873 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance =100;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//Nature's Grasp
	sp = dbcSpell.LookupEntryForced( 16689 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 339; 
		sp->Effect[1] = 0; 
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_REMOVEONUSE;
		sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 16810 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 1062; 
		sp->Effect[1] = 0; 
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_REMOVEONUSE;
		sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 16811 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 5195; 
		sp->Effect[1] = 0; 
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_REMOVEONUSE;
		sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 16812 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 5196; 
		sp->Effect[1] = 0; 
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_REMOVEONUSE;
		sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 16813 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 9852; 
		sp->Effect[1] = 0; 
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_REMOVEONUSE;
		sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 17329 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 9853; 
		sp->Effect[1] = 0; 
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_REMOVEONUSE;
		sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		sp->procChance = 100;
	}
	sp = dbcSpell.LookupEntryForced( 27009 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6; 
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 26989; 
		sp->Effect[1] = 0; 
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM | PROC_REMOVEONUSE;
		sp->AuraInterruptFlags = 0; //we remove it on proc or timeout
		sp->procChance = 100;
	}

	//wrath of air totem targets sorounding creatures instead of us
	sp = dbcSpell.LookupEntryForced( 2895 );
	if( sp != NULL )
	{
		sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
		sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
		sp->EffectImplicitTargetA[2] = 0;
		sp->EffectImplicitTargetB[0] = 0;
		sp->EffectImplicitTargetB[1] = 0;
		sp->EffectImplicitTargetB[2] = 0;
	}

	//-----BLEED effects----- (setting mech to BLEED)
	//garrot
	sp = dbcSpell.LookupEntryForced( 703 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 8631 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 8632 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 8633 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11289 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11290 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 26839 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 26884 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;

	//pounce
	sp = dbcSpell.LookupEntryForced( 9007 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9824 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9826 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 27007 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;

	//rend
	sp = dbcSpell.LookupEntryForced( 772 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 6546 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 6547 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 6548 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11572 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11573 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11574 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 25208 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;

	//rip
	sp = dbcSpell.LookupEntryForced( 1079 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9492 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9493 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9752 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9894 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9896 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 27008 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;

	//rupture
	sp = dbcSpell.LookupEntryForced( 1943 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 8639 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 8640 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11273 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11274 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 11275 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 26867 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;

	//rake
	sp = dbcSpell.LookupEntryForced( 1822 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 1823 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 1824 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 9904 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;
	sp = dbcSpell.LookupEntryForced( 27003 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;

	//lacerate
	sp = dbcSpell.LookupEntryForced( 33745 );
	if( sp != NULL )
		sp->MechanicsType = MECHANIC_BLEEDING;

	//deuid - Pounce Bleed
	sp = dbcSpell.LookupEntryForced( 9007 );
	if( sp != NULL )
		sp->DurationIndex = 18000;
	sp = dbcSpell.LookupEntryForced( 9824 );
	if( sp != NULL )
		sp->DurationIndex = 18000;
	sp = dbcSpell.LookupEntryForced( 9826 );
	if( sp != NULL )
		sp->DurationIndex = 18000;
	sp = dbcSpell.LookupEntryForced( 27007 );
	if( sp != NULL )
		sp->DurationIndex = 18000;

	//Druid: Natural Shapeshifter
	sp = dbcSpell.LookupEntryForced( 16833 );
	if( sp != NULL )
		sp->DurationIndex = 0;
	sp = dbcSpell.LookupEntryForced( 16834 );
	if( sp != NULL )
		sp->DurationIndex = 0;
	sp = dbcSpell.LookupEntryForced( 16835 );
	if( sp != NULL )
		sp->DurationIndex = 0;

    //Priest - Inspiration proc spell
    sp = dbcSpell.LookupEntryForced( 14893 );
    if( sp != NULL )
        sp->rangeIndex = 4;
    sp = dbcSpell.LookupEntryForced( 15357 );
    if( sp != NULL )
        sp->rangeIndex = 4;
    sp = dbcSpell.LookupEntryForced( 15359 );
    if( sp != NULL )
        sp->rangeIndex = 4;

	//Relentless Strikes
	sp = dbcSpell.LookupEntryForced( 14179 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;//proc spell
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
		sp->EffectBasePoints[1] = 20; //client showes 20% chance but whe do not have it ? :O
	}

	//priest - surge of light
	sp = dbcSpell.LookupEntryForced( 33150 );
	if( sp != NULL )
		sp->procFlags = uint32(PROC_ON_SPELL_CRIT_HIT_VICTIM | PROC_TARGET_SELF);
	sp = dbcSpell.LookupEntryForced( 33154 );
	if( sp != NULL )
		sp->procFlags = uint32(PROC_ON_SPELL_CRIT_HIT_VICTIM | PROC_TARGET_SELF);
	sp = dbcSpell.LookupEntryForced( 33151 );
	if( sp != NULL )
	{
		sp->AuraInterruptFlags = AURA_INTERRUPT_ON_CAST_SPELL;
	}

	//Seal of Justice -lowered proc chance (experimental values !)
	sp = dbcSpell.LookupEntryForced( 20164 );
	if( sp != NULL )
		sp->procChance = 20;
	sp = dbcSpell.LookupEntryForced( 31895 );
	if( sp != NULL )
		sp->procChance = 20;

	//make Berserking a simple spell 
	sp = dbcSpell.LookupEntryForced( 20554 );
	if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 26635;
	}
	sp = dbcSpell.LookupEntryForced( 26296 );
	if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 26635;
	}
	sp = dbcSpell.LookupEntryForced( 26297 );
	if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 26635;
	}

	//rogue - intiative
	sp = dbcSpell.LookupEntryForced( 13976 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = uint32(PROC_ON_CAST_SPELL|PROC_TARGET_SELF);
	}
	sp = dbcSpell.LookupEntryForced( 13979 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = uint32(PROC_ON_CAST_SPELL|PROC_TARGET_SELF);
	}
	sp = dbcSpell.LookupEntryForced( 13980 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procFlags = uint32(PROC_ON_CAST_SPELL|PROC_TARGET_SELF);
	}

	//this an on equip item spell(2824) :  ice arrow(29501)
	sp = dbcSpell.LookupEntryForced( 29501 );
	if( sp != NULL )
	{
		sp->procChance = 30;//some say it is triggered every now and then
		sp->procFlags = PROC_ON_RANGED_ATTACK;
	}

	//warrior - second wind should trigger on self
	sp = dbcSpell.LookupEntryForced( 29841 );
	if( sp != NULL )
		sp->procFlags |= PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 29842 );
	if( sp != NULL )
		sp->procFlags |= PROC_TARGET_SELF;

	//warrior - berserker rage is missing 1 effect = regenerate rage
	sp = dbcSpell.LookupEntryForced( 18499 );
	if( sp != NULL )
	{
		sp->Effect[2] = 6;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 37521; //not sure if this is the one. In my time this adds 30 rage
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;
	}

	//warrior - improved berserker rage
	sp = dbcSpell.LookupEntryForced( 20500 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 20501 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;

	//warrior - berserker rage is missing 1 effect = regenerate rage
	sp = dbcSpell.LookupEntryForced( 18499 );
	if( sp != NULL )
	{
		sp->Effect[2] = 6;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[2] = 9174; //not sure if this is the one. In my time this adds 30 rage
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM | PROC_TARGET_SELF;
	}

	//warrior - Blood Frenzy
	sp = dbcSpell.LookupEntryForced( 29836 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 29859 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	}

	//warrior - Rampage
	sp = dbcSpell.LookupEntryForced( 30030 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
		sp->EffectTriggerSpell[0] = sp->EffectTriggerSpell[1];
	}
	sp = dbcSpell.LookupEntryForced( 30033 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
		sp->EffectTriggerSpell[0] = sp->EffectTriggerSpell[1];
	}

	//warrior - Unbridled Wrath
	sp = dbcSpell.LookupEntryForced( 12322 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 12999 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 13000 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 13001 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;
	sp = dbcSpell.LookupEntryForced( 13002 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_TARGET_SELF;

	// warrior - overpower r1
	sp = dbcSpell.LookupEntryForced(7384);
	if( sp != NULL )
		sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;

	// warrior - overpower r2
	sp = dbcSpell.LookupEntryForced(7887);
	if( sp != NULL )
		sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;

	// warrior - overpower r3
	sp = dbcSpell.LookupEntryForced(11584);
	if( sp != NULL )
		sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;

	// warrior - overpower r4
	sp = dbcSpell.LookupEntryForced(11585);
	if( sp != NULL )
		sp->Attributes |= ATTRIBUTES_CANT_BE_DPB;

	// warrior - heroic fury
	sp = dbcSpell.LookupEntryForced(60970);
	if( sp != NULL )
	{
		sp->Effect[1] = 3;
	}

	// priest - Reflective Shield
	sp = dbcSpell.LookupEntryForced( 33201 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ABSORB;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 33619; //!! WRONG spell, we will make direct dmg here
	}
	sp = dbcSpell.LookupEntryForced( 33202 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ABSORB;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 33619; //!! WRONG spell, we will make direct dmg here
	}
	sp = dbcSpell.LookupEntryForced( 33203 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ABSORB;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 33619; //!! WRONG spell, we will make direct dmg here
	}
	sp = dbcSpell.LookupEntryForced( 33204 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ABSORB;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 33619; //!! WRONG spell, we will make direct dmg here
	}
	sp = dbcSpell.LookupEntryForced( 33205 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_ABSORB;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 33619; //!! WRONG spell, we will make direct dmg here
	}

	// paladin - Improved Sanctity Aura
	sp = dbcSpell.LookupEntryForced( 31869 );
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
	sp = dbcSpell.LookupEntryForced( 31870 );
	if( sp != NULL )
	{
		sp->EffectMiscValue[0] = SMT_MISC_EFFECT;
	}
    sp = dbcSpell.LookupEntryForced( 20608 ); //Reincarnation
    if( sp != NULL )
    {
        for(uint32 i=0;i<8;i++)
        {
            if(sp->Reagent[i])
            {
                sp->Reagent[i] = 0;
                sp->ReagentCount[i] = 0;
            }
        }
    }

	// druid - travel form
	sp = dbcSpell.LookupEntryForced(5419);
	if( sp != NULL )
		sp->Attributes |= ATTRIBUTES_MOUNT_CASTABLE;

	// druid - Naturalist
	sp = dbcSpell.LookupEntryForced( 17069 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[1] = 1;  
	}
	sp = dbcSpell.LookupEntryForced( 17070 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[1] = 1; 
	}
	sp = dbcSpell.LookupEntryForced( 17071 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[1] = 1; 
	}
	sp = dbcSpell.LookupEntryForced( 17072 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[1] = 1;
	}
	sp = dbcSpell.LookupEntryForced( 17073 );
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[1] = SPELL_AURA_MOD_DAMAGE_PERCENT_DONE;
		sp->EffectMiscValue[1] = 1; 
	}

	// druid - Nature's Grace
	sp = dbcSpell.LookupEntryForced( 16880 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

	sp = dbcSpell.LookupEntryForced( 16886 );
	if( sp != NULL )
	{
		sp->procCharges = 1;
	}

	// Druid: Omen of Clarity
	sp = dbcSpell.LookupEntryForced( 16864 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK | PROC_ON_CRIT_ATTACK;
		sp->procs_per_minute = 2.0f;
	}

	//Thunderfury
	sp = dbcSpell.LookupEntryForced( 21992 );
	if( sp != NULL )
	{
        sp->Effect[2] = SPELL_EFFECT_TRIGGER_SPELL;
        sp->EffectTriggerSpell[2] = 27648;
		sp->EffectImplicitTargetA[2] = EFF_TARGET_SELF;
	}

	//Energized 
	sp = dbcSpell.LookupEntryForced( 43750 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	//Spell Haste Trinket
	sp = dbcSpell.LookupEntryForced( 33297 ); 
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL | PROC_TARGET_SELF;

	// Band of the Eternal Sage
	sp = dbcSpell.LookupEntryForced( 35083 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	// Band of the Eternal Restorer 
	sp = dbcSpell.LookupEntryForced( 35086 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	// Ashtongue Talisman of Shadows 
	sp = dbcSpell.LookupEntryForced( 40478 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	// Ashtongue Talisman of Swiftness
	sp = dbcSpell.LookupEntryForced( 40485 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	// Ashtongue Talisman of Valor
	sp = dbcSpell.LookupEntryForced( 40458 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	// Memento of Tyrande
	sp = dbcSpell.LookupEntryForced( 37655 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 10;
		sp->proc_interval = 45000;
	}

	// Ashtongue Talisman of Insight
	sp = dbcSpell.LookupEntryForced( 40482 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;

	//Ashtongue Talisman of Equilibrium
	sp = dbcSpell.LookupEntryForced( 40442 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 40;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[0] = 40452;
		sp->maxstack = 1;
		sp->Effect[1] = 6;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 25;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[1] = 40445;
		sp->maxstack = 1;
		sp->Effect[2] = 6;
		sp->EffectApplyAuraName[2] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 25;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[2] = 40446;
		sp->maxstack = 1;
	}

	//Ashtongue Talisman of Acumen
	sp = dbcSpell.LookupEntryForced( 40438 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 10;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[0] = 40441;
		sp->maxstack = 1;
		sp->Effect[1] = 6;
		sp->EffectApplyAuraName[1] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 10;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[1] = 40440;
		sp->maxstack = 1;
	}

	//Ashtongue Talisman of Lethality
	sp = dbcSpell.LookupEntryForced( 40460 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 20;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[0] = 40461;
		sp->maxstack = 1;
	}

	//Serpent-Coil Braid
	sp = dbcSpell.LookupEntryForced( 37447 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 100;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->EffectTriggerSpell[0] = 37445;
		sp->maxstack = 1;
	}

	//Item Set: Malorne Harness
	sp = dbcSpell.LookupEntryForced( 37306 );
	if( sp != NULL )
	{
		sp->procChance = 4;
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	}
	sp = dbcSpell.LookupEntryForced( 37311 );
	if( sp != NULL )
	{
		sp->procChance = 4;
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	}

	//Item Set: Deathmantle
	sp = dbcSpell.LookupEntryForced( 37170 );
	if( sp != NULL )
	{
		sp->procChance = 4;
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	}

	//Item Set: Netherblade
	sp = dbcSpell.LookupEntryForced( 37168 );
	if( sp != NULL )
	{
		sp->procChance = 15;
		//sp->procFlags = PROC_ON_CAST_SPELL; Need new flag - PROC_ON_FINISH_MOVE;
	}

	//Item Set: Tirisfal Regalia
	sp = dbcSpell.LookupEntryForced( 37443 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}

	//Item Set: Avatar Regalia
	sp = dbcSpell.LookupEntryForced( 37600 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 6;
	}

	//Item Set: Incarnate Raiment
	sp = dbcSpell.LookupEntryForced( 37568 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//Item Set: Voidheart Raiment
	sp = dbcSpell.LookupEntryForced( 37377 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 5;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->proc_interval = 20;
		sp->EffectTriggerSpell[0] = 37379;
	}
	sp = dbcSpell.LookupEntryForced( 39437 );
	if( sp != NULL )
	{
		sp->Effect[0] = 6;
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->procChance = 5;
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->proc_interval = 20;
		sp->EffectTriggerSpell[0] = 37378;
	}

	//Item Set: Cataclysm Raiment
	sp = dbcSpell.LookupEntryForced( 37227 );
	if( sp != NULL )
	{
		sp->proc_interval = 60000;
		sp->procChance = 100;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}

	//Item Set: Cataclysm Regalia
	sp = dbcSpell.LookupEntryForced( 37228 );
	if( sp != NULL )
	{
		sp->procChance = 7;
		sp->procFlags = PROC_ON_CAST_SPELL;
	}
	sp = dbcSpell.LookupEntryForced( 37237 );
	if( sp != NULL )
	{
		sp->procChance = 25;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}

	//Item Set: Cataclysm Harness
	sp = dbcSpell.LookupEntryForced( 37239 );
	if( sp != NULL )
	{
		sp->procChance = 2;
		sp->procFlags = PROC_ON_MELEE_ATTACK;
	}

	//Item Set: Cyclone Regalia
	sp = dbcSpell.LookupEntryForced( 37213 );
	if( sp != NULL )
	{
		sp->procChance = 11;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}

	//Item Set: Lightbringer Battlegear
	sp = dbcSpell.LookupEntryForced( 38427 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK;
		sp->procChance = 20;
	}

	//Item Set: Crystalforge Armor
	sp = dbcSpell.LookupEntryForced( 37191 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//Item Set: Crystalforge Battlegear
	sp = dbcSpell.LookupEntryForced( 37195 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 6;
	}

	//Item Set: Crystalforge Raiment
	sp = dbcSpell.LookupEntryForced( 37189 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->proc_interval = 60000;
	}
	sp = dbcSpell.LookupEntryForced( 37188 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	//Item Set: Destroyer Armor
	sp = dbcSpell.LookupEntryForced( 37525 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_MELEE_ATTACK_VICTIM;
		sp->procChance = 7;
	}

	//Item Set: Destroyer Battlegear
	sp = dbcSpell.LookupEntryForced( 37528 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
	}

	//Item Set: Warbringer Armor
	sp = dbcSpell.LookupEntryForced( 37516 );
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
		sp->procChance = 100;
	}

	//all Drums 
	sp = dbcSpell.LookupEntryForced( 35474 );
	if( sp != NULL )
		sp->RequiredShapeShift = 0;
	sp = dbcSpell.LookupEntryForced( 35475 );
	if( sp != NULL )
		sp->RequiredShapeShift = 0;
	sp = dbcSpell.LookupEntryForced( 35476 );
	if( sp != NULL )
		sp->RequiredShapeShift = 0;
	sp = dbcSpell.LookupEntryForced( 35477 );
	if( sp != NULL )
		sp->RequiredShapeShift = 0;
	sp = dbcSpell.LookupEntryForced( 35478 );
	if( sp != NULL )
		sp->RequiredShapeShift = 0;

	//Paladin - Improved Lay on Hands
	sp = dbcSpell.LookupEntryForced( 20234 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;
	sp = dbcSpell.LookupEntryForced( 20235 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_CAST_SPELL;

	//windfury weapon changes. Start to hate these day by day
	EnchantEntry* Enchantment;
		
	Enchantment = dbcEnchant.LookupEntryForced( 283 );
	if( Enchantment != NULL )
	{
		Enchantment->spell[0] = 33757; //this is actually good
		sp = dbcSpell.LookupEntryForced( 33757 );
		if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK; //we do not need proc on spell ;)
			sp->EffectTriggerSpell[0] = 8232; //for the logs and rest
			sp->procChance = 20;
			sp->proc_interval = 3000;//http://www.wowwiki.com/Windfury_Weapon
			sp->maxstack = 1;
		}
	}

	Enchantment = dbcEnchant.LookupEntryForced( 284 );
	if( Enchantment != NULL )
	{
		Enchantment->spell[0] = 33756; 
		sp = dbcSpell.LookupEntryForced( 33756 );
		if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK; //we do not need proc on spell ;)
			sp->EffectTriggerSpell[0] = 8235; //for the logs and rest
			sp->procChance = 20;
			sp->proc_interval = 3000; //http://www.wowwiki.com/Windfury_Weapon
			sp->maxstack = 1;
		}
	}

	Enchantment = dbcEnchant.LookupEntryForced( 525 );
	if( Enchantment != NULL )
	{
		Enchantment->spell[0] = 33755; 
		sp = dbcSpell.LookupEntryForced( 33755 );
		if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK; //we do not need proc on spell ;)
			sp->EffectTriggerSpell[0] = 10486; //for the logs and rest
			sp->procChance = 20;
			sp->proc_interval = 3000;//http://www.wowwiki.com/Windfury_Weapon
			sp->maxstack = 1;
		}
	}

	Enchantment = dbcEnchant.LookupEntryForced( 1669 );
	if( Enchantment != NULL )
	{
		Enchantment->spell[0] = 33754; 
		sp = dbcSpell.LookupEntryForced( 33754 );
		if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK; //we do not need proc on spell ;)
			sp->EffectTriggerSpell[0] = 16362; //for the logs and rest
			sp->procChance = 20;
			sp->proc_interval = 3000;//http://www.wowwiki.com/Windfury_Weapon
			sp->maxstack = 1;
		}
	}

	Enchantment = dbcEnchant.LookupEntryForced( 2636 );
	if( Enchantment != NULL )
	{
		Enchantment->spell[0] = 33727; 
		sp = dbcSpell.LookupEntryForced( 33727 );
		if( sp != NULL )
		{
			sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
			sp->procFlags = PROC_ON_MELEE_ATTACK; //we do not need proc on spell ;)
			sp->EffectTriggerSpell[0] = 25505; //for the logs and rest
			sp->procChance = 20;
			sp->proc_interval = 3000;//http://www.wowwiki.com/Windfury_Weapon
			sp->maxstack = 1;
		}
	}

	//for test only
	//sp = dbcSpell.LookupEntryForced( 32796 );
	//if( sp != NULL )
	//{
		//printf("!!!!!!hash %u \n",sp->NameHash);
		//sp->procChance=100;
		//SpellDuration *sd=sSpellDuration.LookupEntryForced(sp->DurationIndex);
		//printf("iterruptflag %u, duration %u",sp->AuraInterruptFlags,GetDuration(sd));
	//}

	//improoved berserker stance should be triggered on berserker stance use
	//sp = sSpellStore.LookupEntryForced(12704);
	//if( sp != NULL )	sp->procFlags = PROC_ON_CAST_SPECIFIC_SPELL;

	//sp = sSpellStore.LookupEntryForced(16280);
	//if( sp != NULL )	printf("!!Interrupt flags %u interval %u charges %u\n",sp->AuraInterruptFlags,sp->proc_interval,sp->procCharges);
	//sp = sSpellStore.LookupEntryForced(16284);
	//if( sp != NULL )	printf("Interrupt flags %u\n",sp->AuraInterruptFlags);

	// dot heals
	sp = dbcSpell.LookupEntryForced( 38394 );
	if( sp != NULL )
	{
		sp->procFlags = 1024;
		//sp->SpellGroupType = 6;
		sp->Dspell_coef_override = 0;
		sp->OTspell_coef_override = 0;
	}

	// Citrine Pendant of Golden Healing
	sp = dbcSpell.LookupEntryForced( 25608 );
	if( sp != NULL )
	{
		sp->Dspell_coef_override = 0;
		sp->OTspell_coef_override = 0;
	}

	//fix for Predatory Strikes
	uint32 mm = (1<<(FORM_BEAR-1))|(1<<(FORM_DIREBEAR-1))|(1<<(FORM_MOONKIN-1))|(1<<(FORM_CAT-1));

	sp = dbcSpell.LookupEntryForced( 16972 );
	if( sp != NULL )
		sp->RequiredShapeShift = mm;
	sp = dbcSpell.LookupEntryForced( 16974 );
	if( sp != NULL )
		sp->RequiredShapeShift = mm;
	sp = dbcSpell.LookupEntryForced( 16975 );
	if( sp != NULL )
		sp->RequiredShapeShift = mm;

	sp = dbcSpell.LookupEntryForced( 20134 );
	if( sp != NULL )
		sp->procChance = 50;

	/* aspect of the pack - change to AA */
	sp = dbcSpell.LookupEntryForced( 13159 );
	if( sp != NULL )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AREA_AURA;
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
	}
	sp = dbcSpell.LookupEntryForced( 13159 );
	if( sp != NULL )
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AREA_AURA;
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;
	}

	/* aspect of the cheetah - add proc flags */
	sp = dbcSpell.LookupEntryForced( 5118 );
	if( sp != NULL )
		sp->procFlags = PROC_ON_ANY_DAMAGE_VICTIM;;
	
	/* thrown - add a 1.6 second cooldown */
	const static uint32 thrown_spells[] = {SPELL_RANGED_GENERAL,SPELL_RANGED_THROW,SPELL_RANGED_WAND, 26679, 29436, 37074, 41182, 41346, 0};
	for(i = 0; thrown_spells[i] != 0; ++i)
	{
		sp = dbcSpell.LookupEntryForced( thrown_spells[i] );
		if( sp != NULL && sp->RecoveryTime==0 && sp->StartRecoveryTime == 0 )
			sp->RecoveryTime = 1600;
	}

	/* wands - s5019 - change Spell_Dmg_Type from magic to ranged (3) */
	sp = dbcSpell.LookupEntryForced( SPELL_RANGED_WAND );
	if( sp != NULL )
		sp->Spell_Dmg_Type = SPELL_DMG_TYPE_RANGED;

	sp = dbcSpell.LookupEntryForced( 40475 );		// Black temple melee trinket
	if( sp != NULL )
		sp->procChance = 50;


	// Druid Trinket Living Root of the Wildheart
	sp = dbcSpell.LookupEntryForced( 37336 );
	if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_DUMMY;// oh noez, we make it DUMMY, no other way to fix it atm

	// Shaman - Grounding totem
	sp = dbcSpell.LookupEntryForced( 8178 );
	if( sp != NULL )
		sp->area_aura_update_interval = 10000;

	/**********************************************************
	* Misc stuff (questfixes etc)
	**********************************************************/

	sp = dbcSpell.LookupEntryForced( 30877 );
	if( sp != NULL )
		sp->EffectImplicitTargetB[0]=0;

	sp = dbcSpell.LookupEntryForced(23179);
	if( sp != NULL )
		sp->EffectMiscValue[0] = 1434;

	//////////////////////////////////////////////////////
	// CLASS-SPECIFIC SPELL FIXES						//
	//////////////////////////////////////////////////////

	/* Note: when applying spell hackfixes, please follow a template */

	//////////////////////////////////////////
	// WARRIOR								//
	//////////////////////////////////////////
	sp = dbcSpell.LookupEntryForced(7405); // Sunder Armor
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(7386); // Sunder Armor
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(8380); // Sunder Armor
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(11596); // Sunder Armor
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(11597); // Sunder Armor
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(25225); // Sunder Armor
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(30330); // Mortal Strike Ranks 
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(25248); // Mortal Strike Ranks 
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(21553); // Mortal Strike Ranks 
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(21552); // Mortal Strike Ranks 
	if( sp != NULL )
	{
		sp->Unique = true;
	}
	sp = dbcSpell.LookupEntryForced(21551); // Mortal Strike Ranks 
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(12294); // Mortal Strike Ranks 
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(16511);	// Hemo Rank 1
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(17347);	// Hemo Rank 2
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(17348);	// Hemo Rank 3
	if( sp != NULL )
		sp->Unique = true;

	sp = dbcSpell.LookupEntryForced(26864);	// Hemo Rank 4
	if( sp != NULL )
		sp->Unique = true;

	//////////////////////////////////////////
	// PALADIN								//
	//////////////////////////////////////////

	// Insert paladin spell fixes here

		// Seal of Command - Holy damage, but melee mechanics (crit damage, chance, etc)
		sp = dbcSpell.LookupEntryForced( 20424 );
		if( sp != NULL )
			sp->is_melee_spell = true;


	//////////////////////////////////////////
	// HUNTER								//
	//////////////////////////////////////////

	sp = dbcSpell.LookupEntryForced( 27065 );
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced( 20904 );
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced( 20903 );
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced( 20902 );
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced( 20901 );
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced( 20900 );
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced( 19434 );
	if( sp != NULL )
	{
		sp->Unique = true;
	}

	//////////////////////////////////////////
	// ROGUE								//
	//////////////////////////////////////////

	// Let's hack the entire cheating death effect to damage perc resist ;)
	sp = dbcSpell.LookupEntryForced(45182); // Cheating Death buff
	if(sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN;
		sp->EffectMiscValue[0] = -90;
	}

	// Wound Poison Stuff
	sp = dbcSpell.LookupEntryForced(27189); 
	if(sp != NULL)
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(13224); 
	if(sp != NULL)
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(13223); 
	if(sp != NULL)
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(13222); 
	if(sp != NULL)
	{
		sp->Unique = true;
	}

	sp = dbcSpell.LookupEntryForced(13218); 
	if(sp != NULL)
	{
		sp->Unique = true;
	}
	//////////////////////////////////////////
	// PRIEST								//
	//////////////////////////////////////////

	// Prayer of mending (tricky one :()
	sp = dbcSpell.LookupEntryForced(33076);
	sp->Effect[0] = SPELL_EFFECT_TRIGGER_SPELL;
	sp->EffectTriggerSpell[0] = 41635;
	sp->Effect[1] = SPELL_EFFECT_DUMMY;
	sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
	sp->EffectImplicitTargetA[1] = EFF_TARGET_SELF;
	sp->EffectImplicitTargetB[0] = 0;
	sp->EffectImplicitTargetB[1] = 0;

	// triggered spell, this is the aura
	sp = dbcSpell.LookupEntryForced(41635);
	sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
	sp->EffectTriggerSpell[0] = 41637;
	sp->procCharges = 0;
	sp->procChance = 101;

	// triggered on hit, this is the spell that does the healing/jump
	sp = dbcSpell.LookupEntryForced(41637);
	sp->Effect[0] = SPELL_EFFECT_DUMMY;
	sp->EffectBasePoints[0] = 5;
	sp->EffectImplicitTargetA[0] = EFF_TARGET_SELF;
	sp->EffectImplicitTargetB[0] = 0;
	
	// Insert priest spell fixes here

	//////////////////////////////////////////
	// SHAMAN								//
	//////////////////////////////////////////
	sp = dbcSpell.LookupEntryForced(25505);
	if(sp)
		sp->Flags3 |= FLAGS3_ENCHANT_OWN_ONLY;

	sp = dbcSpell.LookupEntryForced(16362);
	if(sp)
		sp->Flags3 |= FLAGS3_ENCHANT_OWN_ONLY;

	sp = dbcSpell.LookupEntryForced(10486);
	if(sp)
		sp->Flags3 |= FLAGS3_ENCHANT_OWN_ONLY;

	sp = dbcSpell.LookupEntryForced(8235);
	if(sp)
		sp->Flags3 |= FLAGS3_ENCHANT_OWN_ONLY;

	sp = dbcSpell.LookupEntryForced(8232);
	if(sp)
		sp->Flags3 |= FLAGS3_ENCHANT_OWN_ONLY;

	sp = dbcSpell.LookupEntryForced(51690);
	if( sp )
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->Effect[1] = 0;
		sp->Effect[2] = 0;

		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
	}

	//////////////////////////////////////////
	// MAGE								//
	//////////////////////////////////////////

	// Insert mage spell fixes here

	//////////////////////////////////////////
	// WARLOCK								//
	//////////////////////////////////////////

	// Insert warlock spell fixes here

	//////////////////////////////////////////
	// DRUID								//
	//////////////////////////////////////////

	// Insert druid spell fixes here
	sp = dbcSpell.LookupEntryForced(22570);
	if(sp)
	{
		sp->AuraInterruptFlags |= AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN;
		sp->Attributes |= ATTRIBUTES_STOP_ATTACK;
	}

	//////////////////////////////////////////
	// BOSSES								//
	//////////////////////////////////////////

	// Insert boss spell fixes here
	
	// Dark Glare
	sp = dbcSpell.LookupEntryForced( 26029 );
	if( sp != NULL )
		sp->cone_width = 15.0f; // 15 degree cone


	sp = dbcSpell.LookupEntryForced( 45057 );
	if( sp != NULL )
	{
		sp->procs_per_minute = 0.5f;
		sp->proc_interval = 30;
	}

	// Recently Dropped Flag
	sp = dbcSpell.LookupEntryForced( 42792 );
	if (sp != NULL)
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;

	sp = dbcSpell.LookupEntryForced( 7712 );
	if( sp != NULL)
		sp->Dspell_coef_override = 0.0f;

	sp = dbcSpell.LookupEntryForced( 43958 );
	{
		sp->Effect[0] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->DurationIndex = 6; // 10 minutes.
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;

		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_ADD_PCT_MODIFIER;
		sp->EffectMiscValue[1] = SMT_RESIST_DISPEL;
		sp->EffectBasePoints[1] = 90;
	}

	// Recently Dropped Flag
	sp = dbcSpell.LookupEntryForced(43869);
	if( sp != NULL)
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_DUMMY;
		sp->c_is_flags |= SPELL_FLAG_IS_FORCEDDEBUFF;
	}

	sp = dbcSpell.LookupEntryForced(44549);
	if( sp != NULL)
	{
		sp->procFlags = PROC_ON_CAST_SPELL;
	}

	sp = dbcSpell.LookupEntryForced(61216);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 1;
	}

	sp = dbcSpell.LookupEntryForced(61221);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 2;
	}

	sp = dbcSpell.LookupEntryForced(61222);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 3;
	}

	sp = dbcSpell.LookupEntryForced(48978);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 1;
	}

	sp = dbcSpell.LookupEntryForced(49390);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 2;
	}

	sp = dbcSpell.LookupEntryForced(49391);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 3;
	}

	sp = dbcSpell.LookupEntryForced(49392);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 4;
	}

	sp = dbcSpell.LookupEntryForced(49393);
	if( sp != NULL)
	{
		sp->Effect[1] = SPELL_EFFECT_APPLY_AURA;
		sp->EffectApplyAuraName[1] = SPELL_AURA_DUMMY;
		sp->EffectMiscValue[1] = 5;
	}

	sp = dbcSpell.LookupEntryForced(46910);
	if( sp != NULL )
	{
		sp->EffectTriggerSpell[0] = 56112;
		sp->procChance = 50;
		sp->procFlags |= PROC_ON_MELEE_ATTACK;
	}

	sp = dbcSpell.LookupEntryForced(46911);
	if( sp != NULL )
	{
		sp->EffectTriggerSpell[0] = 56112;
		sp->procChance = 100;
		sp->procFlags |= PROC_ON_MELEE_ATTACK;
	}

	// Rogue: Hunger for Blood!
	sp = dbcSpell.LookupEntryForced(51662);
	if( sp != NULL )
	{
		sp->Effect[1] = SPELL_EFFECT_DUMMY;
	}

	// Mage: Focus Magic
	sp = dbcSpell.LookupEntryForced(54646);
	if( sp != NULL )
	{
		sp->c_is_flags = SPELL_FLAG_ON_ONLY_ONE_TARGET;
	}

	// Mage: Hot Streak
	sp = dbcSpell.LookupEntryForced(44445);
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 48108;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->EffectSpellClassMask[0][0] = 0x100013;
	}

	sp = dbcSpell.LookupEntryForced(44446);
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 48108;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->EffectSpellClassMask[0][0] = 0x100013;
	}

	sp = dbcSpell.LookupEntryForced(44448);
	if( sp != NULL )
	{
		sp->EffectApplyAuraName[0] = SPELL_AURA_PROC_TRIGGER_SPELL;
		sp->EffectTriggerSpell[0] = 48108;
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
		sp->EffectSpellClassMask[0][0] = 0x100013;
	}

	sp = dbcSpell.LookupEntryForced(1122);
	if( sp != NULL )
		sp->EffectBasePoints[0] = 0;

	sp = dbcSpell.LookupEntryForced(1860);
	if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_DUMMY;

	sp = dbcSpell.LookupEntryForced(20719);
	if( sp != NULL )
		sp->Effect[0] = SPELL_EFFECT_DUMMY;

	sp = dbcSpell.LookupEntryForced(46915);
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}

	sp = dbcSpell.LookupEntryForced(46914);
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}

	sp = dbcSpell.LookupEntryForced(46913);
	if( sp != NULL )
	{
		sp->procFlags = PROC_ON_SPELL_CRIT_HIT;
	}


	//Waylay       
	sp = dbcSpell.LookupEntryForced( 51692 );
	if( sp != NULL )
    	sp->procFlags = PROC_ON_CRIT_ATTACK;

	sp = dbcSpell.LookupEntryForced( 51696 );
	if( sp != NULL )   
		sp->procFlags = PROC_ON_CRIT_ATTACK;

	// Cold Blood
	sp = dbcSpell.LookupEntryForced( 14177 );
	if( sp != NULL )   
		sp->procFlags = PROC_ON_CAST_SPELL;


	// priest - mind flay
	ranks = fill(ids, 15407, 17311, 17312, 17313, 17314, 18807, 25387, 48155, 48156, 0);
	for(uint32 i = 0; i < ranks; i++)
	{
		sp = dbcSpell.LookupEntryForced( ids[i] );
		if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
	}

	//Warlock Chaos bolt
	ranks = fill(ids, 50796, 59170, 59171, 59172, 0);
	for(uint32 i = 0; i < ranks; i++)
	{
		sp = dbcSpell.LookupEntryForced( ids[i] );
		if( sp != NULL )
			sp->Attributes = ATTRIBUTES_IGNORE_INVULNERABILITY;
	}
	   
	//Force debuff's   
	// Hypothermia
	sp = dbcSpell.LookupEntryForced( 41425 );  
	if( sp != NULL )
		sp->c_is_flags = SPELL_FLAG_IS_FORCEDDEBUFF;
	
	// Forbearance
	sp = dbcSpell.LookupEntryForced( 25771 );  
	if( sp != NULL )        
		sp->c_is_flags = SPELL_FLAG_IS_FORCEDDEBUFF;
	// Weakened Soul
	sp = dbcSpell.LookupEntryForced( 6788 );  
	if( sp != NULL )
		sp->c_is_flags = SPELL_FLAG_IS_FORCEDDEBUFF;   

	// Death Knight spell fixes
	//Death and Decay
	ranks = fill(ids, 43265, 49936, 49937, 49938, 0);
	for(uint32 i = 0; i < ranks; i++)
	{
		sp = dbcSpell.LookupEntryForced( ids[i] );
		if( sp != NULL )
			sp->EffectApplyAuraName[0] = SPELL_AURA_PERIODIC_DAMAGE;
	}

#ifdef DUMP_CLASS_SPELLS
	DumpClassSpells();
#endif
#ifdef DUMP_SPELL_RANKS_SQL
	DumpSpellRanksSQL();
#endif
}
