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

#include "WowCrypt.h"
#include <algorithm>

WowCrypt::WowCrypt()
{
	_initialized = false;
}

void WowCrypt::Init(uint8 *K)
{
	const uint8 SeedKeyLen = 16;
    uint8 ServerEncryptionKey[SeedKeyLen] = { 0x22, 0xBE, 0xE5, 0xCF, 0xBB, 0x07, 0x64, 0xD9, 0x00, 0x45, 0x1B, 0xD0, 0x24, 0xB8, 0xD5, 0x45 };

	AuthenticationPacketKey auth;
	uint8 *encryptHash = auth.GenerateKey(SeedKeyLen, (uint8*)ServerEncryptionKey, K);

    uint8 ServerDecryptionKey[SeedKeyLen] = { 0xF4, 0x66, 0x31, 0x59, 0xFC, 0x83, 0x6E, 0x31, 0x31, 0x02, 0x51, 0xD5, 0x44, 0x31, 0x67, 0x98 };
    uint8 *decryptHash = auth.GenerateKey(SeedKeyLen, (uint8*)ServerDecryptionKey, K);

    _Decrypt.Init((uint8*)decryptHash);
    _Encrypt.Init((uint8*)encryptHash);

    uint8 decryptRotateBuffer[1024];
	memset(decryptRotateBuffer, 0, 1024);
	_Decrypt.UpdateData(1024, (uint8*)decryptRotateBuffer);

	uint8 encryptRotateBuffer[1024];
    memset(encryptRotateBuffer, 0, 1024);
	_Encrypt.UpdateData(1024, (uint8*)encryptRotateBuffer);
   

    _initialized = true;
}

void WowCrypt::DecryptRecv(uint8 *data, size_t len)
{
    if (!_initialized)
        return;

    _Decrypt.UpdateData(len, (uint8*)data);
}

void WowCrypt::EncryptSend(uint8 *data, size_t len)
{
    if (!_initialized)
        return;

    _Encrypt.UpdateData(len, (uint8*)data);
}

WowCrypt::~WowCrypt()
{
}
