//------------------------------------------------------------------------------
//  Main.cpp
//  (C) 2016 n.lee
//------------------------------------------------------------------------------
#include <stdlib.h>
#include <tchar.h>
#include <string.h>
#include <Ole2.h>
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "UsingBase.h"
#include "crash_reporter/win/crash_service_main.h"
#include "base/logging.h"

#ifdef _MSC_VER
# ifdef _DEBUG
#  include <vld.h>
# endif
#endif

// hide console window
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

#ifdef _MSC_VER
#ifdef _DEBUG
#define new   new(_NORMAL_BLOCK, __FILE__,__LINE__)
#endif	
#endif

static void
on_exit(void* /*unused*/) {
	base::clear_at_exit();
}

//////////////////////////////////////////////////////////////////////////
/// main
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {
	// enable memLeak check
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(5069);

	::OleInitialize(nullptr);
	{
		base::AtExitManager at_exit_manager;
		base::CommandLine::Init(argc, argv);
		base::AtExitManager::RegisterCallback(on_exit, nullptr);

		//
		const std::wstring cmd_line;
		crash_service::Main(cmd_line.c_str());
	}
	::OleUninitialize();
}

/** -- EOF -- **/