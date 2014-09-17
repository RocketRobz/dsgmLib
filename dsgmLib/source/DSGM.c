#include "DSGM.h"

void DSGM_Debug(char *text, ...) {
	#ifdef DEBUG
		char buff[1024];
		va_list args;
		va_start(args, text);
		vsprintf(buff, text, args);
		va_end(args);
		nocashMessage(buff);
		while(!DSGM_newpress.Start) DSGM_UpdateInput();
		while(DSGM_newpress.Start) DSGM_UpdateInput();
	#endif
}

void DSGM_Log(bool wait, char *text, ...) {
	char buff[1024];
	va_list args;
	va_start(args, text);
	vsprintf(buff, text, args);
	va_end(args);
	nocashMessage(buff);
	if(wait) {
		while(!DSGM_newpress.Start) DSGM_UpdateInput();
		while(DSGM_newpress.Start) DSGM_UpdateInput();
	}
}

void DSGM_InitGFX(void) {
	videoSetMode(MODE_0_2D);
	videoSetModeSub(MODE_0_2D);
	
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	vramSetBankG(VRAM_G_LCD);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
	
	bgExtPaletteEnable();
	bgExtPaletteEnableSub();
	
	oamInit(&oamMain, SpriteMapping_1D_128, true);
	oamInit(&oamSub, SpriteMapping_1D_128, true);
}

// If you need anything more custom than this, you're going to have to write it yourself
void DSGM_InitCustomGFX(bool topScreenDrawable, bool bottomScreenDrawable) {
	if(topScreenDrawable) videoSetMode(MODE_3_2D);
	else videoSetMode(MODE_0_2D);
	if(bottomScreenDrawable) videoSetModeSub(MODE_3_2D);
	else videoSetModeSub(MODE_0_2D);
	
	vramSetBankA(VRAM_A_MAIN_BG_0x06000000);
	vramSetBankB(VRAM_B_MAIN_SPRITE_0x06400000);
	vramSetBankC(VRAM_C_SUB_BG_0x06200000);
	vramSetBankD(VRAM_D_SUB_SPRITE);
	vramSetBankE(VRAM_E_BG_EXT_PALETTE);
	vramSetBankF(VRAM_F_SPRITE_EXT_PALETTE);
	vramSetBankG(VRAM_G_LCD);
	vramSetBankH(VRAM_H_SUB_BG_EXT_PALETTE);
	vramSetBankI(VRAM_I_SUB_SPRITE_EXT_PALETTE);
	
	bgExtPaletteEnable();
	bgExtPaletteEnableSub();
	
	oamInit(&oamMain, SpriteMapping_1D_128, true);
	oamInit(&oamSub, SpriteMapping_1D_128, true);
}

void DSGM_InitRand(void) {
	srand(time(NULL));
}

void DSGM_InitNitro(void) {
	if(!nitroFSInit(NULL)) {
		DSGM_Debug("NitroFS failed");
	}
	chdir("nitro:/");
}

void DSGM_Update(void) {
	DSGM_UpdateInput();
	
	swiWaitForVBlank();
	
	bgUpdate();
	
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
}
