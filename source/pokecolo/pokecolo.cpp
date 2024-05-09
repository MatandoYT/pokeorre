using namespace pokecolo;

void mainAntiActionReplay(void)
{
  uint uVar1;
  int *piVar2;
  
  if (DAT_804ea8cc == 0) {
    uVar1 = 0;
    piVar2 = &_clearAddress;
    do {
      Runtime.PPCEABI.H::memset
                ((void *)(*piVar2 + -0x7fffffeb),0,(piVar2[1] + 0x16) - (*piVar2 + 0x15));
      piVar2 = piVar2 + 2;
      uVar1 = uVar1 + 2;
    } while (uVar1 < 0x20);
    Runtime.PPCEABI.H::memset((void *)((int)&DAT_80001800 + 1),0,0x17ff);
    DAT_804ea8cc = 100;
  }
  DAT_804ea8cc = DAT_804ea8cc + -1;
  return;
}

void pokecolo::pokecoloInitRomVersion(void)
{
  _RomVer = 0;
  return;
}

int pokecolo::pokecoloGetLanguage(void)
{
  if (fade::_fadeWork != 0) {
    return fade::_fadeWork;
  }
  return 2;
}

void pokecolo::pokecoloCheckDiskTray(void)
{
  char menuStatus;
  int driveStatus;
  
  menuStatus = menu::menuIsCheck();
  if (menuStatus == NULL) {
    driveStatus = GSfsys::GSfsysGetDriveStatus();
    if ((driveStatus == 0xb) || (((driveStatus < 0xb && (driveStatus < 7)) && (2 < driveStatus)))) {
      menuStatus = pause::pauseIsPause();
      if (menuStatus == NULL) {
        pause::pauseOn();
      }
    }
    else {
      menuStatus = pause::pauseIsPause();
      if (menuStatus != NULL) {
        pause::pauseOff();
      }
    }
  }
  else {
    menuStatus = pause::pauseIsPause();
    if (menuStatus == NULL) {
      pause::pauseOn();
    }
  }
  return;
}

double pokecolo::pokecoloGetFrameTime(void)
{
  double dVar1;
  
  dVar1 = (double)Runtime.PPCEABI.H::__cvt_ull_flt();
  return (double)(float)((double)(float)(dVar1 / (double)FLOAT_804ec538) / (double)FLOAT_804ec538);
}

u32 pokecolo::pokecoloGetRomVersion(void)
{
  return _RomVer;
}

double pokecolo::pokecoloGetPlayTime(void)
{
  int savPlayTime;
  double playTime;
  
  savPlayTime = _getSaveSystemDataPtr();
  playTime = DOUBLE_804ec528;
  if (savPlayTime != 0) {
    playTime = (double)gamedata::gamedatasaveBiosGetPlaytime();
  }
  return playTime;
}

void pokecoloMain(void)
{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  
  GSgfxM::GSgfxRelocToScratch();
  pokecoloFrameCounter = 0;
  if (DAT_80312048 == 1) {
    GSgfxM::GSgfxPerfbarSetRenderMode();
  }
  else if (DAT_80312048 < 1) {
    if (-1 < DAT_80312048) {
      GSgfxM::GSgfxPerfbarSetRenderMode();
    }
  }
  else if (DAT_80312048 < 3) {
    GSgfxM::GSgfxPerfbarSetRenderMode();
  }
  GSthread::GSthreadInit();
  zz_005c068_(2);
  bVar1 = false;
  uVar2 = _pokecoloCheckExDisc();
  if (uVar2 == 1) {
    iVar3 = os::OSGetProgressiveMode();
    if (iVar3 == 1) {
      bVar1 = true;
    }
  }
  else {
    iVar3 = os::OSGetProgressiveMode();
    if ((iVar3 == 1) && (uVar2 = os::OSGetResetCode(), (uVar2 & 0x80000000) != 0)) {
      bVar1 = true;
    }
  }
  if (bVar1) {
    GSgfxM::GSgfxVideoSetMode();
  }
  pause::pauseInit();
  GStexture::GStextureInit(0x10);
  GSmodel::GSmodelInit();
  GSpart::GSpartInit(8);
  GSmaterial::GSmaterialInit();
  GScamera::GScameraInit(0x20);
  GSlight::GSlightInit(0x20);
  GSshape::shapeInit(0x20);
  GSparticle::GSparticleInit(0x20);
  GSinput::GSinputInit();
  iVar3 = 1;
  do {
    GSinput::GSinputOpen(iVar3);
    GSinput::GSinputSetClamping(iVar3,2);
    GSinput::GSinputSetSmoothingRate(iVar3,7);
    GSinput::GSinputSetSmoothingFunc(iVar3,1);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 5);
  GSgapp::GSgappInit(0x14,4);
  GSres::GSresInit(0x15e);
  floor::GSfloorInit((EVP_PKEY_CTX *)0x4);
  GScolsys::GScolsys2Init();
  GSmsg::GSmsgInit(2,5);
  GSmsg::GSmsgSetCtrlFunc(&msgctrl::msgcrtlcode);
  GSnetwork::GSnetworkInit();
  GSmsg::GSmsgFontOpen((short *)&resident_fnt$2161);
  GSmsg::GSmsgFontOpen((short *)&common_fnt$2162);
  GSmsg::GSmsgOpen(-0x7fc88040);
  GSmsg::GSmsgFontOpen((short *)&debug_menu_fnt$2163);
  GSmsg::GSmsgOpen(-0x7fc70784);
  GSmsg::GSmsgFontOpen((short *)&system_error_fnt$2165);
  GSmsg::GSmsgOpen(-0x7fc70420);
  GSdvd::GSdvdSetErrorMsg(0x65,0x66,0x67,0x68,0x69);
  GSvtr::GSvtrInit();
  GSlensFlare::GSlensFlareInit();
  GSmovie::GSmovieInit();
  menu::menuInit();
  GSgfxM::GSgfxVideoSetLockFrameRate(0);
  GSgfxM::GSgfxVideoSetLockFrameActive(1);
  pokecoloGappRenderHandle = GSgapp::GSgappCreate((int *)0x1,0xff,(int *)0x0,(int *)_mainRender);
  GSgapp::GSgappSetName(pokecoloGappRenderHandle,s_Render_804ec53c);
  pokecoloGappPadReadHandle = GSgapp::GSgappCreate((int *)0x1,0,(int *)0x0,(int *)_mainPadRead);
  GSgapp::GSgappSetName(pokecoloGappPadReadHandle,s_PADRead_804ec544);
  pokecoloGappGBAReadHandle = GSgapp::GSgappCreate((int *)0x1,1,(int *)0x0,(int *)_mainGBARead);
  GSgapp::GSgappSetName(pokecoloGappGBAReadHandle,s_GBARead_804ec54c);
  pokecoloGappThreadHandle = GSgapp::GSgappCreate((int *)0x1,10,(int *)0x0,(int *)_mainThreadExec);
  GSgapp::GSgappSetName(pokecoloGappThreadHandle,s_mainThread_802eb1e8);
  GSgapp::GSgappSetPauseLevel(pokecoloGappThreadHandle,1);
  GSvtr::GSvtrRegisterGSgapp(pokecoloGappThreadHandle);
  pokecoloGappAntiActionReplayHandle =
       GSgapp::GSgappCreate((int *)0x1,0xfd,(int *)0x0,(int *)mainAntiActionReplay);
  GSgapp::GSgappSetName(pokecoloGappAntiActionReplayHandle,s_AntiActionReplay_802eb1f4);
  pokecoloGappMainDeamonHandle = GSgapp::GSgappCreate((int *)0x1,0xfe,(int *)0x0,(int *)_mainDaemon)
  ;
  GSgapp::GSgappSetName(pokecoloGappMainDeamonHandle,s_mainDeamon_802eb208);
  GSgfxM::GSgfxResetEnable();
  GSgfxM::GSgfxResetSetShutdownCallback(0x8005c6fc);
  fade::fadeInit();
  GSfilter::GSfilterInitialise(8);
  GSeffect::GSeffectInitSystem();
  deck::deckInit();
  GSthread::GSthreadCreate(0,1000,0x4000,'\x01',1,_pokecoloInit);
  os::OSGetTime();
  do {
    GSgapp::GSgappUpdate();
    pokecoloCheckDiskTray();
    os::OSGetTime();
    uVar4 = Runtime.PPCEABI.H::__div2u();
    _frameTime = (undefined4)((ulonglong)uVar4 >> 0x20);
    DAT_804ea89c = (undefined4)uVar4;
    os::OSGetTime();
    pokecoloFrameCounter = pokecoloFrameCounter + 1;
  } while( true );
}