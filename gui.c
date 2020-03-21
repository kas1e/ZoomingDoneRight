/*
**	Gui initialization
*/

#include "includes.h"
#include "globals.h"

/*
 *	CreateGrid - Genera una rejilla de 25 rectángulos de igual tamaño  // Comentarios de SSDR
 *		a la pantalla visible y los posiciona en un espacio tridimensional.
 *	return: sin retorno.
 */

void CreateGrid(struct Screen *scre)
{
	pantalla.st.x = 0;
	pantalla.st.y = 0;
	pantalla.st.z = 0.0;
	pantalla.nd.x = scre->Width;
	pantalla.nd.y = 0;
	pantalla.nd.z = 0.0;
	pantalla.rd.x = scre->Width;
	pantalla.rd.y = scre->Height;
	pantalla.rd.z = 0.0;
	pantalla.th.x = 0;
	pantalla.th.y = scre->Height;
	pantalla.th.z = 0.0;
	pantalla.scr = NULL;
}

/*
 *	LockScreens - Obtiene el puntero a todas las pantallas en orden hasta un máximo de 25.
 *	Si hubiese más pantallas al intercambiarlas cíclicamente irán apareciendo por el final.
 *	Bloquear las pantallas solo si son publicas y del mismo tamaño que la inicial
 *	return: número de pantallas abiertas.
 */

uint32 LockScreens(void)
{
	struct Screen	*sc;
	char name[MAXPUBSCREENNAME+1];
	LONG stDepth,result;
	if((sc = IIntuition->LockScreenList()))
	{
		IIntuition->GetScreenAttrs(sc,SA_DisplayID,&ID,TAG_DONE);
		Resolution.Width = IP96->p96GetModeIDAttr(ID,P96IDA_WIDTH);
		Resolution.Height = IP96->p96GetModeIDAttr(ID,P96IDA_HEIGHT);
		CreateGrid(&Resolution);
		result = IIntuition->GetScreenAttrs(sc,SA_PubName,&name,SA_Depth,&stDepth,TAG_DONE);
		if(result ==0 && (stDepth>=16))
		{
			pantalla.scr =  IIntuition->LockPubScreen(name);
		}

	}
	IIntuition->UnlockScreenList();
	return 1;
}

ULONG DrawGrid( void )
{
	ULONG	held_off = 0;
	uint16 indexArray[]= { 0,1,2,0,2,3};
	if ( status[ buf_nextdraw ] == OK_REDRAW )
	{

		IGraphics->SetRPAttrs(&rport[ buf_nextdraw ],RPTAG_APenColor,0x00000000,TAG_DONE);
		IGraphics->RectFill(&rport[ buf_nextdraw ],0,0,Resolution.Width,Resolution.Height);
			if(pantalla.scr)
			{
				vertices[0].x = (pantalla.st.x+camera.x)/(camera.z+pantalla.st.z);
				vertices[0].y = (pantalla.st.y+camera.y)/(camera.z+pantalla.st.z);
				vertices[0].s =  0.0f;
				vertices[0].t =  0.0f;
				vertices[0].w =  1.0f;
				// ----- Vertex 2 -----
				vertices[1].x =  (pantalla.nd.x+camera.x)/(camera.z+pantalla.nd.z);
				vertices[1].y = (pantalla.nd.y+camera.y)/(camera.z+pantalla.nd.z);
				vertices[1].s =  pantalla.scr->Width;
				vertices[1].t =  0.0f;
				vertices[1].w =  1.0f;
				// ----- Vertex 3 -----
				vertices[2].x =  (pantalla.rd.x+camera.x)/(camera.z+pantalla.rd.z);
				vertices[2].y =  (pantalla.rd.y+camera.y)/(camera.z+pantalla.rd.z);
				vertices[2].s =  pantalla.scr->Width;
				vertices[2].t =  pantalla.scr->Height;
				vertices[2].w =  1.0f;		
				// ----- Vertex 4 -----
				vertices[3].x = (pantalla.th.x+camera.x)/(camera.z+pantalla.th.z);
				vertices[3].y =  (pantalla.th.y+camera.y)/(camera.z+pantalla.th.z);
				vertices[3].s =  0.0f;
				vertices[3].t =  pantalla.scr->Height;
				vertices[3].w =  1.0f;	
				if(Filter ==TRUE)
					IGraphics->CompositeTags(COMPOSITE_Src_Over_Dest,pantalla.scr->RastPort.BitMap,scbuf[buf_nextdraw]->sb_BitMap,
							COMPTAG_NumTriangles, 2,
							COMPTAG_VertexArray, vertices, 
							COMPTAG_IndexArray, indexArray, 
							COMPTAG_SrcAlpha,COMP_FLOAT_TO_FIX(1.0f),
							COMPTAG_DestAlpha,COMP_FLOAT_TO_FIX(1.0f),
							COMPTAG_VertexFormat, COMPVF_STW0_Present,
							COMPTAG_Flags,COMPFLAG_HardwareOnly | COMPFLAG_SrcFilter|COMPFLAG_SrcAlphaOverride|COMPFLAG_DestAlphaOverride,
							TAG_DONE);
				else
					IGraphics->CompositeTags(COMPOSITE_Src_Over_Dest,pantalla.scr->RastPort.BitMap,scbuf[buf_nextdraw]->sb_BitMap,
							COMPTAG_NumTriangles, 2,
							COMPTAG_VertexArray, vertices, 
							COMPTAG_IndexArray, indexArray, 
							COMPTAG_SrcAlpha,COMP_FLOAT_TO_FIX(1.0f),
							COMPTAG_DestAlpha,COMP_FLOAT_TO_FIX(1.0f),
							COMPTAG_VertexFormat, COMPVF_STW0_Present,
							COMPTAG_Flags,COMPFLAG_HardwareOnly | COMPFLAG_SrcAlphaOverride|COMPFLAG_DestAlphaOverride,
							TAG_DONE);
				if(LensFlag ==TRUE)
				{
					IGraphics->CompositeTags(COMPOSITE_Src_Over_Dest,lens,scbuf[buf_nextdraw]->sb_BitMap,
							COMPTAG_OffsetX,(int32)mouse.x-(ow/2),
							COMPTAG_OffsetY,(int32)mouse.y-(oh/2),
						//	COMPTAG_ScaleX,COMP_FLOAT_TO_FIX(2.2f),
						//	COMPTAG_ScaleY,COMP_FLOAT_TO_FIX(2.2f),
							COMPTAG_Flags,COMPFLAG_HardwareOnly | COMPFLAG_SrcFilter|COMPFLAG_DestAlphaOverride,
							TAG_DONE);
				}
				if(Clicked == TRUE)
				{
						pantalla.st.z= 0.0;
						pantalla.nd.z= 0.0;
						pantalla.rd.z= 0.0;
						pantalla.th.z= 0.0;
				}
			}
		status[ buf_nextdraw ] = OK_SWAPIN;
	//	buf_nextdraw = ( buf_nextdraw+1 ) % NUMBUFFERS;	// TRIPLE BUFFERING.
		buf_nextdraw ^= 1;
	}
	if ( status[ buf_nextswap ] == OK_SWAPIN )
	{
		scbuf[ buf_nextswap ]->sb_DBufInfo->dbi_SafeMessage.mn_ReplyPort = buffPort;

		if ( IIntuition->ChangeScreenBuffer( scr, scbuf[ buf_nextswap ] ) )
		{
			status[ buf_nextswap ] = 0;

			buf_current = buf_nextswap;
			buf_nextswap ^= 1;
		}
		else
		{
			held_off = 1;
		}
	}
	return( held_off );
}

/*
 *	Gestiona mensajes de doble/triple buffering.
 */

void handleDBufMessage( struct Message *dbmsg )
{
	ULONG buffer;

	/* dbi_SafeMessage is followed by an APTR dbi_UserData1, which
	 * contains the buffer number.  This is an easy way to extract
	 * it.
	 * The dbi_SafeMessage tells us that it's OK to redraw the
	 * in the previous buffer.
	 */

	buffer = ( ULONG ) *( ( APTR ** ) ( dbmsg+1 ) );
	/* Mark the previous buffer as OK to redraw into.
	 * If you're using multiple ( >2 ) buffering, you
	 * would use
	 *
	 *    ( buffer + NUMBUFFERS - 1 ) % NUMBUFFERS
	 *
	 */
	status[ buffer^1 ] = OK_REDRAW;
}

void SetDestinationInside(void)
{
	destination.z = 1.0;
	destination.x = 0;
	destination.y= 0;
}

void SetDestinationOutside(struct Screen *sc)
{
			differx = Resolution.Width/sc->Width;
			differy = Resolution.Height/sc->Height;
			destination.z=0.5;
			zoom=destination.z;
			destination.x = (-sc->MouseX)+(sc->MouseX*destination.z)/differx;
			destination.y = (-sc->MouseY)+(sc->MouseY*destination.z)/differy;
			mouse.x = sc->MouseX;
			mouse.y = sc->MouseY;
}

void Displacement(void)
{
	inc = 0;
	IDOS->DateStamp(&now);

	inc	=	now.ds_Days - then.ds_Days; 
	inc	=	inc*24*60 + now.ds_Minute - then.ds_Minute;	
	inc	=	inc*50*60 + now.ds_Tick	 - then.ds_Tick;	
	if (inc >=10) inc = 1;
	if(inc < 0) inc = 0;
	then.ds_Days = now.ds_Days;
	then.ds_Minute = now.ds_Minute;
	then.ds_Tick = now.ds_Tick;

	difference.x = ((destination.x-camera.x)*inc)/3.0;
	difference.y = ((destination.y-camera.y)*inc)/3.0;
	difference.z = ((destination.z-camera.z)*inc)/3.0;

	camera.x+=difference.x;
	camera.y+=difference.y;
	camera.z+=difference.z;
	steps++;
	if(delay >0) delay--;
}



BOOL controlIDCMP(VOID)
{
	struct IntuiMessage *message;
	ULONG mclass;
	USHORT code;
	WORD wheel;
	struct IntuiWheelData *iaddress;
	BOOL done = FALSE;
	ULONG mousex, mousey;
	while (NULL != (message = (struct IntuiMessage *)IExec->GetMsg(winPort)))
	{
		code   = message->Code;
		mousex = message->MouseX;
		mousey = message->MouseY;
		mclass = message->Class;
		iaddress = message->IAddress;
		wheel = iaddress->WheelY;
		win=message->IDCMPWindow;
		IExec->ReplyMsg((struct Message *)message);
		switch (mclass)
		{
			case IDCMP_RAWKEY:
				switch(code)
				{
					case RAWKEY_SPACE:
						if(LensFlag ==TRUE) LensFlag =FALSE;
						else LensFlag = TRUE;
					break;
				}
				break;
			case IDCMP_EXTENDEDMOUSE:
				switch(code)
				{
					case IMSGCODE_INTUIWHEELDATA:
					if(wheel ==-1 && zwheel <3)
					{
						zwheel-=wheel;
						destination.z =zoom+ (zwheel/10.0);
						destination.x = (-mouse.x)+(mouse.x*destination.z)/differx;
						destination.y = (-mouse.y)+(mouse.y*destination.z)/differy;

					}
					if(wheel ==1 && zwheel >-4)
					{
						zwheel-=wheel;
						destination.z =zoom+ (zwheel/10.0);
						destination.x = (-mouse.x)+(mouse.x*destination.z)/differx;
						destination.y = (-mouse.y)+(mouse.y*destination.z)/differy;
					}
					break;
				}
				break;
			case IDCMP_MOUSEBUTTONS:
				switch(code)
				{
					case SELECTUP:
						break;
					case SELECTDOWN:
						Clicked = TRUE;
						destination.z=1.0;	// fijar destino
						selected = mouse.z;
						destination.x=0;
						destination.y=0;
						break;
					case MIDDLEDOWN:
						if(Filter== TRUE) Filter = FALSE;
						else Filter = TRUE;
						break;
					case MIDDLEUP:
						if(Middle == TRUE)
						{
							Middle = FALSE;
						}
						break;
				}
				break;
			case IDCMP_MOUSEMOVE:
				mouse.x = mousex;
				mouse.y = mousey;
				if(Clicked ==FALSE)
				{
				destination.x = (-mouse.x)+(mouse.x*destination.z)/differx;
				destination.y = (-mouse.y)+(mouse.y*destination.z)/differy;

				}
				break;
		}
	}
	return (done);
}
