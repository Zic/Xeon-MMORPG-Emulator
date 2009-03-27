// spellfailure_extractor.cpp : Defines the entry point for the console application.
//

#include <cstring>
#include <cstdio>
#include <cstdlib>

#define SEARCH_TEXT "SPELL_FAILED_AFFECTING_COMBAT"
#define FIRST_FAILURE 0

bool reverse_pointer_back_to_string(char ** ptr, char * str)
{
	size_t slen = strlen(str);
	size_t i;
	for(;;)
	{
		while((*ptr)[0] != str[0])
		{
			(*ptr)--;
		}

		for(i = 0; i < slen; ++i)
			if((*ptr)[i] != str[i])
				break;

		if(i == slen)
			return true;
		else
			(*ptr)--;
	}
	return false;
}
int find_string_in_buffer(char * str, size_t str_len, char * buf, size_t buf_len)
{
	char * p = buf;
	char * p_end = buf + buf_len;
	size_t remaining = buf_len;
	size_t i;

	for(;;)
	{
		while(*p != str[0] && p != p_end)
		{
			--remaining;
			++p;
		}

		if(p == p_end)
			break;

		if(remaining < str_len)
			break;

		for(i = 0; i < str_len; ++i)
		{
			if(p[i] != str[i])
				break;
		}

		if(i == str_len)
			return (int)(p - buf);

		*p++;
	}
	return -1;
}

int main(int argc, char* argv[])
{
	FILE * in = fopen("WoW.exe", "rb");
	FILE * out = fopen("SpellFailure.h", "w");
	if(!in || !out)
		return 1;

	fseek(in, 0, SEEK_END);
	int len = ftell(in);
	fseek(in, 0, SEEK_SET);

	char * buffer = (char*)malloc(len);
	if(!buffer)
		return 2;

	if(fread(buffer, 1, len, in) != len)
		return 3;

	printf("Searching for `%s`...", SEARCH_TEXT);
	size_t offset = find_string_in_buffer(SEARCH_TEXT, strlen(SEARCH_TEXT), buffer, len);
	printf(" at %d.\n", offset);
	if(offset < 0)
		return 3;

	/* dump header */
	fprintf(out, "/****************************************************************************\n");
    fprintf(out, " *\n");
    fprintf(out, " * Spell System\n");
    fprintf(out, " * Copyright (C) 2007 Antrix Team\n");
    fprintf(out, " * Copyright (C) 2008 Hearthstone <http://www.hearthstone-project.com/>\n");
    fprintf(out, " *\n");
    fprintf(out, " * This program is free software: you can redistribute it and/or modify\n");
    fprintf(out, " * it under the terms of the GNU Affero General Public License as published by\n");
    fprintf(out, " * the Free Software Foundation, either version 3 of the License, or\n");
    fprintf(out, " * any later version.\n");
    fprintf(out, " *\n");
    fprintf(out, " * This program is distributed in the hope that it will be useful,\n");
    fprintf(out, " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
    fprintf(out, " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n");
    fprintf(out, " * GNU Affero General Public License for more details.\n");
    fprintf(out, " *\n");
    fprintf(out, " * You should have received a copy of the GNU Affero General Public License\n");
    fprintf(out, " * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n");
    fprintf(out, " *\n");
    fprintf(out, " */\n");
	fprintf(out, "\n#ifndef _SPELLFAILURE_H\n#define _SPELLFAILURE_H\n\nenum SpellCastError\n{\n");

	printf("Ripping...");
	char * p = (buffer + offset);
	char * name = p;
	int index = FIRST_FAILURE;
	size_t no_spaces;
	size_t j;
	do
	{
		name = p;
		no_spaces = 60 - strlen(name);
		fprintf(out, "\t%s", name);
		for(j=0;j<no_spaces;++j)
			fprintf(out, " ");

		fprintf(out," = %d,\n", index);
		p--;
		index++;
		reverse_pointer_back_to_string(&p, "SPELL_FAILED");
	}while(strcmp(name, "SPELL_FAILED_UNKNOWN"));

	name = "SPELL_CANCAST_OK";
	no_spaces = 60 - strlen(name);
	fprintf(out, "\t%s", name);
	for(j=0;j<no_spaces;++j)
		fprintf(out, " ");

	fprintf(out," = %d,\n", 255);

	fprintf(out, "};\n\n#endif\n\n");
	fclose(out);
	fclose(in);
	free(buffer);

	printf("\nDone.\n");

	return 0;
}

