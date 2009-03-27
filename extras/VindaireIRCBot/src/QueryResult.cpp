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

#include "StdAfx.h"

QueryResult::QueryResult(MYSQL_RES * res, uint32 uFields, uint32 uRows)
{
	m_res = res;
	mFields = uFields;
	mRows = uRows;
	mCurrentRow = new Field[uFields];
}

QueryResult::~QueryResult()
{
	mysql_free_result(m_res);
	delete [] mCurrentRow;
}

bool QueryResult::NextRow()
{
	MYSQL_ROW row = mysql_fetch_row(m_res);
	if(row == NULL)
		return false;

	for(uint32 i = 0; i < mFields; ++i)
		mCurrentRow[i].SetValue(row[i]);

	return true;
}