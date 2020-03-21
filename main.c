/*
**	Main function 
*/

#include "includes.h"
#include "globals.h"

const char *version = "$VER:  "PROGNAME" "VERSION"."REVISION" (05.02.14)©2014,"DEVELOPER"\n\0";

int main( void )
{
	ULONG result=0;
	camera.z = 1.0;
	camera.x = 0.0;
	camera.y = 0.0;
	delay = 0;
	zwheel =0;
	Clicked = FALSE;
	LensFlag =TRUE;
	Filter = TRUE;
	steps = 0;
	struct BitMap *lensb;
	if((buffPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE))&&(winPort =IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE)))
	{
		OpenLibs();
		AppRegistering();
		if((IDOS->Cli())== NULL)
		{
			IDOS->Printf("This program not to be run from Workbench\n");
			CleanExit("JustExit");
		}

		result = LockScreens();
		if(result ==0) CleanExit("JustExit");
		if ((scr = IIntuition->OpenScreenTags(NULL,
					SA_DisplayID,ID,
					SA_Width,Resolution.Width,
					SA_Height,Resolution.Height,
					SA_LikeWorkbench,TRUE,
					SA_ShowTitle, FALSE,
					TAG_DONE)))
		{
	if ((doicon = IIcon->GetIconTags("Sys:Utilities/Multiview",
		ICONGETA_Screen,scr,
		ICONGETA_GenerateImageMasks,TRUE,	
		TAG_DONE)))
	{
		result =IIcon->IconControl(doicon,
								ICONCTRLA_GetBitMap1,&lensb,
								ICONCTRLA_GetImageMask1,&lensalpha,
								ICONCTRLA_GetWidth,&ow,
								ICONCTRLA_GetHeight,&oh,
								ICONCTRLA_SetGlobalScreen,scr,
								ICONCTRLA_SetGlobalPrecision,PRECISION_EXACT,
								TAG_DONE);
		if((lens = IGraphics->AllocBitMap(ow,oh,32,BMF_CLEAR | BMF_DISPLAYABLE,scr->RastPort.BitMap)))
				{
					IGraphics->BltBitMapTags(BLITA_Width, ow,
								BLITA_Height, oh,
								BLITA_Source, lensb,
								BLITA_SrcType, BLITT_BITMAP,
								BLITA_UseSrcAlpha, TRUE,
								BLITA_Dest,lens,
								BLITA_DestType, BLITT_BITMAP,
								BLITA_MaskPlane,lensalpha,
								TAG_DONE);
					IIcon->FreeDiskObject(doicon);
				}
			}

			SetDestinationOutside(scr);
			if((win = IIntuition->OpenWindowTags (NULL,
						WA_CustomScreen,scr,
						WA_NoCareRefresh, TRUE,
						WA_Activate, TRUE,
						WA_Borderless, TRUE,
						WA_ReportMouse, TRUE,
						WA_Backdrop, TRUE,
						WA_Backdrop,TRUE,
						WA_Pointer,POINTERTYPE_NONE ,
						WA_UserPort, winPort,
						WA_Flags,WFLG_ACTIVATE,
						WA_IDCMP,IDCMP_MOUSEBUTTONS| IDCMP_MOUSEMOVE |IDCMP_EXTENDEDMOUSE|IDCMP_RAWKEY,
						TAG_END)))
			{
				if ( !( scbuf[ 0 ] = IIntuition->AllocScreenBuffer( scr, NULL, SB_SCREEN_BITMAP ) ) )
				{
					CleanExit( "Couldn't allocate ScreenBuffer 1" );
				}
	
				if ( !( scbuf[ 1 ] = IIntuition->AllocScreenBuffer( scr, NULL, SB_COPY_BITMAP ) ) )
				{
					CleanExit( "Couldn't allocate ScreenBuffer 2" );
				}
				scbuf[ 0 ]->sb_DBufInfo->dbi_UserData1 = ( APTR ) ( 0 );
				scbuf[ 1 ]->sb_DBufInfo->dbi_UserData1 = ( APTR ) ( 1 );
				status[ 0 ] = OK_REDRAW;
				status[ 1 ] = OK_REDRAW;
				IGraphics->InitRastPort( &rport[0] );
				IGraphics->InitRastPort( &rport[1] );
				rport[ 0 ].BitMap = scbuf[0]->sb_BitMap;
				rport[ 1 ].BitMap = scbuf[1]->sb_BitMap;
				buf_current = 0;
				buf_nextdraw = 1;
				buf_nextswap = 1;
				Events();
			}
		}
	}
	CleanExit("JustExit");
}
