/*****************************************************************************
 * x11_graphics.cpp: X11 implementation of the Graphics and Region classes
 *****************************************************************************
 * Copyright (C) 2003 VideoLAN
 * $Id: x11_graphics.cpp,v 1.3 2003/05/18 17:48:05 asmax Exp $
 *
 * Authors: Cyril Deguet     <asmax@videolan.org>
 *          Emmanuel Puig    <karibu@via.ecp.fr>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111,
 * USA.
 *****************************************************************************/

#ifdef X11_SKINS

//--- X11 -----------------------------------------------------------------
#include <X11/Xlib.h>

//--- VLC -----------------------------------------------------------------
#include <vlc/intf.h>

//--- SKIN ------------------------------------------------------------------
#include "../src/graphics.h"
#include "../src/window.h"
#include "../os_window.h"
#include "x11_graphics.h"
#include "../src/skin_common.h"

#include <stdio.h>
#include <math.h>

//---------------------------------------------------------------------------
// X11 GRAPHICS
//---------------------------------------------------------------------------
X11Graphics::X11Graphics( intf_thread_t *p_intf, int w, int h,
                          SkinWindow *from ) : Graphics( w, h )
{
    display = p_intf->p_sys->display;
    int screen = DefaultScreen( display );

    if( from != NULL )
    {
        Window fromWnd = ( (X11Window *)from )->GetHandle();

        XWindowAttributes attr;
        XGetWindowAttributes( display, fromWnd, &attr);

        Image = XCreatePixmap( display, fromWnd, w, h, attr.depth );
        Gc = DefaultGC( display, screen );
    }
    else
    {
        Window root = DefaultRootWindow( display );
        Image = XCreatePixmap( display, root, w, h,
                               DefaultDepth( display, screen ) );
        Gc = DefaultGC( display, screen );
    }

    // Set the background color to black
    XFillRectangle( display, Image, Gc, 0, 0, w, h );    
}
//---------------------------------------------------------------------------
X11Graphics::~X11Graphics()
{
    XFreePixmap( display, Image );
}
//---------------------------------------------------------------------------
void X11Graphics::CopyFrom( int dx, int dy, int dw, int dh, Graphics *Src,
                              int sx, int sy, int Flag )
{
    XCopyArea( display, (( X11Graphics* )Src )->GetImage(), Image, Gc, 
            sx, sy, dw, dh, dx, dy );
}
//---------------------------------------------------------------------------
void X11Graphics::DrawRect( int x, int y, int w, int h, int color )
{
/*    gdk_rgb_gc_set_foreground( Gc, color );
    gdk_draw_rectangle( Image, Gc, TRUE, x, y, w, h);*/
}
//---------------------------------------------------------------------------
void X11Graphics::SetClipRegion( SkinRegion *rgn )
{
/*    gdk_gc_set_clip_region( Gc, ( (X11Region *)rgn )->GetHandle() );*/
}
//---------------------------------------------------------------------------
void X11Graphics::ResetClipRegion()
{
/*    GdkRectangle rect;
    rect.x = 0;
    rect.y = 0;
    rect.width = Width;
    rect.height = Height;
    GdkRegion *rgn = gdk_region_rectangle( &rect );
    gdk_gc_set_clip_region( Gc, rgn );
    gdk_region_destroy( rgn );*/
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// X11 REGION
//---------------------------------------------------------------------------
X11Region::X11Region()
{
/*    Rgn = gdk_region_new();*/
}
//---------------------------------------------------------------------------
X11Region::X11Region( int x, int y, int w, int h )
{
/*    GdkRectangle rect;
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
    Rgn = gdk_region_rectangle( &rect );*/
}
//---------------------------------------------------------------------------
X11Region::~X11Region()
{
/*    gdk_region_destroy( Rgn );*/
}
//---------------------------------------------------------------------------
void X11Region::AddPoint( int x, int y )
{
    AddRectangle( x, y, 1, 1 );
}
//---------------------------------------------------------------------------
void X11Region::AddRectangle( int x, int y, int w, int h )
{
/*    GdkRectangle rect;
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
    GdkRegion *Buffer = gdk_region_rectangle( &rect );
    gdk_region_union( Rgn, Buffer );*/
}
//---------------------------------------------------------------------------
void X11Region::AddElipse( int x, int y, int w, int h )
{
/*    GdkRegion *Buffer;
    GdkRectangle rect;
    rect.height = 1;

    double ex, ey;
    double a = w / 2;
    double b = h / 2;

    if( !a || !b )
        return;

    for( ey = 0; ey < h; ey++ )
    {
        // Calculate coords
        ex = a * sqrt( 1 - ey * ey / ( b * b ) );

        // Upper line
        rect.x     = (gint)( x + a - ex );
        rect.y     = (gint)( y + b - ey );
        rect.width = (gint)( 2 * ex );
        Buffer = gdk_region_rectangle( &rect );
        gdk_region_union( Rgn, Buffer );
        gdk_region_destroy( Buffer );

        // Lower line
        rect.y = (gint)( y + b + ey );
        Buffer = gdk_region_rectangle( &rect );
        gdk_region_union( Rgn, Buffer );
        gdk_region_destroy( Buffer );
    }*/
}
//---------------------------------------------------------------------------
void X11Region::Move( int x, int y )
{
/*    gdk_region_offset( Rgn, x, y );*/
}
//---------------------------------------------------------------------------
bool X11Region::Hit( int x, int y )
{
/*    return gdk_region_point_in( Rgn, x, y );*/
}
//---------------------------------------------------------------------------

#endif
