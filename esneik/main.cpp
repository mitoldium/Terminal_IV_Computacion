/*-------------------------------------------------
   TEST1.C -- Demo Test de posición del ratón, nº 1
              (c) Charles Petzold, 1996
  -------------------------------------------------*/

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define DIVISIONS1 90
#define DIVISIONS2 50
#define ID_TIMER 1
#define MoveTo(hdc, x, y) MoveToEx (hdc, x, y, NULL)


typedef struct _nodo {
   int x;
   int y;
   struct _nodo *siguiente;
   struct _nodo *anterior;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;


void Insertar(Lista *lista, int v, int w)
{
   pNodo nuevo, actual;
   nuevo = (pNodo)malloc(sizeof(tipoNodo));
   nuevo->x = v;
   nuevo->y = w;

   /* Colocamos actual en la primera posición de la lista */
   actual = *lista;
   if(actual) while(actual->anterior) actual = actual->anterior;
    nuevo->siguiente= actual;
    nuevo->anterior = NULL;
   /* Si la lista está vacía o el primer miembro es mayor que el nuevo*/ if(!actual ) {
      /* Añadimos la lista a continuación del nuevo nodo */
      nuevo->anterior = actual;
      nuevo->siguiente= NULL;
      if(actual) actual->anterior = nuevo;
      if(!*lista) *lista = nuevo;
   }
   else {
      /* Avanzamos hasta el último elemento o hasta que el siguiente tenga
         un valor mayor que v */
      while(actual->siguiente && actual->siguiente->x <= v && actual->siguiente->y <= w)
         actual = actual->siguiente;
      /* Insertamos el nuevo nodo después del nodo anterior */
      nuevo->siguiente = actual->siguiente;
      actual->siguiente = nuevo;
      nuevo->anterior = actual;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
   }

}


void BorrarLista(Lista *lista)
{
   pNodo nodo, actual;

   actual = *lista;
   while(actual->anterior) actual = actual->anterior;

   while(actual) {
      nodo = actual;
      actual = actual->siguiente;
      free(nodo);
   }
   *lista = NULL;
}


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

     hwnd = CreateWindow (szAppName, "ESNEIK GUEIM :v",
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
     static BOOL fState[DIVISIONS1][DIVISIONS2], inicio;

     static int  cxBlock, cyBlock,dire=1,ban1=0,xrand=0,yrand=0,sum=9, score=0;
     char escore[100];

     static Lista esneik = NULL;
     static BOOL FState[DIVISIONS1][DIVISIONS2];
     HDC         hdc ;
     PAINTSTRUCT ps ;
      HBRUSH hBrush, hBrush1;
     RECT        rect2 ;
     int         kk,ll,sum1=0, headx, heady;
     if (inicio == 0)
     {
        SetTimer(hwnd, ID_TIMER, 10, NULL);
         for(kk = 0;kk < 9; kk++)
         {
             fState[kk+40][20] = 1;
             Insertar(&esneik, kk+40, 20);
                    rect2.left   = (kk+40) * cxBlock ;
                    rect2.top    = 20 *cyBlock;
                    rect2.right  = (kk+40 + 1) * cxBlock ;
                    rect2.bottom = 21*cyBlock;
                    InvalidateRect (hwnd, &rect2, FALSE) ;
         }
         inicio = 1;
        while(esneik->anterior!=NULL)
        esneik=esneik->anterior;
     }


     if(ban1==0){
     FState[xrand][yrand]=0;
     do{
        xrand=rand()%90;
        yrand=rand()%50;
     }while(fState[xrand][yrand]==1);
     FState[xrand][yrand]=1;
     rect2.left   = (xrand) * cxBlock ;
     rect2.top    = (yrand)*cyBlock ;
     rect2.right  = (xrand+1) * cxBlock ;
     rect2.bottom = (yrand+1)*cyBlock;
     InvalidateRect (hwnd, &rect2, TRUE) ;
     ban1=1;
     }

     switch (iMsg)
          {
          case WM_SIZE :
               cxBlock = LOWORD (lParam) / DIVISIONS1 ;
               cyBlock = HIWORD (lParam) / DIVISIONS2 ;
               return 0 ;

          case WM_TIMER :
               //x = LOWORD (lParam) / cxBlock ;
               //y = HIWORD (lParam) / cyBlock ;
                if(dire==1){
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                    headx=esneik->x+1;
                    heady=esneik->y;
                    while(esneik->anterior!=NULL){
                        esneik=esneik->anterior;
                        if(esneik->x==headx && esneik->y==heady){
                            KillTimer(hwnd,ID_TIMER);
                            itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }

                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            score=0;
                            inicio=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                        }
                    }
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                    if(esneik->x+1==xrand&&esneik->y==yrand)
                    {

                        fState[xrand][yrand]=1;
                        Insertar(&esneik,xrand,yrand);
                        score++;
                        ban1=0;
                        sum++;
                    }

                    while(esneik->anterior!=NULL)
                        esneik=esneik->anterior;
                    for (int i = 0 ; i < DIVISIONS1 ; i++)
                    for (int j = 0 ; j < DIVISIONS2 ; j++)
                        sum1=sum1+fState[i][j];
                    fState[esneik->x][esneik->y]=0;
                    rect2.left   = (esneik->x) * cxBlock ;
                    rect2.top    = (esneik->y)*cyBlock ;
                    rect2.right  = ((esneik->x)+1) * cxBlock ;
                    rect2.bottom = ((esneik->y)+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, TRUE) ;
                    while(esneik->siguiente!=NULL){
                        esneik->x=(esneik->siguiente)->x;
                        esneik->y=(esneik->siguiente)->y;
                        esneik=esneik->siguiente;
                    }
                    if((esneik->x)+1>=DIVISIONS1){
                        KillTimer(hwnd,ID_TIMER);
                        itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }

                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            inicio=0;
                            score=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                    }
                    esneik->x=(esneik->x)+1;
                    fState[esneik->x][esneik->y]=1;
                    rect2.left   = (esneik->x) * cxBlock ;
                    rect2.top    = (esneik->y)*cyBlock ;
                    rect2.right  = ((esneik->x)+1) * cxBlock ;
                    rect2.bottom = ((esneik->y)+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, TRUE) ;
                    while(esneik->anterior!=NULL)
                    esneik=esneik->anterior;
                }
                if(dire==2){
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                        headx=esneik->x;
                    heady=esneik->y-1;
                    while(esneik->anterior!=NULL){
                        esneik=esneik->anterior;
                        if(esneik->x==headx && esneik->y==heady){
                            KillTimer(hwnd,ID_TIMER);
                            itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }

                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            score=0;
                            inicio=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                        }
                    }
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                    if(esneik->x==xrand&&esneik->y-1==yrand)
                    {
                        fState[xrand][yrand]=1;
                        Insertar(&esneik,xrand,yrand);
                        score++;
                        ban1=0;
                        sum++;
                    }

                    while(esneik->anterior!=NULL)
                        esneik=esneik->anterior;
                    for (int i = 0 ; i < DIVISIONS1 ; i++)
                    for (int j = 0 ; j < DIVISIONS2 ; j++)
                        sum1=sum1+fState[i][j];
                    fState[esneik->x][esneik->y]=0;
                    rect2.left   = esneik->x * cxBlock ;
                    rect2.top    = esneik->y*cyBlock ;
                    rect2.right  = (esneik->x+1) * cxBlock ;
                    rect2.bottom = (esneik->y+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, FALSE) ;
                    while(esneik->siguiente!=NULL){
                        esneik->x=esneik->siguiente->x;
                        esneik->y=esneik->siguiente->y;
                        esneik=esneik->siguiente;
                    }
                    if(esneik->y-1<0){
                        KillTimer(hwnd,ID_TIMER);
                        itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }

                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            inicio=0;
                            score=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                    }
                    esneik->y=esneik->y-1;
                    fState[esneik->x][esneik->y]=1;
                    rect2.left   = esneik->x * cxBlock ;
                    rect2.top    = esneik->y*cyBlock ;
                    rect2.right  = (esneik->x+1) * cxBlock ;
                    rect2.bottom = (esneik->y+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, FALSE) ;
                    while(esneik->anterior!=NULL)
                    esneik=esneik->anterior;
                }
                if(dire==3){
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                        headx=esneik->x-1;
                    heady=esneik->y;
                    while(esneik->anterior!=NULL){
                        esneik=esneik->anterior;
                        if(esneik->x==headx && esneik->y==heady){
                            KillTimer(hwnd,ID_TIMER);
                            itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }

                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            score=0;
                            inicio=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                        }
                    }
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                    if(esneik->x-1==xrand&&esneik->y==yrand)
                    {

                        fState[esneik->x-1][esneik->y]=1;
                        Insertar(&esneik,xrand,yrand);
                        score++;
                        ban1=0;
                        sum++;
                    }

                    while(esneik->anterior!=NULL)
                        esneik=esneik->anterior;
                    fState[esneik->x][esneik->y]=0;
                    rect2.left   = esneik->x * cxBlock ;
                    rect2.top    = esneik->y*cyBlock ;
                    rect2.right  = (esneik->x+1) * cxBlock ;
                    rect2.bottom = (esneik->y+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, FALSE) ;

                    while(esneik->siguiente!=NULL){
                        esneik->x=esneik->siguiente->x;
                        esneik->y=esneik->siguiente->y;
                        esneik=esneik->siguiente;
                    }
                    if(esneik->x-1<0){
                        KillTimer(hwnd,ID_TIMER);
                        itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }
                            score=0;
                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            inicio=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                    }
                    esneik->x=(esneik->x)-1;
                    fState[esneik->x][esneik->y]=1;
                    rect2.left   = (esneik->x) * cxBlock ;
                    rect2.top    = (esneik->y)*cyBlock ;
                    rect2.right  = ((esneik->x)+1) * cxBlock ;
                    rect2.bottom = ((esneik->y)+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, FALSE) ;
                    while(esneik->anterior!=NULL)
                    esneik=esneik->anterior;
                }
                if(dire==4){
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                        headx=esneik->x;
                    heady=esneik->y+1;
                    while(esneik->anterior!=NULL){
                        esneik=esneik->anterior;
                        if(esneik->x==headx && esneik->y==heady){
                            KillTimer(hwnd,ID_TIMER);
                            itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }
                            score=0;
                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            inicio=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }
                        }
                    }
                    while(esneik->siguiente!=NULL)
                        esneik=esneik->siguiente;
                    if(esneik->x==xrand&&esneik->y+1==yrand)
                    {

                        fState[xrand][yrand]=1;
                        Insertar(&esneik,xrand,yrand);
                        score++;
                        ban1=0;
                        sum++;


                    }

                    while(esneik->anterior!=NULL)
                        esneik=esneik->anterior;
                    for (int i = 0 ; i < DIVISIONS1 ; i++)
                    for (int j = 0 ; j < DIVISIONS2 ; j++)
                        sum1=sum1+fState[i][j];
                    fState[esneik->x][esneik->y]=0;
                    rect2.left   = esneik->x * cxBlock ;
                    rect2.top    = esneik->y*cyBlock ;
                    rect2.right  = (esneik->x+1) * cxBlock ;
                    rect2.bottom = (esneik->y+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, FALSE) ;
                    while(esneik->siguiente!=NULL){
                        esneik->x=esneik->siguiente->x;
                        esneik->y=esneik->siguiente->y;
                        esneik=esneik->siguiente;
                    }
                    if((esneik->y)+1>=DIVISIONS2){
                        KillTimer(hwnd,ID_TIMER);
                        itoa(score, escore, 10);
                            strcat(escore," \nGame Over!");
                        if(MessageBox(0,escore,"Died!",MB_OK)==IDOK){
                            BorrarLista(&esneik);
                            for ( kk = 0 ; kk < DIVISIONS1 ; kk++)
                                for ( ll = 0 ; ll < DIVISIONS2 ; ll++){
                                    fState[kk][ll]=0;
                                    FState[kk][ll]=0;
                                }
                            score=0;
                            dire=1;
                            ban1=0;
                            xrand=0;
                            yrand=0;
                            sum=9;
                            inicio=0;
                            InvalidateRect (hwnd, NULL, TRUE) ;
                            return 0;
                        }

                    }
                    esneik->y=esneik->y+1;
                    fState[esneik->x][esneik->y]=1;
                    rect2.left   = esneik->x * cxBlock ;
                    rect2.top    = esneik->y*cyBlock ;
                    rect2.right  = (esneik->x+1) * cxBlock ;
                    rect2.bottom = (esneik->y+1)*cyBlock;
                    InvalidateRect (hwnd, &rect2, FALSE) ;
                    while(esneik->anterior!=NULL)
                    esneik=esneik->anterior;
                }
               return 0 ;
          case WM_KEYDOWN:
                switch(wParam)
                    {
                    case VK_RIGHT:
                       if(dire!=3)
                        dire = 1;
                        break;
                    case VK_UP:
                        if(dire!=4)
                        dire = 2;
                        break;
                    case VK_LEFT:
                        if(dire!=1)
                        dire = 3;
                        break;
                    case VK_DOWN:
                        if(dire!=2)
                        dire = 4;
                        break;
                    }
                return 0;
          case WM_PAINT :
               hdc = BeginPaint (hwnd, &ps) ;
                for (int i = 0 ; i < DIVISIONS1 ; i++)
                    for (int j = 0 ; j < DIVISIONS2 ; j++)
                         {
                         if (fState [i][j]==1)
                              {

                        hBrush = CreateSolidBrush (RGB (rand()%256, rand()%256,
                                                    rand()%256)) ;

                    rect2.left   = i * cxBlock ;
                    rect2.top    = j*cyBlock ;
                    rect2.right  = (i+1) * cxBlock ;
                    rect2.bottom = (j+1)*cyBlock;

                            FillRect (hdc, &rect2, hBrush) ;
                            DeleteObject(hBrush);
                              }
                              else {
                            hBrush1 = CreateSolidBrush (RGB (0, 0,
                                                    0) );
                    rect2.left   = i * cxBlock ;
                    rect2.top    = j*cyBlock ;
                    rect2.right  = (i+1) * cxBlock ;
                    rect2.bottom = (j+1)*cyBlock;
                            FillRect (hdc, &rect2, hBrush1) ;
                            DeleteObject(hBrush1);
                         }
                         }
                for (int i = 0 ; i < DIVISIONS1 ; i++)
                    for (int j = 0 ; j < DIVISIONS2 ; j++)
                        if (FState [i][j]==1)
                              {
                                  hBrush = CreateSolidBrush (RGB (255, 255,255)) ;
                                rect2.left   = i * cxBlock ;
                            rect2.top    = j*cyBlock ;
                            rect2.right  = (i+1) * cxBlock ;
                            rect2.bottom = (j+1)*cyBlock;
                            FillRect (hdc, &rect2, hBrush) ;
                            DeleteObject(hBrush);
                              }

               EndPaint (hwnd, &ps) ;
               return 0 ;
          case WM_CLOSE:
                KillTimer(hwnd, ID_TIMER);

                if (MessageBox(0,"Are you sure you want to exit?","EXIT", MB_YESNO)==IDYES)
                    exit(0);
                else         SetTimer(hwnd, ID_TIMER, 100, NULL);
                return 0;

          case WM_DESTROY :
               PostQuitMessage (0) ;
               KillTimer(hwnd, ID_TIMER);
               return 0 ;
          }
     return DefWindowProc (hwnd, iMsg, wParam, lParam) ;
     }
