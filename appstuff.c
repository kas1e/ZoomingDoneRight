/*
**	Application.library housekeeping
*/

#include "includes.h"
#include "globals.h"

/*
**	Register the Application
*/


void AppRegistering( void )
{
	AppID=IApplication->RegisterApplication("ZDR", 
			REGAPP_URLIdentifier, "Ami603.es",
			REGAPP_LoadPrefs, FALSE,
			REGAPP_SavePrefs, FALSE,
		//	REGAPP_FileName,"ZDR",
			REGAPP_NoIcon,TRUE,
			REGAPP_UniqueApplication, TRUE,
			TAG_DONE);
	if (!AppID)		CleanExit((STRPTR) "JustExit");
}
