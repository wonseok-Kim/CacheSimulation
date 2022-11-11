#pragma once

#include <assert.h>
#include <basetsd.h>

static constexpr UINT_PTR TAG_MASK = ~(UINT_PTR)0xfff;
static constexpr UINT_PTR INDEX_MASK = (UINT_PTR)0xfc0;

inline UINT_PTR GetTag(void* addr)
{
    return ((UINT_PTR)addr & TAG_MASK) >> 12;
}

inline UINT_PTR GetIndex(void* addr)
{
    return ((UINT_PTR)addr & INDEX_MASK) >> 6;
}

class CacheEntry
{
public:
    CacheEntry(void* lineAddress)
        : m_StartAddress{ (UINT_PTR)lineAddress & ~(UINT_PTR)0x3f }
    {         
    }

    bool IsIncluding(void* addr)
    {
        assert(GetIndex(addr) == GetIndex((void*)m_StartAddress));

        UINT_PTR tag1 = GetTag((void*)m_StartAddress);
        UINT_PTR tag2 = GetTag(addr);

        return tag1 == tag2;
    }

private:
    UINT_PTR m_StartAddress;
};
