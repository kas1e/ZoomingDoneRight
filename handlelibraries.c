/*
**	library stuff
*/

#include "includes.h"
#include "globals.h"

void OpenLibs()
{
	
	if ((IntuitionBase = IExec->OpenLibrary("intuition.library",53L)))
	{
		IIntuition = (struct IntuitionIFace *) IExec->GetInterface(IntuitionBase,"main",1,NULL);
		if (!IIntuition)	CleanExit("Can't open intuition.library Interface");
	}
	else CleanExit("Can't open intuition.library");

	if ((IconBase = IExec->OpenLibrary("icon.library",53L)))
	{
		IIcon = (struct IconIFace *) IExec->GetInterface(IconBase,"main",1,NULL);
		if (!IIcon)	CleanExit("Can't open icon.library Interface");
	}
	else CleanExit("Can't open icon.library");
		
	if ((GraphicsBase = IExec->OpenLibrary("graphics.library",53L)))
	{
		IGraphics = (struct GraphicsIFace *) IExec->GetInterface(GraphicsBase,"main",1,NULL);
		if (!IGraphics)	CleanExit("Can't open graphics.library Interface");
	}
	else CleanExit("Can't open graphics.library");

	if((ApplicationBase = IExec->OpenLibrary("application.library", 51L)))
	{
		IApplication = (struct ApplicationIFace *) IExec->GetInterface(ApplicationBase,"application",2,NULL);
		if(!IApplication)	CleanExit((STRPTR)"Can't open application.library Interface");
 	}
	if ((UtilityBase = IExec->OpenLibrary("utility.library",53L)))
	{
		IUtility = (struct UtilityIFace *) IExec->GetInterface(UtilityBase,"main",1,NULL);
		if (!IUtility)	CleanExit("Can't open utility.library Interface");
	}
	else CleanExit("Can't open utility.library");
	if ((P96Base = IExec->OpenLibrary("Picasso96API.library",2)))
	{
		IP96= (struct P96IFace *) IExec->GetInterface(P96Base,"main",1,NULL);
		if (!IP96)	CleanExit("Can't open Picasso96API.library Interface");
	}
	else CleanExit("Can't open Picasso96API.library");
}

void CleanExit(CONST_STRPTR str)
{
	if (strcmp(str,"JustExit")) IDOS->Printf("Error: :%s\n",str);


	if(win)			IIntuition->CloseWindow(win);
	if(scr)
	{
		IIntuition->FreeScreenBuffer(scr,scbuf[0]);
		IIntuition->FreeScreenBuffer(scr,scbuf[1]);
		IIntuition->CloseScreen(scr);
	}
	if(lens)			IGraphics->FreeBitMap(lens);
	if(pantalla.scr)	IIntuition->UnlockPubScreen(NULL, pantalla.scr);

	if(buffPort)		IExec->FreeSysObject(ASOT_PORT,buffPort);
	if(winPort)			IExec->FreeSysObject(ASOT_PORT, winPort);

	if (AppID)			IApplication->UnregisterApplication(AppID, NULL);

	if (IUtility)			IExec->DropInterface((struct Interface *)IUtility);
	if (IGraphics)		IExec->DropInterface((struct Interface *)IGraphics);
	if (IIcon)		IExec->DropInterface((struct Interface *)IIcon);
	if (IIntuition)		IExec->DropInterface((struct Interface *)IIntuition);
	if(IApplication)		IExec->DropInterface((struct Interface *)IApplication);
	if(IP96)			IExec->DropInterface((struct Interface *)IP96);

	if (UtilityBase)		IExec->CloseLibrary(UtilityBase);
	if (GraphicsBase)	IExec->CloseLibrary(GraphicsBase);
	if (IconBase)	IExec->CloseLibrary(IconBase);
	if (IntuitionBase)	IExec->CloseLibrary(IntuitionBase);
	if(ApplicationBase)	IExec->CloseLibrary(ApplicationBase);
	if(P96Base)	IExec->CloseLibrary(P96Base);


	exit(0);
}
