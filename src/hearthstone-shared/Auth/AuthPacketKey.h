#ifndef AUTH_PACKET_KEY_H
#define AUTH_PACKET_KEY_H

#include "Common.h"
#include "Sha1.h"

class AuthenticationPacketKey
{
public:
	HEARTHSTONE_INLINE uint8* GenerateKey(const uint8 SeedKeyLen, uint8* SeedKey, uint8 *sessionkey)
	{
		uint8 firstBuffer[64];
		uint8 secondBuffer[64];

		memset(firstBuffer, 0x36, 64);
		memset(secondBuffer, 0x5C, 64);

		for(uint8 i = 0; i < SeedKeyLen; ++i)
		{
			firstBuffer[i] = (uint8)(SeedKey[i] ^ firstBuffer[i]);
			secondBuffer[i] = (uint8)(SeedKey[i] ^ secondBuffer[i]);
		}

		Sha1Hash sha1;
		sha1.UpdateData(firstBuffer, 64);
		sha1.UpdateData(sessionkey, 40);
		sha1.Finalize();

		uint8 *tempDigest = sha1.GetDigest();
		Sha1Hash sha2;
		sha2.UpdateData(secondBuffer, 64);
		sha2.UpdateData(tempDigest, 20);
		sha2.Finalize();

		return sha2.GetDigest();
	}
};

#endif
