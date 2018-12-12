#include "stdafx.h"
#include "WinSockDeleter.h"

void app::util::WinSockDeleter::operator()(addrinfo * ptr) const
{
	if (ptr != nullptr) { freeaddrinfo(ptr); }
}

void app::util::WinSockDeleter::operator()(SOCKET * ptr) const
{
	if (ptr != nullptr) { closesocket(*ptr); }
}
