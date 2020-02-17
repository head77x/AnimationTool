#define DESKTOP_ACCESSOR_API	__declspec(dllimport)


extern DESKTOP_ACCESSOR_API int Init_desktop_processer( void );
extern DESKTOP_ACCESSOR_API void Uninit_desktop_processer( void );
extern DESKTOP_ACCESSOR_API int Set_desktop( int xsize, int ysize, int colorbit );
extern DESKTOP_ACCESSOR_API int Get_desktop( int &xsize, int &ysize, int &colorbit );

DESKTOP_ACCESSOR_API int Init_desktop_processer( void );
DESKTOP_ACCESSOR_API void Uninit_desktop_processer( void );
DESKTOP_ACCESSOR_API int Set_desktop( int xsize, int ysize, int colorbit );
DESKTOP_ACCESSOR_API int Get_desktop( int &xsize, int &ysize, int &colorbit );
