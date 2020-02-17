//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit4.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

void DrawAlphaImage( int xx, int yy, LPAN_IMAGE imageobject, LAYER *layerdata )
{
    DWORD *temp, color;
    int cnt = 0, cnt2 = 0;
    byte ind;
    WORD alpha, r, g, b, br, bg, bb;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    BYTE *image = (BYTE *)imageobject->imagebuf;
    int x, y, set;

    if ( !image )
        return;

    x = xx + imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 2;

    	set = (image[1]<<8) | image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

        if ( layerdata->an_version == 0x1001 )  // 8Bit 데이터라면..
        {
            BYTE    *pal = layerdata->palette;
    	while( setcnter < set )
    	{
            cnt = (image[addresser]<<16) | (image[addresser+1]<<24) | (image[addresser+2]) | (image[addresser+3]<<8);
            temp += (int)cnt;

    		addresser+=4;

            cnt = (image[addresser+1]<<8) | image[addresser];
            if ( cnt == 0xffff )
            {
                addresser+=4;
                temp += ( BACK_SIZEX - sizex );
        		setcnter++;
                continue;
            }

            cnt2 = ((image[addresser + 1]<<8) | image[addresser]);

                    for ( cnt = 0; cnt < cnt2; cnt++ )
                    {
                        alpha = image[addresser+cnt*2+2];
                        ind = image[addresser+cnt*2+1+2];

                        r = (WORD)pal[ind*3] * alpha;
                        g = (WORD)pal[ind*3+1] * alpha;
                        b = (WORD)pal[ind*3+2] * alpha;

                        br = ((WORD)((temp[cnt]>>16)&0xff)) * (255-alpha);
                        bg = ((WORD)((temp[cnt]>>8)&0xff)) * (255-alpha);
                        bb = ((WORD)((temp[cnt])&0xff)) * (255-alpha);

                        {
                            r = (r+br)/255;//(temp[cnt]>>10);
                            g = (g+bg)/255;//((temp[cnt]>>5)&0x1f);
                            b = (b+bb)/255;//((temp[cnt])&0x1f);
                        }

                        temp[cnt] = (DWORD)(0xff<<24) | (DWORD)(r << 16) | (DWORD)(g << 8) | (DWORD)(b);
                    }

            temp += cnt2;
	    	addresser+=(cnt2 * 2 + 2);

    		setcnter++;
	    }
        }
        else    // 이전 an3 파일 처리
    	while( setcnter < set )
    	{
            cnt = (image[addresser]<<16) | (image[addresser+1]<<24) | (image[addresser+2]) | (image[addresser+3]<<8);
            temp += (int)cnt;

    		addresser+=4;

            cnt = (image[addresser+1]<<8) | image[addresser];
            if ( cnt == 0xffff )
            {
                addresser+=4;
                temp += ( BACK_SIZEX - sizex );
        		setcnter++;
                continue;
            }

            cnt2 = ((image[addresser + 1]<<8) | image[addresser]);

                    for ( cnt = 0; cnt < cnt2; cnt++ )
                    {
                        alpha = image[addresser+cnt*4+3+2];
                        r = (WORD)image[addresser+cnt*4+2+2] * alpha;
                        g = (WORD)image[addresser+cnt*4+1+2] * alpha;
                        b = (WORD)image[addresser+cnt*4+0+2] * alpha;

                        br = ((WORD)((temp[cnt]>>16)&0xff)) * (255-alpha);
                        bg = ((WORD)((temp[cnt]>>8)&0xff)) * (255-alpha);
                        bb = ((WORD)((temp[cnt])&0xff)) * (255-alpha);

                        {
                            r = (r+br)/255;//(temp[cnt]>>10);
                            g = (g+bg)/255;//((temp[cnt]>>5)&0x1f);
                            b = (b+bb)/255;//((temp[cnt])&0x1f);
                        }

                        temp[cnt] = (DWORD)(0xff<<24) | (DWORD)(r << 16) | (DWORD)(g << 8) | (DWORD)(b);
                    }

            temp += cnt2;
	    	addresser+=(cnt2 * 4 + 2);

    		setcnter++;
	    }
    }
}

void DrawFlipAlphaImage( int xx, int yy, LPAN_IMAGE imageobject, LAYER *layerdata )
{
    DWORD *temp, color;
    int cnt = 0, cnt2 = 0;
    WORD alpha, r, g, b, br, bg, bb;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    BYTE *image = (BYTE *)imageobject->imagebuf;
    int x, y, set;
    byte ind;

    if ( !image )
        return;

    x = xx - imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 2;

    	set = (image[1]<<8) | image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

        if ( layerdata->an_version == 0x1001 )  // 8Bit 데이터라면..
        {
            BYTE    *pal = layerdata->palette;
    	while( setcnter < set )
    	{
            cnt = (image[addresser]<<16) | (image[addresser+1]<<24) | (image[addresser+2]) | (image[addresser+3]<<8);
            temp -= (int)cnt;

    		addresser+=4;

            cnt = (image[addresser+1]<<8) | image[addresser];
            if ( cnt == 0xffff )
            {
                cnt = (image[addresser+3]<<8) | image[addresser+2];
                temp += ( BACK_SIZEX + cnt );
                addresser+=4;
        		setcnter++;
                continue;
            }

            cnt2 = ((image[addresser + 1]<<8) | image[addresser]);

                    for ( cnt = 0; cnt < cnt2; cnt++ )
                    {
                        alpha = image[addresser+cnt*2+2];
                        ind = image[addresser+cnt*2+1+2];

                        r = (WORD)pal[ind*3] * alpha;
                        g = (WORD)pal[ind*3+1] * alpha;
                        b = (WORD)pal[ind*3+2] * alpha;

                        br = ((WORD)((temp[cnt]>>16)&0xff)) * (255-alpha);
                        bg = ((WORD)((temp[cnt]>>8)&0xff)) * (255-alpha);
                        bb = ((WORD)((temp[cnt])&0xff)) * (255-alpha);

                        {
                            r = (r+br)/255;//(temp[cnt]>>10);
                            g = (g+bg)/255;//((temp[cnt]>>5)&0x1f);
                            b = (b+bb)/255;//((temp[cnt])&0x1f);
                        }

                        *temp = (DWORD)(0xff<<24) | (DWORD)(r << 16) | (DWORD)(g << 8) | (DWORD)(b);
                        temp--;
                    }

	    	addresser+=(cnt2 * 2 + 2);

    		setcnter++;
	    }
        }
        else    // 이전 an3 파일 처리
    	while( setcnter < set )
    	{
            cnt = (image[addresser]<<16) | (image[addresser+1]<<24) | (image[addresser+2]) | (image[addresser+3]<<8);
            temp -= (int)cnt;

    		addresser+=4;

            cnt = (image[addresser+1]<<8) | image[addresser];
            if ( cnt == 0xffff )
            {
                cnt = (image[addresser+3]<<8) | image[addresser+2];
                temp += ( BACK_SIZEX + cnt );
                addresser+=4;
        		setcnter++;
                continue;
            }

            cnt2 = ((image[addresser + 1]<<8) | image[addresser]);

                    for ( cnt = 0; cnt < cnt2; cnt++ )
                    {
                        alpha = image[addresser+cnt*4+3+2];
                        r = (WORD)image[addresser+cnt*4+2+2] * alpha;
                        g = (WORD)image[addresser+cnt*4+1+2] * alpha;
                        b = (WORD)image[addresser+cnt*4+0+2] * alpha;

                        br = ((WORD)((temp[cnt]>>16)&0xff)) * (255-alpha);
                        bg = ((WORD)((temp[cnt]>>8)&0xff)) * (255-alpha);
                        bb = ((WORD)((temp[cnt])&0xff)) * (255-alpha);

                        {
                            r = (r+br)/255;//(temp[cnt]>>10);
                            g = (g+bg)/255;//((temp[cnt]>>5)&0x1f);
                            b = (b+bb)/255;//((temp[cnt])&0x1f);
                        }

                        *temp = (DWORD)(0xff<<24) | (DWORD)(r << 16) | (DWORD)(g << 8) | (DWORD)(b);
                        temp--;
                    }

	    	addresser+=(cnt2 * 4 + 2);

    		setcnter++;
	    }

    }
}

void DrawImage( int xx, int yy, LPAN_IMAGE imageobject )
{
    DWORD *temp;
    int cnt = 0, cnt2 = 0;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    WORD *image = (WORD *)imageobject->imagebuf;
    int x, y, set;

    if ( !image )
        return;

    x = xx + imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 1;

    	set = image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

    	while( setcnter < set )
    	{
            temp += (int)((image[addresser]<<16)|image[addresser+1]);

    		addresser+=2;

            if ( image[addresser] == 0xffff )
            {
                addresser+=2;
                temp += ( BACK_SIZEX - sizex );
        		setcnter++;
                continue;
            }

    		memcpy( temp, &image[addresser+1], image[addresser] * 4 );
            temp += image[addresser]*2;
	    	addresser+=(image[addresser]+1);

    		setcnter++;
	    }
    }
}

void DrawFlipImage( int xx, int yy, LPAN_IMAGE imageobject )
{
    DWORD *temp;
    int cnt = 0, cnt2 = 0;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    WORD *image = (WORD *)imageobject->imagebuf;
    int x, y, set;

    if ( !image )
        return;

    x = xx - imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 1;

    	set = image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

    	while( setcnter < set )
    	{
            temp -= (int)(((image[addresser]<<16)|image[addresser+1]));

    		addresser+=2;

            if ( image[addresser] == 0xffff )
            {
                temp += ( BACK_SIZEX + image[addresser+1] );
                addresser+=2;
        		setcnter++;
                continue;
            }

            for ( cnt = 0; cnt < image[addresser]; cnt++ )
            {
                *temp = image[addresser+cnt+1];
                temp--;
            }

//    		memcpy( temp, &image[addresser+1], image[addresser] * 2 );

//            temp -= image[addresser];
	    	addresser+=(image[addresser]+1);

    		setcnter++;
	    }
    }
}




void DrawColorImage( int xx, int yy, LPAN_IMAGE imageobject, WORD color )
{
    DWORD *temp;
    int cnt = 0, cnt2 = 0;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    WORD *image = (WORD *)imageobject->imagebuf, tempcolor;
    int x, y, set;
    BYTE r, g, b;

    if ( !image )
        return;

    x = xx + imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 1;

    	set = image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

    	while( setcnter < set )
    	{
            temp += (int)((image[addresser]<<16)|image[addresser+1]);

    		addresser+=2;

            if ( image[addresser] == 0xffff )
            {
                addresser+=2;
                temp += ( BACK_SIZEX - sizex );
        		setcnter++;
                continue;
            }

            for ( cnt = 0; cnt < image[addresser]; cnt++ )
            {
                tempcolor = image[addresser+cnt+1] & 0x1f;
                r = (color >> 10) & 0x1f;
                g = (color >> 5) & 0x1f;
                b = color & 0x1f;

                r = (r * tempcolor) / 0x1f;
                g = (g * tempcolor) / 0x1f;
                b = (b * tempcolor) / 0x1f;

                *temp = (r<<10)|(g<<5)|b;
                temp++;
            }

//    		memcpy( temp, &image[addresser+1], image[addresser] * 2 );
  //          temp += image[addresser];
	    	addresser+=(image[addresser]+1);

    		setcnter++;
	    }
    }
}

void DrawFlipColorImage( int xx, int yy, LPAN_IMAGE imageobject, WORD color )
{
    DWORD *temp;
    int cnt = 0, cnt2 = 0;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    WORD *image = (WORD *)imageobject->imagebuf, tempcolor;
    int x, y, set;
    BYTE r, g, b;

    if ( !image )
        return;

    x = xx - imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 1;

    	set = image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

    	while( setcnter < set )
    	{
            temp -= (int)(((image[addresser]<<16)|image[addresser+1]));

    		addresser+=2;

            if ( image[addresser] == 0xffff )
            {
                temp += ( BACK_SIZEX + image[addresser+1] );
                addresser+=2;
        		setcnter++;
                continue;
            }

            for ( cnt = 0; cnt < image[addresser]; cnt++ )
            {
                tempcolor = image[addresser+cnt+1] & 0x1f;
                r = (color >> 10) & 0x1f;
                g = (color >> 5) & 0x1f;
                b = color & 0x1f;

                r = (r * tempcolor) / 0x1f;
                g = (g * tempcolor) / 0x1f;
                b = (b * tempcolor) / 0x1f;

                *temp = (r<<10)|(g<<5)|b;
                temp--;
            }

//    		memcpy( temp, &image[addresser+1], image[addresser] * 2 );

//            temp -= image[addresser];
	    	addresser+=(image[addresser]+1);

    		setcnter++;
	    }
    }
}



void DrawOtherImage( int xx, int yy, LPAN_IMAGE imageobject, int puttype )
{
    DWORD *temp;
    int cnt = 0, cnt2 = 0;
    int type = puttype>>5;
    int alpha = (puttype&0x1f) * 100 / 31;
    int disalpha = 100 - alpha;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    WORD *image = (WORD *)imageobject->imagebuf;
    int x, y, set;
    WORD r, g, b, br, bg, bb;

    if ( !image )
        return;

    x = xx + imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 1;

    	set = image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

    	while( setcnter < set )
    	{
            temp += (int)((image[addresser]<<16)|image[addresser+1]);

    		addresser+=2;

            if ( image[addresser] == 0xffff )
            {
                addresser+=2;
                temp += ( BACK_SIZEX - sizex );
        		setcnter++;
                continue;
            }

            switch( type )
            {
                // 반투명
                case 2:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        r = (((temp[cnt]>>10)&0x1f)>>1) + (((image[addresser+cnt+1]>>10)&0x1f)>>1);
                        g = (((temp[cnt]>>5)&0x1f)>>1) + (((image[addresser+cnt+1]>>5)&0x1f)>>1);
                        b = ((temp[cnt]&0x1f)>>1) + ((image[addresser+cnt+1]&0x1f)>>1);

                        temp[cnt] = (r << 10) | (g << 5) | b;
                    }
                break;
                // 빛효과
                case 3:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        r = (((temp[cnt]>>10)&0x1f)) + (((image[addresser+cnt+1]>>10)&0x1f));
                        g = (((temp[cnt]>>5)&0x1f)) + (((image[addresser+cnt+1]>>5)&0x1f));
                        b = ((temp[cnt]&0x1f)) + ((image[addresser+cnt+1]&0x1f));

                        if ( r > 0x1f )
                            r = 0x1f;
                        if ( g > 0x1f )
                            g = 0x1f;
                        if ( b > 0x1f )
                            b = 0x1f;

                        temp[cnt] = (r << 10) | (g << 5) | b;
                    }
                break;
                // 먼지효과
                case 4:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        br = (temp[cnt]>>10)&0x1f;
                        bg = (temp[cnt]>>5)&0x1f;
                        bb = temp[cnt]&0x1f;
                        r = (image[addresser+cnt+1]>>10)&0x1f;
                        g = (image[addresser+cnt+1]>>5)&0x1f;
                        b = image[addresser+cnt+1]&0x1f;

                        r = max(r, br);
                        g = max(g, bg);
                        b = max(b, bb);

                        temp[cnt] = (r << 10) | (g << 5) | b;
                    }
                break;
                // screen
                case 5:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        r = 0x1f - ((0x1f - ((temp[cnt]>>10)&0x1f)) * (0x1f - ((image[addresser+cnt+1]>>10)&0x1f))>>5);
                        g = 0x1f - ((0x1f - ((temp[cnt]>>5)&0x1f)) * (0x1f - ((image[addresser+cnt+1]>>5)&0x1f))>>5);
                        b = 0x1f - ((0x1f - (temp[cnt]&0x1f)) * (0x1f - (image[addresser+cnt+1]&0x1f))>>5);

                        temp[cnt] = (r << 10) | (g << 5) | b;
                    }
                break;
                // differnt
                case 6:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        br = (temp[cnt]>>10)&0x1f;
                        bg = (temp[cnt]>>5)&0x1f;
                        bb = temp[cnt]&0x1f;
                        r = (image[addresser+cnt+1]>>10)&0x1f;
                        g = (image[addresser+cnt+1]>>5)&0x1f;
                        b = image[addresser+cnt+1]&0x1f;

                        r = max(br,r)- min(br,r);
                        g = max(bg,g)- min(bg,g);
                        b = max(bb,b)- min(bb,b);

                        temp[cnt] = (r << 10) | (g << 5) | b;
                    }
                break;
                // 알파블렌딩
                case 7:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        if ( !disalpha )
                        {
                            r = ((image[addresser+cnt+1]>>10)&0x1f);
                            g = ((image[addresser+cnt+1]>>5)&0x1f);
                            b = (image[addresser+cnt+1]&0x1f);
                        }
                        else
                        if ( !alpha )
                        {
                            r = ((temp[cnt]>>10)&0x1f);
                            g = ((temp[cnt]>>5)&0x1f);
                            b = (temp[cnt]&0x1f);
                        }
                        else
                        {
                            br = ((temp[cnt]>>10)&0x1f) * disalpha / 100;
                            bg = ((temp[cnt]>>5)&0x1f) * disalpha / 100;
                            bb = (temp[cnt]&0x1f) * disalpha / 100;
                            r = ((image[addresser+cnt+1]>>10)&0x1f) * alpha / 100;
                            g = ((image[addresser+cnt+1]>>5)&0x1f) * alpha / 100;
                            b = (image[addresser+cnt+1]&0x1f) * alpha / 100;

                            r += br;
                            g += bg;
                            b += bb;
                        }

                        temp[cnt] = (r << 10) | (g << 5) | b;
                    }
                break;
            }

            temp += image[addresser];
	    	addresser+=(image[addresser]+1);

    		setcnter++;
	    }
    }
}

void DrawOtherFlipImage( int xx, int yy, LPAN_IMAGE imageobject, int puttype )
{
    DWORD *temp;
    int cnt = 0, cnt2 = 0;
    int type = puttype>>5;
    int alpha = (puttype&0x1f) * 100 / 31;
    int disalpha = 100 - alpha;

    int sizex = imageobject->xsize, sizey = imageobject->ysize;
    int setcnter = 0, addresser = 0;
    WORD *image = (WORD *)imageobject->imagebuf;
    int x, y, set;
    WORD r, g, b, br, bg, bb;

    if ( !image )
        return;

    x = xx - imageobject->startx;
    y = yy + imageobject->starty;

    if ( x + sizex < -99 || x > 899 || y + sizey < -99 || y > 899 )
        return;


    if ( x < -99 || y < -99 || x + sizex > 899 || y + sizey > 899 )
    {
    }
    else
    {
    	setcnter = 0;
    	addresser = 1;

    	set = image[0];

        temp = &Offscreen[(y + BACK_GAPY) * BACK_SIZEX + x + BACK_GAPX];

    	while( setcnter < set )
    	{
            temp -= (int)(((image[addresser]<<16)|image[addresser+1]));

    		addresser+=2;

            if ( image[addresser] == 0xffff )
            {
                temp += ( BACK_SIZEX + image[addresser+1] );
                addresser+=2;
        		setcnter++;
                continue;
            }

            switch( type )
            {
                // 반투명
                case 2:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        r = (((*temp>>10)&0x1f)>>1) + (((image[addresser+cnt+1]>>10)&0x1f)>>1);
                        g = (((*temp>>5)&0x1f)>>1) + (((image[addresser+cnt+1]>>5)&0x1f)>>1);
                        b = ((*temp&0x1f)>>1) + ((image[addresser+cnt+1]&0x1f)>>1);

                        *temp = (r << 10) | (g << 5) | b;
                        temp--;
                    }
                break;
                // 빛효과
                case 3:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        r = (((*temp>>10)&0x1f)) + (((image[addresser+cnt+1]>>10)&0x1f));
                        g = (((*temp>>5)&0x1f)) + (((image[addresser+cnt+1]>>5)&0x1f));
                        b = ((*temp&0x1f)) + ((image[addresser+cnt+1]&0x1f));

                        if ( r > 0x1f )
                            r = 0x1f;
                        if ( g > 0x1f )
                            g = 0x1f;
                        if ( b > 0x1f )
                            b = 0x1f;

                        *temp = (r << 10) | (g << 5) | b;
                        temp--;
                    }
                break;
                // 먼지효과
                case 4:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        br = (*temp>>10)&0x1f;
                        bg = (*temp>>5)&0x1f;
                        bb = *temp&0x1f;
                        r = (image[addresser+cnt+1]>>10)&0x1f;
                        g = (image[addresser+cnt+1]>>5)&0x1f;
                        b = image[addresser+cnt+1]&0x1f;

                        r = max( r, br );
                        g = max( g, bg );
                        b = max( b, bb );

                        *temp = (r << 10) | (g << 5) | b;
                        temp--;
                    }
                break;
                // screen
                case 5:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        r = 0x1f - ((0x1f - ((*temp>>10)&0x1f)) * (0x1f - ((image[addresser+cnt+1]>>10)&0x1f))>>5);
                        g = 0x1f - ((0x1f - ((*temp>>5)&0x1f)) * (0x1f - ((image[addresser+cnt+1]>>5)&0x1f))>>5);
                        b = 0x1f - ((0x1f - (*temp&0x1f)) * (0x1f - (image[addresser+cnt+1]&0x1f))>>5);

                        *temp = (r << 10) | (g << 5) | b;
                        temp--;
                    }
                break;
                // differnt
                case 6:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        br = (*temp>>10)&0x1f;
                        bg = (*temp>>5)&0x1f;
                        bb = *temp&0x1f;
                        r = (image[addresser+cnt+1]>>10)&0x1f;
                        g = (image[addresser+cnt+1]>>5)&0x1f;
                        b = image[addresser+cnt+1]&0x1f;

                        r = max(br,r)- min(br,r);
                        g = max(bg,g)- min(bg,g);
                        b = max(bb,b)- min(bb,b);

                        *temp = (r << 10) | (g << 5) | b;
                        temp--;
                    }
                break;
                // 알파블렌딩
                case 7:
                    for ( cnt = 0; cnt < image[addresser]; cnt++ )
                    {
                        if ( !disalpha )
                        {
                            r = ((image[addresser+cnt+1]>>10)&0x1f);
                            g = ((image[addresser+cnt+1]>>5)&0x1f);
                            b = (image[addresser+cnt+1]&0x1f);
                        }
                        else
                        if ( !alpha )
                        {
                            r = ((*temp>>10)&0x1f);
                            g = ((*temp>>5)&0x1f);
                            b = (*temp&0x1f);
                        }
                        else
                        {
                            br = ((*temp>>10)&0x1f) * disalpha / 100;
                            bg = ((*temp>>5)&0x1f) * disalpha / 100;
                            bb = (*temp&0x1f) * disalpha / 100;
                            r = ((image[addresser+cnt+1]>>10)&0x1f) * alpha / 100;
                            g = ((image[addresser+cnt+1]>>5)&0x1f) * alpha / 100;
                            b = (image[addresser+cnt+1]&0x1f) * alpha / 100;

                            r += br;
                            g += bg;
                            b += bb;
                        }

                        *temp = (r << 10) | (g << 5) | b;
                        temp--;
                    }
                break;
            }

//    		memcpy( temp, &image[addresser+1], image[addresser] * 2 );

//            temp -= image[addresser];
	    	addresser+=(image[addresser]+1);

    		setcnter++;
	    }
    }
}

void Render_sourcescreen( void )
{
    bool flip_draw;
    int i;
    int ani = 0;
    DWORD *temp = Offscreen;

    strcpy( Source_screen_text, "No Source Image." );

    if ( BackColorFlag )
    {
        _asm
        {
            mov edi, dword ptr [temp]
            mov eax, dword ptr [BackColor]
//            mov ebx, eax
//            shl eax, 16
//            or eax, ebx

            mov ecx, BACK_SIZEX * BACK_SIZEY
            rep stosd
        }
    }
    else
    {
        memcpy( Offscreen, BackMemory, BACK_SIZEX * BACK_SIZEY * 4 );
    }

    for ( i = 0; i < 8; i++ )
    {
        flip_draw = false;
        // 이미지가 로딩된 상태일 경우 화면에 표시
        if ( AN_Source[i].loaded_flag )
        {
            ani = AN_Source[i].now_animation;
            int dir = AN_Source[i].now_direction;

            if ( AN_Source[i].flip_flag && (dir%4) && dir > 4 )   // 뒤집어 찍어야 할 상황이라면..
            {
                flip_draw = true;
                dir = 4 - (dir%4);
            }

            int frame = AN_Source[i].now_frame;
            int abs_frame = AN_Source[i].animation_source.abs_framestart[ani] + frame +
                AN_Source[i].animation_source.direction_total_frame * dir;

            // 해당 방향의 해당 에니메이션 데이터가 있는 경우에만 출력
            if ( AN_Source[i].animation_source.direction_animation[ani] && !AN_Source[i].view_flag )
                if ( flip_draw )
                {
                    if ( AN_Source[i].source_images[abs_frame]->alphaflag )
                    {
                        DrawFlipAlphaImage( 200, 200, AN_Source[i].source_images[abs_frame], &AN_Source[i] );
                    }
                    else
                    {
                        if ( AN_Source[i].color_flag )
                            DrawFlipColorImage( 200, 200, AN_Source[i].source_images[abs_frame], AN_Source[i].color );
                        else
                            DrawFlipImage( 200, 200, AN_Source[i].source_images[abs_frame] );
                    }
                }
                else
                {
                    if ( AN_Source[i].source_images[abs_frame]->alphaflag )
                    {
                        DrawAlphaImage( 200, 200, AN_Source[i].source_images[abs_frame], &AN_Source[i] );
                    }
                    else
                    {
                        if ( AN_Source[i].color_flag )
                            DrawColorImage( 200, 200, AN_Source[i].source_images[abs_frame], AN_Source[i].color );
                        else
                            DrawImage( 200, 200, AN_Source[i].source_images[abs_frame] );
                    }
                }

            sprintf( Source_screen_text, "ACT : %d, FRAME : %d", ani, frame );
        }
    }

    Form1->Flip( SOURCE_SCREEN );
}

void Render_editscreen( void )
{
    int layer = 0;
    bool flip_draw;
    int i, xstep, ystep;
    int ani = 0;
    DWORD *temp = Offscreen;

    strcpy( Edit_screen_text, "No Edit Image." );

    if ( BackColorFlag )
    {
        _asm
        {
            mov edi, dword ptr [temp]
            mov eax, dword ptr [BackColor]
  //          mov ebx, eax
  //          shl eax, 16
  //          or eax, ebx

            mov ecx, BACK_SIZEX * BACK_SIZEY
            rep stosd
        }
    }
    else
    {
        memcpy( Offscreen, BackMemory, BACK_SIZEX * BACK_SIZEY * 4 );
    }

    for ( i = 0; i < 8; i++ )
    {
        flip_draw = false;

        ani = Global_edit_info.now_animation;
        int frame = Global_edit_info.now_frame;
        int dir = Global_edit_info.now_direction;
        layer = 0;
        LPEDITFRAME tempframe = GetEditFrameSortindex( i, ani, frame, dir, layer );

        // 이미지가 로딩된 상태일 경우 화면에 표시
        if ( AN_Source[layer].loaded_flag && Use_edit_animation[ani] )
        {
            xstep = ystep = 0;

            if ( tempframe && tempframe->index != -1 && (tempframe->draw_mode_and_alpha>>5) > 0 )
            {
                int dir = (Global_edit_info.now_direction + tempframe->direction_gap + AN_Source[i].max_direction + 1) % (AN_Source[i].max_direction + 1);
                dir = (dir + Global_edit_animation[ani]->direction_link[dir] )%8;

                switch( dir )
                {
                    // 아래쪽 보고 있을때
                    case 0:
                        xstep = tempframe->x_gap;
                        ystep = tempframe->y_gap + tempframe->z_gap;
                    break;
                    // 오른쪽아래 보고 있을때
                    case 1:
                        xstep = tempframe->x_gap + (tempframe->z_gap / 2);
                        ystep = tempframe->y_gap + tempframe->z_gap - (tempframe->x_gap / 2);
                    break;
                    // 오른쪽 보고 있을때
                    case 2:
                        xstep = tempframe->z_gap;
                        ystep = tempframe->y_gap - tempframe->x_gap;
                    break;
                    // 오른쪽위 보고 있을때
                    case 3:
                        xstep = -tempframe->x_gap + ( tempframe->z_gap / 2);
                        ystep = tempframe->y_gap - tempframe->z_gap - (tempframe->x_gap / 2);
                    break;
                    // 위쪽 보고 있을때
                    case 4:
                        xstep = -tempframe->x_gap;
                        ystep = tempframe->y_gap - tempframe->z_gap;
                    break;
                    // 왼쪽위 보고 있을때
                    case 5:
                        xstep = -tempframe->x_gap - ( tempframe->z_gap / 2);
                        ystep = tempframe->y_gap - tempframe->z_gap + (tempframe->x_gap / 2);
                    break;
                    // 왼쪽 보고 있을때
                    case 6:
                        xstep = -tempframe->z_gap;
                        ystep = tempframe->y_gap + tempframe->x_gap;
                    break;
                    // 왼쪽아래 보고 있을때
                    case 7:
                        xstep = tempframe->x_gap - ( tempframe->z_gap / 2);
                        ystep = tempframe->y_gap + tempframe->z_gap + (tempframe->x_gap / 2);
                    break;
                }

                if ( AN_Source[layer].flip_flag && (dir%4) && dir > 4 )   // 뒤집어 찍어야 할 상황이라면..
                {
                    flip_draw = true;
                    dir = 4 - (dir%4);
                }

                int abs_frame = tempframe->index + AN_Source[layer].animation_source.direction_total_frame * dir;

                if ( flip_draw )
                {
                    if ( AN_Source[layer].source_images[abs_frame]->alphaflag )
                    {
                        DrawFlipAlphaImage( 200 + xstep, 200 + ystep, AN_Source[layer].source_images[abs_frame], &AN_Source[layer] );
                    }
                    else
                    {
                        if ( (tempframe->draw_mode_and_alpha>>5) > 1 )
                            DrawOtherFlipImage( 200 + xstep, 200 + ystep, AN_Source[layer].source_images[abs_frame], tempframe->draw_mode_and_alpha );
                        else
                            DrawFlipImage( 200 + xstep, 200 + ystep, AN_Source[layer].source_images[abs_frame] );
                    }
                }
                else
                {
                    if ( AN_Source[layer].source_images[abs_frame]->alphaflag )
                    {
                        DrawAlphaImage( 200 + xstep, 200 + ystep, AN_Source[layer].source_images[abs_frame], &AN_Source[layer] );
                    }
                    else
                    {
                        if ( (tempframe->draw_mode_and_alpha>>5) > 1 )
                            DrawOtherImage( 200 + xstep, 200 + ystep, AN_Source[layer].source_images[abs_frame], tempframe->draw_mode_and_alpha );
                        else
                            DrawImage( 200 + xstep, 200 + ystep, AN_Source[layer].source_images[abs_frame] );
                    }
                }

                sprintf( Edit_screen_text, "ACT : %s, FRAME : %d", Form2->EditAnimationList->Items->Strings[ani].c_str(), frame );
            }
        }
    }

    Form1->Flip( EDIT_SCREEN );
}
