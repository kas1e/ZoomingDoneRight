
/*
**	Events handling functions.
**
*/

#include "includes.h"
#include "globals.h"

void Events(void)
{
	ULONG		wait = 0,
				bufsig = (1L << buffPort->mp_SigBit),
				winsig = (1L << winPort->mp_SigBit);

	ULONG		done = FALSE;

				

	do
	{
		if ( wait & SIGBREAKF_CTRL_C )
		{
			done = TRUE;
		}
		if ( wait & winsig )
		{
			done = controlIDCMP();
		}
		if ( wait & bufsig )
		{
			struct Message *dbmsg;
			while (( dbmsg = IExec->GetMsg( buffPort ) ))
			{
				handleDBufMessage( dbmsg );
			}

		}
		if(!done)
		{
			ULONG held_off = 0;
			held_off = DrawGrid();
			Displacement();
			if(steps >20 && camera.z >=0.99)
			{
				if(pantalla.scr)	IIntuition->ScreenToFront(pantalla.scr);
				done = TRUE;
			}

			if ( held_off )
			{
				IGraphics->WaitTOF();
			}
			else
			{
				wait = IExec->Wait( SIGBREAKF_CTRL_C | bufsig | winsig);	
			}
		}	

	}while(!done);
}
