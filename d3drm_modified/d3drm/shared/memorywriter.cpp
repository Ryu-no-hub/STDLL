#include <vector>
#include "memorywriter.h"

namespace MemoryWriter {
	struct _reservedAddressSpace 
	{
		unsigned long address;
		SIZE_T length;

		_reservedAddressSpace(unsigned long x, SIZE_T y)
		{
			address = x;
			length = y;
		}
	};
	static std::vector<_reservedAddressSpace> _reservedAddressSpaces;

	bool AddressIntersects(unsigned long left, unsigned long leftSize)
	{
		for (auto it = _reservedAddressSpaces.begin(); it != _reservedAddressSpaces.end(); ++it)
		{
			unsigned long leftEnd = left + leftSize;
			unsigned long rightEnd = it->address + it->length;
			if (left < rightEnd && leftEnd > it->address /* right */)
				return true;
		}

		_reservedAddressSpaces.push_back(_reservedAddressSpace(left, leftSize));
		return false;
	}

	bool Write(unsigned long address, unsigned char* bytes, SIZE_T length, bool enforceNoIntersecting)
	{
		// Prevent intersecting detours/overwrites
		if (enforceNoIntersecting && AddressIntersects(address, length))
			return false;
	
		HANDLE currentProcess = GetCurrentProcess();
		unsigned long* addressPointer = (unsigned long*)address;

		unsigned long previousProtection = 0;
		if (VirtualProtectEx(currentProcess, addressPointer, length, PAGE_EXECUTE_READWRITE, &previousProtection) == FALSE)
			return false;

		memcpy(addressPointer, bytes, length);

		FlushInstructionCache(currentProcess, addressPointer, length); // Failing is ok...ish

		return VirtualProtectEx(currentProcess, addressPointer, length, previousProtection, &previousProtection) == TRUE;
	}
}