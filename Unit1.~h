//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <stdio.h>
#include "CSPIN.h"
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
//---------------------------------------------------------------------------
#define WM_ENTERMAINLOOP (WM_USER+101)

#define max(a,b)    ( a > b ) ? a : b
#define min(a,b)    ( a < b ) ? a : b

#define BACK_GAPY   100
#define BACK_GAPX   100
#define BACK_SIZEX  600
#define BACK_SIZEY  600
#define SCR_SIZEX   400
#define SCR_SIZEY   400

#define BASICFRAMETIME  0.02f


enum { SOURCE_SCREEN = 0, EDIT_SCREEN };
enum { NOT_PUT = 0, NORMAL_PUT };

class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TBevel *Bevel1;
        TMainMenu *MainMenu1;
        TMenuItem *N1;
        TStatusBar *StatusBar1;
        TBevel *Bevel2;
        TBevel *Bevel4;
        TBevel *Bevel5;
        TImage *Edit_screen;
        TImage *Source_screen;
        TGroupBox *GroupBox1;
        TListBox *AN_ListBox;
    TCheckBox *AllSourceSelect;
        TButton *Load_AN_button;
        TButton *Del_AN_button;
        TGroupBox *GroupBox2;
        TBevel *Bevel3;
    TCheckBox *AN_ViewCheck;
        TButton *Play_AN_button;
        TButton *Stop_AN_button;
        TLabel *Label2;
        TLabel *Label3;
        TButton *Before_AN_action;
        TButton *Next_AN_action;
        TLabel *Label4;
        TButton *Before_AN_direction;
        TButton *Next_AN_direction;
        TLabel *Label5;
        TButton *Before_AN_frame;
        TButton *Next_AN_frame;
        TGroupBox *GroupBox3;
        TLabel *Label6;
    TButton *Copy_frame;
    TButton *Append_frame;
        TLabel *Label7;
        TButton *Copy_all_frame_selected;
        TButton *Copy_all_frame_all;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TLabel *Label8;
    TButton *Play_Edit_button;
    TButton *Stop_Edit_button;
    TButton *EditNextAnimation;
    TButton *EditBeforeAnimation;
        TLabel *Label9;
        TLabel *Label10;
    TButton *Before_Edit_direction;
    TButton *Next_Edit_direction;
    TButton *Next_Edit_frame;
    TButton *Before_Edit_frame;
        TLabel *Label11;
        TGroupBox *GroupBox6;
    TButton *CopyEditFrame;
    TButton *DeleteEditFrame;
        TGroupBox *GroupBox7;
    TButton *InsDelAnimationButton;
    TRadioGroup *OutputType;
        TGroupBox *GroupBox8;
    TCSpinEdit *Frame_X;
        TLabel *Label13;
        TLabel *Label14;
    TCSpinEdit *Frame_Y;
        TLabel *Label15;
    TCSpinEdit *Frame_Z;
        TGroupBox *GroupBox9;
    TListBox *Edit_ListBox;
    TCheckBox *AllEditSelect;
    TEdit *Edit_Select;
        TLabel *Label12;
    TButton *SortUp;
    TButton *SortDown;
        TGroupBox *GroupBox10;
    TButton *Copy_AnimationSort;
    TButton *Copy_DirectionSort;
    TButton *Copy_AllAnimationSort;
        TGroupBox *GroupBox11;
        TLabel *Label16;
    TCSpinEdit *BlendValue;
        TTreeView *SoundTreeView;
    TButton *InsertSound;
    TButton *DeleteSound;
    TButton *AllSoundDelete;
        TGroupBox *GroupBox12;
    TButton *EditFileSave;
    TButton *LoadAnimationInfo;
        TGroupBox *GroupBox13;
        TButton *Button26;
    TButton *BackLoading;
        TGroupBox *GroupBox14;
        TMemo *Memo1;
        TOpenDialog *OpenAN3;
    TLabeledEdit *AN_Select;
    TEdit *SourceAnimation;
    TEdit *SourceDirection;
    TEdit *SourceFrame;
    TEdit *EditAnimation;
    TEdit *EditDirection;
    TEdit *EditFrame;
    TGroupBox *GroupBox15;
    TEdit *DirectionLinkGap;
    TCheckBox *DirectionLinkCheck;
    TButton *DirectionLinkBefore;
    TButton *DirectionLinkNext;
    TButton *AllCopyButton;
        TRadioGroup *FramePerSecond;
    TColorDialog *ColorDialog1;
    TOpenPictureDialog *OpenPictureDialog1;
    TImage *BackImage;
    TMenuItem *New1;
    TMenuItem *Close1;
    TSaveDialog *SaveDialog1;
    TOpenDialog *OpenDialog1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TButton *Button1;
    TTrackBar *TrackBar1;
    TLabel *Label1;
    TEdit *Edit1;
    TButton *Button2;
    TButton *Button3;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
    void __fastcall SoundTreeViewDblClick(TObject *Sender);
    void __fastcall Load_AN_buttonClick(TObject *Sender);
    void __fastcall AN_ListBoxClick(TObject *Sender);
    void __fastcall AllSourceSelectClick(TObject *Sender);
    void __fastcall Before_AN_actionClick(TObject *Sender);
    void __fastcall Next_AN_actionClick(TObject *Sender);
    void __fastcall Before_AN_directionClick(TObject *Sender);
    void __fastcall Next_AN_directionClick(TObject *Sender);
    void __fastcall Before_AN_frameClick(TObject *Sender);
    void __fastcall Next_AN_frameClick(TObject *Sender);
    void __fastcall Play_AN_buttonClick(TObject *Sender);
    void __fastcall Stop_AN_buttonClick(TObject *Sender);
    void __fastcall AN_ViewCheckClick(TObject *Sender);
    void __fastcall Del_AN_buttonClick(TObject *Sender);
    void __fastcall InsDelAnimationButtonClick(TObject *Sender);
    void __fastcall EditBeforeAnimationClick(TObject *Sender);
    void __fastcall AllCopyButtonClick(TObject *Sender);
    void __fastcall EditNextAnimationClick(TObject *Sender);
    void __fastcall Before_Edit_directionClick(TObject *Sender);
    void __fastcall Next_Edit_directionClick(TObject *Sender);
    void __fastcall Before_Edit_frameClick(TObject *Sender);
    void __fastcall Next_Edit_frameClick(TObject *Sender);
    void __fastcall Play_Edit_buttonClick(TObject *Sender);
    void __fastcall Stop_Edit_buttonClick(TObject *Sender);
    void __fastcall Copy_all_frame_selectedClick(TObject *Sender);
    void __fastcall Copy_all_frame_allClick(TObject *Sender);
    void __fastcall Append_frameClick(TObject *Sender);
    void __fastcall Copy_frameClick(TObject *Sender);
    void __fastcall CopyEditFrameClick(TObject *Sender);
    void __fastcall DeleteEditFrameClick(TObject *Sender);
    void __fastcall DirectionLinkCheckClick(TObject *Sender);
    void __fastcall DirectionLinkBeforeClick(TObject *Sender);
    void __fastcall DirectionLinkNextClick(TObject *Sender);
    void __fastcall Frame_XChange(TObject *Sender);
    void __fastcall AllEditSelectClick(TObject *Sender);
    void __fastcall Edit_ListBoxClick(TObject *Sender);
    void __fastcall Frame_YChange(TObject *Sender);
    void __fastcall Frame_ZChange(TObject *Sender);
    void __fastcall InsertSoundClick(TObject *Sender);
    void __fastcall DeleteSoundClick(TObject *Sender);
    void __fastcall AllSoundDeleteClick(TObject *Sender);
    void __fastcall OutputTypeClick(TObject *Sender);
    void __fastcall BlendValueChange(TObject *Sender);
    void __fastcall Button26Click(TObject *Sender);
    void __fastcall BackLoadingClick(TObject *Sender);
    void __fastcall SortUpClick(TObject *Sender);
    void __fastcall SortDownClick(TObject *Sender);
    void __fastcall Copy_AnimationSortClick(TObject *Sender);
    void __fastcall Copy_AllAnimationSortClick(TObject *Sender);
    void __fastcall Copy_DirectionSortClick(TObject *Sender);
    void __fastcall Close1Click(TObject *Sender);
    void __fastcall New1Click(TObject *Sender);
    void __fastcall EditFileSaveClick(TObject *Sender);
    void __fastcall LoadAnimationInfoClick(TObject *Sender);
    void __fastcall N3Click(TObject *Sender);
    void __fastcall N4Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall TrackBar1Change(TObject *Sender);
    void __fastcall Edit1Change(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
    void __fastcall Button3Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void Flip( int flag );
        void __fastcall MainLoop(TMessage & Msg);

protected:
    BEGIN_MESSAGE_MAP   // Catch the following messages:
        VCL_MESSAGE_HANDLER(WM_ENTERMAINLOOP, TMessage, MainLoop)
    END_MESSAGE_MAP(TForm)
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
extern int max_enable_animation;
extern bool Use_edit_animation[100];

// AN 파일과 함께 사용할 DAT 파일의 구조
typedef struct
{
    int total_frame;                    // AN 파일의 총 프레임수
    int direction_total_frame;          // 방향별 총 프레임수
    bool direction_animation[99];    // 방향별 존재하는 에니메이션
    int abs_framestart[99];         // 해당 에니메이션의 해당 방향별 시작 프레임
    int abs_framecount[99];         // 해당 에니메이션의 해당 방향별 프레임수
    void Clear( void )
    {
        total_frame = 0;
        memset( direction_animation, 0, sizeof( direction_animation ) );
        memset( abs_framestart, -1, sizeof( abs_framestart ) );
        memset( abs_framecount, -1, sizeof( abs_framecount ) );
    };

} AN_DATA, *LPAN_DATA;

// AN 파일의 이미지 데이터 구조
typedef struct
{
    BOOL alphaflag;
    short startx, starty, xsize, ysize;
    DWORD *imagebuf;

    bool AllocImage( int imgsize )
    {
        if ( imagebuf )
        {
            free( imagebuf );
            imagebuf = 0;
        }

        if ( (imagebuf = (DWORD *)malloc( imgsize ) ) == NULL )
            return false;

        return true;
    };

    void Release( void )
    {
        startx = starty = xsize = ysize = 0;
        if ( imagebuf )
        {
            free( imagebuf );
            imagebuf = 0;
        }
    };
} AN_IMAGE, *LPAN_IMAGE;

// 각 레이어( AN 이미지 )의 내용물
typedef struct
{
    bool view_flag;
    bool flip_flag;
    bool color_flag;
    WORD color;
    int flip_direction;
    int total_frame;
    bool loaded_flag;
    bool playing_flag;
    char filename[50];
    AN_DATA animation_source;
    LPAN_IMAGE  *source_images;
    int now_direction;
    int now_animation;
    int now_frame;
    int max_animation;
    int max_direction;

    int an_version;
    BYTE    palette[768];

    void Release_sourceimages( void )
    {
        if ( !source_images )
            return;

        for ( int i = 0; i < total_frame; i++ )
            if ( source_images[i] )
            {
                source_images[i]->Release();
                free( source_images[i] );
                source_images[i] = NULL;
            }

        free( source_images );
        source_images = NULL;
    };

    bool Alloc_sourceimages( int totalframe )
    {
        total_frame = totalframe;
        if ( ( source_images = (LPAN_IMAGE *)malloc( sizeof( LPAN_IMAGE ) * totalframe ) ) == NULL )
            return false;

        memset( source_images, 0, sizeof( LPAN_IMAGE ) * totalframe );

        for ( int i = 0; i < totalframe; i++ )
        {
            if ( ( source_images[i] = (LPAN_IMAGE)malloc( sizeof( AN_IMAGE ) ) ) == NULL )
            {
                Release_sourceimages();
                return false;
            }

            // 생성자 없으므로, 직접 클리어
            source_images[i]->imagebuf = NULL;

        }
        return true;
    };

    void Clear( void )
    {
        if ( source_images )
            Release_sourceimages();

        flip_flag = false;
        playing_flag = false;
        now_direction = 0;
        now_animation = 0;
        now_frame = 0;
        max_direction = 0;
        max_animation = 0;
        total_frame = 0;
        loaded_flag = false;
        view_flag = false;
        animation_source.Clear();
        memset( filename, 0, sizeof( filename ) );
    };
} LAYER, *LPLAYER;

typedef struct
{
    byte draw_mode_and_alpha;
    char direction_gap;
    short index;    // 방향기준으로 프레임의 인덱스
    char x_gap, y_gap, z_gap;
    char sort_index[33];

} EDITFRAME, *LPEDITFRAME;

typedef struct EDITFRAMELAYER
{
    EDITFRAMELAYER *before_node;
    EDITFRAME   Edit_frame[8];
    short sound_index[5];
    float frame_time;
    EDITFRAMELAYER *next_node;

    EDITFRAMELAYER *Insert( void )
    {
        EDITFRAMELAYER *temp;
        if ( (temp = (EDITFRAMELAYER *)malloc( sizeof( EDITFRAMELAYER ) ) ) != NULL )
        {
            memset( temp, 0, sizeof( EDITFRAMELAYER ) );
            for ( int i = 0; i < 8; i++ )
            {
                temp->Edit_frame[i].index = -1;
                for ( int j = 0; j < 33; j++ )
                    temp->Edit_frame[i].sort_index[j] = i;
            }

            for ( int i = 0; i < 5; i++ )
                temp->sound_index[i] = -1;

            temp->before_node = this;
            temp->next_node = next_node;
            if ( next_node )
                next_node->before_node = temp;
            next_node = temp;
            return temp;
        }

        return NULL;
    }

    EDITFRAMELAYER *CopyFrame( EDITFRAMELAYER *node )
    {
        memcpy( Edit_frame, node->Edit_frame, sizeof( Edit_frame ) );
        frame_time = node->frame_time;
        return this;
    }

    EDITFRAMELAYER *Delete( void )
    {
        if ( !before_node )
            return NULL;

        EDITFRAMELAYER *temp;

        if ( next_node )
            next_node->before_node = before_node;

        before_node->next_node = next_node;
        return next_node;
    }

} *LPEDITFRAMELAYER;

typedef struct
{
    int total_frame;
    float total_time;
    EDITFRAMELAYER edit_frame;
    int direction_link[33];
} EDITANIMATION, *LPEDITANIMATION;

typedef struct
{
    bool playing_flag;
    int max_direction;
    int now_animation;
    int now_direction;
    int now_frame;

} EDITINFO, *LPEDITINFO;

typedef struct
{
    int datasize;
    int soundindex;
} SOUNDDATA, *LPSOUNDDATA;

typedef struct
{
    int datasize;
    int animation;
    int frame;
    int soundindex;
} EDITSOUNDDATA, *LPEDITSOUNDDATA;

extern LAYER AN_Source[8];

extern LPEDITANIMATION *Global_edit_animation;

extern EDITINFO Global_edit_info;

extern LPEDITFRAMELAYER GetEditFrameLayer( int animation, int frame );
extern LPEDITFRAME GetEditFrameSortindex( int layer, int animation, int frame, int direction, int &returnlayer );


extern DWORD Offscreen[BACK_SIZEX * BACK_SIZEY];
extern DWORD BackMemory[BACK_SIZEX * BACK_SIZEY];
extern char Source_screen_text[255];
extern char Edit_screen_text[255];

extern bool BackColorFlag;
extern DWORD BackColor;


//---------------------------------------------------------------------------
#endif
