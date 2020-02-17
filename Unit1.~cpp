//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "desktop_pro.h"
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "mss.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"


DWORD FPS[2] = { 33, 16 };

TForm1 *Form1;
HAUDIO SoundHandle[10000];
S32 Which=0;
TTreeNode *SoundTree[10000];
DWORD Offscreen[BACK_SIZEX * BACK_SIZEY];
DWORD BackMemory[BACK_SIZEX * BACK_SIZEY];
bool WantToQuit = false;
int max_enable_animation;
bool Use_edit_animation[100];
char Source_screen_text[255];
char Edit_screen_text[255];
DWORD BackColor = 0;
bool BackColorFlag = true;
LAYER AN_Source[8];
DEVMODE before_desktop, full_desktop;

LPEDITANIMATION *Global_edit_animation;

EDITINFO Global_edit_info;

DWORD g_animationtick[2] = { 100, 30 };

/*
				this->Effect_RB_Table[EFFECT_LIGHTTEN ][back][src] = max(back,src);
				this->Effect_RB_Table[EFFECT_DODGE    ][back][src] = (long)((back*32)/(32.0-src));
				this->Effect_RB_Table[EFFECT_SCREEN   ][back][src] = ( 31 - ( ( (31-src) * (31-back) ) >>5 ) );
				this->Effect_RB_Table[EFFECT_DIFFERENT][back][src] = (max(back,src)-min(back,src));
				this->Effect_RB_Table[EFFECT_H_ALPHA  ][back][src] = (back>>1) + (src>>1);
*/

float XterGetCurrentTimeInSec( void )
{
	static bool bFirst = true;
	static LARGE_INTEGER freq;
	static LARGE_INTEGER initial;

	if (bFirst)
	{
		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&initial);
		bFirst = false;
	}

	LARGE_INTEGER counter;
	QueryPerformanceCounter(&counter);
	return (float)((long double)
		(counter.QuadPart - initial.QuadPart) / 
		(long double) freq.QuadPart);
}



//---------------------------------------------------------------------------
void DirectionLinkCheck_refresh( int ani, int direction )
{
    if ( Global_edit_animation[ani]->direction_link[direction] )
    {
        Form1->DirectionLinkCheck->Checked = true;
        Form1->DirectionLinkGap->Text = Global_edit_animation[ani]->direction_link[direction];
    }
    else
    {
        Form1->DirectionLinkCheck->Checked = false;
        Form1->DirectionLinkGap->Text = Global_edit_animation[ani]->direction_link[direction];
    }
}

void Clear_global_animation( int animation )
{
    LPEDITFRAMELAYER    tempframe, nextframe;
    int i = animation;

    if ( Global_edit_animation[i] )
    {
        tempframe = Global_edit_animation[i]->edit_frame.next_node;

        while( tempframe )
        {
            nextframe = tempframe->Delete();
            free( tempframe );
            tempframe = NULL;
            tempframe = nextframe;
        }

        Global_edit_animation[i]->total_frame = 0;
        memset( Global_edit_animation[i]->direction_link, 0, sizeof( Global_edit_animation[i]->direction_link ) );
    }
}

LPEDITFRAME GetEditFrame( int layer, int animation, int frame )
{
    int cnt = 0;
    LPEDITFRAMELAYER tempframe;

    tempframe = &Global_edit_animation[animation]->edit_frame;

    while( tempframe )
    {
        if ( cnt == frame )
        {
            return &tempframe->Edit_frame[layer];
        }

        tempframe = tempframe->next_node;
        cnt++;
    }

    return NULL;
}

LPEDITFRAME GetEditFrameSortindex( int layer, int animation, int frame, int direction, int &returnlayer )
{
    int cnt = 0;
    LPEDITFRAMELAYER tempframe;

    tempframe = &Global_edit_animation[animation]->edit_frame;

    while( tempframe )
    {
        if ( cnt == frame )
        {
            for ( int i = 0; i < 8; i++ )
                if ( tempframe->Edit_frame[i].sort_index[direction] == layer )
                {
                    returnlayer = i;
                    return &tempframe->Edit_frame[i];
                }
        }

        tempframe = tempframe->next_node;
        cnt++;
    }

    returnlayer = 0;
    return NULL;
}


LPEDITFRAMELAYER GetEditFrameLayer( int animation, int frame )
{
    int cnt = 0;
    LPEDITFRAMELAYER tempframe;

    tempframe = &Global_edit_animation[animation]->edit_frame;

    while( tempframe )
    {
        if ( cnt == frame )
        {
            return tempframe;
        }

        tempframe = tempframe->next_node;
        cnt++;
    }

    return NULL;
}

void Refresh_sorting( void )
{
    int ani, dir, frame;
    int i, j;

    ani = Global_edit_info.now_animation;
    dir = Global_edit_info.now_direction;
    frame = Global_edit_info.now_frame;

    LPEDITFRAMELAYER tempframe = GetEditFrameLayer( ani, frame );

    Form1->Edit_ListBox->Clear();

    if ( Use_edit_animation[ani] && tempframe )
    {
        for ( i = 0; i < 8; i++ )
        {
            if ( tempframe->Edit_frame[i].sort_index[dir] == 0 )
            {
                Form1->Edit_ListBox->Items->Add( AN_Source[i].filename );
                continue;
            }

            for ( j = 0; j < 8; j++ )
            {
                if ( tempframe->Edit_frame[j].sort_index[dir] == i )
                {
                    Form1->Edit_ListBox->Items->Add( AN_Source[j].filename );
                    break;
                }
            }
        }
    }
}

int GetEditLayer( int index )
{
    int ani, dir, frame;
    int i, j;

    if ( index == -1 )
        return -1;

    ani = Global_edit_info.now_animation;
    dir = Global_edit_info.now_direction;
    frame = Global_edit_info.now_frame;

    LPEDITFRAMELAYER tempframe = GetEditFrameLayer( ani, frame );

    if ( Use_edit_animation[ani] && tempframe )
    {
        for ( i = 0; i < 8; i++ )
            if ( tempframe->Edit_frame[i].sort_index[dir] == index )
                return i;
    }

    return -1;
}

void AllClear( void )
{
    char tempstring[50];
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, sound;
    LPEDITSOUNDDATA tempdata;
    TTreeNode *temp;

    temp = Form1->SoundTreeView->Items[0].GetFirstNode();

    while( temp )
    {
        if ( temp->Data )
        {
            tempdata = (LPEDITSOUNDDATA)temp->Data;

            if ( tempdata->datasize == sizeof( EDITSOUNDDATA ) )
            {
                i = tempdata->animation;
                frame = tempdata->frame;
                sound = tempdata->soundindex;

                tempframe = GetEditFrameLayer( i, frame );

                if ( Use_edit_animation[i] && tempframe )
                {
                    for ( j = 0; j < 5; j++ )
                    {
                        if ( tempframe->sound_index[j] == sound )
                        {
                            tempframe->sound_index[j] = -1;
                            if ( temp->Data )
                            {
                                delete temp->Data;
                                temp->Data = NULL;
                            }
                            Form1->SoundTreeView->Items->Delete( temp );
                            temp = Form1->SoundTreeView->Items[0].GetFirstNode();
                            goto next;
                        }
                    }

                    if ( temp && temp->Data )
                    {
                        delete temp->Data;
                        temp->Data = NULL;
                        Form1->SoundTreeView->Items->Delete( temp );
                    }

next:;
                }
            }
        }

        temp = temp->GetNext();
    }

    for ( i = 0; i < max_enable_animation; i++ )
        Clear_global_animation( i );

    for ( i = 0; i < 8; i++ )
        AN_Source[i].Clear();

    memset( &Global_edit_info, 0, sizeof( Global_edit_info ) );

    memset( Use_edit_animation, 0, sizeof( Use_edit_animation ) );
}

void Refresh_soundtreeview( void )
{
    char tempstring[50];
    LPEDITFRAMELAYER tempframe;
    int i, j, k, frame, sound;
    LPEDITSOUNDDATA tempdata;
    TTreeNode *temp;

    temp = Form1->SoundTreeView->Items[0].GetFirstNode();

    while( temp )
    {
        if ( temp->Data )
        {
            tempdata = (LPEDITSOUNDDATA)temp->Data;

            if ( tempdata->datasize == sizeof( EDITSOUNDDATA ) )
            {
                delete temp->Data;
                temp->Data = NULL;
                Form1->SoundTreeView->Items->Delete( temp );
                temp = Form1->SoundTreeView->Items[0].GetFirstNode();
                goto next;
            }
        }

        temp = temp->GetNext();
next:;
    }

    for ( i = 0; i < max_enable_animation; i++ )
    {
        for ( j = 0; j < Global_edit_animation[i]->total_frame; j++ )
        {
            tempframe = GetEditFrameLayer( i, j );

            if ( Use_edit_animation[i] && tempframe )
            {
                for ( k = 0; k < 5; k++ )
                {
                    if ( tempframe->sound_index[k] != -1 )
                    {
                        int soundindex = tempframe->sound_index[k];
                        temp = Form1->SoundTreeView->Items[0].GetFirstNode();
                        while( temp )
                        {
                            LPSOUNDDATA tempsound = (LPSOUNDDATA)temp->Data;

                            if ( tempsound->datasize == sizeof( SOUNDDATA ) && tempsound->soundindex == soundindex )
                            {
                                sprintf( tempstring, "A:%d,F:%d", i, j );
                                TTreeNode *temptree = Form1->SoundTreeView->Items->AddChild( temp, tempstring );
                                temptree->Data = new EDITSOUNDDATA;
                                LPEDITSOUNDDATA tempeditdata = (LPEDITSOUNDDATA)temptree->Data;
                                tempeditdata->datasize = sizeof( EDITSOUNDDATA );
                                tempeditdata->animation = i;
                                tempeditdata->frame = j;
                                tempeditdata->soundindex = soundindex;
                            }

                            temp = temp->GetNext();
                        }
                    }
                }
            }
        }
    }
}



BOOL FrameInfo_refresh( int layer, int ani, int frame )
{
    LPEDITFRAMELAYER tempframe;

    tempframe = GetEditFrameLayer( ani, frame );

    if ( Use_edit_animation[ani] && tempframe )
    {
        Form1->Frame_X->Value = tempframe->Edit_frame[layer].x_gap;
        Form1->Frame_Y->Value = tempframe->Edit_frame[layer].y_gap;
        Form1->Frame_Z->Value = tempframe->Edit_frame[layer].z_gap;

        Form1->OutputType->ItemIndex = tempframe->Edit_frame[layer].draw_mode_and_alpha>>5;
        Form1->BlendValue->Value = tempframe->Edit_frame[layer].draw_mode_and_alpha&0x1f;

        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Animation_sourcescreen( float fTime )
{
    int i;
    int ani = 0;

    for ( i = 0; i < 8; i++ )
    {
        // 이미지가 로딩된 상태일 경우 화면에 표시
        if ( AN_Source[i].loaded_flag )
        {
            ani = AN_Source[i].now_animation;

            if ( AN_Source[i].playing_flag )
            {
                int abs_framecount = AN_Source[i].animation_source.abs_framecount[ani];
                AN_Source[i].now_frame=((int)(fTime/BASICFRAMETIME))%abs_framecount;
//                if ( AN_Source[i].now_frame >= abs_framecount )
  //                  AN_Source[i].now_frame = 0;
            }
        }
    }
}

void Animation_editscreen( float fTime )
{
    int i, j;
    int ani = 0;

//        for ( i = 0; i < 8; i++ )
        {
        // 이미지가 로딩된 상태일 경우 화면에 표시
//            if ( AN_Source[i].loaded_flag )
            {
                ani = Global_edit_info.now_animation;
                if ( Global_edit_info.playing_flag )
                {
                    int abs_framecount = Global_edit_animation[ani]->total_frame;
                    int timecal = fTime/Global_edit_animation[ani]->total_time;
                    float nowtime = fTime - ((float)timecal * Global_edit_animation[ani]->total_time);

                    DWORD frame = 0;

                    LPEDITFRAMELAYER tempframedata = &Global_edit_animation[ani]->edit_frame;

                    while( tempframedata )
                    {
                        nowtime -= tempframedata->frame_time;
                        if ( nowtime >= 0L )
                            frame++;
                        else
                            break;

                        tempframedata = tempframedata->next_node;
                    }

                    if ( frame >= abs_framecount )
                        frame = 0;

                    LPEDITFRAMELAYER tempframe = GetEditFrameLayer( ani, frame );

                    for ( j = 0; j < 5; j++ )
                    {
                        int sound = tempframe->sound_index[j];
                        if ( sound != -1 && Global_edit_info.now_frame < frame )
                            AIL_quick_play( SoundHandle[sound], 1 );
                    }

                    Global_edit_info.now_frame = frame;

                }
            }
        }
}


void __fastcall TForm1::MainLoop(TMessage & Msg)
{
    static DWORD nowtick = 0, beforetick = 0;
    float fStartTime = XterGetCurrentTimeInSec();

    while (!WantToQuit)
    {
        float   fTime = XterGetCurrentTimeInSec() - fStartTime;

        Application->ProcessMessages(); // let the app still react

        Animation_sourcescreen(fTime);
        Animation_editscreen(fTime);

        Render_sourcescreen();
        Render_editscreen();

        beforetick = nowtick;
    }
}

void TForm1::Flip( int flag )
{
    DWORD *temp, *dest;

    switch( flag )
    {
        case SOURCE_SCREEN:
            temp = (DWORD *)Source_screen->Picture->Bitmap->ScanLine[0];
        break;
        case EDIT_SCREEN:
            temp = (DWORD *)Edit_screen->Picture->Bitmap->ScanLine[0];
        break;
    }

    dest = (DWORD *)&Offscreen[BACK_GAPY * BACK_SIZEX + BACK_GAPX];

    _asm
    {
            mov edi, DWORD PTR [temp]
            mov esi, DWORD PTR [dest]
            mov eax, SCR_SIZEY
        again:
            mov ecx, SCR_SIZEX
            rep movsd
            sub edi, (BACK_SIZEX+BACK_GAPX*2)*4
            add esi, BACK_GAPX*2*4
            dec eax
            jnz again
    }

    switch( flag )
    {
        case SOURCE_SCREEN:
            Source_screen->Canvas->TextOutA( 10, 10, Source_screen_text );
            Source_screen->Repaint();
        break;
        case EDIT_SCREEN:
            Edit_screen->Canvas->TextOutA( 10, 10, Edit_screen_text );
            Edit_screen->Repaint();
        break;
    }
}




void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
    TTreeNode *temp;
    int i;

    for ( i = 0; i < 10000; i++ )
    {
        if ( SoundHandle[i] )
        {
            AIL_quick_unload( SoundHandle[i] );
            SoundHandle[i] = 0;
            if ( SoundTree[i]->Data )
            {
                delete SoundTree[i]->Data;
                SoundTree[i]->Data = NULL;
            }
        }
    }

    temp = SoundTreeView->Items[0].GetFirstNode();

    while( temp )
    {
        if ( temp->Data )
        {
            delete temp->Data;
            temp->Data = NULL;
        }

        temp = temp->GetNext();
    }

    for ( i = 0; i < 8; i++ )
        AN_Source[i].Clear();

    AIL_quick_shutdown();

    WantToQuit = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
    int i;
    LPSOUNDDATA temp;
    char filename[255];
    AIL_set_redist_directory( "" );

    BackColor = clBlack;

    char dispname[255];

    int cnt = 0;
    while( true )
    {
        if ( !EnumDisplaySettings( NULL, cnt, &before_desktop ) )
            break;

        if ( before_desktop.dmPelsWidth == Screen->Width && before_desktop.dmPelsHeight == Screen->Height )
            break;

        cnt++;
    }

    cnt = 0;
    while( true )
    {
        if ( !EnumDisplaySettings( NULL, cnt, &full_desktop ) )
            break;

        if ( full_desktop.dmPelsWidth == 800 && full_desktop.dmPelsHeight == 600 && full_desktop.dmBitsPerPel == 16 )
            break;

        cnt++;
    }

    // Miles Sound 초기화
    if (AIL_quick_startup(1,1,44100,8,1) == 0) // open digital and MIDI
    {
        ::MessageBox( 0, AIL_last_error(), "Couldn't open MSS.", MB_OK );
    }

    // 효과음 존재하는 것들 효과음 리스트에 최초 표시하기
    for ( i = 0; i < 10000; i++ )
    {
        sprintf( filename, ".\\sound\\%06d.wav", i );

        if ( FileExists( filename ) )
        {
            SoundHandle[i] = AIL_quick_load( filename );
            sprintf( filename, "%06d.wav", i );
            SoundTree[i] = SoundTreeView->Items->Add( SoundTree[i], filename );
            SoundTree[i]->Data = new SOUNDDATA;
            temp = (LPSOUNDDATA)SoundTree[i]->Data;
            temp->datasize = sizeof( SOUNDDATA );
            temp->soundindex = i;
        }
    }

    for ( i = 0; i < 8; i++ )
        sprintf( AN_Source[i].filename, "Layer %d ( no image )", i + 1 );

    Source_screen->Picture->Bitmap->Width = 400;
    Source_screen->Picture->Bitmap->Height = 400;
    Source_screen->Picture->Bitmap->PixelFormat = pf32bit;

    Edit_screen->Picture->Bitmap->Width = 400;
    Edit_screen->Picture->Bitmap->Height = 400;
    Edit_screen->Picture->Bitmap->PixelFormat = pf32bit;

    // 메인 루프로~
    PostMessage(Handle, WM_ENTERMAINLOOP, 0, 0);


}
//---------------------------------------------------------------------------



void __fastcall TForm1::SoundTreeViewDblClick(TObject *Sender)
{
    LPSOUNDDATA tempdata;
    char soundname[50];
    TTreeNode *temp = SoundTreeView->Selected;
    tempdata = (LPSOUNDDATA)temp->Data;

    // 효과음 넘버가 지정되어 있는것만 플레이 되도록
    if ( tempdata->datasize == sizeof( SOUNDDATA ) )
        AIL_quick_play( SoundHandle[tempdata->soundindex], 1 );
    else
    // 프레임에 넣어진 사운드를 더블 클릭한 경우에는 원본 사운드 들려줌
    {
        temp = temp->Parent;
        tempdata = (LPSOUNDDATA)temp->Data;

        if ( tempdata->datasize == sizeof( SOUNDDATA ) )
            AIL_quick_play( SoundHandle[tempdata->soundindex], 1 );
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Load_AN_buttonClick(TObject *Sender)
{
    int index = AN_ListBox->ItemIndex, i;

    if ( AllSourceSelect->Checked )
    {
        Application->MessageBoxA( "Already 'Selected All Layer'. So Cannot Loading. Please Select One Layer.",
        "Error", MB_OK | MB_TOPMOST );
        return;
    }

    if ( index > -1 )
    {
        if ( OpenAN3->Execute() )
        {
            Load_sourceimage( index, OpenAN3->FileName.c_str() );
            AN_ListBox->ItemIndex = index;
            AN_ListBox->OnClick( Sender );
            OpenAN3->FileName = "*.AN3";
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::AN_ListBoxClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;
    AllSourceSelect->Checked = false;
    AN_ListBox->ItemIndex = temp;
    AN_Select->Text = AN_ListBox->Items->Strings[AN_ListBox->ItemIndex];
    SourceAnimation->Text = AN_Source[temp].now_animation;
    SourceDirection->Text = AN_Source[temp].now_direction;
    SourceFrame->Text = AN_Source[temp].now_frame;
    AN_ViewCheck->Checked = AN_Source[temp].view_flag;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AllSourceSelectClick(TObject *Sender)
{
    if ( AllSourceSelect->Checked )
    {
        AN_ListBox->MultiSelect = true;
        AN_ListBox->SelectAll();
        AN_Select->Text = "전체 선택";
    }
    else
    {
        AN_ListBox->MultiSelect = false;
        AN_ListBox->ItemIndex = 0;
        AN_ListBox->OnClick( Sender );
    }
}
//---------------------------------------------------------------------------
// 소스 이미지의 바로 이전 동작으로 이동

void __fastcall TForm1::Before_AN_actionClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
            if ( AN_Source[temp].now_animation < 1 )
                AN_Source[temp].now_animation = AN_Source[temp].max_animation;
            else
                AN_Source[temp].now_animation--;

        SourceAnimation->Text = "전체";

        for ( temp = 0; temp < 8; temp++ )
        {
            int ani = AN_Source[temp].now_animation;

            if ( AN_Source[temp].now_frame >= AN_Source[temp].animation_source.abs_framecount[ani] )
                AN_Source[temp].now_frame = 0;
        }

        SourceFrame->Text = "전체";

    }
    else
    {
        if ( AN_Source[temp].now_animation < 1 )
            AN_Source[temp].now_animation = AN_Source[temp].max_animation;
        else
            AN_Source[temp].now_animation--;

        SourceAnimation->Text = AN_Source[temp].now_animation;

        int ani = AN_Source[temp].now_animation;

        if ( AN_Source[temp].now_frame >= AN_Source[temp].animation_source.abs_framecount[ani] )
            AN_Source[temp].now_frame = 0;

        SourceFrame->Text = AN_Source[temp].now_frame;
    }
}
//---------------------------------------------------------------------------
// 소스 이미지의 바로 이후 동작으로 이동

void __fastcall TForm1::Next_AN_actionClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
            if ( AN_Source[temp].now_animation == AN_Source[temp].max_animation )
                AN_Source[temp].now_animation = 0;
            else
                AN_Source[temp].now_animation++;

        SourceAnimation->Text = "전체";

        for ( temp = 0; temp < 8; temp++ )
        {
            int ani = AN_Source[temp].now_animation;

            if ( AN_Source[temp].now_frame >= AN_Source[temp].animation_source.abs_framecount[ani] )
                AN_Source[temp].now_frame = 0;
        }

        SourceFrame->Text = "전체";
    }
    else
    {
        if ( AN_Source[temp].now_animation == AN_Source[temp].max_animation )
            AN_Source[temp].now_animation = 0;
        else
            AN_Source[temp].now_animation++;

        SourceAnimation->Text = AN_Source[temp].now_animation;

        int ani = AN_Source[temp].now_animation;

        if ( AN_Source[temp].now_frame >= AN_Source[temp].animation_source.abs_framecount[ani] )
            AN_Source[temp].now_frame = 0;

        SourceFrame->Text = AN_Source[temp].now_frame;
    }

}
//---------------------------------------------------------------------------
// 소스 이미지의 바로 이전 방향으로 이동

void __fastcall TForm1::Before_AN_directionClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
            if ( AN_Source[temp].now_direction < 1 )
                AN_Source[temp].now_direction = AN_Source[temp].max_direction - 1;
            else
                AN_Source[temp].now_direction--;

        SourceDirection->Text = "전체";
    }
    else
    {
        if ( AN_Source[temp].now_direction < 1 )
            AN_Source[temp].now_direction = AN_Source[temp].max_direction;
        else
            AN_Source[temp].now_direction--;

        SourceDirection->Text = AN_Source[temp].now_direction;
    }

}
//---------------------------------------------------------------------------
// 소스 이미지의 바로 이후 방향으로 이동

void __fastcall TForm1::Next_AN_directionClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
            if ( AN_Source[temp].now_direction == AN_Source[temp].max_direction )
                AN_Source[temp].now_direction = 0;
            else
                AN_Source[temp].now_direction++;

        SourceDirection->Text = "전체";
    }
    else
    {
        if ( AN_Source[temp].now_direction == AN_Source[temp].max_direction )
            AN_Source[temp].now_direction = 0;
        else
            AN_Source[temp].now_direction++;

        SourceDirection->Text = AN_Source[temp].now_direction;
    }
}
//---------------------------------------------------------------------------
// 소스 이미지의 바로 이전 프레임으로 이동

void __fastcall TForm1::Before_AN_frameClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
            if ( AN_Source[temp].now_frame < 1 )
            {
                int ani = AN_Source[temp].now_animation;
                AN_Source[temp].now_frame = AN_Source[temp].animation_source.abs_framecount[ani];

                if ( AN_Source[temp].now_frame )
                    AN_Source[temp].now_frame--;
            }
            else
                AN_Source[temp].now_frame--;

        SourceFrame->Text = "전체";
    }
    else
    {
        if ( AN_Source[temp].now_frame < 1 )
        {
            int ani = AN_Source[temp].now_animation;
            AN_Source[temp].now_frame = AN_Source[temp].animation_source.abs_framecount[ani];

            if ( AN_Source[temp].now_frame )
                AN_Source[temp].now_frame--;
        }
        else
            AN_Source[temp].now_frame--;

        SourceFrame->Text = AN_Source[temp].now_frame;
    }
}
//---------------------------------------------------------------------------
// 소스 이미지의 바로 이후 프레임으로 이동

void __fastcall TForm1::Next_AN_frameClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
        {
            int ani = AN_Source[temp].now_animation;

            if ( AN_Source[temp].now_frame >= AN_Source[temp].animation_source.abs_framecount[ani] - 1 )
                AN_Source[temp].now_frame = 0;
            else
                AN_Source[temp].now_frame++;
        }

        SourceFrame->Text = "전체";
    }
    else
    {
        int ani = AN_Source[temp].now_animation;

        if ( AN_Source[temp].now_frame >= AN_Source[temp].animation_source.abs_framecount[ani] - 1 )
            AN_Source[temp].now_frame = 0;
        else
            AN_Source[temp].now_frame++;

        SourceFrame->Text = AN_Source[temp].now_frame;
    }
}
//---------------------------------------------------------------------------
// 소스 이미지의 에니메이션 플레이

void __fastcall TForm1::Play_AN_buttonClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
            AN_Source[temp].playing_flag = true;
    }
    else
        AN_Source[temp].playing_flag = true;
}
//---------------------------------------------------------------------------
// 소스 이미지의 에니메이션 플레이 중지

void __fastcall TForm1::Stop_AN_buttonClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount == 1 ) )
        return;

    // 전체 선택인 경우
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
            AN_Source[temp].playing_flag = false;
    }
    else
        AN_Source[temp].playing_flag = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AN_ViewCheckClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;

    if ( AN_ViewCheck->Checked == true && ( AllSourceSelect->Checked || temp == -1 || !AN_Source[temp].loaded_flag ) )
    {
        AN_ViewCheck->Checked = false;
        return;
    }

    AN_Source[temp].view_flag = AN_ViewCheck->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Del_AN_buttonClick(TObject *Sender)
{
    int index = AN_ListBox->ItemIndex, i;

    if ( AllSourceSelect->Checked )
    {
        if ( Application->MessageBoxA( "Do you want delete All Layer's Source Images?",
            "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
                    return;

        if ( Application->MessageBoxA( "One More Confirm! DO YOU WANT DELETE ALL LAYER'S SOURCE IMAGES?",
            "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
                    return;

        for ( i = 0; i < 8; i++ )
        {
            AN_Source[i].Clear();
            sprintf( AN_Source[i].filename, "Layer %d ( no image )", i + 1 );
        }

        AN_ListBox->Items->Clear();
        for( int i = 0; i < 8; i++ )
            AN_ListBox->Items->Add( AN_Source[i].filename );

        AN_ListBox->ItemIndex = 0;
        AN_ListBox->OnClick( Sender );

        return;
    }

    if ( index > -1 )
    {
        // 이미 로딩되어 있는 레이어가 있는 상태라면..
        if ( AN_Source[index].loaded_flag == true )
        {
            if ( Application->MessageBoxA( "Do you want to remove now Layer's Source Image?",
            "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
                    return;

            // 로딩되어있는 데이터 위에 로딩하는 경우라면.. 초기화
            AN_Source[index].Clear();
            sprintf( AN_Source[index].filename, "Layer %d ( no image )", index + 1 );

            AN_ListBox->Items->Clear();
            for( i = 0; i < 8; i++ )
                AN_ListBox->Items->Add( AN_Source[i].filename );

            AN_ListBox->ItemIndex = index;
            AN_ListBox->OnClick( Sender );
        }

    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InsDelAnimationButtonClick(TObject *Sender)
{
    int temp = AN_ListBox->ItemIndex;
    char message[50];

    if ( temp == -1 || AN_ListBox->SelCount > 1 || ( !AN_Source[temp].loaded_flag && AN_ListBox->SelCount < 1 ) )
        return;

    Form2->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditBeforeAnimationClick(TObject *Sender)
{
    int cnt = 0;
again:
    if ( Global_edit_info.now_animation < 1 )
        Global_edit_info.now_animation = max_enable_animation - 1;
    else
        Global_edit_info.now_animation--;

    if ( !Use_edit_animation[Global_edit_info.now_animation] )
    {
        cnt++;
        if ( cnt == max_enable_animation )
        {
            EditAnimation->Text = Global_edit_info.now_animation;
            return;
        }
        goto again;
    }

    if ( Global_edit_info.now_frame >= Global_edit_animation[Global_edit_info.now_animation]->total_frame - 1 )
        Global_edit_info.now_frame = Global_edit_animation[Global_edit_info.now_animation]->total_frame - 1;

    DirectionLinkCheck_refresh( Global_edit_info.now_animation, Global_edit_info.now_direction );

    EditAnimation->Text = Global_edit_info.now_animation;
    EditFrame->Text = Global_edit_info.now_frame;

    int layer = GetEditLayer( Edit_ListBox->ItemIndex );

    // 모든 레이어에 적용시키기
    if ( layer != -1 )
    {
        if ( Edit_ListBox->SelCount > 1 )
        {
            for ( layer = 0; layer < 8; layer++ )
                FrameInfo_refresh( layer, Global_edit_info.now_animation, Global_edit_info.now_frame );
        }
        // 각 레이어에 적용시키기
        else
            FrameInfo_refresh( layer, Global_edit_info.now_animation, Global_edit_info.now_frame );
    }

    int tempindex = Edit_ListBox->ItemIndex;
    Refresh_sorting();
    Edit_ListBox->ItemIndex = tempindex;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AllCopyButtonClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, k, m, o, frame, max_layerframe, layerframe;

    if ( Application->MessageBoxA( "Copy All SOURCE to EDIT. Do you want copy all?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
              return;

    for ( j = 0; j < max_enable_animation; j++ )
    {
        Clear_global_animation( j );

        max_layerframe = 0;
        for ( i = 0; i < 8; i++ )
        {
            layerframe = 0;
            if ( AN_Source[i].animation_source.direction_animation[j] )
            {
                Use_edit_animation[j] = true;

                tempframe = &Global_edit_animation[j]->edit_frame;

                for ( k = 0; k < AN_Source[i].animation_source.abs_framecount[j] - 1; k++ )
                {
                    for ( m = 0; m < FramePerSecond->ItemIndex + 1; m++ )
                    {
                    frame = AN_Source[i].animation_source.abs_framestart[j] + k;

                    tempframe->Edit_frame[i].index = frame;
                    tempframe->Edit_frame[i].draw_mode_and_alpha = NORMAL_PUT<<5;
                    tempframe->frame_time = BASICFRAMETIME;

                    for ( o = 0; o < 8; o++ )
                    memset( tempframe->Edit_frame[o].sort_index, o, sizeof( tempframe->Edit_frame[o].sort_index ) );

                    if ( tempframe->next_node )
                    {
                        tempframe = tempframe->next_node;
                    }
                    else
                        if ( (tempframe = tempframe->Insert() ) == NULL )
                            return;

                    layerframe++;
                    }
                }

                for ( m = 0; m < FramePerSecond->ItemIndex + 1; m++ )
                {
                frame = AN_Source[i].animation_source.abs_framestart[j] + k;

                tempframe->Edit_frame[i].index = frame;
                tempframe->Edit_frame[i].draw_mode_and_alpha = NORMAL_PUT<<5;

                for ( o = 0; o < 8; o++ )
                    memset( tempframe->Edit_frame[o].sort_index, o, sizeof( tempframe->Edit_frame[o].sort_index ) );

                if ( tempframe->next_node )
                {
                    tempframe = tempframe->next_node;
                }
                else
                    if ( (tempframe = tempframe->Insert() ) == NULL )
                        return;

                layerframe++;
                }
                layerframe--;
            }

            if ( layerframe > max_layerframe )
                max_layerframe = layerframe;
        }

        Global_edit_animation[j]->total_frame = max_layerframe + 1;
        Global_edit_animation[j]->total_time = (max_layerframe + 1) * BASICFRAMETIME;

    }

    Refresh_soundtreeview();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditNextAnimationClick(TObject *Sender)
{
    int cnt = 0;
again:
    if ( Global_edit_info.now_animation >= max_enable_animation - 1 )
        Global_edit_info.now_animation = 0;
    else
        Global_edit_info.now_animation++;

    if ( !Use_edit_animation[Global_edit_info.now_animation] )
    {
        cnt++;
        if ( cnt == max_enable_animation )
        {
            EditAnimation->Text = Global_edit_info.now_animation;
            return;
        }
        goto again;
    }

    if ( Global_edit_info.now_frame >= Global_edit_animation[Global_edit_info.now_animation]->total_frame - 1 )
        Global_edit_info.now_frame = Global_edit_animation[Global_edit_info.now_animation]->total_frame - 1;

    DirectionLinkCheck_refresh( Global_edit_info.now_animation, Global_edit_info.now_direction );

    EditAnimation->Text = Global_edit_info.now_animation;
    EditFrame->Text = Global_edit_info.now_frame;
    int tempindex = Edit_ListBox->ItemIndex;
    Refresh_sorting();
    Edit_ListBox->ItemIndex = tempindex;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Before_Edit_directionClick(TObject *Sender)
{
    int ani = Global_edit_info.now_animation;

    if ( Use_edit_animation[ani] )
    {
        Global_edit_info.max_direction = 0;

        for ( int i = 0; i < 8; i++ )
            if ( AN_Source[i].max_direction + 1 > Global_edit_info.max_direction )
                Global_edit_info.max_direction = AN_Source[i].max_direction + 1;

        if ( Global_edit_info.now_direction < 1 )
            Global_edit_info.now_direction = Global_edit_info.max_direction - 1;
        else
            Global_edit_info.now_direction--;

        EditDirection->Text = Global_edit_info.now_direction;

        DirectionLinkCheck_refresh( ani, Global_edit_info.now_direction );

        int tempindex = Edit_ListBox->ItemIndex;
        Refresh_sorting();
        Edit_ListBox->ItemIndex = tempindex;
    }
}


void __fastcall TForm1::Next_Edit_directionClick(TObject *Sender)
{
    int ani = Global_edit_info.now_animation;

    if ( Use_edit_animation[ani] )
    {
        Global_edit_info.max_direction = 0;

        for ( int i = 0; i < 8; i++ )
            if ( AN_Source[i].max_direction + 1 > Global_edit_info.max_direction )
                Global_edit_info.max_direction = AN_Source[i].max_direction + 1;

        if ( Global_edit_info.now_direction >= Global_edit_info.max_direction - 1 )
            Global_edit_info.now_direction = 0;
        else
            Global_edit_info.now_direction++;

        EditDirection->Text = Global_edit_info.now_direction;

        DirectionLinkCheck_refresh( ani, Global_edit_info.now_direction );

        int tempindex = Edit_ListBox->ItemIndex;
        Refresh_sorting();
        Edit_ListBox->ItemIndex = tempindex;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Before_Edit_frameClick(TObject *Sender)
{
    if ( Global_edit_info.now_frame < 1 )
        Global_edit_info.now_frame = Global_edit_animation[Global_edit_info.now_animation]->total_frame - 1;
    else
        Global_edit_info.now_frame--;

    EditFrame->Text = Global_edit_info.now_frame;

    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;
//    Frame_X->Value = 0;
//    Frame_Y->Value = 0;
//    Frame_Z->Value = 0;

    if ( layer == -1 )
        return;

    // 모든 레이어에 적용시키기
    if ( Edit_ListBox->SelCount > 1 )
    {
        for ( layer = 0; layer < 8; layer++ )
            FrameInfo_refresh( layer, i, j );
    }
    // 각 레이어에 적용시키기
    else
        FrameInfo_refresh( layer, i, j );

    int tempindex = Edit_ListBox->ItemIndex;
    Refresh_sorting();
    Edit_ListBox->ItemIndex = tempindex;

    tempframe = GetEditFrameLayer( i, j );
    Edit1->Text = tempframe->frame_time;
}

//---------------------------------------------------------------------------


void __fastcall TForm1::Next_Edit_frameClick(TObject *Sender)
{
    if ( Global_edit_info.now_frame >= Global_edit_animation[Global_edit_info.now_animation]->total_frame - 1 )
        Global_edit_info.now_frame = 0;
    else
        Global_edit_info.now_frame++;

    EditFrame->Text = Global_edit_info.now_frame;

    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;
//    Frame_X->Value = 0;
//    Frame_Y->Value = 0;
//    Frame_Z->Value = 0;

    if ( layer == -1 )
        return;

    // 모든 레이어에 적용시키기
    if ( Edit_ListBox->SelCount > 1 )
    {
        for ( layer = 0; layer < 8; layer++ )
            FrameInfo_refresh( layer, i, j );
    }
    // 각 레이어에 적용시키기
    else
        FrameInfo_refresh( layer, i, j );

    int tempindex = Edit_ListBox->ItemIndex;
    Refresh_sorting();
    Edit_ListBox->ItemIndex = tempindex;
    tempframe = GetEditFrameLayer( i, j );
    Edit1->Text = tempframe->frame_time;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Play_Edit_buttonClick(TObject *Sender)
{
    Global_edit_info.playing_flag = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Stop_Edit_buttonClick(TObject *Sender)
{
    Global_edit_info.playing_flag = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy_all_frame_selectedClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, k, frame, layerframe;
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || AN_ListBox->SelCount > 1 )
    {
        Application->MessageBoxA( "Please Select Layer first.", "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    if ( Application->MessageBoxA( "Now Selected Layer's ACTION ALL Copy to EDIT. Before ACTION EDIT DATA will deleted. Do you want it?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
              return;

    i = AN_Source[temp].now_animation;
    j = Global_edit_info.now_animation;
    layerframe = 0;
    if ( AN_Source[temp].animation_source.direction_animation[i] )
    {
        Use_edit_animation[j] = true;

        tempframe = &Global_edit_animation[j]->edit_frame;

        for ( k = 0; k < AN_Source[temp].animation_source.abs_framecount[i] - 1; k++ )
        {
            frame = AN_Source[temp].animation_source.abs_framestart[i] + k;

            tempframe->Edit_frame[temp].index = frame;
            tempframe->Edit_frame[temp].draw_mode_and_alpha = NORMAL_PUT<<5;
            tempframe->Edit_frame[temp].direction_gap = AN_Source[temp].now_direction - Global_edit_info.now_direction;
            memset( tempframe->Edit_frame[temp].sort_index, temp, sizeof( tempframe->Edit_frame[temp].sort_index ) );

            if ( tempframe->next_node )
            {
                tempframe = tempframe->next_node;
            }
            else
                if ( (tempframe = tempframe->Insert() ) == NULL )
                    return;

            layerframe++;
        }

        frame = AN_Source[temp].animation_source.abs_framestart[i] + k;

        tempframe->Edit_frame[temp].index = frame;
        tempframe->Edit_frame[temp].draw_mode_and_alpha = NORMAL_PUT<<5;
        tempframe->Edit_frame[temp].direction_gap = AN_Source[temp].now_direction - Global_edit_info.now_direction;
        memset( tempframe->Edit_frame[temp].sort_index, temp, sizeof( tempframe->Edit_frame[temp].sort_index ) );
    }

    if ( layerframe > Global_edit_animation[j]->total_frame )
    {
            Global_edit_animation[j]->total_frame = layerframe;
    }

    Refresh_soundtreeview();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy_all_frame_allClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, k, l, frame, layerframe, max_layerframe = 0;
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 || AN_ListBox->SelCount < 2 )
    {
        Application->MessageBoxA( "Please Select ALL Layer first.", "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    if ( Application->MessageBoxA( "Copy ALL Layer and ALL ACT to Edit. Will be deleted before Edit datas. Do you want it?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
              return;

    j = Global_edit_info.now_animation;

    for ( l = 0; l < 8; l++ )
    {
        i = AN_Source[l].now_animation;
        layerframe = 0;

        if ( AN_Source[l].animation_source.direction_animation[i] )
        {
            Use_edit_animation[j] = true;

            tempframe = &Global_edit_animation[j]->edit_frame;

            for ( k = 0; k < AN_Source[l].animation_source.abs_framecount[i] - 1; k++ )
            {
                frame = AN_Source[l].animation_source.abs_framestart[i] + k;

                tempframe->Edit_frame[l].index = frame;
                tempframe->Edit_frame[l].draw_mode_and_alpha = NORMAL_PUT<<5;
                tempframe->Edit_frame[l].direction_gap = AN_Source[l].now_direction - Global_edit_info.now_direction;
                memset( tempframe->Edit_frame[l].sort_index, l, sizeof( tempframe->Edit_frame[l].sort_index ) );

                if ( tempframe->next_node )
                {
                    tempframe = tempframe->next_node;
                }
                else
                    if ( (tempframe = tempframe->Insert() ) == NULL )
                        return;

                layerframe++;
            }

            frame = AN_Source[l].animation_source.abs_framestart[i] + k;

            tempframe->Edit_frame[l].index = frame;
            tempframe->Edit_frame[l].draw_mode_and_alpha = NORMAL_PUT<<5;
            tempframe->Edit_frame[l].direction_gap = AN_Source[l].now_direction - Global_edit_info.now_direction;
            memset( tempframe->Edit_frame[l].sort_index, l, sizeof( tempframe->Edit_frame[l].sort_index ) );
        }

        if ( layerframe > max_layerframe )
            max_layerframe = layerframe;
    }

    Global_edit_animation[j]->total_frame = max_layerframe + 1;
    Refresh_soundtreeview();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Append_frameClick(TObject *Sender)
{
    bool firstnode = false;
    LPEDITFRAMELAYER tempframe;
    int i, j, frame;
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 )
    {
        Application->MessageBoxA( "Please Select One or All Layer first.", "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    // 전체 레이어 한 프레임 복사
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
        {
            i = AN_Source[temp].now_animation;
            j = Global_edit_info.now_animation;
            if ( AN_Source[temp].animation_source.direction_animation[i] )
            {
                Use_edit_animation[j] = true;

                if ( !firstnode )
                {
                    tempframe = GetEditFrameLayer( j, Global_edit_info.now_frame );
                    if ( (tempframe = tempframe->Insert()) == NULL )
                        return;

                    firstnode = true;
                }
                else
                    tempframe = GetEditFrameLayer( j, Global_edit_info.now_frame + 1 );

                frame = AN_Source[temp].animation_source.abs_framestart[i] + AN_Source[temp].now_frame;
                tempframe->Edit_frame[temp].index = frame;
                tempframe->Edit_frame[temp].draw_mode_and_alpha = NORMAL_PUT<<5;
                tempframe->Edit_frame[temp].direction_gap = AN_Source[temp].now_direction - Global_edit_info.now_direction;
                tempframe->frame_time = BASICFRAMETIME;
                memset( tempframe->Edit_frame[temp].sort_index, temp, sizeof( tempframe->Edit_frame[temp].sort_index ) );
            }
        }

        if ( firstnode )
        {
            Global_edit_animation[j]->total_frame++;
            Global_edit_animation[j]->total_time += BASICFRAMETIME;
        }

        Next_Edit_frame->OnClick( Sender );
        Refresh_soundtreeview();
    }
    // 한 레이어의 한 프레임만 복사
    else
    {
        i = AN_Source[temp].now_animation;
        j = Global_edit_info.now_animation;
        if ( AN_Source[temp].animation_source.direction_animation[i] )
        {
            Use_edit_animation[j] = true;

            tempframe = GetEditFrameLayer( j, Global_edit_info.now_frame );
            if ( (tempframe = tempframe->Insert()) == NULL )
                return;

            frame = AN_Source[temp].animation_source.abs_framestart[i] + AN_Source[temp].now_frame;
            tempframe->Edit_frame[temp].index = frame;
            tempframe->Edit_frame[temp].draw_mode_and_alpha = NORMAL_PUT<<5;
            tempframe->Edit_frame[temp].direction_gap = AN_Source[temp].now_direction - Global_edit_info.now_direction;
            tempframe->frame_time = BASICFRAMETIME;
            memset( tempframe->Edit_frame[temp].sort_index, temp, sizeof( tempframe->Edit_frame[temp].sort_index ) );
            Global_edit_animation[j]->total_frame++;
            Global_edit_animation[j]->total_time += BASICFRAMETIME;
            Next_Edit_frame->OnClick( Sender );
            Refresh_soundtreeview();
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy_frameClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame;
    int temp = AN_ListBox->ItemIndex;

    if ( temp == -1 )
    {
        Application->MessageBoxA( "Please Select Edit one or All Layer first.", "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    // 전체 레이어 한 프레임 복사
    if ( AN_ListBox->SelCount > 1 )
    {
        for ( temp = 0; temp < 8; temp++ )
        {
            i = AN_Source[temp].now_animation;
            j = Global_edit_info.now_animation;
            if ( AN_Source[temp].animation_source.direction_animation[i] )
            {
                Use_edit_animation[j] = true;

                tempframe = GetEditFrameLayer( j, Global_edit_info.now_frame );

                frame = AN_Source[temp].animation_source.abs_framestart[i] + AN_Source[temp].now_frame;
                tempframe->Edit_frame[temp].index = frame;
                tempframe->Edit_frame[temp].draw_mode_and_alpha = NORMAL_PUT<<5;
                tempframe->Edit_frame[temp].direction_gap = AN_Source[temp].now_direction - Global_edit_info.now_direction;
            }
        }
    }
    // 한 레이어의 한 프레임만 복사
    else
    {
        i = AN_Source[temp].now_animation;
        j = Global_edit_info.now_animation;
        if ( AN_Source[temp].animation_source.direction_animation[i] )
        {
            Use_edit_animation[j] = true;

            tempframe = GetEditFrameLayer( j, Global_edit_info.now_frame );

            frame = AN_Source[temp].animation_source.abs_framestart[i] + AN_Source[temp].now_frame;
            tempframe->Edit_frame[temp].index = frame;
            tempframe->Edit_frame[temp].draw_mode_and_alpha = NORMAL_PUT<<5;
            tempframe->Edit_frame[temp].direction_gap = AN_Source[temp].now_direction - Global_edit_info.now_direction;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CopyEditFrameClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame;

    // 전체 레이어 한 프레임 복사
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        if ( (tempframe = tempframe->Insert()) == NULL )
            return;

        tempframe->CopyFrame( tempframe->before_node );
        Global_edit_animation[i]->total_frame++;
        Global_edit_animation[i]->total_time += tempframe->frame_time;
        Next_Edit_frame->OnClick( Sender );
        Refresh_soundtreeview();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteEditFrameClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame;

    // 전체 레이어 한 프레임 복사
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe && Global_edit_animation[i]->total_frame > 0 )
    {
        Global_edit_animation[i]->total_time -= tempframe->frame_time;

        // 마지막 프레임이 삭제된 것이라면..
        if ( (tempframe = tempframe->Delete()) == NULL )
        {
            Before_Edit_frame->OnClick( Sender );
        }

        Global_edit_animation[i]->total_frame--;
        Refresh_soundtreeview();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DirectionLinkCheckClick(TObject *Sender)
{
    if ( DirectionLinkCheck->Checked )
    {
        DirectionLinkNext->Enabled = true;
        DirectionLinkBefore->Enabled = true;
        DirectionLinkGap->Enabled = true;
    }
    else
    {
        DirectionLinkNext->Enabled = false;
        DirectionLinkBefore->Enabled = false;
        DirectionLinkGap->Enabled = false;

        int ani = Global_edit_info.now_animation;
        int dir = Global_edit_info.now_direction;
        Global_edit_animation[ani]->direction_link[dir] = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DirectionLinkBeforeClick(TObject *Sender)
{
    int ani = Global_edit_info.now_animation;
    int dir = Global_edit_info.now_direction;
    int dir2 = Global_edit_animation[ani]->direction_link[dir];
    dir2 -= 1;
    dir2 = (dir2 + 8) % 8;
    Global_edit_animation[ani]->direction_link[dir] = dir2;
    DirectionLinkGap->Text = Global_edit_animation[ani]->direction_link[dir];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DirectionLinkNextClick(TObject *Sender)
{
    int ani = Global_edit_info.now_animation;
    int dir = Global_edit_info.now_direction;
    int dir2 = Global_edit_animation[ani]->direction_link[dir];
    dir2 += 1;
    dir2 = (dir2 + 8) % 8;
    Global_edit_animation[ani]->direction_link[dir] = dir2;
    DirectionLinkGap->Text = Global_edit_animation[ani]->direction_link[dir];
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Frame_XChange(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    if ( layer == -1 )
        return;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        // 모든 레이어에 적용시키기
        if ( Edit_ListBox->SelCount > 1 )
        {
            for ( layer = 0; layer < 8; layer++ )
            {
                tempframe->Edit_frame[layer].x_gap = Frame_X->Value;
            }
        }
        // 각 레이어에 적용시키기
        else
        {
            tempframe->Edit_frame[layer].x_gap = Frame_X->Value;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AllEditSelectClick(TObject *Sender)
{
    if ( AllEditSelect->Checked )
    {
        Edit_ListBox->MultiSelect = true;
        Edit_ListBox->SelectAll();
        Edit_Select->Text = "전체 선택";
        SortUp->Enabled = false;
        SortDown->Enabled = false;
    }
    else
    {
        Edit_ListBox->MultiSelect = false;
        Edit_ListBox->ItemIndex = 0;
        Edit_ListBox->OnClick( Sender );
        SortUp->Enabled = true;
        SortDown->Enabled = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit_ListBoxClick(TObject *Sender)
{
    int temp = Edit_ListBox->ItemIndex;
    AllEditSelect->Checked = false;
    Edit_ListBox->ItemIndex = temp;
    Edit_Select->Text = Edit_ListBox->Items->Strings[Edit_ListBox->ItemIndex];

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Frame_YChange(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    if ( layer == -1 )
        return;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        // 모든 레이어에 적용시키기
        if ( Edit_ListBox->SelCount > 1 )
        {
            for ( layer = 0; layer < 8; layer++ )
            {
                tempframe->Edit_frame[layer].y_gap = Frame_Y->Value;
            }
        }
        // 각 레이어에 적용시키기
        else
        {
            tempframe->Edit_frame[layer].y_gap = Frame_Y->Value;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Frame_ZChange(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    if ( layer == -1 )
        return;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        // 모든 레이어에 적용시키기
        if ( Edit_ListBox->SelCount > 1 )
        {
            for ( layer = 0; layer < 8; layer++ )
            {
                tempframe->Edit_frame[layer].z_gap = Frame_Z->Value;
            }
        }
        // 각 레이어에 적용시키기
        else
        {
            tempframe->Edit_frame[layer].z_gap = Frame_Z->Value;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::InsertSoundClick(TObject *Sender)
{
    char tempstring[50];
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, sound;
    LPSOUNDDATA tempdata;
    LPEDITSOUNDDATA tempeditdata;
    TTreeNode *temp = SoundTreeView->Selected;

    if ( !temp )
        return;

    tempdata = (LPSOUNDDATA)temp->Data;

    if ( tempdata->datasize != sizeof( SOUNDDATA ) )
        temp = temp->Parent;

    tempdata = (LPSOUNDDATA)temp->Data;

    // 전체 레이어 한 프레임 복사
    i = Global_edit_info.now_animation;
    frame = Global_edit_info.now_frame;
    sound = tempdata->soundindex;

    tempframe = GetEditFrameLayer( i, frame );

    if ( Use_edit_animation[i] && tempframe )
    {
        for ( j = 0; j < 5; j++ )
        {
            if ( tempframe->sound_index[j] == sound )
            {
                Application->MessageBoxA( "Already Inserted same sound.",
                "Caution", MB_OK | MB_TOPMOST );
                return;
            }
            else
            if ( tempframe->sound_index[j] == -1 )
            {
                tempframe->sound_index[j] = sound;
                sprintf( tempstring, "A:%d,F:%d", i, frame );
                TTreeNode *temptree = SoundTreeView->Items->AddChild( temp, tempstring );
                temptree->Data = new EDITSOUNDDATA;
                tempeditdata = (LPEDITSOUNDDATA)temptree->Data;
                tempeditdata->datasize = sizeof( EDITSOUNDDATA );
                tempeditdata->animation = i;
                tempeditdata->frame = frame;
                tempeditdata->soundindex = sound;
                return;
            }
        }

        Application->MessageBoxA( "One Frame Can insert Maximum 5 Sounds",
        "Caution", MB_OK | MB_TOPMOST );
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::DeleteSoundClick(TObject *Sender)
{
    char tempstring[50];
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, sound;
    LPEDITSOUNDDATA tempdata;
    TTreeNode *temp = SoundTreeView->Selected;

    if ( !temp )
        return;

    tempdata = (LPEDITSOUNDDATA)temp->Data;

    if ( tempdata->datasize != sizeof( EDITSOUNDDATA ) )
        return;

    i = tempdata->animation;
    frame = tempdata->frame;
    sound = tempdata->soundindex;

    tempframe = GetEditFrameLayer( i, frame );

    if ( Use_edit_animation[i] && tempframe )
    {
        for ( j = 0; j < 5; j++ )
        {
            if ( tempframe->sound_index[j] == sound )
            {
                tempframe->sound_index[j] = -1;
                if ( temp->Data )
                {
                    delete temp->Data;
                    temp->Data = NULL;
                }
                SoundTreeView->Items->Delete( temp );
                return;
            }
        }

        if ( temp->Data )
        {
            delete temp->Data;
            temp->Data = NULL;
        }
        SoundTreeView->Items->Delete( temp );
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::AllSoundDeleteClick(TObject *Sender)
{
    char tempstring[50];
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, sound;
    LPEDITSOUNDDATA tempdata;
    TTreeNode *temp;

    if ( Application->MessageBoxA( "All sound edit data Delete. Do you want it?",
                "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
                return;

    temp = SoundTreeView->Items[0].GetFirstNode();

    while( temp )
    {
        if ( temp->Data )
        {
            tempdata = (LPEDITSOUNDDATA)temp->Data;

            if ( tempdata->datasize == sizeof( EDITSOUNDDATA ) )
            {
                i = tempdata->animation;
                frame = tempdata->frame;
                sound = tempdata->soundindex;

                tempframe = GetEditFrameLayer( i, frame );

                if ( Use_edit_animation[i] && tempframe )
                {
                    for ( j = 0; j < 5; j++ )
                    {
                        if ( tempframe->sound_index[j] == sound )
                        {
                            tempframe->sound_index[j] = -1;
                            if ( temp->Data )
                            {
                                delete temp->Data;
                                temp->Data = NULL;
                            }
                            SoundTreeView->Items->Delete( temp );
                            temp = SoundTreeView->Items[0].GetFirstNode();
                            goto next;
                        }
                    }

                    if ( temp && temp->Data )
                    {
                        delete temp->Data;
                        temp->Data = NULL;
                        SoundTreeView->Items->Delete( temp );
                    }

next:;
                }
            }
        }

        temp = temp->GetNext();
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::OutputTypeClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;
    int index = OutputType->ItemIndex;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    if ( index == -1 || layer == -1 )
    {
        Application->MessageBoxA( "Nothing To edit layer. You should to copy one or All layer first.",
        "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    if ( index == 7 )
        BlendValue->Enabled = true;
    else
    {
        BlendValue->Enabled = false;
    }

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        // 모든 레이어에 적용시키기
        if ( Edit_ListBox->SelCount > 1 )
        {
            for ( layer = 0; layer < 8; layer++ )
            {
                tempframe->Edit_frame[layer].draw_mode_and_alpha = (index<<5)|BlendValue->Value;
            }
        }
        // 각 레이어에 적용시키기
        else
        {
            tempframe->Edit_frame[layer].draw_mode_and_alpha = (index<<5)|BlendValue->Value;
        }
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::BlendValueChange(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;
    int index = OutputType->ItemIndex;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    if ( index == -1 || layer == -1 || index != 7 )
        return;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        // 모든 레이어에 적용시키기
        if ( Edit_ListBox->SelCount > 1 )
        {
            for ( layer = 0; layer < 8; layer++ )
            {
                tempframe->Edit_frame[layer].draw_mode_and_alpha = (index<<5)|BlendValue->Value;
            }
        }
        // 각 레이어에 적용시키기
        else
        {
            tempframe->Edit_frame[layer].draw_mode_and_alpha = (index<<5)|BlendValue->Value;
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button26Click(TObject *Sender)
{
    if ( ColorDialog1->Execute() )
    {
        DWORD r, g, b;
        r = ColorDialog1->Color&0xff;
        g = (ColorDialog1->Color>>8)&0xff;
        b = (ColorDialog1->Color>>16)&0xff;
        BackColor = (0xff<<24)|(r<<16)|(g<<8)|b;
        BackColorFlag = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BackLoadingClick(TObject *Sender)
{
    BYTE r, g, b;
    int i, j;

    if ( OpenPictureDialog1->Execute() )
    {
        BackImage->Picture->LoadFromFile( OpenPictureDialog1->FileName );

        memset( BackMemory, 0, sizeof( BackMemory ) );

        int xsize = 400, ysize = 400;
        if ( BackImage->Picture->Bitmap->Width < xsize )
            xsize = BackImage->Picture->Bitmap->Width;
        if ( BackImage->Picture->Bitmap->Height < ysize )
            ysize = BackImage->Picture->Bitmap->Height;

        for ( i = 0; i < ysize; i++ )
        {
            BYTE *temp = (BYTE *)BackImage->Picture->Bitmap->ScanLine[i];

            for ( j = 0; j < xsize; j++ )
            {
                switch( BackImage->Picture->Bitmap->PixelFormat )
                {
                    case pf15bit:
                        BackMemory[(i + BACK_GAPY) * BACK_SIZEX + j + BACK_GAPX] = (WORD)temp[j * 2];
                        BackColorFlag = false;
                    break;
                    case pf16bit:
                        BackMemory[(i + BACK_GAPY) * BACK_SIZEX + j + BACK_GAPX] = (WORD)temp[j * 2];
                        BackColorFlag = false;
                    break;
                    case pf24bit:
                        r = temp[j * 3 + 2]>>3;
                        g = temp[j * 3 + 1]>>3;
                        b = temp[j * 3]>>3;
                        BackMemory[(i + BACK_GAPY) * BACK_SIZEX + j + BACK_GAPX] = (WORD)(((WORD)r<<10)|((WORD)g<<5)|b);
                        BackColorFlag = false;
                    break;
                    default:
                        Application->MessageBoxA( "16Bit or 24Bit BMP File Enable",
                        "Error", MB_OK | MB_TOPMOST );

                        BackColorFlag = true;
                    return;
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SortUpClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, dir, layer, now_sort;
    int tempindex = Edit_ListBox->ItemIndex;

    layer = GetEditLayer( tempindex );
    i = Global_edit_info.now_animation;
    dir = Global_edit_info.now_direction;
    j = Global_edit_info.now_frame;

    if ( layer == -1 )
    {
        Application->MessageBoxA( "First Copy Source and Select Sort Layer",
        "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        now_sort = tempframe->Edit_frame[layer].sort_index[dir];

        if ( !now_sort )
            return;

        for ( i = 0; i < 8; i++ )
            if ( tempframe->Edit_frame[i].sort_index[dir] == now_sort - 1 )
            {
                tempframe->Edit_frame[i].sort_index[dir] = now_sort;
                tempframe->Edit_frame[layer].sort_index[dir] = now_sort - 1;
                Refresh_sorting();
                Edit_ListBox->ItemIndex = tempindex - 1;
                break;
            }
    }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SortDownClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, dir, layer, now_sort;
    int tempindex = Edit_ListBox->ItemIndex;

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    dir = Global_edit_info.now_direction;
    j = Global_edit_info.now_frame;

    if ( layer == -1 )
    {
        Application->MessageBoxA( "First Copy Source and Select Sort Layer",
        "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        now_sort = tempframe->Edit_frame[layer].sort_index[dir];

        if ( now_sort >= 7 )
            return;

        for ( i = 0; i < 8; i++ )
            if ( tempframe->Edit_frame[i].sort_index[dir] == now_sort + 1 )
            {
                tempframe->Edit_frame[i].sort_index[dir] = now_sort;
                tempframe->Edit_frame[layer].sort_index[dir] = now_sort + 1;
                Refresh_sorting();
                Edit_ListBox->ItemIndex = tempindex+1;
                break;
            }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy_AnimationSortClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe, tempframe2;
    int i, j, k, dir, layer;

    i = Global_edit_info.now_animation;
    dir = Global_edit_info.now_direction;
    j = Global_edit_info.now_frame;

    if ( Application->MessageBoxA( "Now ACT's ALL DIR Sorting Data will copy. Do you want it?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
        return;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        tempframe2 = tempframe;

        if ( Use_edit_animation[i] )
        {
            for ( j = 0; j < Global_edit_animation[i]->total_frame; j++ )
            {
                tempframe = GetEditFrameLayer( i, j );

                if ( tempframe )
                {
                    for ( layer = 0; layer < 8; layer++ )
                        for ( k = 0; k < 33; k++ )
                            tempframe->Edit_frame[layer].sort_index[k] =
                                tempframe2->Edit_frame[layer].sort_index[dir];
                }
            }
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy_AllAnimationSortClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe, tempframe2;
    int i, j, k, dir, layer;

    i = Global_edit_info.now_animation;
    dir = Global_edit_info.now_direction;
    j = Global_edit_info.now_frame;

    if ( Application->MessageBoxA( "ALL DIR DATA WILL BE COPY. Do you want it?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
        return;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        tempframe2 = tempframe;

        for ( i = 0; i < 99; i++ )
            if ( Use_edit_animation[i] )
            {
                for ( j = 0; j < Global_edit_animation[i]->total_frame; j++ )
                {
                    tempframe = GetEditFrameLayer( i, j );

                    if ( tempframe )
                    {
                        for ( layer = 0; layer < 8; layer++ )
                            for ( k = 0; k < 33; k++ )
                                tempframe->Edit_frame[layer].sort_index[k] =
                                    tempframe2->Edit_frame[layer].sort_index[dir];
                    }
                }
            }
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Copy_DirectionSortClick(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe, tempframe2;
    int i, j, dir, layer;

    i = Global_edit_info.now_animation;
    dir = Global_edit_info.now_direction;
    j = Global_edit_info.now_frame;

    if ( Application->MessageBoxA( "NOW ACT, NOW DIR's Sorting Data will copy. Do you want it?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
        return;

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        tempframe2 = tempframe;

        if ( Use_edit_animation[i] )
        {
            for ( j = 0; j < Global_edit_animation[i]->total_frame; j++ )
            {
                tempframe = GetEditFrameLayer( i, j );

                if ( tempframe )
                {
                    for ( layer = 0; layer < 8; layer++ )
                        tempframe->Edit_frame[layer].sort_index[dir] =
                            tempframe2->Edit_frame[layer].sort_index[dir];
                }
            }
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Close1Click(TObject *Sender)
{
    if ( Application->MessageBoxA( "Do you want quit?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
              return;

    Form1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::New1Click(TObject *Sender)
{
    if ( Application->MessageBoxA( "All Datas Initialize. Do you want it?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
              return;

    AllClear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::EditFileSaveClick(TObject *Sender)
{
    int i, j, k, cnt;
    FILE *fp;
    char filename[255];
    LPEDITFRAMELAYER    tempframe;

    if ( SaveDialog1->Execute() )
    {
        fp = fopen( SaveDialog1->FileName.c_str(), "wb" );

        if ( fp )
        {
            // 파일 버전
            i = 0x10000002;
            fwrite( &i, sizeof( int ), 1, fp );

            // 사용한 원본 레이어 정보 저장
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].loaded_flag, sizeof( AN_Source[i].loaded_flag ), 1, fp );

            // 사용한 원본 레이어의 파일명 저장
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].filename, 1, 50, fp );

            // 사용한 원본 레이어의 방향별 프레임 수 저장
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].animation_source.direction_total_frame, sizeof( int ), 1, fp );

            cnt = 0;
            for ( i = 0; i < max_enable_animation; i++ )
                if ( Use_edit_animation[i] )
                    cnt++;

            // 총 에니메이션의 갯수
            fwrite( &cnt, sizeof( int ), 1, fp );
            // 최대 방향수
            fwrite( &Global_edit_info.max_direction, sizeof( int ), 1, fp );
            // 뒤집힐 방향수
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].flip_direction, sizeof( int ), 1, fp );

            for ( i = 0; i < max_enable_animation; i++ )
            {
                if ( Use_edit_animation[i] )
                {
                    // 에니메이션 번호
                    fwrite( &i, sizeof( int ), 1, fp );
                    // 에니메이션당 총 프레임수
                    cnt = Global_edit_animation[i]->total_frame;
                    fwrite( &cnt, sizeof( int ), 1, fp );

                    fwrite( &Global_edit_animation[i]->total_time, sizeof( float ), 1, fp );

                    // 해당 에니메이션의 방향 링크된 정보
                    fwrite( Global_edit_animation[i]->direction_link, sizeof( int ), Global_edit_info.max_direction, fp );

                    for ( j = 0; j < cnt; j++ )
                    {
                        tempframe = GetEditFrameLayer( i, j );

                        // 해당 프레임의 사운드 정보 저장
                        fwrite( tempframe->sound_index, sizeof( short ), 5, fp );
                        fwrite( &tempframe->frame_time, sizeof( float ), 1, fp );

                        for ( k = 0; k < 8; k++ )
                        {
                            // 해당 프레임의 각 방향별 소팅 정보 저장
                            fwrite( tempframe->Edit_frame[k].sort_index, sizeof( char ), Global_edit_info.max_direction, fp );
                            // 프레임 인덱스
                            fwrite( &tempframe->Edit_frame[k].index, sizeof( short ), 1, fp );
                            // 프레임의 방향 틀어진 정보
                            fwrite( &tempframe->Edit_frame[k].direction_gap , sizeof( char ), 1, fp );
                            // 프레임의 x 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].x_gap, sizeof( char ), 1, fp );
                            // 프레임의 y 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].y_gap, sizeof( char ), 1, fp );
                            // 프레임의 z 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].z_gap, sizeof( char ), 1, fp );
                            // 프레임의 z 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].draw_mode_and_alpha, sizeof( unsigned char ), 1, fp );
                        }
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------


void convert( char *filename )
{
    int i, j, k, cnt;
    FILE *fp;
//    char filename[255];
    LPEDITFRAMELAYER    tempframe;

        fp = fopen( filename, "wb" );

        if ( fp )
        {
            // 파일 버전
            i = 0x10000001;
            fwrite( &i, sizeof( int ), 1, fp );

            // 사용한 원본 레이어 정보 저장
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].loaded_flag, sizeof( AN_Source[i].loaded_flag ), 1, fp );

            // 사용한 원본 레이어의 파일명 저장
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].filename, 1, 50, fp );

            // 사용한 원본 레이어의 방향별 프레임 수 저장
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].animation_source.direction_total_frame, sizeof( int ), 1, fp );

            cnt = 0;
            for ( i = 0; i < max_enable_animation; i++ )
                if ( Use_edit_animation[i] )
                    cnt++;

            // 총 에니메이션의 갯수
            fwrite( &cnt, sizeof( int ), 1, fp );
            // 최대 방향수
            fwrite( &Global_edit_info.max_direction, sizeof( int ), 1, fp );
            // 뒤집힐 방향수
            for ( i = 0; i < 8; i++ )
                fwrite( &AN_Source[i].flip_direction, sizeof( int ), 1, fp );

            for ( i = 0; i < max_enable_animation; i++ )
            {
                if ( Use_edit_animation[i] )
                {
                    // 에니메이션 번호
                    fwrite( &i, sizeof( int ), 1, fp );
                    // 에니메이션당 총 프레임수
                    cnt = Global_edit_animation[i]->total_frame;
                    fwrite( &cnt, sizeof( int ), 1, fp );

                    // 해당 에니메이션의 방향 링크된 정보
                    fwrite( Global_edit_animation[i]->direction_link, sizeof( int ), Global_edit_info.max_direction, fp );

                    for ( j = 0; j < cnt; j++ )
                    {
                        tempframe = GetEditFrameLayer( i, j );

                        // 해당 프레임의 사운드 정보 저장
                        fwrite( tempframe->sound_index, sizeof( short ), 5, fp );

                        for ( k = 0; k < 8; k++ )
                        {
                            // 해당 프레임의 각 방향별 소팅 정보 저장
                            fwrite( tempframe->Edit_frame[k].sort_index, sizeof( char ), Global_edit_info.max_direction, fp );
                            // 프레임 인덱스
                            fwrite( &tempframe->Edit_frame[k].index, sizeof( short ), 1, fp );
                            // 프레임의 방향 틀어진 정보
                            fwrite( &tempframe->Edit_frame[k].direction_gap , sizeof( char ), 1, fp );
                            // 프레임의 x 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].x_gap, sizeof( char ), 1, fp );
                            // 프레임의 y 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].y_gap, sizeof( char ), 1, fp );
                            // 프레임의 z 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].z_gap, sizeof( char ), 1, fp );
                            // 프레임의 z 축으로 이동
                            fwrite( &tempframe->Edit_frame[k].draw_mode_and_alpha, sizeof( unsigned char ), 1, fp );
                        }
                    }
                }
            }
        }
}






void __fastcall TForm1::LoadAnimationInfoClick(TObject *Sender)
{
    int i, j, k, cnt, ani, frame, ver;
    bool flag[8];
    FILE *fp;
    char filename[255];
    LPEDITFRAMELAYER    tempframe;

    if ( OpenDialog1->Execute() )
    {
        fp = fopen( OpenDialog1->FileName.c_str(), "rb" );

        if ( fp )
        {
            AllClear();

            fread( &ver, sizeof( int ), 1, fp );

            // 파일 버전 체크
            if ( ver != 0x10000000 && ver != 0x10000001 && ver != 0x10000002 )
                return;

            // 사용한 원본 레이어 정보
            for ( i = 0; i < 8; i++ )
                fread( &flag[i], sizeof( bool ), 1, fp );

            // 사용한 원본 레이어의 파일명 읽기
            for ( i = 0; i < 8; i++ )
                fread( &AN_Source[i].filename, 1, 50, fp );

            // 사용한 원본 레이어의 방향별 프레임 수 저장
            for ( i = 0; i < 8; i++ )
                fread( &AN_Source[i].animation_source.direction_total_frame, sizeof( int ), 1, fp );

            // 소스 읽어들이기
            for ( i = 0; i < 8; i++ )
                if ( flag[i] )
                {
                    sprintf( filename, "AN_files\\%s.AN", AN_Source[i].filename );
                    Load_sourceimage( i, filename );
                }

            // 총 에니메이션 갯수
            fread( &cnt, sizeof( int ), 1, fp );

            // 최대 방향수
            fread( &j, sizeof( int ), 1, fp );
            Global_edit_info.max_direction = j;

            if ( ver != 0x10000000 )
                fseek( fp, sizeof( int ) * 8, SEEK_CUR );

            for ( i = 0; i < cnt; i++ )
            {
                // 에니메이션 번호
                fread( &ani, sizeof( int ), 1, fp );
                Use_edit_animation[ani] = true;
                // 에니메이션당 총 프레임수
                fread( &frame, sizeof( int ), 1, fp );
                Global_edit_animation[ani]->total_frame = frame;

                if ( ver == 0x10000002 )
                {
                    float frame_time;
                    fread( &frame_time, sizeof( float ), 1, fp );
                    Global_edit_animation[ani]->total_time = frame_time;
                }
                else
                    Global_edit_animation[ani]->total_time = BASICFRAMETIME * frame;


                // 해당 에니메이션의 방향 링크된 정보
                fread( Global_edit_animation[ani]->direction_link, sizeof( int ), Global_edit_info.max_direction, fp );

                tempframe = &Global_edit_animation[ani]->edit_frame;

                for ( j = 0; j < frame; j++ )
                {
                    // 해당 프레임의 사운드 정보 저장
                    fread( tempframe->sound_index, sizeof( short ), 5, fp );

                    if ( ver == 0x10000002 )
                        fread( &tempframe->frame_time, sizeof( float ), 1, fp );
                    else
                        tempframe->frame_time = BASICFRAMETIME;


                    for ( k = 0; k < 8; k++ )
                    {
                        // 해당 프레임의 각 방향별 소팅 정보 저장
                        fread( tempframe->Edit_frame[k].sort_index, sizeof( char ), Global_edit_info.max_direction, fp );
                        // 프레임 인덱스
                        fread( &tempframe->Edit_frame[k].index, sizeof( short ), 1, fp );
                        // 프레임의 방향 틀어진 정보
                        fread( &tempframe->Edit_frame[k].direction_gap , sizeof( char ), 1, fp );
                        // 프레임의 x 축으로 이동
                        fread( &tempframe->Edit_frame[k].x_gap, sizeof( char ), 1, fp );
                        // 프레임의 y 축으로 이동
                        fread( &tempframe->Edit_frame[k].y_gap, sizeof( char ), 1, fp );
                        // 프레임의 z 축으로 이동
                        fread( &tempframe->Edit_frame[k].z_gap, sizeof( char ), 1, fp );
                        // 프레임의 z 축으로 이동
                        fread( &tempframe->Edit_frame[k].draw_mode_and_alpha, sizeof( unsigned char ), 1, fp );
                    }

                    tempframe = tempframe->Insert();
                }
            }

            Refresh_soundtreeview();

            fclose( fp );
        }
    }

//    convert( OpenDialog1->FileName.c_str() );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
    ChangeDisplaySettings( &full_desktop, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N4Click(TObject *Sender)
{
    ChangeDisplaySettings( &before_desktop, 0 );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if ( ColorDialog1->Execute() )
    {
        DWORD temp;
        WORD color;
        temp = (DWORD)ColorDialog1->Color;
        color = (((temp>>3)&0x1f)<<10)|(((temp>>11)&0x1f)<<5)|((temp>>19)&0x1f);
        if ( AllSourceSelect->Checked )
        {
            for ( int i = 0; i < 8; i++ )
            {
                if ( !color )
                    AN_Source[i].color_flag = false;
                else
                {
                    AN_Source[i].color_flag = true;
                    AN_Source[i].color = color;
                }
            }
        }
        else
        {
            int i = AN_ListBox->ItemIndex;

            if ( !color )
                AN_Source[i].color_flag = false;
            else
            {
                AN_Source[i].color_flag = true;
                AN_Source[i].color = color;
            }
        }
    }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
    Edit1->Text = (float)TrackBar1->Position/1000;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit1Change(TObject *Sender)
{
    LPEDITFRAMELAYER tempframe;
    int i, j, frame, layer;
    float times = atof( Edit1->Text.c_str() );

    layer = GetEditLayer( Edit_ListBox->ItemIndex );
    i = Global_edit_info.now_animation;
    j = Global_edit_info.now_frame;

    if ( layer == -1 )
    {
        Application->MessageBoxA( "Nothing To edit layer. You should to copy one or All layer first.",
        "Caution", MB_OK | MB_TOPMOST );
        return;
    }

    tempframe = GetEditFrameLayer( i, j );

    if ( Use_edit_animation[i] && tempframe )
    {
        Global_edit_animation[i]->total_time -= tempframe->frame_time;
        tempframe->frame_time = times;
        Global_edit_animation[i]->total_time += tempframe->frame_time;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
    if ( Application->MessageBoxA( "Copy All Frame's Time. Do you want copy time all?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
              return;

    LPEDITFRAMELAYER tempframe;
    int i, j, k, m, o, frame, max_layerframe, layerframe;

    for ( j = 0; j < max_enable_animation; j++ )
    {
        tempframe = &Global_edit_animation[j]->edit_frame;

        while( tempframe )
        {
            tempframe->frame_time = atof( Edit1->Text.c_str() );
            tempframe = tempframe->next_node;
        }

        Global_edit_animation[j]->total_time = (float)Global_edit_animation[j]->total_frame * atof( Edit1->Text.c_str() );
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    if ( Application->MessageBoxA( "Copy Now Animation's All Frame's Time. Do you want copy time?",
        "Caution", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
              return;

    LPEDITFRAMELAYER tempframe;
    int i, j, k, m, o, frame, max_layerframe, layerframe;

    j = Global_edit_info.now_animation;
    {
        tempframe = &Global_edit_animation[j]->edit_frame;
        Global_edit_animation[j]->total_time = 0L;

        while( tempframe )
        {
            tempframe->frame_time = atof( Edit1->Text.c_str() );
            Global_edit_animation[j]->total_time += tempframe->frame_time;
            tempframe = tempframe->next_node;
        }
    }

}
//---------------------------------------------------------------------------

