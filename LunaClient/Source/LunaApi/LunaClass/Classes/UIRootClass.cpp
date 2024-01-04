#include "stdafx.h"
#include "UIRootClass.h"

#include "LunaApi/LunaIO/LunaIO.h"
#include "LunaApi/LunaUtil/LunaUtil.h"
#include "PvZ/UIElement.h"
#include "Luna.h"

#include "LunaBase.h"
#include "UIContainerClass.h"

using namespace Luna::Class;
using namespace Fields;

LunaClass* LunaUIRoot::Source = new LunaClass();
int LunaUIRoot::Init(lua_State* L)
{
	Source->AllowsInjection = true;
	Source->SetName("UIRoot");
	Source->AddSubClass("UIBase");
	Source->AddSubClass("UIManager");
	Source->Inherit(LunaUIContainer::Source);

	return 0;
}