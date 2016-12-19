#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define DIVISIONS 5
#define MoveTo(hdc, x, y) MoveToEx (hdc, x, y, NULL)

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR  szCmdLine, int iCmdShow)
     {
     static char szAppName[] = "Test1" ;
     HWND        hwnd ;
     MSG         msg ;
     WNDCLASSEX  wndclass ;

     wndclass.cbSize        = sizeof (wndclass) ;
     wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
     wndclass.lpfnWndProc   = WndProc ;
     wndclass.cbClsExtra    = 0 ;
     wndclass.cbWndExtra    = 0 ;
     wndclass.hInstance     = hInstance ;
     wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
     wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
     wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
     wndclass.lpszMenuName  = NULL ;
     wndclass.lpszClassName = szAppName ;
     wndclass.hIconSm       = LoadIcon (NULL, IDI_APPLICATION) ;
     srand(time(NULL));
     RegisterClassEx (&wndclass) ;

     hwnd = CreateWindow (szAppName, "Test1 - Test de Posición del Ratón",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, CW_USEDEFAULT,
                          NULL, NULL, hInstance, NULL) ;

     ShowWindow (hwnd, iCmdShow) ;
     UpdateWindow (hwnd) ;

     while (GetMessage (&msg, NULL, 0, 0))
          {
          TranslateMessage (&msg) ;
          DispatchMessage (&msg) ;
          }
     return msg.wParam ;
     }

LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
     {
     static BOOL fState[DIVISIONS][DIVISIONS] ;
     static BOOL XState[DIVISIONS+1][DIVISIONS] ;
     static BOOL YState[DIVISIONS][DIVISIONS+1] ;
     static int winn[DIVISIONS][DIVISIONS]={{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
     static int  cxBlock, cyBlock ;
     static int XYState[6][5], XYResult[DIVISIONS][DIVISIONS];
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect, lin ;
     int         x, y, i,j,xrand,yrand,MXoY,ban=0, ban1 = 0, ban2=0, ajustx, ajusty, score1=0, score2=0,ban5=0,ban6=0;
     float       x_0,y_0,x_1,y_1,x_2,y_2,minz=0;


     switch (iMsg)
          {
          case WM_SIZE :
               cxBlock = LOWORD (lParam) / DIVISIONS ;
               cyBlock = HIWORD (lParam) / DIVISIONS ;
               return 0 ;

          case WM_LBUTTONDOWN :
               x_0=LOWORD (lParam);
               y_0=HIWORD (lParam);
               x = LOWORD (lParam) / cxBlock ;
               y = HIWORD (lParam) / cyBlock;
               if (x < DIVISIONS && y < DIVISIONS)
               {
               x_1=x*cxBlock;
               y_1=y*cyBlock;
               x_2=(x+1)*cxBlock;
               y_2=(y+1)*cyBlock;
               minz=x_0-x_1;
               if(x_2-x_0<minz)
                    minz=x_2-x_0;
               if(y_0-y_1<minz)
                    minz=y_0-y_1;
               if(y_2-y_0<minz)
                    minz=y_2-y_0;
               if(x_0-x_1==minz && YState[y][x] != 1){
                    YState[y][x]=1;
                    ban1 = 1;
               }
               if(x_2-x_0==minz && YState[y][x+1] != 1){
                    YState[y][x+1]=1;
                        ban1 = 1;
               }
               if(y_0-y_1==minz && XState[y][x] != 1){
                    XState[y][x]=1;
                        ban1 = 1;
               }
               if(y_2-y_0==minz && XState[y+1][x] != 1){
                    XState[y+1][x]=1;
                        ban1 = 1;
               }
                if (ban1 == 1){
                    score1=0;
                    score2=0;
                for (i = 0 ; i+1 <= 5; i++)
                    for (j = 0 ; j+1 <= 5; j++)
                    {
                        if(XYResult[i][j]!=4&&XState[i][j] + XState[i+1][j] + YState[i][j] + YState[i][j+1]==4){
                            winn[i][j]=1;
                            ban2=1;
                        }
                        XYResult[i][j] = XState[i][j] + XState[i+1][j] + YState[i][j] + YState[i][j+1];
                        score1=XYResult[i][j] +score1;
                        score2=winn[i][j]+score2;
                    }
                if(score1==DIVISIONS*DIVISIONS*4)
                    if(score2<0){
                        InvalidateRect (hwnd, NULL, FALSE) ;
                        if(MessageBox(0,"You have lost","Defeat",MB_OK)==IDOK){
                            for (i = 0 ; i <= 5; i++)
                                for (j = 0 ; j <= 5; j++)
                                {
                                    XState[i][j]=0;
                                    YState[i][j]=0;
                                    XYResult[i][j]=0;
                                    winn[i][j]=0;
                                }
                            ban=0;
                            ban1=0;
                            ban2=0;
                            score1=0;
                            score2=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                    } else{
                        InvalidateRect (hwnd, NULL, FALSE) ;
                        if(MessageBox(0,"You have won","Victory",MB_OK)==IDOK){
                            for (i = 0 ; i<= 5; i++)
                                for (j = 0 ; j<= 5; j++)
                                {
                                    XState[i][j]=0;
                                    YState[i][j]=0;
                                    XYResult[i][j]=0;
                                    winn[i][j]=0;
                                }
                            ban=0;
                            ban1=0;
                            ban2=0;
                            score1=0;
                            score2=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                    }

                if(ban2==1){
                    InvalidateRect (hwnd, NULL, FALSE) ;
                    return 0;
                }

                do{
                ban2=0;
                ban=0;
                score1=0;
                score2=0;
                ban5=0;
                ban6=0;
                for (i = 0 ; i+1 <= 5; i++)
                    for (j = 0 ; j+1 <= 5; j++)
                        if(XYResult[i][j]==3){
                            if(XState[i][j]==0){
                                xrand=i;
                                yrand=j;
                                MXoY=0;
                                ban5=1;
                            }
                            if(XState[i+1][j]==0){
                                xrand=i+1;
                                yrand=j;
                                MXoY=0;
                                ban5=1;
                            }
                            if(YState[i][j]==0){
                                xrand=i;
                                yrand=j;
                                MXoY=1;
                                ban5=1;
                            }
                            if(YState[i][j+1]==0){
                                xrand=i;
                                yrand=j+1;
                                MXoY=1;
                                ban5=1;
                            }
                        }
                if(ban5==0){
                    for (i = 0 ; i+1 <= 5; i++)
                        for (j = 0 ; j+1 <= 5; j++)
                            if(XYResult[i][j]<2){
                                ban6=1;
                                ban5=1;
                            }
                    if(ban6==1)
                    do{
                        xrand=rand()%6;
                        yrand=rand()%6;
                        MXoY=rand()%2;
                        if(MXoY==0&&XState[xrand][yrand]==FALSE)
                            break;
                        if(MXoY==1&&YState[xrand][yrand]==FALSE)
                            break;
                    }while(TRUE);
                }
                if(ban5==0)
                do{
                        xrand=rand()%6;
                        yrand=rand()%6;
                        MXoY=rand()%2;
                        if(MXoY==0&&XState[xrand][yrand]==FALSE)
                            ban=1;
                        if(MXoY==1&&YState[xrand][yrand]==FALSE)
                            ban=1;
                    }while(ban!=1);
                if(MXoY==0)
                {
                    XState[xrand][yrand]=1;
                }
                if(MXoY==1)
                {
                    YState[xrand][yrand]=1;
                }

                    fState [x][y] ^= 1 ;
                for (i = 0 ; i+1 <= 5; i++)
                    for (j = 0 ; j+1 <= 5; j++)
                        {
                        if(XYResult[i][j] != 4&&XState[i][j] + XState[i+1][j] + YState[i][j] + YState[i][j+1]==4){
                            winn[i][j] = -1;
                            ban2=1;
                        }
                        XYResult[i][j] = XState[i][j] + XState[i+1][j] + YState[i][j] + YState[i][j+1];
                        score1=XYResult[i][j] +score1;
                        score2=winn[i][j]+score2;
                    }
                  if(score1==DIVISIONS*DIVISIONS*4)
                    if(score2<0){
                        InvalidateRect (hwnd, NULL, FALSE) ;
                        if(MessageBox(0,"You have lost","Defeat",MB_OK)==IDOK){
                            for (i = 0 ; i <= 5; i++)
                                for (j = 0 ; j <= 5; j++)
                                {
                                    XState[i][j]=0;
                                    YState[i][j]=0;
                                    XYResult[i][j]=0;
                                    winn[i][j]=0;
                                }
                            ban=0;
                            ban1=0;
                            ban2=0;
                            score1=0;
                            score2=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                    } else{
                        InvalidateRect (hwnd, NULL, FALSE) ;
                        if(MessageBox(0,"You have won","Victory",MB_OK)==IDOK){
                            for (i = 0 ; i <= 5; i++)
                                for (j = 0 ; j <= 5; j++)
                                {
                                    XState[i][j]=0;
                                    YState[i][j]=0;
                                    XYResult[i][j]=0;
                                    winn[i][j]=0;
                                }
                            ban=0;
                            ban1=0;
                            ban2=0;
                            score1=0;
                            score2=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                    }
                InvalidateRect (hwnd, NULL, FALSE) ;
                }while(ban2==1);
                   InvalidateRect (hwnd, NULL, FALSE) ;
                }
               else
                    MessageBeep (0) ;
               return 0 ;

          case WM_PAINT :
               hdc = BeginPaint (hwnd, &ps) ;
               for (i = 0 ; i < DIVISIONS +1; i++)
                    for (j = 0 ; j < DIVISIONS+1; j++)
                            Ellipse(hdc,i*cxBlock-3,j*cyBlock-3,i*cxBlock+3,(j)*cyBlock+3);
               for (i = 0 ; i < DIVISIONS ; i++)
                    for (j = 0 ; j < DIVISIONS +1; j++)
                         if (XState [j][i]==1)
                              {

                                ajustx=0;
                                ajusty=0;
                                if (j==0)
                                    ajusty=3;
                                if (i==0)
                                    ajustx=3;
                                if (j==DIVISIONS)
                                    ajusty=-3;
                                if (i==DIVISIONS-1)
                                    ajustx=-3;
                              MoveTo (hdc,  i    * cxBlock +ajustx,  j    * cyBlock+ajusty) ;
                              LineTo (hdc, (i+1) * cxBlock+ajustx, (j) * cyBlock+ajusty ) ;

                              }
                for (i = 0 ; i < DIVISIONS +1 ; i++)
                    for (j = 0 ; j < DIVISIONS ; j++)
                         if (YState [j][i]==1)
                              {
                                ajustx=0;
                                ajusty=0;
                                if (j==0)
                                    ajusty=3;
                                if (i==0)
                                    ajustx=3;
                                if (j==DIVISIONS)
                                    ajusty=-3;
                                if (i==DIVISIONS-1)
                                    ajustx=-3;
                              MoveTo (hdc,  i * cxBlock+ajustx,  j    * cyBlock+ajusty) ;
                              LineTo (hdc, (i) * cxBlock+ajustx, (j+1) * cyBlock+ajusty) ;
                              }
                for (i = 0 ; i < DIVISIONS  ; i++)
                    for (j = 0 ; j < DIVISIONS ; j++)
                    {
                        if(winn[j][i]==1){
                             MoveTo (hdc,  i    * cxBlock,  j    * cyBlock) ;
                              LineTo (hdc, (i+1) * cxBlock, (j+1) * cyBlock) ;
                              MoveTo (hdc,  i    * cxBlock, (j+1) * cyBlock) ;
                              LineTo (hdc, (i+1) * cxBlock,  j    * cyBlock) ;
                        }
                        if(winn[j][i]==-1)
                        {
                            Ellipse(hdc,i * cxBlock, j * cyBlock,(i + 1) * cxBlock, (j + 1) * cyBlock);
                        }
                    }
               }
               LockWindowUpdate (NULL) ;
               EndPaint (hwnd, &ps) ;

               return 0 ;
          case WM_CLOSE:
            if(MessageBox(0,"Are you sure you want to exit?","Exit",MB_YESNO)==IDYES)
                exit(0);
            return 0;
          case WM_DESTROY :
               PostQuitMessage (0) ;
               return 0 ;
          }
     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
     }
