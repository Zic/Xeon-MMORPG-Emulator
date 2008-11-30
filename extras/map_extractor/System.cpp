#define _CRT_SECURE_NO_DEPRECATE
//#define GENERATE_EQUIPINFO

#include <stdio.h>
#include <vector>
#include "dbcfile.h"
#include "adt.h"
#include "mpq_libmpq.h"
#include <io.h>
#include <fcntl.h>
#include <string>
#include <map>
#include <Windows.h>
#include <mmsystem.h>
#include <mysql/mysql.h>
using namespace std;

#define SFIELD_EQUIP_1 "equipmodel1"
#define SFIELD_EQUIP_2 "equipmodel2"
#define SFIELD_EQUIP_3 "equipmodel3"
#define FIELD_EQUIP_1 18
#define FIELD_EQUIP_2 21
#define FIELD_EQUIP_3 24

extern unsigned int iRes;
bool ConvertADT(uint32 x, uint32 y, FILE * out_file, char* name);
void reset();
void CleanCache();

typedef struct{
	char name[64];
	unsigned int id;
}map_id;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
map_id * map_ids;

uint32 MapCount;

void SetProgressBar(int val, int max, const char* label)
{
    printf("\r");
    for(int i = 0; i < 78; ++i)
        printf(" ");

    printf("\r");
    printf ("[%s]",&label[6]);
    int total = strlen(label) + 12;
    int diff = 78 - total;
    for(int i = 0; i < diff; ++i)
        printf(" ");

    printf("|");
    int barPos = val * 8/*30*/ / max + 1;


    int p;
    for (p = 0; p < barPos; p++) putchar ('=');
    for (; p <8/*30*/; p++) putchar (' ');

    printf ("| %d%%\r", val * 100 / max);
    fflush(stdout);
}

void ClearProgressBar()
{
    for(int p = 0; p<70;p++)
        putchar(' ');
    printf("\r");
}

void SimpleProgressBar(int val, int max)
{
    printf("\r");
    printf("\xba");
    int barPos = val * 60 / max + 1;
    int p;
    for (p = 0; p < barPos; p++) putchar (0xb1);
    for (; p <60; p++) putchar (' ');

    printf ("\xba %d%%\r", val * 100 / max);
    fflush(stdout);
}


void ExtractMapsFromMpq()
{
    bool Available_Maps[64][64];
    uint32 Offsets[512][512];
    uint32 TotalTiles = 0;
    uint32 AvailableTiles = 0;
    char output_filename[50];
    map_id * map;
	char mpq_filename[128];
	printf("\nProcessing %u maps...\n\n", MapCount);

    for(uint32 i = 0; i < MapCount; ++i)
    {	
        map = &map_ids[i];
        printf("Converting maps for mapid %u [%s]...\n", map->id, map->name);
        // Create the container file
        sprintf(output_filename, "maps\\Map_%u.bin", map->id);
        printf("  Creating output file %s.\n", output_filename);
        FILE * out_file = fopen(output_filename, "wb");
        if(!out_file)
        {
            printf("  Could not create output file!\n");
            return;
        }
        printf("  Checking which tiles are extractable...\n");

        // First, check the number of present tiles.
        for(uint32 x = 0; x < 64; ++x)
        {
            for(uint32 y = 0; y < 64; ++y)
            {
                // set up the mpq filename
                sprintf(mpq_filename, "World\\Maps\\%s\\%s_%u_%u.adt", map->name, map->name, y, x);

                // check if the file exists
                if(!mpq_file_exists(mpq_filename))
                {
                    // file does not exist
                    Available_Maps[x][y] = false;
                }
                else
                {
                    // file does exist
                    Available_Maps[x][y] = true;
                    ++AvailableTiles;
                }
                ++TotalTiles;

                // Update Progress Bar
                SimpleProgressBar( (x * 64 + y), 64 * 64 );
            }
        }

        // Clear progress bar.
        ClearProgressBar();

        // Calculate the estimated size.
        float Estimated_Size = 1048576.0f;
        uint32 TilesToExtract = 0;

        for(uint32 x = 0; x < 512; ++x)
        {
            for(uint32 y = 0; y < 512; ++y)
            {
                Offsets[x][y] = 0;
                if(Available_Maps[x/8][y/8] == true)
                    ++TilesToExtract;                
            }
        }
        // Write the offsets to file
        printf("  Writing empty index to the beginning of the file...\n");
        fwrite(Offsets, sizeof(Offsets), 1, out_file);

        Estimated_Size += 4124.0f * TilesToExtract;
        Estimated_Size /= 1024.0f;
        Estimated_Size /= 1024.0f;
        printf("  %u of %u tiles are available. Estimated file size will be %.4fMB.\n", AvailableTiles, TotalTiles, Estimated_Size);
        printf("  %u passes in total have to be performed, it may take a while.\n", TilesToExtract);
        printf("  Extracting data...\n");
        uint32 DoneTiles = 0;
        uint32 start_time = timeGetTime();
        reset();

        // call the extraction function.
        for(uint32 x = 0; x < 512; ++x)
        {
            for(uint32 y = 0; y < 512; ++y)
            {
                // Check if the map is available.
                if(Available_Maps[x/8][y/8])
                {
                    uint32 Offset = ftell(out_file);
                    if(ConvertADT(x, y, out_file, map->name))
                        Offsets[x][y] = Offset;

                    ++DoneTiles;
                    SimpleProgressBar( DoneTiles, TilesToExtract );
                }
            }

            // Clean the cache every 8 cells.
            if(!(x % 8))
                CleanCache();
        }
        ClearProgressBar();
        // clean any leftover cells
        CleanCache();

        printf("  Finished extracting in %ums. Appending header to start of file...\n", timeGetTime() - start_time);
        fseek(out_file, 0, SEEK_SET);
        fwrite(Offsets, sizeof(Offsets), 1, out_file);
        printf("  Closing output file.\n");
        fclose(out_file);

        printf("  Conversion of map %u completed\n\n", map->id);
    }

}

int main(int argc, char * arg[])
{
    printf("Ascent map extractor for versions 2.1.0 and above.. maybe :p\n");
    printf("============================================================\n\n");

	FILE * tf;
	const char* localeNames[] = { "enUS", "enGB", "deDE", "frFR", "koKR", "zhCN", "zhTW", "esES", 0 };
	int maxPatches = 3;
	int locale = -1;
	char tmp[100];

	tf = fopen("Data/common.MPQ", "r");
	if (!tf)
	{
		printf("Could not find Data/common.MPQ\n");
		return 1;
	}
	fclose(tf);
	new MPQArchive("Data/common.MPQ");

	for( size_t i = 0; localeNames[i] != 0; i++ )
	{
		sprintf(tmp, "Data/%s/locale-%s.MPQ", localeNames[i], localeNames[i]);
		tf = fopen(tmp, "r");
		if (!tf)
			continue;
		fclose(tf);
		locale = i;
		new MPQArchive(tmp);
	}

	new MPQArchive("Data/common-2.MPQ");

	for( size_t i = 0; localeNames[i] != 0; i++ )
	{
		sprintf(tmp, "Data/%s/locale-%s.MPQ", localeNames[i], localeNames[i]);
		tf = fopen(tmp, "r");
		if (!tf)
			continue;
		fclose(tf);
		locale = i;
		new MPQArchive(tmp);
	}

	tf = fopen("Data/expansion.MPQ", "r");
	if (tf)
	{
		fclose(tf);
		new MPQArchive("Data/expansion.MPQ");
		if ( -1 != locale )
		{
			sprintf(tmp, "Data/%s/expansion-locale-%s.MPQ", localeNames[locale], localeNames[locale]);
			new MPQArchive(tmp);
		}
	}

	tf = fopen("Data/lichking.MPQ", "r");
	if (tf)
	{
		fclose(tf);
		new MPQArchive("Data/lichking.MPQ");
		if ( -1 != locale )
		{
			sprintf(tmp, "Data/%s/lichking-locale-%s.MPQ", localeNames[locale], localeNames[locale]);
			new MPQArchive(tmp);
		}
	}

	tf = fopen("Data/patch.MPQ", "r");
	if (tf)
	{
		fclose(tf);
		new MPQArchive("Data/patch.MPQ");
		for(int i = 2; i <= maxPatches; i++)
		{
			sprintf(tmp, "Data/patch-%d.MPQ", i);
			tf = fopen(tmp, "r");
			if (!tf)
				continue;
			fclose(tf);
			new MPQArchive(tmp);
		}
		if ( -1 != locale )
		{
			sprintf(tmp, "Data/%s/patch-%s.MPQ", localeNames[locale], localeNames[locale]);
			tf = fopen(tmp, "r");
			if (tf)
			{
				fclose(tf);
				new MPQArchive(tmp);
				for(int i = 2; i <= maxPatches; i++)
				{
					sprintf(tmp, "Data/%s/patch-%s-%d.MPQ", localeNames[locale], localeNames[locale], i);
					tf = fopen(tmp, "r");
					if (!tf)
						continue;
					fclose(tf);
					new MPQArchive(tmp);
				}
			}
		}
	}

#ifdef GENERATE_EQUIPINFO
	DBCFile * itemDBC = new DBCFile("DBFilesClient\\Item.dbc");
	itemDBC->open();

	FILE* sql = fopen("Update.sql", "w");
	if(sql == NULL )
	{
		printf("Unable to open Update.sql");
		exit(-1);
	}

	std::map<uint32,uint32> mapforquickness;
	for(uint32 i = 0; i < itemDBC->getRecordCount(); ++i)
	{
		mapforquickness.insert(std::make_pair<uint32, uint32>(itemDBC->getRecord(i).getUInt(5), itemDBC->getRecord(i).getUInt(0)));
	}

	MYSQL* con;
	MYSQL* startup = mysql_init(NULL);
	con = mysql_real_connect(startup, "localhost", "root", "yourpw", "yourworlddb", 3306, NULL, 0); // fill in the connect info yourself, lazy
	if(con == NULL)
	{
		printf("Error connecting to mySQL.");
		exit(-1);
	}

	uint32 pie = mysql_query(con, "SELECT * FROM creature_proto;");
	if( pie == 0 )
	{
		MYSQL_RES* res = mysql_store_result(con);
		while(MYSQL_ROW r = mysql_fetch_row(res))
		{
			if( r == NULL) // wtfbbq
				break;

			uint32 entry = atol(r[0]);
			uint32 model = 0;
			std::map<uint32,uint32>::iterator itr;
			model = atol(r[FIELD_EQUIP_1 - 1]);
			itr = mapforquickness.find( model );

			if( itr != mapforquickness.end() )
			{
				fprintf(sql, "UPDATE creature_proto SET `%s` = %u WHERE `entry` = %u;\r\n", SFIELD_EQUIP_1, itr->second, entry);
			}

			model = atol(r[FIELD_EQUIP_2 - 1]);
			itr = mapforquickness.find( model );

			if( itr != mapforquickness.end() )
			{
				fprintf(sql, "UPDATE creature_proto SET `%s` = %u WHERE `entry` = %u;\r\n", SFIELD_EQUIP_2, itr->second, entry);
			}

			model = atol(r[FIELD_EQUIP_3 - 1]);
			itr = mapforquickness.find( model );

			if( itr != mapforquickness.end() )
			{
				fprintf(sql, "UPDATE creature_proto SET `%s` = %u WHERE `entry` = %u;\r\n", SFIELD_EQUIP_3, itr->second, entry);
			}
		}
	}
	else
	{
		printf("MySQL error: %s (%u)", mysql_error(con), pie);
		exit(-1);
	}
	delete itemDBC;
	fclose(sql);
	printf("Done generating EquipInfo!");
#endif

	//map.dbc
	DBCFile * dbc= new DBCFile("DBFilesClient\\Map.dbc");
	dbc->open();

	MapCount=dbc->getRecordCount ();
	map_ids=new map_id[MapCount];
	for(unsigned int x = 0; x < MapCount; x++)
	{
		map_ids[x].id=dbc->getRecord (x).getUInt(0);
		strcpy(map_ids[x].name,dbc->getRecord(x).getString(1));
	}
	delete dbc;

	CreateDirectory("maps", NULL);
	ExtractMapsFromMpq();
	delete [] map_ids;

	return 0; // Exit The Program
}
