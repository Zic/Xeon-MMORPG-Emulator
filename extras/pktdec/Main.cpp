#include <stdio.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <sys/stat.h>
#include <zlib.h>

#include "Common.h"
#include "Main.h"
#include "hashmap.h"
#include "Opcodes.h"
#include "Const.h"


typedef struct {
	int visual_items;
} mainOpts;

mainOpts opts;

char *itemsbuf;

extern NameTableEntry g_worldOpcodeNames[];

unsigned char fromhex(unsigned char val) {
	if (val >= '0' && val <= '9') {
		return val - '0';
	} else {
		return (val - 'A')+0xA;
	}
}

typedef struct {
	unsigned char *data;
	int len;
} byteBuf;

unsigned char getByte(byteBuf *b) {
	if (b->len >= 1) {
		b->len--;
		return *(b->data++);
	} else {
		printf("need more data!!\n");
		return 0;
	}
}

unsigned short getShort(byteBuf *b) {
	return getByte(b) | (getByte(b)<<8);
}

unsigned int getInt(byteBuf *b) {
	return getByte(b) | (getByte(b)<<8) | (getByte(b)<<16) | (getByte(b)<<24);
}

float getFloat(byteBuf *b) {
	unsigned int f = getByte(b) | (getByte(b)<<8) | (getByte(b)<<16) | (getByte(b)<<24);
	return *(float*)&f;
}

unsigned long long getLong(byteBuf *b) {
	return ((unsigned long long)getInt(b)) | (((unsigned long long)getInt(b))<<32);
}


void getString(byteBuf *b, char *dest) {
	unsigned char c;
	while ((c = getByte(b))) {
		*(dest++) = c;
	}
	*dest = 0;
}

unsigned long long getPackedGuid(byteBuf *b) {
	unsigned char guid[8];
	unsigned char flags = getByte(b);
	int i;

	for (i=0; i<8; i++) {
		if (flags & (1<<i)) {
				guid[i] = getByte(b);
		} else {
			guid[i] = 0;
		}
	}

	return *(unsigned long long*)guid;
}

void showPackedGuid(byteBuf *b) {
	unsigned long long guid = getPackedGuid(b);

	printf("GUID = %8.8llX\n", guid);
}

void handleAuraUpdate(byteBuf *b) {
	unsigned int id;
	unsigned char flags;
	unsigned short flags2;

	showPackedGuid(b);
	printf("auraVisual = %2.2X\n", getByte(b));
	id = getInt(b);
	printf("spellID = %d (%8.8X)\n", id, id);

	if (id == 0) return;

	flags = getByte(b);
	flags2 = getShort(b);
	printf("flags = %2.2X flags2 = %4.4X\n", flags, flags2);
}

void handleAttackerStateUpdate(byteBuf *b) {
	unsigned int flags = getInt(b);
	printf("Flags = %8.8X\n", flags);

	showPackedGuid(b);
	showPackedGuid(b);

	printf("Damage = %d\n", getInt(b));
	printf("Overkill = %d\n", getInt(b));
	printf("Type = %d\n", getByte(b));
	printf("SchoolMask = %8.8X\n", getInt(b));
	printf("DamageFloat = %f\n", getFloat(b));
	printf("DamageAmt = %d\n", getInt(b));

	if (flags & 0x20) {
		printf("Abs = %d\n", getInt(b));
	}
	if (flags & 0x40) {
		printf("Resisted = %d\n", getInt(b));
	}
	printf("UnkByte = %d\n", getByte(b));
	printf("Unk = %8.8X\n", getInt(b));
	if (flags & 0x00800000) {
		printf("VState = %d\n", getInt(b));
	}
	if (flags & 0x2000) {
		printf("Blocked = %d\n", getInt(b));
	}
	printf("HitNumber = %d\n", getInt(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleSendPeriodicAuraLog(byteBuf *b) {
	unsigned int flags;

	showPackedGuid(b);
	showPackedGuid(b);

	printf("Id = %d\n", getInt(b));
	printf("Unk = %d\n", getInt(b));
	flags = getInt(b);
	printf("Flags = 0x%x\n", flags);
	printf("Amt = %d\n", getInt(b));
	printf("Overkill = %d\n", getInt(b));

	if (flags & 0x1) {
		printf("School = 0x%x\n", getInt(b));
		printf("Abs = %d\n", getInt(b));
		printf("Resisted = %d\n", getInt(b));
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleSendSpellNonMeleeLog(byteBuf *b) {
}

void handleTogglePvP(byteBuf *b) {
}

static map_t objects;
static map_t entrylist;

void writeVisualItem(unsigned int entry, int field, unsigned int value) {
	FILE *f;
	char str[256];
	int slot = (field-0x37)+1;
	map_t list = NULL;

	sprintf(str, "entry=%d;", entry);
	if (hashmap_get(entrylist, entry, (any_t*)&list) == MAP_OK) {
		if (hashmap_get(list, slot, NULL) == MAP_OK) return;
	}

//	if (itemsbuf && strstr(itemsbuf, str)) return;

	f = fopen("visual_items.sql", "a");
	if (f) {
		fprintf(f, "UPDATE creature_proto set equipslot%d=%d where entry=%d;\n", slot, value, entry);
		fclose(f);
	}

	if (list == NULL) {
		list = hashmap_new();
		hashmap_put(entrylist, entry, (any_t)list);
	}
	hashmap_put(list, slot, NULL);
}

void handleValuesUpdate(byteBuf *b, unsigned long long guid) {
	unsigned int buf[64];
	unsigned int type = 0;
	unsigned int entry = 0;
	any_t val;
	int blocks;
	int i;

	blocks = getByte(b);
	printf("Blocks = %d\n", blocks);
	if (blocks > 64) return;

	for (i=0; i<blocks; i++) {
		buf[i] = getInt(b);
//		printf("[%d] = %x\n", i, buf[i]);
	}

	if (hashmap64_get(objects, guid, &val) == MAP_OK) {
		type = (unsigned int)(unsigned long long)val;
	}

	for (i=0; i<blocks; i++) {
		int k;
		for (k=0; k<32; k++) {
			if (buf[i] & (1<<k)) {
				int field = i*32+k;
				unsigned int value = getInt(b);

				switch (field) {
					case 2:
						type = value;
						if (hashmap64_get(objects, guid, NULL) != MAP_OK) {
							hashmap64_put(objects, guid, (any_t)type);
						}
						printf("[%d] TYPE = 0x%x\n", field, value); break;
						break;
					case 3:
						entry = value;
						printf("[%d] ENTRY = %d\n", field, value); break;
					default:
						if (opts.visual_items) {
							if (type & 0x8 && entry!=0 && 
								(field >= 0x0037 && field <= 0x0039)) {
								writeVisualItem(entry, field, value);
							}
						}

						if (type & 0x8) {
							printf("[%d] %s = 0x%x; %d; %f (entry=%d)\n", field, unitFields[field], value, value, *(float*)&value, entry);
						} else {
							printf("[%d] Value = 0x%x; %d\n", field, value, value);
						}
						break;
				}
			}
		}
	}
}

void handleSMSG_UpdateObject(byteBuf *b) {
	unsigned long long guid;
	int count = getInt(b);
	int i,j;

	printf("Count = %d\n", count);
//	printf("Unk = %d\n", getByte(b));

	for (i=0; i<count; i++) {
		int type = getByte(b);
		unsigned int flags;
		unsigned int flags2;
		int blocks;
		printf("Type = %d\n", type);

		switch (type) {
			case 0:
				guid = getPackedGuid(b);
				printf("GUID = %8.8llX\n", guid);
				handleValuesUpdate(b, guid);
				break;

			case 3:
			case 2:
				guid = getPackedGuid(b);
				printf("GUID = %8.8llX\n", guid);
				printf("TypeId = %d\n", getByte(b));
				flags = getByte(b);
				flags2 = 0;
				printf("Flags = 0x%x\n", flags);
				if (flags & 0x20) {
					flags2 = getInt(b);
					printf("Flags2 = 0x%x\n", flags2);
					printf("Unk = %d\n", getShort(b));
					printf("Time = %d\n", getInt(b));
				}

				if (flags & 0x40) {
					if (flags & 0x2) {
						printf("X = %f\n", getFloat(b));
						printf("Y = %f\n", getFloat(b));
						printf("Z = %f\n", getFloat(b));
						printf("O = %f\n", getFloat(b));
					} else {
						printf("X = %f\n", getFloat(b));
						printf("Y = %f\n", getFloat(b));
						printf("Z = %f\n", getFloat(b));
						printf("O = %f\n", getFloat(b));
					}

					if (flags & 0x20 && flags2 & 0x200) {
						printf("TransporterGUID = 0x%llx\n", getLong(b));
						printf("TransporterX = %f\n", getFloat(b));
						printf("TransporterY = %f\n", getFloat(b));
						printf("TransporterZ = %f\n", getFloat(b));
						printf("TransporterO = %f\n", getFloat(b));
						printf("TransporterUnk = %f\n", getFloat(b));
						printf("Unk = %d\n", getByte(b));
					}
				}

				if (flags & 0x20) {
					printf("Unk = %d\n", getInt(b));
				}

				if (flags & 0x20 & flags2 & 0x2000) {
					printf("UnkF0 = %f\n", getFloat(b));
					printf("UnkF1 = %f\n", getFloat(b));
					printf("UnkF2 = %f\n", getFloat(b));
					printf("UnkF3 = %f\n", getFloat(b));
				}

				if (flags & 0x20) {
					printf("UnkF0 = %f\n", getFloat(b));
					printf("UnkF1 = %f\n", getFloat(b));
					printf("UnkF2 = %f\n", getFloat(b));
					printf("UnkF3 = %f\n", getFloat(b));
					printf("UnkF4 = %f\n", getFloat(b));
					printf("UnkF5 = %f\n", getFloat(b));
					printf("UnkF6 = %f\n", getFloat(b));
					printf("UnkF7 = %f\n", getFloat(b));
					printf("UnkF8 = %f\n", getFloat(b));

					if ((flags2 & 0x8000001) == 0x8000001) {
						printf("Spline flags = %d\n", getInt(b));
						printf("Unk = %d\n", getInt(b));
						printf("Unk = %d\n", getInt(b));
						printf("Unk = %d\n", getInt(b));
						blocks = getInt(b);
						printf("Spline Count = %d\n", blocks);
						if (blocks > 64) return;

						for (j=0; j<blocks+1; j++) {
							printf("X = %f\n", getFloat(b));
							printf("Y = %f\n", getFloat(b));
							printf("Z = %f\n", getFloat(b));
						}
					}
				}

				if (flags & 0x8) {
					printf("FieldGUID = 0x%X\n", getInt(b));
					if (flags & 0x10) {
						printf("FieldGUID2 = 0x%X\n", getInt(b));
					}
				}

				if (flags & 0x2) {
					printf("Time = %d\n", getInt(b));
				}

				if (flags & 0x80) {
					printf("Unk = %f\n", getFloat(b));
					printf("Unk = 0x%X\n", getInt(b));
				}

				handleValuesUpdate(b, guid);
				break;

			case 4:
				blocks = getInt(b);
				printf("Blocks = %d\n", blocks);
				if (blocks > 256) return;
				for (j=0; j<blocks; j++) {
					showPackedGuid(b);
				}
				break;
		}
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleSMSG_CompressedUpdateObject(byteBuf *b) {
	z_stream stream;
	byteBuf b1;
	unsigned char *data;
	int len = getInt(b);

	printf("Length = %d\n", len);

	stream.zalloc = 0;
	stream.zfree  = 0;
	stream.opaque = 0;
	stream.avail_in = 0;
	stream.next_in = Z_NULL;

	if(inflateInit(&stream) != Z_OK) {
		printf("inflateInit failed\n");
		return;
	}

	data = (unsigned char*)malloc(len);
	b1.data = data;
	b1.len = len;

	// set up stream pointers
	stream.next_out  = (Bytef*)b1.data;
	stream.avail_out = (uInt)b1.len;
	stream.next_in   = (Bytef*)b->data;
	stream.avail_in  = (uInt)b->len;

	// call the actual process
	if(inflate(&stream, Z_NO_FLUSH) == Z_STREAM_ERROR) {
		printf("inflate failed\n");
		return;
	}

	// finish up
	if(inflateEnd(&stream) != Z_OK) {
		printf("inflateEnd failed\n");
		return;
	}

	handleSMSG_UpdateObject(&b1);

	free(data);
}

void handleQuestGiverQuestComplete(byteBuf *b) {
	int count;
	int i;

	printf("Id = %d\n", getInt(b));
	printf("Flags = %d\n", getInt(b));
	printf("Xp = %d\n", getInt(b));
	printf("Money = %d\n", getInt(b));
	printf("Honor = %d\n", getInt(b));
	printf("Unk = %d\n", getInt(b));
	count = getInt(b);
	printf("CountItem = %d\n", count);

	for (i=0; i<count; i++) {
		printf("Item = %d\n", getInt(b));
		printf("ItemCount = %d\n", getInt(b));
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleItemQuerySingleResponse(byteBuf *b) {
	char name[1024];
	int count;
	int i;

	printf("Id = %d\n", getInt(b));
	printf("Class = %d\n", getInt(b));
	printf("SubClass = %d\n", getInt(b));
	printf("unk = %d\n", getInt(b));
	getString(b, name);
	printf("name = %s\n", name);
	getByte(b); getByte(b); getByte(b);

	printf("displayinfoid = %d\n", getInt(b));
	printf("quality = %d\n", getInt(b));
	printf("flags = 0x%8.8x\n", getInt(b));
	printf("buyprice = %d\n", getInt(b));
	printf("sellprice = %d\n", getInt(b));
	printf("inventorytype = %d\n", getInt(b));
	printf("allowableclass = %d\n", getInt(b));
	printf("allowablerace = %d\n", getInt(b));
	printf("itemlevel = %d\n", getInt(b));
	printf("requiredlevel = %d\n", getInt(b));
	printf("requiredskill = %d\n", getInt(b));
	printf("requiredskillrank = %d\n", getInt(b));
	printf("requiredskillsubrank = %d\n", getInt(b));
	printf("requiredplayerrank1 = %d\n", getInt(b));
	printf("requiredplayerrank2 = %d\n", getInt(b));
	printf("requiredfaction = %d\n", getInt(b));
	printf("requiredfactionstanding = %d\n", getInt(b));
	printf("unique = %d\n", getInt(b));
	printf("maxcount = %d\n", getInt(b));
	printf("containerslots = %d\n", getInt(b));

	count = getInt(b);
	for (i=0; i<count; i++) {
		printf("Stats[%d].Type = %d\n", i, getInt(b));
		printf("Stats[%d].Value = %d\n", i, getInt(b));
	}

	printf("Unk = %d\n", getInt(b));
	printf("Unk = %d\n", getInt(b));

	for (i=0; i<5; i++) {
		printf("Damage[%d].Min = %f\n", i, getFloat(b));
		printf("Damage[%d].Max = %f\n", i, getFloat(b));
		printf("Damage[%d].Type = %d\n", i, getInt(b));
	}

	printf("Armor = %d\n", getInt(b));
	printf("HolyRes = %d\n", getInt(b));
	printf("FireRes = %d\n", getInt(b));
	printf("NatureRes = %d\n", getInt(b));
	printf("FrostRes = %d\n", getInt(b));
	printf("ShadowRes = %d\n", getInt(b));
	printf("ArcaneRes = %d\n", getInt(b));
	printf("Delay = %d\n", getInt(b));
	printf("AmmoType = %d\n", getInt(b));
	printf("Range = %d\n", getInt(b));
	for (i=0; i<5; i++) {
		printf("Spells[%d].Id = %d\n", i, getInt(b));
		printf("Spells[%d].Trigger = %d\n", i, getInt(b));
		printf("Spells[%d].Charges = %d\n", i, getInt(b));
		printf("Spells[%d].Cooldown = %d\n", i, getInt(b));
		printf("Spells[%d].Category = %d\n", i, getInt(b));
		printf("Spells[%d].CategoryCooldown = %d\n", i, getInt(b));
	}
	printf("Bonding = %d\n", getInt(b));
	getString(b, name);
	printf("Description = %s\n", name);
	printf("PageId = %d\n", getInt(b));
	printf("PageLanguage = %d\n", getInt(b));
	printf("PageMaterial = %d\n", getInt(b));
	printf("QuestId = %d\n", getInt(b));
	printf("LockId = %d\n", getInt(b));
	printf("LockMaterial = %d\n", getInt(b));
	printf("Field108 = %d\n", getInt(b));
	printf("RandomPropId = %d\n", getInt(b));
	printf("RandomSuffixId = %d\n", getInt(b));
	printf("Block = %d\n", getInt(b));
	printf("ItemSet = %d\n", getInt(b));
	printf("MaxDurability = %d\n", getInt(b));
	printf("ZoneNameId = %d\n", getInt(b));
	printf("MapId = %d\n", getInt(b));
	printf("BagFamily = %d\n", getInt(b));
	printf("TotemCategory = %d\n", getInt(b));
	for (i=0; i<3; i++) {
		printf("Sockets[%d].SocketColor = %d\n", i, getInt(b));
		printf("Sockets[%d].Unk = %d\n", i, getInt(b));
	}
	printf("SocketBonus = %d\n", getInt(b));
	printf("GemProperties = %d\n", getInt(b));
	printf("DisenchantReqSkill = %d\n", getInt(b));
	printf("ArmorDamageModifier = %d\n", getInt(b));
	printf("Unk = %d\n", getInt(b));
	printf("Unk2 = %d\n", getInt(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}


void handleAchievementEarned(byteBuf *b) {
	showPackedGuid(b);

	printf("Id = %d\n", getInt(b));
	printf("Time? = %d\n", getInt(b));
	printf("Unk= %d\n", getInt(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleQueryInspectAchievements(byteBuf *b) {
	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleRespondInspectAchievements(byteBuf *b) {
	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleAllAchievementData(byteBuf *b) {
	unsigned int flags;
	int i;

	printf("Unk = 0x%8.8X\n", getInt(b));
	printf("Unk = 0x%8.8X\n", getInt(b));
	printf("Unk = 0x%8.8X\n", getInt(b));
	for (i=0; i<256; i++) {
		unsigned int id = getInt(b);
		printf("[%d] Id = 0x%8.8X\n", i, id);
		if (id == (unsigned int)-1) break;
		flags = getByte(b);
		printf("[%d] Flags = 0x%8.8X\n", i, flags);
		printf("[%d] Unk = 0x%8.8X\n", i, getByte(b));
		if (flags & 0x2) {
			printf("[%d] Unk = 0x%8.8X\n", i, getByte(b));
		}
/*		if (flags == 0x06) {
			printf("[%d] Unk = 0x%8.8X\n", i, getByte(b));
			printf("[%d] Unk = 0x%8.8X\n", i, getShort(b));
		}*/
		showPackedGuid(b);
		printf("[%d] Unk = 0x%8.8X\n", i, getInt(b));
		printf("[%d] Unk = 0x%8.8X\n", i, getInt(b));
		printf("[%d] Unk = 0x%8.8X\n", i, getInt(b));
		printf("[%d] Unk = 0x%8.8X\n", i, getInt(b));
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleSMSG_MessageChat(byteBuf *b) {
	char str[4096];
	printf("Channel = %d\n", getByte(b));
	printf("Lang = 0x%8.8X\n", getInt(b));
	printf("GUID = 0x%16.16llX\n", getLong(b));
	printf("Rank = 0x%8.8X\n", getInt(b));
	printf("GUID = 0x%16.16llX\n", getLong(b));
	printf("Length = %d\n", getInt(b));
	getString(b, str);
	printf("Msg = %s\n", str);
	printf("Flags = %d\n", getByte(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleSMSG_MoveRoot(byteBuf *b) {
	showPackedGuid(b);
	printf("Unk = 0x%8.8X\n", getShort(b));
	printf("Unk = 0x%8.8X\n", getInt(b));
	printf("Unk = %f\n", getFloat(b));
	printf("X = %f\n", getFloat(b));
	printf("Y = %f\n", getFloat(b));
	printf("Z = %f\n", getFloat(b));
	printf("O = %f\n", getFloat(b));
	printf("Unk = %f\n", getFloat(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleSMSG_MoveUnroot(byteBuf *b) {
	showPackedGuid(b);
	printf("Unk = 0x%8.8X\n", getShort(b));
	printf("Unk = 0x%8.8X\n", getInt(b));
	printf("Unk = %f\n", getFloat(b));
	printf("X = %f\n", getFloat(b));
	printf("Y = %f\n", getFloat(b));
	printf("Z = %f\n", getFloat(b));
	printf("O = %f\n", getFloat(b));
	printf("Unk = %f\n", getFloat(b));
	printf("Unk = %f\n", getFloat(b));
	printf("Unk = %f\n", getFloat(b));
	printf("Unk = %f\n", getFloat(b));
	printf("Unk = %f\n", getFloat(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleHighestThreatUpdate(byteBuf *b) {
	showPackedGuid(b);
	while (b->len > 0) {
		showPackedGuid(b);
		printf("Threat = %d\n", getInt(b));
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleCastSpell(byteBuf *b) {
	printf("CastNumber = %d\n", getByte(b));
	printf("Id = %d\n", getInt(b));
	printf("Unk = %d\n", getByte(b));
	printf("Unk = %d\n", getInt(b));
	printf("Unk = %X\n", getInt(b));
	printf("Unk = %X\n", getInt(b));
	
	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleSpellStart(byteBuf *b) {
	showPackedGuid(b);
	showPackedGuid(b);
	printf("CastNumber = %d\n", getByte(b));
	printf("Id = %d\n", getInt(b));
	printf("Flags = 0x%X\n", getInt(b));
	printf("Time = %X\n", getInt(b));
	printf("Unk = %X\n", getInt(b));
	
	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void showTargets(byteBuf *b) {
	int mask = getInt(b);
	printf("TargetsMask = %X\n", mask);
	if (mask & (0x1 | 0x4)) {
		showPackedGuid(b);
	}
	if (mask & (0x8202 | 0x800)) {
		showPackedGuid(b);
	}
	if (mask & (0x20|0x40)) {
		printf("X = %f\n", getFloat(b));
		printf("Y = %f\n", getFloat(b));
		printf("Z = %f\n", getFloat(b));
	}
	if (mask & 0x4000) {
		printf("Unk = %x\n", getInt(b));
		printf("Unk = %x\n", getByte(b));
		printf("Unk = %x\n", getByte(b));
		printf("Unk = %x\n", getByte(b));
		showPackedGuid(b);
	}
}

void handleSpellGO(byteBuf *b) {
	unsigned int flags;
	int count;
	int i;

	showPackedGuid(b);
	showPackedGuid(b);
	printf("CastNumber = %d\n", getByte(b));
	printf("Id = %d\n", getInt(b));
	flags = getInt(b);
	printf("Flags = 0x%X\n", flags);
	printf("Time = %X\n", getInt(b));

	count = getByte(b);
	printf("HitCount = %X\n", count);
	for (i=0; i<count; i++) {
		printf("GUID = %16.16llX\n", getLong(b));
	}

	count = getByte(b);
	printf("MissCount = %X\n", count);
	for (i=0; i<count; i++) {
		printf("GUID = %16.16llX\n", getLong(b));
	}

	showTargets(b);
	if (flags & 0x20) {
		printf("DisplayInfoId = %d\n", getInt(b));
		printf("InventoryType = %d\n", getInt(b));
	}
	if (flags & 0x200000) {
		for (i=0; i<6; i++) {
			printf("Rune[%d] = %X\n", i, getByte(b));
		}
		if (!(flags & 0x1)) {
			printf("Unk = %X\n", getByte(b));
		}
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handlePowerUpdate(byteBuf *b) {
	showPackedGuid(b);
	printf("Type = %d\n", getByte(b));
	printf("Value = %d\n", getInt(b));
	
	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleCastFailed(byteBuf *b) {
	printf("CastNumber = %d\n", getByte(b));
	printf("Id = %d\n", getInt(b));
	printf("Error = %d\n", getByte(b));
	
	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleGuildBankList(byteBuf *b) {
	char str[256];
	int count;
	int i;

	printf("Balance %lld\n", getLong(b));
	printf("Id = %d\n", getByte(b));
	printf("Allowed = %x\n", getInt(b));
	printf("Unk = %x\n", getByte(b));
	count = getByte(b);
	printf("Count = %x\n", count);
	for (i=0; i<count; i++) {
		getString(b, str);
		printf("Name = %s\n", str);
		getString(b, str);
		printf("Mmm = %s\n", str);
	}

	if (b->len != 0) {
		count = getByte(b);
		printf("Count = %x\n", count);
		for (i=0; i<count; i++) {
			printf("Index = %d\n", getByte(b));
			printf("Entry = %d\n", getInt(b));
			printf("Props = %d\n", getInt(b));
			printf("StackCount = %d\n", getByte(b));
			printf("Unk = %d\n", getInt(b));
			printf("Unk2= %d\n", getByte(b));
			printf("Unk3 = %x\n", getInt(b));
		}
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleMailListResult(byteBuf *b) {
	char str[256];
	int count;
	int count2;
	int i, j, k;

	count = getByte(b);
	printf("Count = %x\n", count);
	for (i=0; i<count; i++) {
		printf("Flags? = %x\n", getShort(b));
		printf("Id = %x\n", getInt(b));
		printf("Type = %x\n", getByte(b));
		printf("SenderGuid = %x\n", getInt(b));
		printf("Cod = %x\n", getInt(b));
		printf("Id = %d\n", getInt(b));
		printf("Unk = %x\n", getInt(b));
		printf("Stationary = %x\n", getInt(b));
		printf("Money = %x\n", getInt(b));
		printf("Unk = %x\n", getInt(b));
		printf("Unk = %x\n", getInt(b));
		printf("Unk2 = %f\n", getFloat(b));
		printf("Unk3 = %x\n", getInt(b));
		getString(b, str);
		printf("Subject = %s\n", str);

		count2 = getByte(b);
		printf("ItemCount = %x\n", count2);
		for (j=0; j<count2; j++) {
			printf("Pos = %x\n", getByte(b));
			printf("Id = %x\n", getInt(b));
			printf("Entry = %x\n", getInt(b));
			for (k=0;k<6;k++) {
				printf("Enchantment0 = %d\n", getInt(b));
				printf("Enchantment1 = %d\n", getInt(b));
				printf("Enchantment2 = %d\n", getInt(b));
			}

			printf("Prop = %x\n", getInt(b));
			printf("Suff = %x\n", getInt(b));
			printf("StackCount = %x\n", getByte(b));
			printf("Charges = %x\n", getInt(b));

			printf("Unk = %x\n", getInt(b));
			printf("Unk = %x\n", getInt(b));
			printf("Unk = %x\n", getInt(b));
			printf("Unk = %x\n", getInt(b));
			printf("MaxDur = %x\n", getInt(b));
			printf("Dur = %x\n", getInt(b));
		}
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleAuctionListResult(byteBuf *b) {
	int count;
	int i, k;

	count = getInt(b);
	printf("Count = %d\n", count);
	for (i=0; i<count; i++) {
		printf("Id = %x\n", getInt(b));
		printf("Entry = %d\n", getInt(b));
		for (k=0;k<6;k++) {
			printf("Enchantment0 = %x\n", getInt(b));
			printf("Enchantment1 = %x\n", getInt(b));
			printf("Enchantment2 = %x\n", getInt(b));
		}

		printf("Prop = %x\n", getInt(b));
		printf("Suff = %x\n", getInt(b));
		printf("StackCount = %x\n", getInt(b));
		printf("Charges = %x\n", getInt(b));

		printf("Unk = %x\n", getInt(b));
		printf("Unk = %x\n", getInt(b));
		printf("Unk = %x\n", getInt(b));

		printf("Unk = %x\n", getInt(b));
		printf("Owner %llx\n", getLong(b));

		printf("HighestBid = %x\n", getInt(b));
		printf("Mod = %x\n", getInt(b));
		printf("BuyoutPrice = %d\n", getInt(b));
		printf("Timeleft = %d\n", getInt(b));

		printf("HighestBidder %llx\n", getLong(b));
		printf("HighestBid = %d\n", getInt(b));
	}

	printf("TotalCount = %d\n", getInt(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleInitWorldStates(byteBuf *b) {
	int count;
	int i;

	printf("MapId = %d\n", getInt(b));
	printf("ZoneId = %d\n", getInt(b));
	printf("AreaId = %d\n", getInt(b));
	count = getShort(b);
	printf("Count = %d\n", count);
	for (i=0; i<count; i++) {
		printf("Index = 0x%x\n", getInt(b));
		printf("Value = 0x%x\n", getInt(b));
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleUpdateWorldState(byteBuf *b) {
	printf("Index = 0x%x\n", getInt(b));
	printf("Value = 0x%x\n", getInt(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleQuestGiverStatus(byteBuf *b) {
	printf("GUID = 0x%llx\n", getLong(b));
	printf("Value = 0x%x\n", getByte(b));

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleGuildRoster(byteBuf *b) {
	char str[1024];
	int flags;
	int ranks;
	int count;
	int i, j;

	count = getInt(b);
	printf("Members = %d\n", count);
	getString(b, str);
	printf("Motd = %s\n", str);
	getString(b, str);
	printf("Info = %s\n", str);

	ranks = getInt(b);
	printf("Ranks = %d\n", count);
	for (i=0; i<ranks; i++) {
		printf("Rights = 0x%x\n", getInt(b));
		printf("GoldLimit = 0x%x\n", getInt(b));

		for (j=0; j<6; j++) {
			printf("[%d] Flags = 0x%x\n", j, getInt(b));
			printf("[%d] StackPerDay = 0x%x\n", j, getInt(b));
		}
	}

	for (i=0; i<count; i++) {
		printf("[%d] GUID = 0x%llx\n", i, getLong(b));
		flags = getByte(b);
		printf("[%d] Logged = 0x%x\n", i, flags);
		getString(b, str);
		printf("[%d] Name = %s\n", i, str);
		printf("[%d] RankId = 0x%x\n", i, getInt(b));
		printf("[%d] Level = 0x%x\n", i, getByte(b));
		printf("[%d] Class = 0x%x\n", i, getByte(b));
		printf("[%d] Unk = 0x%x\n", i, getByte(b));
		printf("[%d] Zone = 0x%x\n", i, getInt(b));
		if (flags == 0)
			printf("[%d] lastOnline = %f\n", i, getFloat(b));

		getString(b, str);
		printf("[%d] PublicNote = %s\n", i, str);
		getString(b, str);
		printf("[%d] OfficerNote = %s\n", i, str);
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handlePartyMemberStats(byteBuf *b) {
	unsigned int mask;
	unsigned int flags;
	int i;

	showPackedGuid(b);
	flags = getInt(b);
	printf("Flags = 0x%x\n", flags);

	if (flags & 0x00000001) { // online
		printf("Online = 0x%x\n", getShort(b));
	}
	if (flags & 0x00000002) { // health
		printf("Health = 0x%x\n", getShort(b));
	}
	if (flags & 0x00000004) { // maxhealth
		printf("MaxHealth = 0x%x\n", getShort(b));
	}
	if (flags & 0x00000008) { // power_type
		printf("PowerType = 0x%x\n", getByte(b));
	}
	if (flags & 0x00000010) { // power
		printf("Power = 0x%x\n", getShort(b));
	}
	if (flags & 0x00000020) { // maxpower
		printf("MaxPower = 0x%x\n", getShort(b));
	}
	if (flags & 0x00000040) { // level
		printf("Level = 0x%x\n", getShort(b));
	}
	if (flags & 0x00000080) { // zoneid
		printf("Zoneid = 0x%x\n", getShort(b));
	}
	if (flags & 0x00000100) { // position
		printf("X = 0x%x\n", getShort(b));
		printf("Y = 0x%x\n", getShort(b));
	}

	if (flags & 0x00000200) { // player_auras
		mask = getInt(b);
		printf("Mask = 0x%x\n", mask);
		for (i=0; i<32; i++) {
			if (mask & (1<<i)) {
				printf("[%d] Id = 0x%x\n", i, getShort(b));
				printf("[%d] Flags = 0x%x\n", i, getByte(b));
			}
		}
	}
	if (flags & 0x00000400) { // pet_guid
	}
	if (flags & 0x00000800) { // pet_name
	}
	if (flags & 0x00001000) { // pet_displayid
	}
	if (flags & 0x00002000) { // pet_health
	}
	if (flags & 0x00004000) { // pet_maxhealth
	}
	if (flags & 0x00008000) { // pet_powertype
	}
	if (flags & 0x00010000) { // pet_power
	}
	if (flags & 0x00020000) { // pet_maxpower
	}
	if (flags & 0x00040000) { // pet_auras
	}

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}

void handleUseItem(byteBuf *b) {
	printf("Tmp1 = 0x%x\n", getByte(b));
	printf("Slot = 0x%x\n", getByte(b));
	printf("Tmp3 = 0x%x\n", getByte(b));
	printf("CastNumber = 0x%x\n", getByte(b));
	printf("ItemGUID = 0x%llx\n", getLong(b));
	printf("Unk = 0x%x\n", getByte(b));

	showTargets(b);

	if (b->len != 0) {
		printf("warning: remaining %d bytes left\n", b->len);
	}
}


void parsePacket(xmlNode *node) {
	xmlChar *sdir = xmlGetProp(node, (const xmlChar*)"direction");
	xmlChar *sop = xmlGetProp(node, (const xmlChar*)"opcode");
	unsigned int op = strtol((const char*)sop, (char**)NULL, 0);
	unsigned char data[64*1024];
	const char *content;
	byteBuf b;
	int i, len;

	// Hardcoded filter, yeah baby xD
//	if (op != 0x14A) return;
//	if (op != 0x0468 && op != 0x46B && op != 0x46C && op != 0x47D) return;
//	if (op != 0x496 && op != 0x495) return;
	if (node->children == NULL) return;

	content = (const char*)node->children->content;
	for (i=0, len=0; i<(int)strlen(content); i+= 2) {
		data[len++] = (fromhex(content[i])<<4) |
					  fromhex(content[i+1]);
	}

	b.data = data;
	b.len = len;

	printf("\n%s; opcode = %4.4X %s\n", sdir, op, g_worldOpcodeNames[op].name);
	printf("%s\n", content);

	switch (op) {
		case 0x0058: handleItemQuerySingleResponse(&b); break;
		case 0x0096: handleSMSG_MessageChat(&b); break;
		case 0x00A9: handleSMSG_UpdateObject(&b); break;
		case 0x00EC: handleSMSG_MoveRoot(&b); break;
		case 0x00ED: handleSMSG_MoveUnroot(&b); break;

		case CMSG_CAST_SPELL:				handleCastSpell(&b); break;
		case CMSG_USE_ITEM:					handleUseItem(&b); break;

		case SMSG_SPELL_START:				handleSpellStart(&b); break;
		case SMSG_SPELL_GO:					handleSpellGO(&b); break;
		case SMSG_CAST_FAILED:				handleCastFailed(&b); break;
		case SMSG_POWER_UPDATE:				handlePowerUpdate(&b); break;
		case SMSG_GUILD_BANK_LIST: 			handleGuildBankList(&b); break;
		case SMSG_MAIL_LIST_RESULT:			handleMailListResult(&b); break;
		case SMSG_AUCTION_LIST_RESULT:		handleAuctionListResult(&b); break;
		case SMSG_INIT_WORLD_STATES:		handleInitWorldStates(&b); break;
		case SMSG_UPDATE_WORLD_STATE:		handleUpdateWorldState(&b); break;
		case SMSG_PARTY_MEMBER_STATS:		handlePartyMemberStats(&b); break;
		case SMSG_QUESTGIVER_STATUS:		handleQuestGiverStatus(&b); break;
		case SMSG_GUILD_ROSTER:				handleGuildRoster(&b); break;

		case 0x014A: handleAttackerStateUpdate(&b); break;
		case 0x01F6: handleSMSG_CompressedUpdateObject(&b); break;
		case 0x0191: handleQuestGiverQuestComplete(&b); break;
		case 0x024E: handleSendPeriodicAuraLog(&b); break;
		case 0x0250: handleSendSpellNonMeleeLog(&b); break;
		case 0x0253: handleTogglePvP(&b); break;
		case 0x0468: handleAchievementEarned(&b); break;
		case 0x046B: handleQueryInspectAchievements(&b); break;
		case 0x046C: handleRespondInspectAchievements(&b); break;
		case 0x047D: handleAllAchievementData(&b); break;
		case 0x0482: handleHighestThreatUpdate(&b); break;
		case 0x0496: handleAuraUpdate(&b); break;
	}
}

void parseFile(char *filename) {
	xmlDocPtr doc;
	xmlNode *node;

	objects = hashmap64_new();
	entrylist = hashmap_new();

    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        fprintf(stderr, "Failed to parse %s\n", filename);
		return;
    }

	node = xmlDocGetRootElement(doc);
	node = node->children;
	while (node->next) {
        if (node->type == XML_ELEMENT_NODE) {
			if (!strcmp((const char*)node->name, "packet")) {
				parsePacket(node);
			}
        }

//        print_element_names(cur_node->children);
		node = node->next;
    }

	xmlFreeDoc(doc);

	hashmap64_free(objects);
	hashmap_free(entrylist);
}

int main(int argc, char *argv[]) {
	int i;

	for (i=0; i<argc; i++) {
		parseFile(argv[i]);
	}

	return 0;
}
