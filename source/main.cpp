#include <gctypes.h>

#define RETAIL_MEM_SIZE	0x1800000
#define MEM_SIZE_DEBUG	0x18
#define MEM_SIZE_DEV	0x30

void main()
{
	u32 memSize;
	void *pArenaHi;

	pokecolo::pokecoloInitRomVersion();
	Runtime.PPCEABI.H::memset(&DAT_80001800,0,0x1800);
	sysvars::sysvarsReadSettings();
	memsize = os::OSGetConsoleSimulatedMemSize();

	if (RETAIL_MEM_SIZE < memsize) {
		if (DAT_80312044 == MEM_SIZE_DEBUG) {
			os::OSSetArenaHi((void *)0x817ed780);
		}
		else if (DAT_80312044 == MEM_SIZE_DEV) {
			os::OSSetArenaHi((void *)0x82ded720);
		}
	}

	os::OSGetArenaLo();
	os::OSGetArenaHi();
	os::OSGetArenaHi();
	pArenaHi = (void *)GSmemman::GSmemInit();
	os::OSSetArenaLo(pArenaHi);
	GSfsys::GSfsysCreateLocalHeap();
	GSfsys::GSfsysCreateCacheHeap();
	floor::floorCreateLocalHeap();
	os::OSGetArenaLo();
	pArenaHi = os::OSGetArenaHi();
	g_hFloorHeap = GSmemman::GSmemCreateHeap();
	GSmemman::GSmemSetCurrentHeap();
	os::OSSetArenaLo(pArenaHi);
	g_hSysdolphineHeap = g_hFloorHeap;
	GSmemman::GSmemInitSysdolAllocator();
	zz_game_get_region();
	GSgfxM::GSgfxInit();

	if (sysvars::systemVars == 1) {
		sysvars::sysvarsShowDebug();
	}

	ar::ARInit((u32 *)&aramMemArray,2);
	ar::ARQInit();
	ai::AIInit(NULL);
	ar::ARQSetChunkSize(0x8000);
	GSlogM::GSlogInit();
	GSscratch::GSscratchInit();
	GSdvd::GSdvdSetDVDServer();
	GSdvd::GSdvdSetReportServer();
	GSdvd::GSdvdSetGCClient();
	pokecolo::pokecoloMain();
	return;
}