//---------------------------------------------------------------------------


#pragma hdrstop

#include "Unit1.h"
#include "Unit3.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

int Load_sourceimage( int layer, char *filename )
{
    int index = layer, i;

    if ( index > -1 )
    {
        // 이미 로딩되어 있는 레이어가 있는 상태라면..
        if ( AN_Source[index].loaded_flag == true )
        {
            if ( Application->MessageBoxA( "해당 레이어에 이미 로딩되어 있는 이미지가 있습니다. 새롭게 로딩하시겠습니까?",
            "주의", MB_OKCANCEL | MB_TOPMOST ) == IDCANCEL )
                    return 0;

            // 로딩되어있는 데이터 위에 로딩하는 경우라면.. 초기화
            AN_Source[index].Clear();
        }

        FILE *fp;
        char filename1[255], filename2[255];
        LPAN_DATA temp = &AN_Source[index].animation_source;
        LPAN_IMAGE tempimages;
        int direction, animation, startframe, framecount, totalframe, bufsize;

        strcpy( filename1, filename );
        memset( filename2, 0, sizeof( filename2 ) );
        strncpy( filename2, filename1, strlen( filename1 ) - strlen( strrchr( filename1, '.' ) ) );

        // DAT 파일 로딩하기
        sprintf( filename1, "%s.dat", filename2 );

        fp = fopen( filename1, "rt" );
        fscanf( fp, "%d\n", &temp->total_frame );
        fscanf( fp, "%d\n", &AN_Source[index].max_direction );
        temp->direction_total_frame = temp->total_frame / AN_Source[index].max_direction;

        while( true )
        {
            if ( fscanf( fp, "%d", &animation ) == EOF )
                break;

            fscanf( fp, "%d", &startframe );
            fscanf( fp, "%d", &framecount );

            temp->direction_animation[animation] = true;
            temp->abs_framestart[animation] = startframe;
            temp->abs_framecount[animation] = framecount;

            // 캐릭터의 마지막 에니메이션 번호 얻기
            if ( animation > AN_Source[index].max_animation )
                AN_Source[index].max_animation = animation;
        }

        fclose( fp );

        // AN 파일 로딩하기
        sprintf( filename1, "%s.an3", filename2 );

        int an_version = 0;

        fp = fopen( filename1, "rb" );

        fread( &totalframe, sizeof( int ), 1, fp );

        if ( totalframe == 0xffffffff ) // 새로운 버전의 an3 파일
        {
            fread( &an_version, sizeof( int ), 1, fp );
            fread( &totalframe, sizeof( int ), 1, fp );
        }
        else
            an_version = 0x1000;

        // DAT 파일과 AN 파일의 총 프레임수가 다르다면, 데이터 에러
        if ( totalframe != temp->total_frame )
        {
            AN_Source[index].Clear();
            fclose( fp );
            return 0;
        }

        if ( AN_Source[index].Alloc_sourceimages( totalframe ) == false )
        {
            AN_Source[index].Clear();
            fclose( fp );
            return 0;
        }

        for ( i = 0; i < totalframe; i++ )
        {
            tempimages = AN_Source[index].source_images[i];

            fread( &tempimages->startx, sizeof( short ), 1, fp );

            if ( tempimages->startx == 30002 )      // 알파 이미지를 사용할 경우
            {
                tempimages->alphaflag = true;
                fread( &tempimages->startx, sizeof( short ), 1, fp );
            }
            else
                tempimages->alphaflag = false;

            if ( tempimages->startx == 30000 )      // 없는 이미지일 경우
                continue;

            fread( &tempimages->starty, sizeof( short ), 1, fp );
            fread( &tempimages->xsize, sizeof( short ), 1, fp );
            fread( &tempimages->ysize, sizeof( short ), 1, fp );

            fread( &bufsize, sizeof( int ), 1, fp );

            if ( tempimages->AllocImage( bufsize ) )
            {
                fread( tempimages->imagebuf, bufsize, 1, fp );
            }
            else
            {
                AN_Source[index].Clear();
                fclose( fp );
                return 0;
            }
        }

        AN_Source[index].an_version = an_version;

        if ( an_version == 0x1001 ) // 새로운 버전의 an3 파일은 팔레트 존재
        {
            fread( AN_Source[index].palette, 768, 1, fp );
        }

        fclose( fp );

        AN_Source[index].loaded_flag = true;

        memset( filename1, 0, sizeof( filename1 ) );
        strcpy( filename1, strrchr( filename2, '\\' ) + 1 );
        strcpy( AN_Source[index].filename, filename1 );

        Form1->AN_ListBox->Items->Clear();
        for( i = 0; i < 8; i++ )
            Form1->AN_ListBox->Items->Add( AN_Source[i].filename );

        LPEDITFRAMELAYER tempframe = GetEditFrameLayer( Global_edit_info.now_animation, Global_edit_info.now_frame );
        if ( Use_edit_animation[ Global_edit_info.now_animation ] && tempframe )
        {
                Form1->Edit_ListBox->Items->Clear();
                for( i = 0; i < 8; i++ )
                {
                    if ( !tempframe || !tempframe->Edit_frame[i].sort_index )
                    {
                        Form1->Edit_ListBox->Items->Add( AN_Source[i].filename );
                    }
                    else
                        for ( int j = 0; j < 8; j++ )
                            if ( i == j )
                                Form1->Edit_ListBox->Items->Add( AN_Source[i].filename );
                }
        }

        if ( AN_Source[index].max_direction < 7 && AN_Source[index].max_direction > 3 )   // 절반의 방향만 사용하는 이미지라면
        {
                AN_Source[index].flip_direction = AN_Source[index].max_direction;      // 뒤집어서찍기 허용
                AN_Source[index].max_direction = 7;
                AN_Source[index].flip_flag = true;      // 뒤집어서찍기 허용
        }
        else
        {
                AN_Source[index].max_direction--;
                AN_Source[index].flip_flag = false;
                AN_Source[index].flip_direction = 0;
        }
            // 캐릭터의 마지막 에니메이션 번호 얻기
        if ( AN_Source[index].max_direction + 1 > Global_edit_info.max_direction )
            Global_edit_info.max_direction = AN_Source[index].max_direction + 1;

        return 1;
    }

    return 0;
}
