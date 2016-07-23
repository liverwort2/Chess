/**
remaining tasks:
1. Castling
2. draw system
3. promoting the pawn
**/


#include<SDL2/SDL.h>
#include<SDL2/SDL_keyboard.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<cstdlib>
#define pos SDL_WINDOWPOS_CENTERED
#define BSIZE 80
using namespace std;

int z=0;

int player=1;
char active='n';
int valid1=0, valid2=0, drawvalid1=0, drawvalid2=0;

bool wk=true, bk=true, wr1=true, wr2=true, br1=true, br2=true, checked1=false, checked2=false;

int kill[32];

int type[16];

int p=0,q=0,s=-1,r=-1,m=-1,n=-1;

SDL_Window* window=NULL;

SDL_Surface* fullBoard=IMG_Load("PNG/chessboard2.png");

SDL_Surface* b_pawn=IMG_Load("PNG/b_pawn.png");

SDL_Surface* b_rook0=IMG_Load("PNG/b_rook.png");
SDL_Surface* b_rook1=IMG_Load("PNG/b_rook.png");

SDL_Surface* b_bishop0=IMG_Load("PNG/b_bishop.png");
SDL_Surface* b_bishop1=IMG_Load("PNG/b_bishop.png");

SDL_Surface* b_knight0=IMG_Load("PNG/b_knight.png");
SDL_Surface* b_king0=IMG_Load("PNG/b_king.png");
SDL_Surface* b_queen0=IMG_Load("PNG/b_queen.png");
SDL_Surface* b_knight1=IMG_Load("PNG/b_knight.png");

SDL_Surface* w_pawn=IMG_Load("PNG/w_pawn.png");

SDL_Surface* w_rook0=IMG_Load("PNG/w_rook.png");
SDL_Surface* w_bishop0=IMG_Load("PNG/w_bishop.png");
SDL_Surface* w_knight0=IMG_Load("PNG/w_knight.png");
SDL_Surface* w_king0=IMG_Load("PNG/w_king.png");
SDL_Surface* w_queen0=IMG_Load("PNG/w_queen.png");
SDL_Surface* w_rook1=IMG_Load("PNG/w_rook.png");
SDL_Surface* w_bishop1=IMG_Load("PNG/w_bishop.png");
SDL_Surface* w_knight1=IMG_Load("PNG/w_knight.png");

SDL_Surface* selected=IMG_Load("PNG/selected.png");
SDL_Surface* allowed=IMG_Load("PNG/allowed.png");
SDL_Surface* checked=IMG_Load("PNG/checked.png");

SDL_Renderer* renderer=NULL;

SDL_Rect block_rect[8][8];
SDL_Rect window_rect;
SDL_Rect selected_rect;

SDL_Texture* t_fullBoard=NULL;

SDL_Texture* t_b_pawn=NULL;

SDL_Texture* t_b_rook0=NULL;
SDL_Texture* t_b_bishop0=NULL;
SDL_Texture* t_b_knight0=NULL;
SDL_Texture* t_b_king0=NULL;
SDL_Texture* t_b_queen0=NULL;
SDL_Texture* t_b_rook1=NULL;
SDL_Texture* t_b_bishop1=NULL;
SDL_Texture* t_b_knight1=NULL;

SDL_Texture* t_w_pawn=NULL;

SDL_Texture* t_w_rook0=NULL;
SDL_Texture* t_w_bishop0=NULL;
SDL_Texture* t_w_knight0=NULL;
SDL_Texture* t_w_king0=NULL;
SDL_Texture* t_w_queen0=NULL;
SDL_Texture* t_w_rook1=NULL;
SDL_Texture* t_w_bishop1=NULL;
SDL_Texture* t_w_knight1=NULL;

SDL_Texture* t_selected=NULL;
SDL_Texture* t_allowed=NULL;
SDL_Texture* t_checked=NULL;


//USER DEFINED FUNCTIONS
void draw();
void close();
void playerOneControls(SDL_Event e);
void playerTwoControls(SDL_Event e);
void kingControls1(SDL_Event e);
void update1(int a, int b, int c, int d);
void update2(int a, int b, int c, int d);
void del1(int a, int b);
void undel1(int a, int b);
void del2(int a, int b);
void undel2(int a, int b);
void winner();
void vqueenlogic1(int a, int b, int c, int d);
void vbishoplogic1(int a, int b, int c, int d);
void vknightlogic1(int a, int b, int c, int d);
void vrooklogic1(int a, int b, int c, int d);
void vpawnlogic1(int a, int b, int c, int d);
void vqueenlogic2(int a, int b, int c, int d);
void vbishoplogic2(int a, int b, int c, int d);
void vknightlogic2(int a, int b, int c, int d);
void vrooklogic2(int a, int b, int c, int d);
void vpawnlogic2(int a, int b, int c, int d);
void goback(int a, int b, int c, int d);
int buttonx(int a);
int buttony(int a);
bool logicP1(int a, int b, int c, int d);
bool logicP2(int a, int b, int c, int d);
bool b_pawnlogic(int a, int b, int c, int d);
bool w_pawnlogic(int a, int b, int c, int d);
bool bishoplogic(int a, int b, int c, int d);
bool knightlogic(int a, int b, int c, int d);
bool kinglogic1(int a, int b, int c, int d);
bool kinglogic2(int a, int b, int c, int d);
bool rooklogic(int a, int b, int c, int d);
bool queenlogic(int a, int b, int c, int d);
bool check1(int a, int b);
bool check2(int a, int b);
bool kingCheck1();
bool kingCheck2();
bool checkfor1(int i, int j);
bool checkfor2(int i, int j);
bool checkforking1(int i, int j);
bool checkforking2(int i, int j);



int main(int argc, char *argv[])
{
    for(int i=0; i<8; i++)
    {
        for (int  j=0; j<8; j++)
        {
            block_rect[i][j].x=j*BSIZE;
            block_rect[i][j].y=i*BSIZE;
            block_rect[i][j].h=BSIZE;
            block_rect[i][j].w=BSIZE;
        }
    }

    //SETTING THE SELECTOR POSITION
    window_rect.h=640,
                  window_rect.w=640;

    SDL_Init( SDL_INIT_EVERYTHING );
    IMG_Init( IMG_INIT_PNG );
    window = SDL_CreateWindow("Chess", pos, pos, 900,640, SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    t_fullBoard=SDL_CreateTextureFromSurface(renderer,fullBoard);

    for(int i=0; i<8; i++)
        t_b_pawn=SDL_CreateTextureFromSurface(renderer,b_pawn);

    t_b_rook0=SDL_CreateTextureFromSurface(renderer,b_rook0);
    t_b_bishop0=SDL_CreateTextureFromSurface(renderer,b_bishop0);
    t_b_knight0=SDL_CreateTextureFromSurface(renderer,b_knight0);
    t_b_king0=SDL_CreateTextureFromSurface(renderer,b_king0);
    t_b_queen0=SDL_CreateTextureFromSurface(renderer,b_queen0);
    t_b_rook1=SDL_CreateTextureFromSurface(renderer,b_rook1);
    t_b_bishop1=SDL_CreateTextureFromSurface(renderer,b_bishop1);
    t_b_knight1=SDL_CreateTextureFromSurface(renderer,b_knight1);


    for(int i=0; i<8; i++)
        t_w_pawn=SDL_CreateTextureFromSurface(renderer,w_pawn);

    t_w_rook0=SDL_CreateTextureFromSurface(renderer,w_rook0);
    t_w_bishop0=SDL_CreateTextureFromSurface(renderer,w_bishop0);
    t_w_knight0=SDL_CreateTextureFromSurface(renderer,w_knight0);
    t_w_king0=SDL_CreateTextureFromSurface(renderer,w_king0);
    t_w_queen0=SDL_CreateTextureFromSurface(renderer,w_queen0);
    t_w_rook1=SDL_CreateTextureFromSurface(renderer,w_rook1);
    t_w_bishop1=SDL_CreateTextureFromSurface(renderer,w_bishop1);
    t_w_knight1=SDL_CreateTextureFromSurface(renderer,w_knight1);

    t_selected=SDL_CreateTextureFromSurface(renderer,selected);
    t_allowed=SDL_CreateTextureFromSurface(renderer,allowed);
    t_checked=SDL_CreateTextureFromSurface(renderer,checked);

    //free all the surface
    SDL_FreeSurface(fullBoard);
    fullBoard=NULL;

    SDL_FreeSurface(b_pawn);
    b_pawn=NULL;

    SDL_FreeSurface(b_rook0);
    b_rook0=NULL;
    SDL_FreeSurface(b_bishop0);
    b_bishop0=NULL;
    SDL_FreeSurface(b_knight0);
    b_knight0=NULL;
    SDL_FreeSurface(b_king0);
    b_king0=NULL;
    SDL_FreeSurface(b_queen0);
    b_queen0=NULL;
    SDL_FreeSurface(b_rook1);
    b_rook1=NULL;
    SDL_FreeSurface(b_bishop1);
    b_bishop1=NULL;
    SDL_FreeSurface(b_knight1);
    b_knight1=NULL;


    SDL_FreeSurface(w_pawn);
    w_pawn=NULL;

    SDL_FreeSurface(w_rook0);
    w_rook0=NULL;
    SDL_FreeSurface(w_bishop0);
    w_bishop0=NULL;
    SDL_FreeSurface(w_knight0);
    w_knight0=NULL;
    SDL_FreeSurface(w_king0);
    w_king0=NULL;
    SDL_FreeSurface(w_queen0);
    w_queen0=NULL;
    SDL_FreeSurface(w_rook1);
    w_rook1=NULL;
    SDL_FreeSurface(w_bishop1);
    w_bishop1=NULL;
    SDL_FreeSurface(w_knight1);
    w_knight1=NULL;


    SDL_Event event;
    bool work=true;
    while(work)
    {
        SDL_Delay(16);
        while(SDL_PollEvent(&event))
        {
            SDL_Delay(16);
            if(event.type==SDL_QUIT)
            {
                work=false;
                break;
            }
            draw();

            if(player==1)
                playerOneControls(event);
            else if(player==2)
                playerTwoControls(event);

            draw();
        }
    }

    close();
    IMG_Quit();
    SDL_Quit();
    return 0;
}


void draw()
{

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, t_fullBoard, NULL, &window_rect);

    if(!kill[8])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][0]);
    if(!kill[9])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][1]);
    if(!kill[10])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][2]);
    if(!kill[11])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][3]);
    if(!kill[12])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][4]);
    if(!kill[13])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][5]);
    if(!kill[14])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][6]);
    if(!kill[15])
        SDL_RenderCopy(renderer, t_b_pawn, NULL, &block_rect[1][7]);

    if(!kill[2])
        SDL_RenderCopy(renderer, t_b_bishop0, NULL, &block_rect[0][2]);
    if(!kill[5])
        SDL_RenderCopy(renderer, t_b_bishop1, NULL, &block_rect[0][5]);
    //if(!kill[5])
    SDL_RenderCopy(renderer, t_b_king0, NULL, &block_rect[0][4]);
    if(!kill[1])
        SDL_RenderCopy(renderer, t_b_knight0, NULL, &block_rect[0][1]);
    if(!kill[6])
        SDL_RenderCopy(renderer, t_b_knight1, NULL, &block_rect[0][6]);
    if(!kill[3])
        SDL_RenderCopy(renderer, t_b_queen0, NULL, &block_rect[0][3]);
    if(!kill[0])
        SDL_RenderCopy(renderer, t_b_rook0, NULL, &block_rect[0][0]);
    if(!kill[7])
        SDL_RenderCopy(renderer, t_b_rook1, NULL, &block_rect[0][7]);

    if(!kill[24])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][0]);
    if(!kill[25])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][1]);
    if(!kill[26])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][2]);
    if(!kill[27])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][3]);
    if(!kill[28])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][4]);
    if(!kill[29])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][5]);
    if(!kill[30])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][6]);
    if(!kill[31])
        SDL_RenderCopy(renderer, t_w_pawn, NULL, &block_rect[6][7]);

    if(!kill[18])
        SDL_RenderCopy(renderer, t_w_bishop0, NULL, &block_rect[7][2]);
    if(!kill[21])
        SDL_RenderCopy(renderer, t_w_bishop1, NULL, &block_rect[7][5]);
    //if(!kill[18])
    SDL_RenderCopy(renderer, t_w_king0, NULL, &block_rect[7][4]);
    if(!kill[17])
        SDL_RenderCopy(renderer, t_w_knight0, NULL, &block_rect[7][1]);
    if(!kill[22])
        SDL_RenderCopy(renderer, t_w_knight1, NULL, &block_rect[7][6]);
    if(!kill[19])
        SDL_RenderCopy(renderer, t_w_queen0, NULL, &block_rect[7][3]);
    if(!kill[16])
        SDL_RenderCopy(renderer, t_w_rook0, NULL, &block_rect[7][0]);
    if(!kill[23])
        SDL_RenderCopy(renderer, t_w_rook1, NULL, &block_rect[7][7]);

    if(active=='y')
    {
        selected_rect.x=s;
        selected_rect.y=r;
        selected_rect.h=80;
        selected_rect.w=80;

        SDL_RenderCopy(renderer, t_selected, NULL, &selected_rect);
    }

    if(kingCheck1())
        SDL_RenderCopy(renderer, t_checked, NULL, &block_rect[7][4]);
    if(kingCheck2())
        SDL_RenderCopy(renderer, t_checked, NULL, &block_rect[0][4]);

    for(int i=0; i<640; i=i+80)
    {
        for(int j=0; j<640; j=j+80)
        {
            for(int k=0; k<8; k++)
            {
                if((s==block_rect[6][k].x&&r==block_rect[6][k].y)&&(!check1(i,j)))
                {
                    if(w_pawnlogic(s,r,i,j)&&active=='y')
                    {
                        selected_rect.x=i;
                        selected_rect.y=j;
                        selected_rect.h=80;
                        selected_rect.w=80;

                        SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                    }
                }
            }//for loop terminate (k)

            for(int l=0; l<8; l++)
            {
                if(s==block_rect[1][l].x&&r==block_rect[1][l].y&&(!check2(i,j)))
                {
                    if(b_pawnlogic(s,r,i,j)&&active=='y')
                    {
                        selected_rect.x=i;
                        selected_rect.y=j;
                        selected_rect.h=80;
                        selected_rect.w=80;

                        SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                    }
                }
            }// for loop terminate (l)

            if((((s==block_rect[0][0].x&&r==block_rect[0][0].y)||(s==block_rect[0][7].x&&r==block_rect[0][7].y))&&(!check2(i,j)))||((s==block_rect[7][0].x&&r==block_rect[7][0].y)||(s==block_rect[7][7].x&&r==block_rect[7][7].y))&&(!check1(i,j)))
            {
                if(rooklogic(s,r,i,j)&&active=='y')
                {
                    selected_rect.x=i;
                    selected_rect.y=j;
                    selected_rect.h=80;
                    selected_rect.w=80;

                    SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                }
            }



            else if((((s==block_rect[0][1].x&&r==block_rect[0][1].y)||(s==block_rect[0][6].x&&r==block_rect[0][6].y))&&(!check2(i,j)))||(((s==block_rect[7][1].x&&r==block_rect[7][1].y)||(s==block_rect[7][6].x&&r==block_rect[7][6].y))&&(!check1(i,j))))
            {
                if(knightlogic(s,r,i,j)&&active=='y')
                {
                    selected_rect.x=i;
                    selected_rect.y=j;
                    selected_rect.h=80;
                    selected_rect.w=80;

                    SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                }
            }

            else if((((s==block_rect[0][2].x&&r==block_rect[0][2].y)||(s==block_rect[0][5].x&&r==block_rect[0][5].y))&&(!check2(i,j)))||(((s==block_rect[7][2].x&&r==block_rect[7][2].y)||(s==block_rect[7][5].x&&r==block_rect[7][5].y))&&(!check1(i,j))))
            {
                if(bishoplogic(s,r,i,j)&&active=='y')
                {
                    selected_rect.x=i;
                    selected_rect.y=j;
                    selected_rect.h=80;
                    selected_rect.w=80;

                    SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                }
            }

            else if(((s==block_rect[0][3].x&&r==block_rect[0][3].y)&&(!check2(i,j)))||((s==block_rect[7][3].x&&r==block_rect[7][3].y)&&(!check1(i,j))))
            {
                if(queenlogic(s,r,i,j)&&active=='y')
                {
                    selected_rect.x=i;
                    selected_rect.y=j;
                    selected_rect.h=80;
                    selected_rect.w=80;

                    SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                }
            }

            else if((s==block_rect[7][4].x&&r==block_rect[7][4].y)&&(!check1(i,j)))
            {
                if(kinglogic1(s,r,i,j)&&active=='y'&&(!checkforking1(i,j)))
                {
                    selected_rect.x=i;
                    selected_rect.y=j;
                    selected_rect.h=80;
                    selected_rect.w=80;

                    SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                }
            }

            else if((s==block_rect[0][4].x&&r==block_rect[0][4].y)&&(!check2(i,j)))
            {
                if(kinglogic2(s,r,i,j)&&active=='y'&&(!checkforking2(i,j)))
                {
                    selected_rect.x=i;
                    selected_rect.y=j;
                    selected_rect.h=80;
                    selected_rect.w=80;

                    SDL_RenderCopy(renderer, t_allowed, NULL, &selected_rect);

                }
            }


        }
    }

    SDL_RenderPresent(renderer);

}

void close()
{

    SDL_DestroyTexture(t_w_pawn);

    SDL_DestroyTexture(t_w_bishop0);
    SDL_DestroyTexture(t_w_king0);
    SDL_DestroyTexture(t_w_knight0);
    SDL_DestroyTexture(t_w_queen0);
    SDL_DestroyTexture(t_w_rook0);
    SDL_DestroyTexture(t_w_bishop1);
    SDL_DestroyTexture(t_w_knight1);
    SDL_DestroyTexture(t_w_rook1);

    SDL_DestroyTexture(t_b_pawn);

    SDL_DestroyTexture(t_b_bishop0);
    SDL_DestroyTexture(t_b_knight0);
    SDL_DestroyTexture(t_b_rook0);
    SDL_DestroyTexture(t_b_bishop1);
    SDL_DestroyTexture(t_b_knight1);
    SDL_DestroyTexture(t_b_rook1);
    SDL_DestroyTexture(t_b_king0);
    SDL_DestroyTexture(t_b_queen0);

    SDL_DestroyTexture(t_fullBoard);
    SDL_DestroyTexture(t_selected);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void playerOneControls(SDL_Event e)
{

    if(e.type==SDL_MOUSEBUTTONDOWN)
    {

        /* Pressing Enter */

        if(e.button.button==SDL_BUTTON_LEFT)
        {
            p=buttonx(e.button.x);
            q=buttony(e.button.y);
            if(active=='y')
            {
                if(logicP1(s, r, p, q)&&(!check1(p,q)))
                {
                    update1(s, r, p, q);
                    winner();
                }
                active='n';
            }
            else
            {
                if(check1(p,q))

                {
                    active='y';
                    s=p;
                    r=q;
                }
            }
        }


    }
}

void playerTwoControls(SDL_Event e)
{
    if(e.type==SDL_MOUSEBUTTONDOWN)

    {
        if(e.button.button==SDL_BUTTON_LEFT)
        {
            p=buttonx(e.button.x);
            q=buttony(e.button.y);
            if(active=='y')
            {
                if(logicP2(s, r, p, q)&&(!check2(p,q)))
                {
                    update2(s, r, p, q);
                    winner();
                }
                active='n';
            }
            else
            {
                if(check2(p,q))

                {
                    active='y';
                    s=p;
                    r=q;
                }
            }
        }
    }
}

bool logicP1(int a, int b, int c, int d)
{

    bool state=false;

    for(int i=0; i<8; i++)
    {
        if((block_rect[6][i].x==a&&block_rect[6][i].y==b))
            if(type[i+8]==0)
                state=w_pawnlogic(a,b,c,d);
            else if(type[i+8]==1)
                state=queenlogic(a,b,c,d);
            else if(type[i+8]==2)
                state=knightlogic(a,b,c,d);
            else if(type[i+8]==3)
                state=rooklogic(a,b,c,d);
            else if(type[i+8]==4)
                state=bishoplogic(a,b,c,d);
    }

    if((block_rect[7][2].x==a&&block_rect[7][2].y==b)||(block_rect[7][5].x==a&&block_rect[7][5].y==b))
        state=bishoplogic(a,b,c,d);

    else if((block_rect[7][1].x==a&&block_rect[7][1].y==b)||(block_rect[7][6].x==a&&block_rect[7][6].y==b))
        state=knightlogic(a,b,c,d);

    else if((block_rect[7][3].x==a&&block_rect[7][3].y==b))
        state=queenlogic(a,b,c,d);

    else if((block_rect[7][4].x==a&&block_rect[7][4].y==b))
    {
        state=kinglogic1(a,b,c,d);
        if(state)
            wk=false;
    }

    else if(block_rect[7][0].x==a&&block_rect[7][0].y==b)
    {
        state=rooklogic(a,b,c,d);
        if(state)
        {
            wr2=false;
        }
    }
    else if(block_rect[7][7].x==a&&block_rect[7][7].y==b)
    {
        state=rooklogic(a,b,c,d);
        if(state)
        {
            wr1=false;
        }
    }

    if(c==block_rect[0][4].x&&d==block_rect[0][4].y)
    {
        state=false;
    }

    return state;
}

bool logicP2(int a, int b, int c, int d)
{
    bool state=false;

    for(int i=0; i<8; i++)
    {
        if((block_rect[1][i].x==a&&block_rect[1][i].y==b))
        {
            if(type[i]==0)
                state=b_pawnlogic(a,b,c,d);
            else if(type[i]==1)
                state=queenlogic(a,b,c,d);
            else if(type[i]==2)
                state=knightlogic(a,b,c,d);
            else if(type[i]==3)
                state=rooklogic(a,b,c,d);
            else if(type[i]==4)
                state=bishoplogic(a,b,c,d);
        }
    }

    if((block_rect[0][2].x==a&&block_rect[0][2].y==b)||(block_rect[0][5].x==a&&block_rect[0][5].y==b))
        state=bishoplogic(a,b,c,d);

    else if((block_rect[0][6].x==a&&block_rect[0][6].y==b)||(block_rect[0][1].x==a&&block_rect[0][1].y==b))
        state=knightlogic(a,b,c,d);

    else if((block_rect[0][3].x==a&&block_rect[0][3].y==b))
        state=queenlogic(a,b,c,d);

    else if((block_rect[0][4].x==a&&block_rect[0][4].y==b))
    {
        state=kinglogic2(a,b,c,d);
        if(state)
            bk=false;
    }
    else if((block_rect[0][0].x==a&&block_rect[0][0].y==b))
    {
        state=rooklogic(a,b,c,d);
        if(state)
        {
            br2=false;
        }

    }

    else if((block_rect[0][7].x==a&&block_rect[0][7].y==b))
    {
        state=rooklogic(a,b,c,d);
        if(state)
        {
            br1=false;
        }

    }

    if(c==block_rect[7][4].x&&d==block_rect[7][4].y)
    {
        state=false;
    }

    return state;
}

void update1(int a, int b, int c, int d)
{
    for(int i=6; i<8; i++)
    {
        for(int j=0; j<8; j++)
            if(block_rect[i][j].x==a&&block_rect[i][j].y==b)
            {
                del1(c,d);
                block_rect[i][j].x=c;
                block_rect[i][j].y=d;
                player=2;
                if(kingCheck1())
                {
                    block_rect[i][j].x=a;
                    block_rect[i][j].y=b;
                    undel1(c,d);
                    player=1;
                }
            }
    }
}

void update2(int a, int b, int c, int d)
{
    for(int i=0; i<2; i++)
    {
        for(int j=0; j<8; j++)
            if(block_rect[i][j].x==a&&block_rect[i][j].y==b)
            {
                del2(c,d);
                block_rect[i][j].x=c;
                block_rect[i][j].y=d;
                player=1;
                if(kingCheck2())
                {
                    block_rect[i][j].x=a;
                    block_rect[i][j].y=b;
                    undel2(c,d);
                    player=2;
                }
            }
    }

}


bool b_pawnlogic(int a, int b, int c, int d)
{
    bool go=false;

    if(a-c==0&&d-b==80&&(!check1(c,d)))
    {
        go=true;
    }
    else if(a-c==0&&d-b==160&&(a>=0&&a<=560)&&b==80&&(!check1(c,d)))
    {
        if((!check1(a,(b+80)))&&(!check2(a,(b+80))))
            go=true;
    }

    else if((a-c==80&&d-b==80&&check1(c,d))||(c-a==80&&d-b==80&&check1(c,d)))
        go=true;

    return go;
}

bool w_pawnlogic(int a, int b, int c, int d)
{
    if(c-a==0&&b-d==80&&(!check2(c,d)))
    {
        return true;
    }

    else if(a-c==0&&b-d==160&&(a>=0&&a<=560)&&b==480&&(!check2(c,d)))
    {
        if((!check1(a,(b-80)))&&(!check2(a,(b-80))))
            return true;
    }

    else if((a-c==80&&b-d==80&&check2(c,d))||(c-a==80&&b-d==80&&check2(c,d)))
        return true;

    else
    {
        return false;
    }
}

bool bishoplogic(int a, int b, int c, int d)
{
    int x=-1,i,j;
    bool go=false;

    if(abs(a-c)==abs(b-d))

    {
        if(a>c&&b>d)
        {
            for(i=a-80, j=b-80; i>c; i=i-80, j=j-80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

        if(a<c&&b<d)
        {
            for(i=a+80, j=b+80; i<c; i=i+80, j=j+80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

        if(a<c&&b>d)
        {
            for(i=a+80, j=b-80; i<c; i=i+80, j=j-80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

        if(a>c&&b<d)
        {
            for(i=a-80, j=b+80; i>c; i=i-80, j=j+80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

    }

    return go;
}

bool knightlogic(int a, int b, int c, int d)
{
    if((abs(a-c)==160 && abs(b-d)==80) || (abs(a-c)==80 && abs(b-d)==160))
        return true;
    else
        return false;
}

bool kinglogic1(int a, int b, int c, int d)
{
    bool go=false;

    if((abs(a-c)==80&&abs(b-d)==80)||(abs(a-c)==0&&abs(b-d)==80)||(abs(a-c)==80&&abs(b-d)==0))
        go=true;
//    else if(c-a==160&&abs(b-d)==0&&wr1&&wk&&(!check1(400,560))&&(!check2(400,560)))
//    {
//        if((!check1(480,560))&&(!check2(480,560)))
//        {
//        block_rect[7][7].x=400;
//        block_rect[7][7].y=560;
//        }
//    }
//    else if(wk&&wr2&&(!check2(c,d))&&c==80&&d==560&&(!check1(240,560))&&(!check2(240,560)))
//    {
//        if((!check1(160,560))&&block_rect[7][4].x==c&&block_rect[7][4].y==d)
//        {
//        go=true;
//        block_rect[7][0].x=160;
//        block_rect[7][0].y=560;
//        wr2=false;
//        }
//    }

    return go;
}

bool kinglogic2(int a, int b, int c, int d)
{
    bool go=false;

    if((abs(a-c)==80&&abs(b-d)==80)||(abs(a-c)==0&&abs(b-d)==80)||(abs(a-c)==80&&abs(b-d)==0))
        go=true;
//    else if((bk&&br1)&&(!check1(c,d))&&c==480&&d==0)
//    {
//        if(!check2(400,0))
//        {
//        go=true;
//        block_rect[0][7].x=400;
//        block_rect[0][7].y=0;
//        br1=false;
//        }
//    }
//    else if((bk&&br2)&&(!check1(c,d))&&c==80&&d==0&&(!check1(240,0))&&(!check2(240,0)))
//    {
//        if(!check2(160,0))
//        {
//        go=true;
//        block_rect[0][0].x=160;
//        block_rect[0][0].y=0;
//        br1=false;
//        }
//    }

    return go;
}

bool queenlogic(int a, int b, int c, int d)
{
    int x=-1,i,j;
    bool go=false;

    if(abs(a-c)==abs(b-d))

    {
        if(a>c&&b>d)
        {
            for(i=a-80, j=b-80; i>c; i=i-80, j=j-80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

        if(a<c&&b<d)
        {
            for(i=a+80, j=b+80; i<c; i=i+80, j=j+80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

        if(a<c&&b>d)
        {
            for(i=a+80, j=b-80; i<c; i=i+80, j=j-80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

        if(a>c&&b<d)
        {
            for(i=a-80, j=b+80; i>c; i=i-80, j=j+80)
            {
                if(check1(i,j)||check2(i,j))
                {
                    x=0;
                    break;
                }
            }

            if(x<0)
                go=true;

        }

    }

    else if(a-c==0)
    {
        if(b>d)
        {
            for(int i=d+80; i<b; i=i+80)
            {
                if(check1(a,i)||check2(a,i))
                    x=1;
            }
            if(x<0)
                go=true;
        }
        else
        {
            for(int i=b+80; i<d; i=i+80)
            {
                if(check1(a,i)||check2(a,i))
                    x=1;
            }
            if(x<0)
                go=true;
        }

    }
    else if(b-d==0)
    {
        if(a>c)
        {
            for(int i=c+80; i<a; i=i+80)
            {
                if(check1(i,b)||check2(i,b))
                    x=1;
            }
            if(x<0)
                go=true;
        }
        else
        {
            for(int i=a+80; i<c; i=i+80)
            {
                if(check1(i,b)||check2(i,b))
                    x=1;
            }
            if(x<0)
                go=true;
        }
    }

    return go;
}

bool rooklogic(int a, int b, int c, int d)
{
    bool go=false;
    int x=-1;

    if(a-c==0)
    {
        if(b>d)
        {
            for(int i=d+80; i<b; i=i+80)
            {
                if(check1(a,i)||check2(a,i))
                    x=1;
            }
            if(x<0)
                go=true;
        }
        else
        {
            for(int i=b+80; i<d; i=i+80)
            {
                if(check1(a,i)||check2(a,i))
                    x=1;
            }
            if(x<0)
                go=true;
        }

    }
    else if(b-d==0)
    {
        if(a>c)
        {
            for(int i=c+80; i<a; i=i+80)
            {
                if(check1(i,b)||check2(i,b))
                    x=1;
            }
            if(x<0)
                go=true;
        }
        else
        {
            for(int i=a+80; i<c; i=i+80)
            {
                if(check1(i,b)||check2(i,b))
                    x=1;
            }
            if(x<0)
                go=true;
        }
    }
    else
        go= false;

    return go;
}

bool check1(int a, int b)
{
    bool go=false;

    for(int i=6; i<8; i++)
    {
        for(int j=0; j<8; j++)
            if(block_rect[i][j].x==a&&block_rect[i][j].y==b)
            {
                go=true;
            }
    }
    return go;
}

bool check2(int a, int b)
{
    bool    go=false;

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<8; j++)
            if(block_rect[i][j].x==a&&block_rect[i][j].y==b)
            {
                go=true;
            }
    }

    return go;
}

void del1(int a, int b)
{
    if(a==block_rect[0][0].x&&b==block_rect[0][0].y)
    {
        kill[0]=1;
        block_rect[0][0].x+=645;
        block_rect[0][0].y+=643;
    }
    if(a==block_rect[0][1].x&&b==block_rect[0][1].y)
    {
        kill[1]=1;
        block_rect[0][1].x+=645;
        block_rect[0][1].y+=643;
    }
    if(a==block_rect[0][2].x&&b==block_rect[0][2].y)
    {
        kill[2]=1;
        block_rect[0][2].x+=645;
        block_rect[0][2].y+=643;
    }
    if(a==block_rect[0][3].x&&b==block_rect[0][3].y)
    {
        kill[3]=1;
        block_rect[0][3].x+=645;
        block_rect[0][3].y+=643;
    }
    if(a==block_rect[0][7].x&&b==block_rect[0][7].y)
    {
        kill[7]=1;
        block_rect[0][7].x+=645;
        block_rect[0][7].y+=643;
    }
    if(a==block_rect[0][6].x&&b==block_rect[0][6].y)
    {
        kill[6]=1;
        block_rect[0][6].x+=645;
        block_rect[0][6].y+=643;
    }
    if(a==block_rect[0][5].x&&b==block_rect[0][5].y)
    {
        kill[5]=1;
        block_rect[0][5].x+=645;
        block_rect[0][5].y+=643;
    }

    if(a==block_rect[1][0].x&&b==block_rect[1][0].y)
    {
        kill[8]=1;
        block_rect[1][0].x+=645;
        block_rect[1][0].y+=643;
    }
    if(a==block_rect[1][1].x&&b==block_rect[1][1].y)
    {
        kill[9]=1;
        block_rect[1][1].x+=645;
        block_rect[1][1].y+=643;
    }
    if(a==block_rect[1][2].x&&b==block_rect[1][2].y)
    {
        kill[10]=1;
        block_rect[1][2].x+=645;
        block_rect[1][2].y+=643;
    }
    if(a==block_rect[1][3].x&&b==block_rect[1][3].y)
    {
        kill[11]=1;
        block_rect[1][3].x+=645;
        block_rect[1][3].y+=643;
    }
    if(a==block_rect[1][4].x&&b==block_rect[1][4].y)
    {
        kill[12]=1;
        block_rect[1][4].x+=645;
        block_rect[1][4].y+=643;
    }
    if(a==block_rect[1][5].x&&b==block_rect[1][5].y)
    {
        kill[13]=1;
        block_rect[1][5].x+=645;
        block_rect[1][5].y+=643;
    }
    if(a==block_rect[1][6].x&&b==block_rect[1][6].y)
    {
        kill[14]=1;
        block_rect[1][6].x+=645;
        block_rect[1][6].y+=643;
    }
    if(a==block_rect[1][7].x&&b==block_rect[1][7].y)
    {
        kill[15]=1;
        block_rect[1][7].x+=645;
        block_rect[1][7].y+=643;
    }
}

void undel1(int a, int b)
{
    if(a+645==block_rect[0][0].x&&b+643==block_rect[0][0].y)
    {
        kill[0]=0;
        block_rect[0][0].x=a;
        block_rect[0][0].y=b;
    }

    if(a+645==block_rect[0][1].x&&b+643==block_rect[0][1].y)
    {
        kill[1]=0;
        block_rect[0][1].x=a;
        block_rect[0][1].y=b;
    }

    if(a+645==block_rect[0][2].x&&b+643==block_rect[0][2].y)
    {
        kill[2]=0;
        block_rect[0][2].x=a;
        block_rect[0][2].y=b;
    }
    if(a+645==block_rect[0][3].x&&b+643==block_rect[0][3].y)
    {
        kill[3]=0;
        block_rect[0][3].x=a;
        block_rect[0][3].y=b;
    }

    if(a+645==block_rect[0][5].x&&b+643==block_rect[0][5].y)
    {
        kill[5]=0;
        block_rect[0][5].x=a;
        block_rect[0][5].y=b;
    }

    if(a+645==block_rect[0][6].x&&b+643==block_rect[0][6].y)
    {
        kill[6]=0;
        block_rect[0][6].x=a;
        block_rect[0][6].y=b;
    }

    if(a+645==block_rect[0][7].x&&b+643==block_rect[0][7].y)
    {
        kill[7]=0;
        block_rect[0][7].x=a;
        block_rect[0][7].y=b;
    }

    if(a+640==block_rect[1][0].x&&b+643==block_rect[1][0].y)
    {
        kill[8]=0;
        block_rect[1][0].x=a;
        block_rect[1][0].y=b;
    }

    if(a+645==block_rect[1][1].x&&b+643==block_rect[1][1].y)
    {
        kill[9]=0;
        block_rect[1][1].x=a;
        block_rect[1][1].y=b;
    }

    if(a+645==block_rect[1][2].x&&b+643==block_rect[1][2].y)
    {
        kill[10]=0;
        block_rect[1][2].x=a;
        block_rect[1][2].y=b;
    }

    if(a+645==block_rect[1][3].x&&b+643==block_rect[1][3].y)
    {
        kill[11]=0;
        block_rect[1][3].x=a;
        block_rect[1][3].y=b;
    }

    if(a+645==block_rect[1][4].x&&b+643==block_rect[1][4].y)
    {
        kill[12]=0;
        block_rect[1][4].x=a;
        block_rect[1][4].y=b;
    }

    if(a+640==block_rect[1][5].x&&b+643==block_rect[1][5].y)
    {
        kill[13]=0;
        block_rect[1][5].x=a;
        block_rect[1][5].y=b;
    }

    if(a+645==block_rect[1][6].x&&b+643==block_rect[1][6].y)
    {
        kill[14]=0;
        block_rect[1][6].x=a;
        block_rect[1][6].y=b;
    }

    if(a+645==block_rect[1][7].x&&b+643==block_rect[1][7].y)
    {
        kill[15]=0;
        block_rect[1][7].x=a;
        block_rect[1][7].y=b;
    }
}

void del2(int a,int b)
{
    if(a==block_rect[7][0].x&&b==block_rect[7][0].y)
    {
        kill[16]=1;
        block_rect[7][0].x+=645;
        block_rect[7][0].y+=643;
    }
    if(a==block_rect[7][1].x&&b==block_rect[7][1].y)
    {
        kill[17]=1;
        block_rect[7][1].x+=645;
        block_rect[7][1].y+=643;
    }
    if(a==block_rect[7][2].x&&b==block_rect[7][2].y)
    {
        kill[18]=1;
        block_rect[7][2].x+=645;
        block_rect[7][2].y+=643;
    }
    if(a==block_rect[7][3].x&&b==block_rect[7][3].y)
    {
        kill[19]=1;
        block_rect[7][3].x+=645;
        block_rect[7][3].y+=643;
    }
    if(a==block_rect[7][5].x&&b==block_rect[7][5].y)
    {
        kill[21]=1;
        block_rect[7][5].x+=645;
        block_rect[7][5].y+=643;
    }
    if(a==block_rect[7][6].x&&b==block_rect[7][6].y)
    {
        kill[22]=1;
        block_rect[7][6].x+=645;
        block_rect[7][6].y+=643;
    }
    if(a==block_rect[7][7].x&&b==block_rect[7][7].y)
    {
        kill[23]=1;
        block_rect[7][7].x+=645;
        block_rect[7][7].y+=643;
    }

    if(a==block_rect[6][0].x&&b==block_rect[6][0].y)
    {
        kill[24]=1;
        block_rect[6][0].x+=645;
        block_rect[6][0].y+=643;
    }
    if(a==block_rect[6][1].x&&b==block_rect[6][1].y)
    {
        kill[25]=1;
        block_rect[6][1].x+=645;
        block_rect[6][1].y+=643;
    }
    if(a==block_rect[6][2].x&&b==block_rect[6][2].y)
    {
        kill[26]=1;
        block_rect[6][2].x+=645;
        block_rect[6][2].y+=643;
    }
    if(a==block_rect[6][3].x&&b==block_rect[6][3].y)
    {
        kill[27]=1;
        block_rect[6][3].x+=645;
        block_rect[6][3].y+=643;
    }

    if(a==block_rect[6][4].x&&b==block_rect[6][4].y)
    {
        kill[28]=1;
        block_rect[6][4].x+=645;
        block_rect[6][4].y+=643;
    }

    if(a==block_rect[6][5].x&&b==block_rect[6][5].y)
    {
        kill[29]=1;
        block_rect[6][5].x+=645;
        block_rect[6][5].y+=643;
    }
    if(a==block_rect[6][6].x&&b==block_rect[6][6].y)
    {
        kill[30]=1;
        block_rect[6][6].x+=645;
        block_rect[6][6].y+=643;
    }
    if(a==block_rect[6][7].x&&b==block_rect[6][7].y)
    {
        kill[31]=1;
        block_rect[6][7].x+=645;
        block_rect[6][7].y+=643;
    }
}

void undel2(int a, int b)
{
    if(a+645==block_rect[7][0].x&&b+643==block_rect[7][0].y)
    {
        kill[16]=0;
        block_rect[7][0].x=a;
        block_rect[7][0].y=b;
    }

    if(a+645==block_rect[7][1].x&&b+643==block_rect[7][1].y)
    {
        kill[17]=0;
        block_rect[7][1].x=a;
        block_rect[7][1].y=b;
    }

    if(a+645==block_rect[7][2].x&&b+643==block_rect[7][2].y)
    {
        kill[18]=0;
        block_rect[7][2].x=a;
        block_rect[7][2].y=b;
    }
    if(a+645==block_rect[7][3].x&&b+643==block_rect[7][3].y)
    {
        kill[19]=0;
        block_rect[7][3].x=a;
        block_rect[7][3].y=b;
    }

    if(a+645==block_rect[7][5].x&&b+643==block_rect[7][5].y)
    {
        kill[21]=0;
        block_rect[7][5].x=a;
        block_rect[7][5].y=b;
    }

    if(a+645==block_rect[7][6].x&&b+643==block_rect[7][6].y)
    {
        kill[22]=0;
        block_rect[7][6].x=a;
        block_rect[7][6].y=b;
    }

    if(a+645==block_rect[7][7].x&&b+643==block_rect[7][7].y)
    {
        kill[23]=0;
        block_rect[7][7].x=a;
        block_rect[7][7].y=b;
    }

    if(a+645==block_rect[6][0].x&&b+643==block_rect[6][0].y)
    {
        kill[24]=0;
        block_rect[6][0].x=a;
        block_rect[6][0].y=b;
    }

    if(a+645==block_rect[6][1].x&&b+645==block_rect[6][1].y)
    {
        kill[25]=0;
        block_rect[6][1].x=a;
        block_rect[6][1].y=b;
    }

    if(a+645==block_rect[6][2].x&&b+643==block_rect[6][2].y)
    {
        kill[26]=0;
        block_rect[6][2].x=a;
        block_rect[6][2].y=b;
    }

    if(a+645==block_rect[6][3].x&&b+643==block_rect[6][3].y)
    {
        kill[27]=0;
        block_rect[6][3].x=a;
        block_rect[6][3].y=b;
    }

    if(a+645==block_rect[6][4].x&&b+643==block_rect[6][4].y)
    {
        kill[28]=0;
        block_rect[6][4].x=a;
        block_rect[6][4].y=b;
    }

    if(a+645==block_rect[6][5].x&&b+643==block_rect[6][5].y)
    {
        kill[29]=0;
        block_rect[6][5].x=a;
        block_rect[6][5].y=b;
    }

    if(a+645==block_rect[6][6].x&&b+643==block_rect[6][6].y)
    {
        kill[30]=0;
        block_rect[6][6].x=a;
        block_rect[6][6].y=b;
    }

    if(a+645==block_rect[6][7].x&&b+643==block_rect[6][7].y)
    {
        kill[31]=0;
        block_rect[6][7].x=a;
        block_rect[6][7].y=b;
    }
}
int buttonx(int a)
{
    int x;

    if(a>0&&a<79)
        x=0;
    else if(a>80&&a<160)
        x=80;
    else if(a>160&&a<240)
        x=160;
    else if(a>240&&a<320)
        x=240;
    else if(a>320&&a<400)
        x=320;
    else if(a>400&&a<480)
        x=400;
    else if(a>480&&a<560)
        x=480;
    else if(a>560&&a<640)
        x=560;
    return x;
}

int buttony(int a)
{
    int x;

    if(a>0&&a<79)
        x=0;
    else if(a>80&&a<160)
        x=80;
    else if(a>160&&a<240)
        x=160;
    else if(a>240&&a<320)
        x=240;
    else if(a>320&&a<400)
        x=320;
    else if(a>400&&a<480)
        x=400;
    else if(a>480&&a<560)
        x=480;
    else if(a>560&&a<640)
        x=560;
    return x;
}

bool kingCheck1()
{
    bool status=false;

    if(rooklogic(block_rect[0][0].x, block_rect[0][0].y, block_rect[7][4].x, block_rect[7][4].y)||rooklogic(block_rect[0][7].x, block_rect[0][7].y, block_rect[7][4].x, block_rect[7][4].y))
        status=true;
    else if(knightlogic(block_rect[0][1].x, block_rect[0][1].y, block_rect[7][4].x, block_rect[7][4].y)||knightlogic(block_rect[0][6].x, block_rect[0][6].y, block_rect[7][4].x, block_rect[7][4].y))
        status=true;
    else if(kinglogic2(block_rect[0][4].x, block_rect[0][4].y, block_rect[7][4].x, block_rect[7][4].y))
        status=true;
    else if(queenlogic(block_rect[0][3].x, block_rect[0][3].y, block_rect[7][4].x, block_rect[7][4].y))
        status=true;
    else if(bishoplogic(block_rect[0][2].x, block_rect[0][2].y, block_rect[7][4].x, block_rect[7][4].y)||bishoplogic(block_rect[0][5].x, block_rect[0][5].y, block_rect[7][4].x, block_rect[7][4].y))
        status=true;
    else
        for(int i=0; i<8; i++)
        {
            if(b_pawnlogic(block_rect[1][i].x, block_rect[1][i].y, block_rect[7][4].x, block_rect[7][4].y))
                status=true;
        }
    return status;
}

bool kingCheck2()
{
    bool status=false;

    if(rooklogic(block_rect[7][0].x, block_rect[7][0].y, block_rect[0][4].x, block_rect[0][4].y)||rooklogic(block_rect[7][7].x, block_rect[7][7].y, block_rect[0][4].x, block_rect[0][4].y))
        status=true;
    else if(knightlogic(block_rect[7][1].x, block_rect[7][1].y, block_rect[0][4].x, block_rect[0][4].y)||knightlogic(block_rect[7][6].x, block_rect[7][6].y, block_rect[0][4].x, block_rect[0][4].y))
        status=true;
    else if(kinglogic1(block_rect[7][4].x, block_rect[7][4].y, block_rect[0][4].x, block_rect[0][4].y))
        status=true;
    else if(queenlogic(block_rect[7][3].x, block_rect[7][3].y, block_rect[0][4].x, block_rect[0][4].y))
        status=true;
    else if(bishoplogic(block_rect[7][2].x, block_rect[7][2].y, block_rect[0][4].x, block_rect[0][4].y)||bishoplogic(block_rect[7][5].x, block_rect[7][5].y, block_rect[0][4].x, block_rect[0][4].y))
        status=true;
    else
        for(int i=0; i<8; i++)
        {
            if(w_pawnlogic(block_rect[6][i].x, block_rect[6][i].y, block_rect[0][4].x, block_rect[0][4].y))
                status=true;
        }
    return status;
}

void winner()
{
    valid2=0;
    drawvalid2=0;
    valid1=0;
    drawvalid1=0;

    for(int i=0; i<640; i=i+80)
    {
        for(int j=0; j<640; j=j+80)
        {
//                for(int k=0; k<8; k++)
//              {
//                if(w_pawnlogic(block_rect[6][k].x,block_rect[6][k].y,i,j))
//                    drawvalid1++;
//              }
//
//              for(int l=0; l<8; l++)
//              {
//                if(b_pawnlogic(block_rect[1][l].x,block_rect[1][l].y,i,j))
//                    drawvalid2++;
//              }
//
//                if(rooklogic(block_rect[0][0].x,block_rect[0][0].y,i,j))
//                    drawvalid2++;
//                if(rooklogic(block_rect[0][7].x,block_rect[0][7].y,i,j))
//                    drawvalid2++;
//                if(rooklogic(block_rect[7][0].x,block_rect[7][0].y,i,j))
//                    drawvalid1++;
//                if(rooklogic(block_rect[7][7].x,block_rect[7][7].y,i,j))
//                    drawvalid1++;
//                if(knightlogic(block_rect[0][1].x,block_rect[0][1].y,i,j))
//                    drawvalid2++;
//                if(knightlogic(block_rect[0][6].x,block_rect[0][6].y,i,j))
//                    drawvalid2++;
//                if(knightlogic(block_rect[7][1].x,block_rect[7][1].y,i,j))
//                    drawvalid1++;
//                if(knightlogic(block_rect[7][6].x,block_rect[7][6].y,i,j))
//                    drawvalid1++;
//                if(bishoplogic(block_rect[0][2].x,block_rect[0][2].y,i,j))
//                    drawvalid2++;
//                if(bishoplogic(block_rect[0][5].x,block_rect[0][5].y,i,j))
//                    drawvalid2++;
//                if(bishoplogic(block_rect[7][2].x,block_rect[7][2].y,i,j))
//                    drawvalid1++;
//                if(bishoplogic(block_rect[7][5].x,block_rect[7][5].y,i,j))
//                    drawvalid1++;
//                if(queenlogic(block_rect[0][3].x,block_rect[0][3].y,i,j))
//                    drawvalid2++;
//                if(queenlogic(block_rect[7][4].x,block_rect[7][4].y,i,j))
//                    drawvalid1++;


            if(kinglogic1(block_rect[7][4].x,block_rect[7][4].y,i,j)&&(!check1(i,j))&&(!checkforking1(i,j)))
                valid1++;
            if(kinglogic2(block_rect[0][4].x,block_rect[0][4].y,i,j)&&(!check2(i,j))&&(!checkforking2(i,j)))
                valid2++;
        }
    }


    if(queenlogic(block_rect[0][3].x, block_rect[0][3].y, block_rect[7][4].x, block_rect[7][4].y))
        vqueenlogic1(block_rect[0][3].x, block_rect[0][3].y, block_rect[7][4].x, block_rect[7][4].y);
    if(bishoplogic(block_rect[0][2].x, block_rect[0][2].y, block_rect[7][4].x, block_rect[7][4].y))
        vbishoplogic1(block_rect[0][2].x, block_rect[0][2].y, block_rect[7][4].x, block_rect[7][4].y);
    if(bishoplogic(block_rect[0][5].x, block_rect[0][5].y, block_rect[7][4].x, block_rect[7][4].y))
        vbishoplogic1(block_rect[0][5].x, block_rect[0][5].y, block_rect[7][4].x, block_rect[7][4].y);
    if(knightlogic(block_rect[0][1].x, block_rect[0][1].y, block_rect[7][4].x, block_rect[7][4].y))
        vknightlogic1(block_rect[0][1].x, block_rect[0][1].y, block_rect[7][4].x, block_rect[7][4].y);
    if(knightlogic(block_rect[0][6].x, block_rect[0][6].y, block_rect[7][4].x, block_rect[7][4].y))
        vknightlogic1(block_rect[0][6].x, block_rect[0][6].y, block_rect[7][4].x, block_rect[7][4].y);
    if(rooklogic(block_rect[0][0].x, block_rect[0][0].y, block_rect[7][4].x, block_rect[7][4].y))
        vrooklogic1(block_rect[0][0].x, block_rect[0][0].y, block_rect[7][4].x, block_rect[7][4].y);
    if(rooklogic(block_rect[0][7].x, block_rect[0][7].y, block_rect[7][4].x, block_rect[7][4].y))
        vrooklogic1(block_rect[0][7].x, block_rect[0][7].y, block_rect[7][4].x, block_rect[7][4].y);
    for(int k=0; k<8; k++)
        if(b_pawnlogic(block_rect[0][k].x,block_rect[0][k].y,block_rect[7][4].x, block_rect[0][4].y))
            vpawnlogic2(block_rect[0][k].x,block_rect[0][k].y,block_rect[7][4].x, block_rect[0][4].y);


    if(queenlogic(block_rect[7][3].x, block_rect[7][3].y, block_rect[0][4].x, block_rect[0][4].y))
        vqueenlogic2(block_rect[7][3].x, block_rect[7][3].y, block_rect[0][4].x, block_rect[0][4].y);
    if(bishoplogic(block_rect[7][2].x, block_rect[7][2].y, block_rect[0][4].x, block_rect[0][4].y))
        vbishoplogic2(block_rect[7][2].x, block_rect[7][2].y, block_rect[0][4].x, block_rect[0][4].y);
    if(bishoplogic(block_rect[7][5].x, block_rect[7][5].y, block_rect[0][4].x, block_rect[0][4].y))
        vbishoplogic2(block_rect[7][5].x, block_rect[7][5].y, block_rect[0][4].x, block_rect[0][4].y);
    if(knightlogic(block_rect[7][1].x, block_rect[7][1].y, block_rect[0][4].x, block_rect[0][4].y))
        vknightlogic2(block_rect[7][1].x, block_rect[7][1].y, block_rect[0][4].x, block_rect[0][4].y);
    if(knightlogic(block_rect[7][6].x, block_rect[7][6].y, block_rect[0][4].x, block_rect[0][4].y))
        vknightlogic2(block_rect[7][6].x, block_rect[7][6].y, block_rect[0][4].x, block_rect[0][4].y);
    if(rooklogic(block_rect[7][0].x, block_rect[7][0].y, block_rect[0][4].x, block_rect[0][4].y))
        vrooklogic2(block_rect[7][0].x, block_rect[7][0].y, block_rect[0][4].x, block_rect[0][4].y);
    if(rooklogic(block_rect[7][7].x, block_rect[7][7].y, block_rect[0][4].x, block_rect[0][4].y))
        vrooklogic2(block_rect[7][7].x, block_rect[7][7].y, block_rect[0][4].x, block_rect[0][4].y);
    for(int k=0; k<8; k++)
                if(w_pawnlogic(block_rect[7][k].x,block_rect[7][k].y,block_rect[0][4].x, block_rect[0][4].y))
                    vpawnlogic2(block_rect[7][k].x,block_rect[7][k].y,block_rect[0][4].x, block_rect[0][4].y);

    cout<<drawvalid1<<" "<<drawvalid2<<endl;


    if(kingCheck1())
        cout<<"checked by black"<<endl;
    if(kingCheck2())
        cout<<"checked by white"<<endl;
        if((!(valid1))&&kingCheck1())
           cout<<"player one looses"<<endl;
        if((!(valid2))&&kingCheck2())
           cout<<"player two looses"<<endl;
}

bool checkforking1(int i,int j)
{
    bool status=false;

    if(rooklogic(block_rect[0][0].x, block_rect[0][0].y,i,j)||rooklogic(block_rect[0][7].x, block_rect[0][7].y,i,j))
        status=true;
    else if(knightlogic(block_rect[0][1].x, block_rect[0][1].y,i,j)||knightlogic(block_rect[0][6].x, block_rect[0][6].y,i,j))
        status=true;
//    else if(kinglogic2(block_rect[0][4].x, block_rect[0][4].y,i,j))
//        status=true;
    else if(queenlogic(block_rect[0][3].x, block_rect[0][3].y,i,j))
        status=true;
    else if(bishoplogic(block_rect[0][2].x, block_rect[0][2].y,i,j)||bishoplogic(block_rect[0][5].x, block_rect[0][5].y,i,j))
        status=true;
    else
        for(int m=0; m<8; m++)
        {
            if(block_rect[1][m].x-i==0&&j-block_rect[1][m].y==80&&(!check1(i,j)))
            {
            status=true;
            }
            else if(block_rect[1][m].x-i==0&&j-block_rect[1][m].y==160&&(block_rect[1][m].x>=0&&block_rect[1][m].x<=560)&&block_rect[1][m].y==80&&(!check1(i,j)))
            {
            if((!check1(block_rect[1][m].x,(block_rect[1][m].y+80)))&&(!check2(block_rect[1][m].x,(block_rect[1][m].y+80))))
            status=true;
            }

            else if((block_rect[1][m].x-i==80&&j-block_rect[1][m].y==80)||(i-block_rect[1][m].x==80&&j-block_rect[1][m].y==80))
            status=true;
        }

    return status;
}

bool checkforking2(int i,int j)
{
    bool status=false;

    if(rooklogic(block_rect[7][0].x, block_rect[7][0].y,i,j)||rooklogic(block_rect[7][7].x, block_rect[7][7].y,i,j))
        status=true;
    else if(knightlogic(block_rect[7][1].x, block_rect[7][1].y,i,j)||knightlogic(block_rect[7][6].x, block_rect[7][6].y,i,j))
       status=true;
//    else if(kinglogic1(block_rect[7][4].x, block_rect[7][4].y,i,j))
//        status=true;
    else if(queenlogic(block_rect[7][3].x, block_rect[7][3].y,i,j))
        status=true;
    else if(bishoplogic(block_rect[7][2].x, block_rect[7][2].y,i,j)||bishoplogic(block_rect[7][5].x, block_rect[7][5].y,i,j))
        status=true;
//    else
//    {
    for(int m=0; m<8; m++)
    {
        if(i-block_rect[6][m].x==0&&block_rect[6][m].y-j==80&&(!check2(i,j)))
            status=true;

    else if(block_rect[6][m].x-i==0&&block_rect[6][m].y-j==160&&(block_rect[6][m].x>=0&&block_rect[6][m].x<=560)&&block_rect[6][m].y==480&&(!check2(i,j)))
    {
        if((!check1(block_rect[6][m].x,(block_rect[6][m].y-80)))&&(!check2(block_rect[6][m].x,(block_rect[6][m].y-80))))
            status=true;
    }

        else if((block_rect[6][m].x-i==80&&block_rect[6][m].y-j==80)||(i-block_rect[6][m].x==80&&block_rect[6][m].y-j==80))
            status=true;
    }

    return status;
}

void vqueenlogic1(int a, int b, int c, int d)
{
    int w,v,i,j;
    bool go=false;

    if(abs(a-c)==abs(b-d))

    {
        if(a>c&&b>d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j-80)
            {
                if(checkfor2(i,j))
                    {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }

        if(a<c&&b<d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j+80)
            {
                if(checkfor2(i,j))
                 {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }

            }
        }

        if(a<c&&b>d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j-80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }

        }

        if(a>c&&b<d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j+80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
    }

    else if(a-c==0)
    {
        if(b>d)
        {
            for(int i=d+80; i<b; i=i+80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=b+80; i<d; i=i+80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }

    }
    else if(b-d==0)
    {
        if(a>c)
        {
            for(int i=c+80; i<a; i=i+80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=a+80; i<c; i=i+80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
    }
}

void vbishoplogic1(int a, int b, int c, int d)
{
    int i,j;

    if(abs(a-c)==abs(b-d))

    {
        if(a>c&&b>d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j-80)
            {
                if(checkfor2(i,j))
                   {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }

        if(a<c&&b<d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j+80)
            {
                if(checkfor2(i,j))
                   {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }

        if(a<c&&b>d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j-80)
            {
                if(checkfor2(i,j))
                 {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }

        }

        if(a>c&&b<d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j+80)
            {
                if(checkfor2(i,j))
                {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
    }
}

void vrooklogic1(int a, int b, int c, int d)
{
    int i,j;

    if(a-c==0)
    {
        if(b>d)
        {
            for(int i=d+80; i<b; i=i+80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                           del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=b+80; i<d; i=i+80)
            {
                if(checkfor2(i,j))
                 {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }

    }
    else if(b-d==0)
    {
        if(a>c)
        {
            for(int i=c+80; i<a; i=i+80)
            {
                if(checkfor2(i,j))
                  {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=a+80; i<c; i=i+80)
            {
                if(checkfor2(i,j))
                 {
                        valid1++;
                        if(check2(i,j))
                        {
                            del1(i,j);
                            goback(a,b,i,j);
                            if(kingCheck1())
                                valid1--;
                            goback(i,j,a,b);
                            undel1(i,j);
                        }
                    }
            }
        }
    }
}

void vknightlogic1(int a, int b, int c, int d)
{
    if((abs(a-c)==160 && abs(b-d)==80) || (abs(a-c)==80 && abs(b-d)==160))
        {
            if(checkfor2(c,d))
            {
                        valid1++;
                        if(check2(c,d))
                        {
                            del1(c,d);
                            goback(a,b,c,d);
                            if(kingCheck1())
                                valid1--;
                            goback(c,d,a,b);
                            undel1(c,d);
                        }
                    }
}
}

void vqueenlogic2(int a, int b, int c, int d)
{
    int i,j;
    bool go=false;

    if(abs(a-c)==abs(b-d))

    {
        if(a>c&&b>d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j-80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }

        if(a<c&&b<d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }

        if(a<c&&b>d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j-80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }

        }

        if(a>c&&b<d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j+80)
            {
                if(checkfor1(i,j))
                {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
    }

    else if(a-c==0)
    {
        if(b>d)
        {
            for(int i=d+80; i<b; i=i+80)
            {
                if(checkfor1(i,j))
                 {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=b+80; i<d; i=i+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }

    }
    else if(b-d==0)
    {
        if(a>c)
        {
            for(int i=c+80; i<a; i=i+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=a+80; i<c; i=i+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
    }
}

void vbishoplogic2(int a, int b, int c, int d)
{
    int i,j;

    if(abs(a-c)==abs(b-d))

    {
        if(a>c&&b>d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j-80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }

        if(a<c&&b<d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }

        if(a<c&&b>d)
        {
            for(i=a, j=b; i<c; i=i+80, j=j-80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }

        }

        if(a>c&&b<d)
        {
            for(i=a, j=b; i>c; i=i-80, j=j+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
    }
}

void vrooklogic2(int a, int b, int c, int d)
{
    int i,j;

    if(a-c==0)
    {
        if(b>d)
        {
            for(int i=d+80; i<b; i=i+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=b+80; i<d; i=i+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }

    }
    else if(b-d==0)
    {
        if(a>c)
        {
            for(int i=c+80; i<a; i=i+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                            del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
        else
        {
            for(int i=a+80; i<c; i=i+80)
            {
                if(checkfor1(i,j))
                  {
                        valid2++;
                        if(check1(i,j))
                        {
                           del2(i,j);
                            goback(a,b,i,j);
                            if(kingCheck2())
                                valid2--;
                            goback(i,j,a,b);
                            undel2(i,j);
                        }
                    }
            }
        }
    }
}

void vknightlogic2(int a, int b, int c, int d)
{
    if((abs(a-c)==160 && abs(b-d)==80) || (abs(a-c)==80 && abs(b-d)==160))
        {
            if(checkfor1(c,d))
                  {
                        valid2++;
                        if(check1(c,d))
                        {
                            del2(c,d);
                            goback(a,b,c,d);
                            if(kingCheck2())
                                valid2--;
                            goback(c,d,a,b);
                            undel2(c,d);
                        }
                    }
        }
}

void vpawnlogic2(int a, int b, int c, int d)
{
     if(checkfor1(c,d))
                  {
                        valid2++;
                        if(check1(c,d))
                        {
                            del2(c,d);
                            goback(a,b,c,d);
                            if(kingCheck2())
                                valid2--;
                            goback(c,d,a,b);
                            undel2(c,d);
                        }
                    }

}

void vpawnlogic1(int a, int b, int c, int d)
{
     if(checkfor2(c,d))
                  {
                        valid1++;
                        if(check2(c,d))
                        {
                            del1(c,d);
                            goback(a,b,c,d);
                            if(kingCheck1())
                                valid1--;
                            goback(c,d,a,b);
                            undel1(c,d);
                        }
                    }
}


bool checkfor1(int i, int j)
    {
    bool status=false;

    if(rooklogic(block_rect[0][0].x, block_rect[0][0].y,i,j)||rooklogic(block_rect[0][7].x, block_rect[0][7].y,i,j))
        status=true;
    else if(knightlogic(block_rect[0][1].x, block_rect[0][1].y,i,j)||knightlogic(block_rect[0][6].x, block_rect[0][6].y,i,j))
        status=true;
    else if(queenlogic(block_rect[0][3].x, block_rect[0][3].y,i,j))
        status=true;
    else if(bishoplogic(block_rect[0][2].x, block_rect[0][2].y,i,j)||bishoplogic(block_rect[0][5].x, block_rect[0][5].y,i,j))
        status=true;
    else
        for(int m=0; m<8; m++)
        {
            if(b_pawnlogic(block_rect[1][m].x, block_rect[1][m].y,i,j)&&(!check1(i,j)))
                status=true;
        }

    return status;
}

bool checkfor2(int i, int j)
{
    bool status=false;

    if(rooklogic(block_rect[7][0].x, block_rect[7][0].y,i,j)||rooklogic(block_rect[7][7].x, block_rect[7][7].y,i,j))
        status=true;
    else if(knightlogic(block_rect[7][1].x, block_rect[7][1].y,i,j)||knightlogic(block_rect[7][6].x, block_rect[7][6].y,i,j))
       status=true;
    else if(queenlogic(block_rect[7][3].x, block_rect[7][3].y,i,j))
        status=true;
    else if(bishoplogic(block_rect[7][2].x, block_rect[7][2].y,i,j)||bishoplogic(block_rect[7][5].x, block_rect[7][5].y,i,j))
        status=true;
    for(int m=0; m<8; m++)
    {
        if(w_pawnlogic(block_rect[6][m].x, block_rect[6][m].y,i,j)&&(!check1(i,j)))
                status=true;
    }

    return status;
}

void goback(int a, int b, int c, int d)
{
    for(int i=6; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(a==block_rect[i][j].x&&b==block_rect[i][j].y)
            {
                block_rect[i][j].x=c;
                block_rect[i][j].y=d;
            }

        }
    }

    for(int i=0; i<2; i++)
    {
        for(int j=0; j<8; j++)
            if(a==block_rect[i][j].x&&b==block_rect[i][j].y)
            {
                block_rect[i][j].x=c;
                block_rect[i][j].y=d;

            }
    }
}
