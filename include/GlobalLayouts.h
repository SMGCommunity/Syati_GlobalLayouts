#pragma once

#include "Game/Screen/LayoutActor.h"
#include "Game/System/NerveExecutor.h"

namespace {
    template<typename T>
    LayoutActor* createExtLayout(const char* pName) {
        return new T(pName);
    }
    typedef LayoutActor* (CreateLayoutFunc)(const char*);

    struct CreateLayoutEntry {
        const char* pActorName;
        const char* pLayoutPath;
        CreateLayoutFunc* mCreationFunc;
    };

    class GlobalLayoutHolder
    {
    public:
        GlobalLayoutHolder();

        LayoutActor** mLayouts;
        s32 mNum;
    };
};