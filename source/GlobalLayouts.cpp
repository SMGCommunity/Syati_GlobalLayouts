#include "Game/Screen/GameSceneLayoutHolder.h"
#include "GlobalLayouts.h"
#include "ModuleData_GlobalLayouts.h"

namespace {
	GlobalLayoutHolder::GlobalLayoutHolder()
	{
		mLayouts = new LayoutActor * [cModuleCreateLayoutTableCount]; //yes I know we're wasting a perfectly good 4 bytes. Shoot me
		mNum = cModuleCreateLayoutTableCount;
		
		for (s32 i = 1; i < cModuleCreateLayoutTableCount; i++) {
			const CreateLayoutEntry entry = cModuleCreateLayoutTable[i];
			mLayouts[i] = NULL;

			if (MR::isFileExist(entry.pLayoutPath, true))
			{
				mLayouts[i] = entry.mCreationFunc(entry.pActorName);
				mLayouts[i]->initWithoutIter();
			}
		}
	}

	//Edit CounterLayoutController
	kmWrite32(0x80471780, 0x38600050); //li r3, 0x4C -> li r3, 0x50

	void createGlobalLayouts(CounterLayoutController* pLayout)
	{
		MR::connectToSceneLayout(pLayout);

		GlobalLayoutHolder* glh = new GlobalLayoutHolder();
		asm("stw %0, 0x4C(%1)" : "=r" (glh) : "=r" (pLayout));
	}

	kmCall(0x804657A0, createGlobalLayouts); //Add branch to create code
}