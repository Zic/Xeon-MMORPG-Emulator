/*
* Vindaire IRC Bot
* Copyright (C) 2008 Valroft <http://www.aspiredev.org/>
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

#ifndef _FIELD_H
#define _FIELD_H

#include "StdAfx.h"

class Field
{
public:

	void SetValue(char* value) { mValue = value; }

	const char *GetString() { return mValue; }
	float GetFloat() { return mValue ? static_cast<float>(atof(mValue)) : 0; }
	bool GetBool() { return mValue ? atoi(mValue) > 0 : false; }
	uint8 GetUInt8() { return mValue ? static_cast<uint8>(atol(mValue)) : 0; }
	int8 GetInt8() { return mValue ? static_cast<int8>(atol(mValue)) : 0; }
	uint16 GetUInt16() { return mValue ? static_cast<uint16>(atol(mValue)) : 0; }
	uint32 GetUInt32() { return mValue ? static_cast<uint32>(atol(mValue)) : 0; }
	uint32 GetInt32() { return mValue ? static_cast<int32>(atol(mValue)) : 0; }
	uint64 GetUInt64() 
	{
		if(mValue)
		{
			uint64 value;
			sscanf(mValue,I64FMTD,&value);
			return value;
		}
		else
			return 0;
	}

private:
	char *mValue;
};

#endif