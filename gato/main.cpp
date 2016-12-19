/*-------------------------------------------------
   TEST1.C -- Demo Test de posición del ratón, nº 1
              (c) Charles Petzold, 1996
  -------------------------------------------------*/

#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define DIVISIONS 3
#define MoveTo(hdc, x, y) MoveToEx (hdc, x, y, NULL)

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;


int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR  szCmdLine, int iCmdShow)
     {
     srand(time(NULL));
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

     RegisterClassEx (&wndclass) ;

     hwnd = CreateWindow (szAppName, "Tic Tac Toe",
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
     static BOOL fState[DIVISIONS][DIVISIONS];

     static int  cxBlock, cyBlock, wonn=0;
     static int  FState[3][3]={{0,0,0},{0,0,0},{0,0,0}};
     HDC         hdc ;
     PAINTSTRUCT ps ;
     RECT        rect1,rect2 ;
     int         x, y , xrand=0,yrand=0,kk,ll,kkk,lll,finsi=1,sum=0,i ,move, ban1=0;
     static int         board[9]={0,0,0,0,0,0,0,0,0};
     switch (iMsg)
          {
          case WM_SIZE :
               cxBlock = LOWORD (lParam) / DIVISIONS ;
               cyBlock = HIWORD (lParam) / DIVISIONS ;
               return 0 ;

          case WM_LBUTTONDOWN :
               x = LOWORD (lParam) / cxBlock ;
               y = HIWORD (lParam) / cyBlock ;

               if(fState [x][y]==FALSE){
                if(wonn==0){
               if (x < DIVISIONS && y < DIVISIONS)
                    {
                    FState[x][y]=1;
                    fState [x][y] =TRUE  ;

                    rect1.left   = x * cxBlock ;
                    rect1.top    = y * cyBlock ;
                    rect1.right  = (x + 1) * cxBlock ;
                    rect1.bottom = (y + 1) * cyBlock ;
                    finsi=1;
                    for(kk=0;kk<=2;kk++)
                        for(ll=0;ll<=2;ll++)
                                if(fState[kk][ll]==FALSE)
                                         finsi=0;
                    InvalidateRect (hwnd, &rect1, FALSE) ;
                     for(kk=0;kk<=2;kk++){
                        for(ll=0;ll<=2;ll++)
                            sum=sum+FState [kk][ll];
                        if(sum==3){
                             wonn=1;
                            if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                        if(sum==-3){
                            wonn=1;
                            if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                        sum=0;
                }
                for(kk=0;kk<=2;kk++){
                        for(ll=0;ll<=2;ll++)
                            sum=sum+FState [ll][kk];
                        if(sum==3){
                            wonn=1;
                            if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                        if(sum==-3){
                            wonn=1;
                                if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                    }
                    sum=0;
                }
                if(FState [0][0]+FState [1][1]+FState [2][2]==3){
                    wonn=1;
                    if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                }
                if(FState [0][0]+FState [1][1]+FState [2][2]==-3){
                    wonn=1;
                                if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                }
                if(FState [2][0]+FState [1][1]+FState [0][2]==3){
                    wonn=1;
                    if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                }
                if(FState [2][0]+FState [1][1]+FState [0][2]==-3){
                    wonn=1;
                                if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                if(finsi==1&&wonn==0)
                     if(MessageBox(0,"it's a Draw", "Tie", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                                        return 0 ;
                            }
                    if(wonn!=1){
                    if(finsi==0){
                   ban1=0;

                    if(fState[1][1]==0){
                        xrand=1;
                        yrand=1;
                        ban1=1;
                    }
                    for(kk=0;kk<=2;kk++)
                            for(ll=0;ll<=2;ll++)
                                sum=sum+fState [kk][ll];
                    if(FState[1][1]==1&&sum==1){
                        xrand=0;
                        yrand=0;
                        ban1=1;
                    }
                    sum=0;
                    for(kk=0;kk<=2;kk++)
                            for(ll=0;ll<=2;ll++)
                                sum=sum+fState [kk][ll];
                    if(fState[1][1]==1&&fState[0][0]==1&&fState[2][2]==1&&sum==3){
                        xrand=0;
                        yrand=2;
                        ban1=1;
                    }
                    //Gane
                    sum=0;
                    if(ban1!=1)
                    {
                        for(kk=0;kk<=2;kk++){
                            for(ll=0;ll<=2;ll++)
                                sum=sum+FState [kk][ll];
                            if (sum==-2){
                                    ll=0;
                                    while(fState[kk][ll]==1)
                                        ll++;
                                    xrand=kk;
                                    yrand=ll;
                                    ban1=1;
                                    break;
                            }
                            sum=0;
                        }
                    }
                    if(ban1!=1)
                    {
                       for(kk=0;kk<=2;kk++){
                            for(ll=0;ll<=2;ll++)
                                sum=sum+FState [ll][kk];
                            if (sum==-2){
                                    ll=0;
                                    while(fState[ll][kk]==1)
                                        ll++;
                                    xrand=ll;
                                    yrand=kk;
                                    ban1=1;
                                    break;
                            }
                            sum=0;
                       }
                    }
                    if(ban1!=1)
                    {
                        if(FState [2][0]+FState [1][1]+FState [0][2]==-2){
                            if (fState[2][0]==0){
                                xrand=2;
                                yrand=0;
                                ban1=1;
                                }
                            if (fState[1][1]==0){
                                xrand=1;
                                yrand=1;
                                ban1=1;
                                }
                            if (fState[0][2]==0){
                                xrand=0;
                                yrand=2;
                                ban1=1;
                                }
                        }
                    }
                    if(ban1!=1)
                    {
                         if(FState [0][0]+FState [1][1]+FState [2][2]==-2){
                             if (fState[0][0]==0){
                                xrand=0;
                                yrand=0;
                                ban1=1;
                                }
                            if (fState[1][1]==0){
                                xrand=1;
                                yrand=1;
                                ban1=1;
                                }
                            if (fState[2][2]==0){
                                xrand=2;
                                yrand=2;
                                ban1=1;
                                }
                         }
                    }
                    sum=0;
                   //Bloqueo
                    if(ban1!=1)
                    {
                        for(kk=0;kk<=2;kk++){
                            for(ll=0;ll<=2;ll++)
                                sum=sum+FState [kk][ll];
                            if (sum==2){
                                    ll=0;
                                    while(fState[kk][ll]==1)
                                        ll++;
                                    xrand=kk;
                                    yrand=ll;
                                    ban1=1;
                                    break;
                            }
                            sum=0;
                        }
                    }
                    if(ban1!=1)
                    {
                       for(kk=0;kk<=2;kk++){
                            for(ll=0;ll<=2;ll++)
                                sum=sum+FState [ll][kk];
                            if (sum==2){
                                    ll=0;
                                    while(fState[ll][kk]==1)
                                        ll++;
                                    xrand=ll;
                                    yrand=kk;
                                    ban1=1;
                                    break;
                            }
                            sum=0;
                       }
                    }
                    if(ban1!=1)
                    {
                        if(FState [2][0]+FState [1][1]+FState [0][2]==2){
                            if (fState[2][0]==0){
                                xrand=2;
                                yrand=0;
                                ban1=1;
                                }
                            if (fState[1][1]==0){
                                xrand=1;
                                yrand=1;
                                ban1=1;
                                }
                            if (fState[0][2]==0){
                                xrand=0;
                                yrand=2;
                                ban1=1;
                                }
                        }
                    }
                    if(ban1!=1)
                    {
                         if(FState [0][0]+FState [1][1]+FState [2][2]==2){
                             if (fState[0][0]==0){
                                xrand=0;
                                yrand=0;
                                ban1=1;
                                }
                            if (fState[1][1]==0){
                                xrand=1;
                                yrand=1;
                                ban1=1;
                                }
                            if (fState[2][2]==0){
                                xrand=2;
                                yrand=2;
                                ban1=1;
                                }
                         }
                    }
                    sum=0;
                    //Libre
                    if(ban1!=1)
                        if(FState [1][0]+FState [1][1]+FState [1][2]==1||FState [1][0]+FState [1][1]+FState [1][2]==-1){
                                if(fState [1][0]==0||fState [1][2]==0){
                                    xrand=1;
                                    yrand=0;
                                    ban1=1;
                                    }
                        }
                    if(ban1!=1)
                        if(FState [0][1]+FState [1][1]+FState [2][1]==1||FState [0][1]+FState [1][1]+FState [2][1]==-1){
                                if(fState [0][1]==0||fState [2][1]==0){
                                    xrand=0;
                                    yrand=1;
                                    ban1=1;
                                }
                        }

                    if(ban1==0)
                   do{
                        xrand=rand()%3;
                        yrand=rand()%3;
                    }while(fState[xrand][yrand]==TRUE);
                    FState[xrand][yrand]=-1;
                    fState [xrand][yrand]=TRUE;
                    rect2.left   = xrand * cxBlock ;
                    rect2.top    = yrand * cyBlock ;
                    rect2.right  = (xrand + 1) * cxBlock ;
                    rect2.bottom = (yrand + 1) * cyBlock ;

                    InvalidateRect (hwnd, &rect2, FALSE) ;
                    }
                    }
                    }
               else
                    MessageBeep (0) ;
                if(wonn!=1){
                for(kk=0;kk<=2;kk++){
                        for(ll=0;ll<=2;ll++)
                            sum=sum+FState [kk][ll];
                        if(sum==3){
                            wonn=1;
                                if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                        if(sum==-3){
                            wonn=1;
                            if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                        sum=0;
                }
                for(kk=0;kk<=2;kk++){
                        for(ll=0;ll<=2;ll++)
                            sum=sum+FState [ll][kk];
                        if(sum==3){
                            wonn=1;
                                if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                        if(sum==-3){
                            wonn=1;
                            if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                        sum=0;
                }
                if(FState [0][0]+FState [1][1]+FState [2][2]==3){
                    wonn=1;
                            if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                if(FState [0][0]+FState [1][1]+FState [2][2]==-3){
                    wonn=1;
                    if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                }
                if(FState [2][0]+FState [1][1]+FState [0][2]==3){
                    wonn=1;
                            if(MessageBox(0,"you have Won!!!", "Victory!!", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                        }
                if(FState [2][0]+FState [1][1]+FState [0][2]==-3){
                    wonn=1;
                    if(MessageBox(0,"you have Lost...", "Defeat...", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                            }
                        return 0 ;
                }
                if(finsi==1&&wonn==0)
                            if(MessageBox(0,"it's a Draw", "Tie", MB_OK )==IDOK){
                                    for(kkk=0;kkk<=2;kkk++)
                                        for(lll=0;lll<=2;lll++)
                                        {
                                            FState[kkk][lll]=0;
                                            fState[kkk][lll]=0;
                                        }
                                        InvalidateRect (hwnd, NULL, FALSE) ;
                                        wonn=0;
                                        return 0 ;
                            }                }
               }
               }
               return 0 ;

          case WM_PAINT :
               hdc = BeginPaint (hwnd, &ps) ;

               for (x = 0 ; x < DIVISIONS ; x++)
                    for (y = 0 ; y < DIVISIONS ; y++)
                         {
                         Rectangle (hdc, x * cxBlock, y * cyBlock,
                                   (x + 1) * cxBlock, (y + 1) * cyBlock) ;

                         if (fState [x][y]&&FState[x][y]==1)
                              {
                              MoveTo (hdc,  x    * cxBlock,  y    * cyBlock) ;
                              LineTo (hdc, (x+1) * cxBlock, (y+1) * cyBlock) ;
                              MoveTo (hdc,  x    * cxBlock, (y+1) * cyBlock) ;
                              LineTo (hdc, (x+1) * cxBlock,  y    * cyBlock) ;
                              }
                          if (fState [x][y]&&FState[x][y]==-1)
                          {
                              Ellipse(hdc,x * cxBlock, y * cyBlock,(x + 1) * cxBlock, (y + 1) * cyBlock);
                          }



                         }
               EndPaint (hwnd, &ps) ;
               return 0 ;
          case WM_CLOSE:
                if(MessageBox(0,"Are you sure you want to exit?","Exit", MB_YESNO )==IDYES)
                        exit(0);
                return 0;

          case WM_DESTROY :

                PostQuitMessage (0) ;
               return 0 ;
          }
     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
     }
