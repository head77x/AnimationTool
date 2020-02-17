//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;

//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
    char temp[100];
    int cnt, i;
    FILE *fp;

    fp = fopen( "Tool.cfg", "rt" );

    if ( fp )
    {
        fscanf( fp, "%d\n", &max_enable_animation );

        EditAnimationList->Clear();

        for ( i = 0; i < max_enable_animation; i++ )
        {
            cnt = 0;
            while( true )
            {
                temp[cnt] = fgetc( fp );
                if ( temp[cnt] == '\n' )
                {
                    temp[cnt] = NULL;
                    break;
                }
                cnt++;
            }

            EditAnimationList->AddItem( temp, NULL );
        }

        fclose( fp );

        // 편집 가능한 에니메이션 만큼의 편집 데이터 저장 장소 확보
        if ( (Global_edit_animation = (LPEDITANIMATION *)malloc( sizeof( LPEDITANIMATION ) * max_enable_animation ) ) != NULL )
        {
            for ( i = 0; i < max_enable_animation; i++ )
            {
                if ( (Global_edit_animation[i] = (LPEDITANIMATION)malloc( sizeof( EDITANIMATION ) ) ) == NULL )
                    return;
                else
                    memset( Global_edit_animation[i], 0, sizeof( EDITANIMATION ) );

                for ( int j = 0; j < 8; j++ )
                    Global_edit_animation[i]->edit_frame.Edit_frame[j].index = -1;

                for ( int j = 0; j < 5; j++ )
                    Global_edit_animation[i]->edit_frame.sound_index[j] = -1;

            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::EditAnimationListClickCheck(TObject *Sender)
{
    int index = EditAnimationList->ItemIndex;

    if ( index > -1 )
        EditAnimationList->State[index] ^= (TCheckBoxState)true;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::EditAnimationListClick(TObject *Sender)
{
    int index = EditAnimationList->ItemIndex;

    if ( index > -1 )
        AnimationName->Text = EditAnimationList->Items->Strings[index];
}
//---------------------------------------------------------------------------
void __fastcall TForm2::AnimationNameButtonClick(TObject *Sender)
{
    int index = EditAnimationList->ItemIndex;

    if ( index > -1 )
        EditAnimationList->Items->Strings[index] = AnimationName->Text;
}
//---------------------------------------------------------------------------
void __fastcall TForm2::InsertAnimationClick(TObject *Sender)
{
    int index = EditAnimationList->ItemIndex;

    if ( index > -1 )
    {
        EditAnimationList->State[index] = (TCheckBoxState)true;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DeleteAnimationClick(TObject *Sender)
{
    int index = EditAnimationList->ItemIndex;

    if ( index > -1 )
    {
        EditAnimationList->State[index] = (TCheckBoxState)false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::DeleteAllClick(TObject *Sender)
{
    int index = EditAnimationList->ItemIndex;

    if ( index > -1 )
    {
        for ( int i = 0; i < max_enable_animation; i++ )
        {
            EditAnimationList->State[i] = (TCheckBoxState)false;
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm2::CONFIRMOKClick(TObject *Sender)
{
    for ( int i = 0; i < max_enable_animation; i++ )
        Use_edit_animation[i] = (bool)EditAnimationList->State[i];
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormShow(TObject *Sender)
{
    for ( int i = 0; i < max_enable_animation; i++ )
        EditAnimationList->State[i] = (TCheckBoxState)Use_edit_animation[i];

    EditAnimationList->ItemIndex = 0;
    EditAnimationList->OnClick( Sender );
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormDestroy(TObject *Sender)
{
    char temp[100];
    int cnt, i;
    FILE *fp;

    fp = fopen( "Tool.cfg", "wt" );

    if ( fp )
    {
        fprintf( fp, "%d\n", max_enable_animation );

        for ( i = 0; i < max_enable_animation; i++ )
            fprintf( fp, "%s\n", EditAnimationList->Items->Strings[i].c_str() );

        fclose( fp );
    }

    LPEDITFRAMELAYER    tempframe, nextframe;

    if ( Global_edit_animation )
    {
        for ( i = 0; i < max_enable_animation; i++ )
            if ( Global_edit_animation[i] )
            {
                tempframe = Global_edit_animation[i]->edit_frame.next_node;

                while( tempframe )
                {
                    nextframe = tempframe->Delete();
                    if ( nextframe )
                    {
                        free( tempframe );
                        tempframe = NULL;
                    }
                    tempframe = nextframe;
                }

                free( Global_edit_animation[i] );
                Global_edit_animation[i] = NULL;
            }

        free( Global_edit_animation );
        Global_edit_animation = NULL;
    }
}
//---------------------------------------------------------------------------
