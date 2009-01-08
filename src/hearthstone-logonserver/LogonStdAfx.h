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

#pragma once

#include <list>
#include <vector>
#include <map>
#include <sstream>
#include <string>
//#include <fstream>

#include "Common.h"
#include <Network/Network.h>

#include "../hearthstone-shared/Log.h"
#include "../hearthstone-shared/Util.h"
#include "../hearthstone-shared/ByteBuffer.h"
#include "../hearthstone-shared/Config/ConfigEnv.h"
#include <zlib.h>

#include "../hearthstone-shared/Database/DatabaseEnv.h"
#include "../hearthstone-shared/Database/DBCStores.h"
#include "../hearthstone-shared/Database/dbcfile.h"

#include "../hearthstone-shared/Auth/BigNumber.h"
#include "../hearthstone-shared/Auth/Sha1.h"
#include "../hearthstone-shared/Auth/WowCrypt.h"
#include "../hearthstone-shared/CrashHandler.h"

#include "LogonOpcodes.h"
#include "../hearthstone-logonserver/Main.h"
#include "../hearthstone-world/NameTables.h"
#include "AccountCache.h"
#include "PeriodicFunctionCall_Thread.h"
#include "../hearthstone-logonserver/AutoPatcher.h"
#include "../hearthstone-logonserver/AuthSocket.h"
#include "../hearthstone-logonserver/AuthStructs.h"
#include "../hearthstone-logonserver/LogonOpcodes.h"
#include "../hearthstone-logonserver/LogonCommServer.h"
#include "../hearthstone-logonserver/LogonConsole.h"
#include "../hearthstone-shared/WorldPacket.h"

// database decl
extern Database* sLogonSQL;
