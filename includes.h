/*
**	includes and definitions header
*/

#include <stdlib.h>
#include <string.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/utility.h>
#include <proto/intuition.h>
#include <proto/icon.h>
#include <proto/graphics.h>
#include <proto/application.h>
#include<proto/Picasso96API.h>

#include <graphics/rpattr.h>
#include <graphics/blitattr.h>
#include <graphics/composite.h>
#include <workbench/icon.h>
#include <intuition/pointerclass.h>
#include <libraries/keymap.h>

#define VERSION "53"
#define REVISION "12"
#define PROGNAME	"ZDR - Zooming Done Right"
#define DEVELOPER	"Vicente Gimeno"
#define EMAIL		"Ami603@gmail.com"

/*

V53.0 - Initial Tests, no screen locking, all screens available

V53.1 - Fixed Double launching, Launching from Workbench, Different screensizes click area.

V53.2 - Fixed Screen Locking, only public named screens and 32-16 bit depth allowed

V53.3 - Added zoom travelling with middle mouse button.

V53.4 -Fixedd multiple zoom bug.

V53.5 -Added Snow when Christmas time

V53.6 -Changed the way zooming works, now only points to the selected screen and back, no mouse tracking.

V53.7 -Yay!! Rendering bugs are gone :).

V53.8 - fixed for screens bigger than resolution

V53.9 - Forked SSDR, cleaned code, faster and smoother anim.

V53.10 - Fixed Wrong Application.library tag, now allkeys should work.

V53.11 - Fixed crash with keyboard input events.

V53.12 - Added Space Events to hide/show the lens.

*/

