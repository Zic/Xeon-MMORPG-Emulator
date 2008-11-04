#ifndef __PACKETENCRYPT_H
#define __PACKETENCRYPT_H


class PacketKeyGenerator
//public ref class PacketKeyGenerator
{
public:
	uint8 *GenerateKey(uint8 *sessionKey);
};

#endif

