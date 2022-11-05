#pragma once

#include <list>
#include <span>

#include "CacheEntry.h"

struct AccessInfo
{
    void* addr;
    const char* VarName;
};

enum class eCacheMissKind
{
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

        CacheEntryNode(void* addr)
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

    void Simulate(const std::initializer_list<AccessInfo>& infos, const char* file, const char* func, int line)
    {
        for (const AccessInfo& info : infos)
        {
            UINT_PTR idx = GetIndex(info.addr);
            assert(0 <= idx && idx < 64);
           
            int cnt = 0;
            CacheEntryNode* current = m_CacheSets[idx];
            CacheEntryNode* prev = nullptr;
            while (true)
            {           
                ++cnt;
                if (current->Entry.IsIncluding(info.addr))
                {
                    printf("file: %s, func: %s, line: %d, CACHE HIT!\n", file, func, line);
                    
                    prev->Next = current->Next;

                    

                    return;
                }

                if (current->Next != nullptr)
                {
                    prev = current;
                    current = current->Next;
                }
                else
                {
                    break;
                }
            }
            assert(0 <= cnt && cnt <= 8);

            if (cnt < 8)
            {

            }
        }
    }

private:
    CacheSimulator() {};

private:
    CacheEntryNode* m_CacheSets[64];
};

