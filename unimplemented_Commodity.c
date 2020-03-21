/*
**	Commodity.c	Constructor/Destructor
**	©2006, Vicente 'Ami603' Gimeno
*/

/*	
**	NOTE: Recursos necesarios.Algunos deberan ser globales
**		struct NewBroker        NBK;
**		STRPTR	snapkey = "RAWMOUSE LALT LBUTTON MOUSE_LEFTPRESS";
**		static CxObj            *broker,*filter,*sender,*translate;
*/

BOOL	InitCommodity		( VOID );
BOOL	DestroyCommodity	( VOID );
VOID	CommodityEvents	( VOID );

BOOL InitCommodity( VOID )
{
	if(CMsgPort = IExec->CreateMsgPort())
	{
                                NBK.nb_Version   =       NB_VERSION;
                                NBK.nb_Name      =       "SSDR";
                                NBK.nb_Title     =       "$VER:  "PROGNAME" "VERSION"."REVISION" (15.12.12)©2012,"DEVELOPER"\n\0";
                                NBK.nb_Descr     =       "Your choice for fast switching between screens";
                                NBK.nb_Unique    =       NBU_UNIQUE;
                                NBK.nb_Flags     =       0;
                                NBK.nb_Pri       =       80;
                                NBK.nb_Port      =       CMsgPort;
                                NBK.nb_ReservedChannel   =       0;	
                                broker = CxBroker(&NBK,NULL);
                                if (broker) {
                                        filter = CxFilter(snapkey);
                                        if (filter) {
                                                AttachCxObj(broker,filter);
                                                sender = CxSender(snapPort,0);
                                                if (sender) {
                                                        AttachCxObj(filter,sender);
                                                        translate = CxTranslate(NULL);
                                                        if (translate) {
                                                                AttachCxObj(filter,translate);
                                                                if (CxObjError(filter) == 0) {	
	}
}

BOOL DestroyCommodity( VOID )
{
                                       DeleteCxObjAll(broker);
                                        broker = NULL;
                                        filter = NULL;
                                        sender = NULL;
                                        translate = NULL;
                                DeleteMsgPort(CMsgPort);
}

VOID CommodityEvents( VOID )
{
	while (msg = GetMsg(snapPort)) 
	{
		signal  =       1;
		msgid   =       CxMsgID((CxMsg *)msg);
		msgtype =       CxMsgType((CxMsg *)msg);
		ReplyMsg(msg);

		switch (msgtype)
		{
			case CXM_IEVENT:
				break;
			case CXM_COMMAND:
				switch (msgid)
				{
					case CXCMD_DISABLE:
						ActivateCxObj(broker,FALSE);
						break;
					case CXCMD_ENABLE:
						ActivateCxObj(broker,TRUE);
						break;
					case CXCMD_KILL:
						abort = TRUE;
						break;
					case CXCMD_UNIQUE:
					case CXCMD_APPEAR:
					case CXCMD_DISAPPEAR:
						break;
			}
			break;
		}
	}
}