#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>

#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include <math.h>
#define pi 3.14
#include <time.h>
#include <iostream>
#include<fstream>
#include<stdint.h>
#include<conio.h>
#include"queue.h"

using namespace std;

SDL_Surface *screen;
int width = 1000;
int height = 700;
queue Queue;
char const* tytul = "GKiM - Lab 5 - Nazwisko Imie";


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);
SDL_Color getPixel (int x, int y);

void czyscEkran(Uint8 R, Uint8 G, Uint8 B);

SDL_Color tab[12000];
int counter=-1;
int tab_count[12000]={0};

void Funkcja1();
void Funkcja2();
void Funkcja3();
void Funkcja4();
void Funkcja5();

struct slownik{
    int key;
    Uint8 huffmancode[6000];
    int dlugosc;
    SDL_Color colors;
};
struct slownik2{
    int key;
    Uint8 huffmancode[6000];
    int dlugosc;
    SDL_Color colors;
};

void Funkcja1() {

    bool waski;

    for(int y=0; y<300; y++)
        {
        for(int x=0; x<450; x++)
        {
            SDL_Color temp=getPixel(x,y);
            waski=true;
            if(counter==-1)
            {
                tab[0]=temp;
                tab_count[0]+=1;
                counter++;
            }
            else
            {
                for(int i=0; i<=counter; i++)
                {
                    if(temp.r == tab[i].r && temp.g == tab[i].g && temp.b == tab[i].b)
                    {
                        tab_count[i]+=1;
                        waski=false;
                    }
                }
            if(waski==true)
            {
                tab[counter+1]=temp;
                tab_count[counter+1]+=1;
                counter++;

            }
            }
        }
    }
        cout<<"counter- " << counter <<endl;
       for(int i=0; i<=counter; i++)
            cout<< i <<". " << "R- "<< (int)tab[i].r <<" G- "<<(int)tab[i].g <<" B- "<< (int)tab[i].b << endl;

         for(int i=0; i<=counter; i++)
            cout<<i<<" ilosc- " << tab_count[i] << endl;

    SDL_Flip(screen);

}
void Funkcja2() {



    for(int i=0; i<=counter; i++)
    {
        Node * p=new Node;
        p->parent=NULL;
        p->left=NULL;
        p->right=NULL;
        p->frequency=tab_count[i];
        p->key=i;
        Queue.push(p);
       // cout<< p->key << " fre- " << p->frequency << endl;


    }


    SDL_Flip(screen);

}
void inorder(Node * n, Uint8 *c, int lg,slownik *tab)
{
  if(!(n->left))                                                    //odczytuje znaki gdy adres lewego daje null
  {
    for(int i = 0; i <=lg; i++)
     {
           tab[n->key].huffmancode[i]=c[i];

    }
 for(int i = 0; i <=lg; i++)
    cout<<(int)c[i];

    cout<< endl;
    tab[n->key].dlugosc=lg;
    tab[n->key].key=n->key;
    cout << endl;
  }
  else                                                             //jesli adres nie jest NULL przypisujemy znaki do krawedzi
  {
    c[lg] = 0; inorder(n->left,c,lg + 1,tab);                       // i zwiekszamy dlugosc lg +1
    c[lg] = 1; inorder(n->right,c,lg + 1,tab);
  }
}

void Funkcja3() {

    Uint8 c[6000];
    Node * temp_node1;
    Node * temp_node2;
    Node * new_root;
    int temp_frequency1;
    int temp_frequency2;

    slownik * tab_elements=new slownik[counter + 1];

    while(!Queue.empty_q())
    {
        temp_frequency1=Queue.pull();
        temp_node1=Queue.pulltree();
        Queue.pop();

        temp_frequency2=Queue.pull();
        temp_node2=Queue.pulltree();
        Queue.pop();

        new_root=new Node;
        new_root->parent=NULL;
        new_root->frequency = (temp_frequency1 + temp_frequency2);
        new_root->left = temp_node1;
        new_root->right= temp_node2;

        if(Queue.empty_q())break;

        Queue.pushroot(new_root);

    }

    inorder(new_root,c,0,tab_elements);
    for(int i=0; i<=counter; i++)
    {
        tab_elements[i].colors.r=tab[i].r;
        tab_elements[i].colors.g=tab[i].g;
        tab_elements[i].colors.b=tab[i].b;

    }
    cout<<"Slownik do kodowania/dekodowania huffmana: " << endl;
    for(int i=0; i<=counter; i++)
    {
        cout << tab_elements[i].key <<"." ;
        cout <<"\tR- "<< (int)tab_elements[i].colors.r ;
        cout <<"\tG- "<< (int)tab_elements[i].colors.g ;
        cout <<"\tB- "<< (int)tab_elements[i].colors.b ;
         cout <<"\tD-" <<(int)tab_elements[i].dlugosc;
        cout <<"\tkod - ";
         for(int j=0; j<tab_elements[i].dlugosc; j++)
        cout << (int)tab_elements[i].huffmancode[j];

        cout <<endl;
    }

    int maximum=0;
    for(int i=0; i<=counter; i++)
    {
        if(maximum <tab_elements[i].dlugosc)
        {
            maximum=tab_elements[i].dlugosc;
        }
    }

    ofstream plik;
    plik.open("zakodowany1.huff", ios::binary);

    Uint16 rozmiar_slownika=0;
    Uint16  najdluzszy_kodH=0;
    rozmiar_slownika=rozmiar_slownika|(counter+1);
    najdluzszy_kodH=najdluzszy_kodH | maximum;
    plik.write((const char *) &rozmiar_slownika,sizeof(rozmiar_slownika));
    plik.write((const char *) &najdluzszy_kodH,sizeof(najdluzszy_kodH));
    Uint16 kolory=0;
    Uint8 kodhuff=0;
    Uint8 dlugosc=0;




    for(int i=0; i<=counter; i++)
    {

        plik.write((const char *) & tab_elements[i].colors.r,sizeof(Uint8));
        plik.write((const char *) & tab_elements[i].colors.g,sizeof(Uint8));
        plik.write((const char *) & tab_elements[i].colors.b,sizeof(Uint8));
        dlugosc=tab_elements[i].dlugosc|dlugosc;
        plik.write((const char *) & dlugosc,sizeof(dlugosc));
        dlugosc=0;

       for(int j=0; j<=tab_elements[i].dlugosc; j++)
        {
            kodhuff<<1;
            kodhuff=kodhuff|tab_elements[i].huffmancode[j];
            plik.write((const char *)&kodhuff,sizeof(kodhuff));
            kodhuff=0;
        }


    }
    int licznik=1;
    Uint8 temp1=0;;
     for(int y=0;y<300;y++)
        {
       for(int x=0; x<450; x++)
        {
           SDL_Color temp=getPixel(x,y);

           for(int i=0; i<=counter;i++)
           {

               if(temp.r == tab_elements[i].colors.r && temp.g == tab_elements[i].colors.g && temp.b == tab_elements[i].colors.b)
               {



                         for(int j=0; j<=tab_elements[i].dlugosc; j++)
                            {

                                        if(licznik<8)
                                        {
                                        licznik++;
                                        temp1= temp1<<1;
                                        temp1=temp1 | tab_elements[i].huffmancode[j];
                                        }
                                        else
                                        {
                                           plik.write((const char *)&temp1,sizeof(Uint8));

                                           temp1=0;
                                           licznik=1;
                                           temp1=temp1 | tab_elements[i].huffmancode[j];

                                        }

                            }



               }
           }

        }



//...
SDL_Flip(screen);
}


}
int przeszukaj_slownik(Uint8 *tab, slownik2 *tab2, int dlugosc_kodu, int rozmiar_slownika);

void Funkcja4()
{
   Uint16 rozmiar_slownika=0;
   Uint16 najdluzszy_kod=0;
   Uint16 kolor=0;
   Uint8 kod_huff=0;
   Uint8 dlugosc=0;

   int temporary=0;

   ifstream plik;
   plik.open("zakodowany1.huff",ios::binary);
   plik.read((char *) & rozmiar_slownika ,sizeof(Uint16));
   plik.read((char *) & najdluzszy_kod ,sizeof(Uint16));
   slownik2 *elementy_slownika=new slownik2[rozmiar_slownika];

   for(int i=0; i<rozmiar_slownika; i++)
   {
       elementy_slownika[i].key=i;


       plik.read((char *)&elementy_slownika[i].colors.r,sizeof(Uint8));
       plik.read((char *)&elementy_slownika[i].colors.g,sizeof(Uint8));
       plik.read((char *)&elementy_slownika[i].colors.b,sizeof(Uint8));
       plik.read((char *) & dlugosc,sizeof(Uint8));
       elementy_slownika[i].dlugosc=dlugosc;

        for(int j=0; j<=elementy_slownika[i].dlugosc; j++)
        {
             plik.read((char *) & kod_huff,sizeof(Uint8));
             elementy_slownika[i].huffmancode[j]=kod_huff;
             kod_huff=0;
        }

   }


   for(int i=0; i<rozmiar_slownika; i++)
    {
        cout << elementy_slownika[i].key <<"." ;
        cout <<"\tR- "<< (int)elementy_slownika[i].colors.r ;
        cout <<"\tG- "<< (int)elementy_slownika[i].colors.g ;
        cout <<"\tB- "<< (int)elementy_slownika[i].colors.b ;
        cout <<"\tD-" <<(int)elementy_slownika[i].dlugosc;
        cout <<"\tkod - ";
        for(int j=0; j<elementy_slownika[i].dlugosc; j++)
         cout << (int)elementy_slownika[i].huffmancode[j];

        cout <<endl;
    }
    Uint8 tablica_do_szukania[najdluzszy_kod];
    Uint8 temp=0;
    int dlugosc_kodu_doszukania=0;
    int wysokosc=0;
    int szerokosc=0;
    int test=0;
    Uint8 maska=0;

    while(!plik.eof())
        {

       plik.read((char *) & temp,sizeof(Uint8));

       for(int i=7; i>=0; i--)
       {

            maska=1;
            maska=maska<<i;
            maska = temp & maska;
            maska= maska>>i;
            tablica_do_szukania[dlugosc_kodu_doszukania]=maska;

            test=przeszukaj_slownik(tablica_do_szukania,elementy_slownika,dlugosc_kodu_doszukania,rozmiar_slownika);


            if(test>=0)
            {
                 if(wysokosc<=299)
                setPixel(szerokosc+455,wysokosc,elementy_slownika[test].colors.r,elementy_slownika[test].colors.g,elementy_slownika[test].colors.b);

                for(int c=0; c<=najdluzszy_kod; c++)
                {
                    tablica_do_szukania[c]=0;
                }
                dlugosc_kodu_doszukania=0;

                szerokosc++;
                if(szerokosc==450)
                {
                    wysokosc++;
                    szerokosc=0;
                }

            }
            else
            {
            dlugosc_kodu_doszukania++;
            }
       }
        }


    SDL_Flip(screen);


}
int przeszukaj_slownik(Uint8 *tab, slownik2 *tab2, int dlugosc_kodu, int rozmiar_slownika)
{
    bool test=true;
    int indeks_slownika=-1;
    for(int i=0; i<rozmiar_slownika; i++)
    {
        test=true;
       if(tab2[i].dlugosc==dlugosc_kodu)
       {
            for(int j=0; j<dlugosc_kodu; j++)
            {
                if(tab2[i].huffmancode[j]!=tab[j])
                {
                    test=false;
                }

            }
            if(test)
            {
                indeks_slownika=i;
                break;

            }
       }
    }
     return indeks_slownika;

}

void Funkcja5() {


//...

    SDL_Flip(screen);

}


void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<width) && (y>=0) && (y<height))
  {
    /* Zamieniamy poszczególne skladowe koloru na format koloru pixela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informacji ile bajtów zajmuje jeden pixel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres pixela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartosc pixela, w zaleznci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;

    }
         /* update the screen (aka double buffering) */
  }
}

void ladujBMP(char const* nazwa, int x, int y)
{
    SDL_Surface* bmp = SDL_LoadBMP(nazwa);
    if (!bmp)
    {
        printf("Unable to load bitmap: %s\n", SDL_GetError());
    }
    else
    {
        SDL_Rect dstrect;
        dstrect.x = x;
        dstrect.y = y;
        SDL_BlitSurface(bmp, 0, screen, &dstrect);
        SDL_Flip(screen);
        SDL_FreeSurface(bmp);
    }

}

void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_Flip(screen);

}


SDL_Color getPixel (int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<width) && (y>=0) && (y<height)) {
        //determine position
        char* pPosition=(char*)screen->pixels ;
        //offset by y
        pPosition+=(screen->pitch*y) ;
        //offset by x
        pPosition+=(screen->format->BytesPerPixel*x);
        //copy pixel data
        memcpy(&col, pPosition, screen->format->BytesPerPixel);
        //convert color
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
    }
    return ( color ) ;
}


int main ( int argc, char** argv )
{
    // console output
    Uint8 cos=0;
    cos= cos | 1;
    cos =cos<<7;
    cout<< (int)cos;
    freopen( "CON", "wt", stdout );
    freopen( "CON", "wt", stderr );
    Uint8 unit=4;
    cout<< (int)cos;
    //cout<<unit<<endl;
    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);

    // create a new window
    screen = SDL_SetVideoMode(width, height, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption( tytul , NULL );
    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
                // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;

                // check for keypresses
            case SDL_KEYDOWN:
                {
                    // exit if ESCAPE is pressed
                    if (event.key.keysym.sym == SDLK_ESCAPE)
                        done = true;
                    if (event.key.keysym.sym == SDLK_1)
                        Funkcja1();
                    if (event.key.keysym.sym == SDLK_2)
                        Funkcja2();
                    if (event.key.keysym.sym == SDLK_3)
                        Funkcja3();
                    if (event.key.keysym.sym == SDLK_4)
                        Funkcja4();
                    if (event.key.keysym.sym == SDLK_5)
                        Funkcja5();
                    if (event.key.keysym.sym == SDLK_a)
                        ladujBMP("obrazek3.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_s)
                        ladujBMP("obrazek4.bmp", 0, 0);
                    if (event.key.keysym.sym == SDLK_d)
                        ladujBMP("obrazek5.bmp", 0, 0);

                    if (event.key.keysym.sym == SDLK_b)
                        czyscEkran(10, 0, 0);          break;
                     }
            } // end switch
        } // end of message processing

    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
