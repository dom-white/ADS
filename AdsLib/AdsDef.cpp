#include "AdsDef.h"

#include <cstring>
#include <ostream>
#include <sstream>

bool operator <(const AmsNetId_& lhs, const AmsNetId_& rhs)
{
	for (unsigned int i = 0; i < sizeof(rhs.b); ++i) {
		if (lhs.b[i] != rhs.b[i]) {
			return lhs.b[i] < rhs.b[i];
		}
	}
	return false;
}

bool operator <(const AmsAddr_& lhs, const AmsAddr_& rhs)
{
	if (memcmp(&lhs.netId, &rhs.netId, sizeof(lhs.netId))) {
		return lhs.netId < rhs.netId;
	}
	return lhs.port < rhs.port;
}

std::ostream& operator<<(std::ostream& os, const AmsNetId_& netId)
{
    return os << (int)netId.b[0] << '.' << (int)netId.b[1] << '.' << (int)netId.b[2] << '.'
        << (int)netId.b[3] << '.' << (int)netId.b[4] << '.' << (int)netId.b[5];
}

AmsNetId_::AmsNetId_(uint32_t ipv4Addr)
{
    b[5] = 1;
    b[4] = 1;
    b[3] = (uint8_t)(ipv4Addr & 0x000000ff);
    b[2] = (uint8_t)((ipv4Addr & 0x0000ff00) >> 8);
    b[1] = (uint8_t)((ipv4Addr & 0x00ff0000) >> 16);
    b[0] = (uint8_t)((ipv4Addr & 0xff000000) >> 24);
}

AmsNetId_::AmsNetId_(uint8_t id_0, uint8_t id_1, uint8_t id_2, uint8_t id_3, uint8_t id_4, uint8_t id_5)
{
	b[5] = id_5;
	b[4] = id_4;
	b[3] = id_3;
	b[2] = id_2;
	b[1] = id_1;
	b[0] = id_0;
}

AmsNetId_::AmsNetId_(const std::string &addr)
{
    std::istringstream iss(addr);
    std::string s;
    size_t i = 0;

    while ((i < sizeof(b)) && std::getline(iss, s, '.')) {
        b[i] = atoi(s.c_str()) % 256;
        ++i;
    }

    if (i != sizeof(b)) {
        memset(b, 0, sizeof(b));
    }
}

AmsNetId_::operator bool() const
{
    static const AmsNetId empty{};
    return 0 != memcmp(b, &empty.b, sizeof(b));
}