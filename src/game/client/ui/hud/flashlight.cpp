/***
 *
 *	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
 *
 *	This product contains software technology licensed from Id
 *	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
 *	All Rights Reserved.
 *
 *   Use, distribution, and modification of this source code and/or resulting
 *   object code is restricted to non-commercial enhancements to products from
 *   Valve LLC.  All other use, distribution, or modification is prohibited
 *   without written permission from Valve LLC.
 *
 ****/
//
// flashlight.cpp
//
// implementation of CHudFlashlight class
//

#include "hud.h"

// Half-Life: Unified SDK - Vanilla branch notice - START
//
// Opposing Force's nightvision does not uses a "beam" sprite like Half-Life's flashlight does.
// In the original SDK, the "LightData" setup and "CHudFlashlight::Draw" code have checks for the presence of said beam.
// Now that Opposing Force's nightvision is gone and that the flashlight does have a beam sprite, those "if" checks are
// useless and thus have been disabled for micro-optimisation purposes.
//
// If you want to restore the original SDK beam checks OR you are going to implement a new "LightData" that does not have
// a beam sprite, simply comment this define to restore those "if" checks to prevent crashes.
// If you want to keep that micro-optimisation and not implement a new "LightData" that does not have a beam sprite, leave
// it commented.
//
// Half-Life: Unified SDK - Vanilla branch notice - END
#define NO_FLASHLIGHT_BEAM_CHECKS

bool CHudFlashlight::Init()
{
	m_fFade = 0;
	m_fOn = false;

	g_ClientUserMessages.RegisterHandler("Flashlight", &CHudFlashlight::MsgFunc_Flashlight, this);
	g_ClientUserMessages.RegisterHandler("FlashBat", &CHudFlashlight::MsgFunc_FlashBat, this);

	m_iFlags |= HUD_ACTIVE;

	gHUD.AddHudElem(this);

	return true;
}

void CHudFlashlight::Reset()
{
	m_fFade = 0;
	m_fOn = false;
}

bool CHudFlashlight::VidInit()
{
	auto setup = [](const char* empty, const char* full, const char* beam)
	{
		const int HUD_flash_empty = gHUD.GetSpriteIndex(empty);
		const int HUD_flash_full = gHUD.GetSpriteIndex(full);

		LightData data;

		data.m_hSprite1 = gHUD.GetSprite(HUD_flash_empty);
		data.m_hSprite2 = gHUD.GetSprite(HUD_flash_full);
		data.m_prc1 = &gHUD.GetSpriteRect(HUD_flash_empty);
		data.m_prc2 = &gHUD.GetSpriteRect(HUD_flash_full);

#ifndef NO_FLASHLIGHT_BEAM_CHECKS
		if (beam)
		{
#endif
			const int HUD_flash_beam = gHUD.GetSpriteIndex(beam);
			data.m_hBeam = gHUD.GetSprite(HUD_flash_beam);
			data.m_prcBeam = &gHUD.GetSpriteRect(HUD_flash_beam);
#ifndef NO_FLASHLIGHT_BEAM_CHECKS
		}
#endif

		data.m_iWidth = data.m_prc2->right - data.m_prc2->left;

		return data;
	};

	m_Flashlight = setup("flash_empty", "flash_full", "flash_beam");
	return true;
}

void CHudFlashlight::MsgFunc_FlashBat(const char* pszName, BufferReader& reader)
{
	int x = reader.ReadByte();
	m_iBat = x;
	m_flBat = ((float)x) / 100.0;
}

void CHudFlashlight::MsgFunc_Flashlight(const char* pszName, BufferReader& reader)
{
	m_fOn = 0 != reader.ReadByte();
	int x = reader.ReadByte();
	m_iBat = x;
	m_flBat = ((float)x) / 100.0;

}

bool CHudFlashlight::Draw(float flTime)
{
	if ((gHUD.m_iHideHUDDisplay & (HIDEHUD_FLASHLIGHT | HIDEHUD_ALL)) != 0)
		return true;

	int x, y;
	Rect rc;

	if (!gHUD.HasSuit())
		return true;

	const int a = m_fOn ? 225 : MIN_ALPHA;

	const auto& originalColor = m_flBat < 0.20 ? RGB_REDISH : gHUD.m_HudItemColor;

	const auto color = originalColor.Scale(a);

	auto data = GetLightData();

	y = (data->m_prc1->bottom - data->m_prc2->top) / 2;
	x = ScreenWidth - data->m_iWidth - data->m_iWidth / 2;

	// Draw the flashlight casing
	SPR_Set(data->m_hSprite1, color);
	SPR_DrawAdditive(0, x, y, data->m_prc1);

	if (m_fOn)
	{ // draw the flashlight beam
		x = ScreenWidth - data->m_iWidth / 2;

#ifndef NO_FLASHLIGHT_BEAM_CHECKS
		if (data->m_hBeam != 0)
		{
#endif
			SPR_Set(data->m_hBeam, color);
			SPR_DrawAdditive(0, x, y, data->m_prcBeam);
#ifndef NO_FLASHLIGHT_BEAM_CHECKS
		}
#endif
	}

	// draw the flashlight energy level
	x = ScreenWidth - data->m_iWidth - data->m_iWidth / 2;
	int iOffset = data->m_iWidth * (1.0 - m_flBat);
	if (iOffset < data->m_iWidth)
	{
		rc = *data->m_prc2;
		rc.left += iOffset;

		SPR_Set(data->m_hSprite2, color);
		SPR_DrawAdditive(0, x + iOffset, y, &rc);
	}


	return true;
}
