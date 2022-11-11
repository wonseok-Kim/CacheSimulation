#pragma once

#include <list>
#include <span>

#include "CacheEntry.h"

struct AccessInfo
{
    byte* Pointer;
    const char* VarName;
    const char* FileName;
    const char* FuncName;
    size_t Size;
    int Line;
};

enum class eCacheHitMissKind
{
    Hit,
    ColdMiss,
    ConflicMiss,
    CapacityMiss
};

class CacheSimulator
{
    struct CacheEntryNode
    {
        CacheEntry Entry;
        CacheEntryNode* Next;

        CacheEntryNode(byte* addr)
            : Entry{ addr }
            , Next{ nullptr }
        {
        }
    };

public:
    static CacheSimulator& GetInstance()
    {
        static CacheSimulator inst{};
        return inst;
    }

    void Simulate(const AccessInfo& info)
    {
        UINT_PTR idx = GetIndex(info.Pointer);

        int cnt = 0;
        CacheEntryNode* node = nullptr;

        for (node = m_CacheSets[idx]; node != nullptr; node = node->Next)
        {
            ++cnt;
            
            if (node->Entry.IsIncluding(info.Pointer))
            {
                if (node->Entry.IsIncluding(info.Pointer + info.Size))
                {

                }
            }
        }
        
    }

private:
    CacheSimulator() {};

private:
    CacheEntryNode* m_CacheSets[64] = { nullptr, };
};

