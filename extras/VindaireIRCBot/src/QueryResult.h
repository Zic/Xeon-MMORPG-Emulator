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

#ifndef _QUERY_RESULT_H
#define _QUERY_RESULT_H

#include "StdAfx.h"

class Field;

class QueryResult
{
public:
	QueryResult(MYSQL_RES * res, uint32 uFields, uint32 uRows);
	~QueryResult();
	bool NextRow();
	Field* Fetch() { return mCurrentRow; }

	uint32 GetAffectedFields() { return mFields; }
	uint32 GetAffectedRows() { return mRows; }

protected:
	MYSQL_RES * m_res;
	Field *mCurrentRow;
	uint32 mFields;
	uint32 mRows;
};

#endif