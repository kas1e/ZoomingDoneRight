/*
**	Globals header
*/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

/*
**	Function Prototypes
*/

void OpenLibs( void );
void CleanExit(CONST_STRPTR);
void Events( void );
void AppRegistering( void );
void CreateGrid(struct Screen *);
ULONG DrawGrid( void );
uint32 LockScreens(void);
void handleDBufMessage( struct Message * );
void SetDestinationOutside(struct Screen *);
void SetDestinationInside(void);
void Displacement( void );
BOOL controlIDCMP(VOID);



/*
**	Library/Interface 
*/

struct Library			*IntuitionBase;
struct Library			*IconBase;
struct Library			*ApplicationBase;
struct Library			*GraphicsBase;
struct Library			*LocaleBase;
struct Library			*P96Base;
struct Library			*UtilityBase;

struct IntuitionIFace		*IIntuition;
struct IconIFace		*IIcon;
struct ApplicationIFace	*IApplication;
struct PrefsObjectsIFace	*IPrefsObjects;
struct ApplicationIFace	*IApplication;
struct GraphicsIFace		*IGraphics;
struct LocaleIFace		*ILocale;
struct UtilityIFace		*IUtility;
struct P96IFace			*IP96;
	
struct Screen 		*scr;
struct Window 		*win;

struct MsgPort		*winPort,
				*buffPort;

struct RastPort		rport[ 2 ];
struct ScreenBuffer	*scbuf[2]; 

#define	OK_REDRAW	1	/* Buffer fully detached, ready for redraw */
#define	OK_SWAPIN	2	/* Buffer redrawn, ready for swap-in */

struct vertex
{
	float32 x,y,z;		// coordenadas 3D
}camera, destination,difference,mouse,focus,oldcamera,areazoom;

struct Vert
{
	float32	x,
		y,
		s,
		t,
		w;
}vertices[4];


struct pantallas
{
	struct vertex	st;
	struct vertex	nd;
	struct vertex	rd;
	struct vertex	th;
	struct Screen	*scr;	
}pantalla;

ULONG selected;

ULONG	ID;

ULONG	status[2];
ULONG	buf_current,
		buf_nextdraw, 
		buf_nextswap;
ULONG	steps;
BOOL Clicked,Middle,Progress;
ULONG	AppID;
LONG inc,delay;
struct	DateStamp	now,then;
struct Screen Resolution;

struct BitMap	*lens;
PLANEPTR	lensalpha;
struct DiskObject *doicon;
int ow,oh;
float32 differx,differy;
BOOL Filter;
float32 zoom;
LONG zwheel;
BOOL LensFlag;
#endif
