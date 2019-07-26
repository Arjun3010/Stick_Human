//Stick Human
#include<raylib.h>
#include<stdio.h>
int logm();//Title Page
int logo();//Start Page with Play and Mute option
void highscores(int);//Scores and saving scores
void highs();//High score storing
static bool ad=true;//Song check
int id=0,i=0;
Rectangle r10,r20;
typedef struct
{
    int cx,cy;
    float r;
}circle;//Structure for circle used for buttons
int score=0;//Knowing scores
int hscore=0;//Knowing high scores
int a1;
int st;
int main(void)
{
    InitWindow(800,450,"RAYLIB PROJECT 007");// Window Opened
    InitAudioDevice();
    Music msc=LoadMusicStream("res/tosong.ogg");//Music initialised
    Texture2D run=LoadTexture("res/running.png");//Running Sprite Sheet
    Texture2D idl1=LoadTexture("res/idle.png");//Idle Sprite
    int cf=0;//Sprites for running based on current frame
    Rectangle r={0.0f,0.0f,(float)run.width/10,(float)run.height};
    Rectangle r1={0.0f,0.0f,(float)idl1.width,(float)idl1.height};
    Vector2 p={0,230};
    int fc=0;//Frames counter
    int fs=10;//Speed of sprites per second
    SetTargetFPS(60);
    int a=-1;    
    int ht=0;
    int w=300;
    int w1=w;
    int hw=5;
    int k1=0;
    r10.x=0;
    r10.y=300;
    r10.width=300;
    r10.height=150;
    r20.x=500;
    r20.y=300;
    r20.width=300;
    r20.height=150;
    while(!WindowShouldClose())
    {       
        int k=0;
        if(a==0)
            k++;
        int m=0;
        UpdateMusicStream(msc);//Updates music every frame
        if(a==0 && k==1)
            PlayMusicStream(msc);//Starts the music
        if(!ad)//Stops the music if game starts
        {
          UnloadMusicStream(msc);
          CloseAudioDevice();
        }
        switch(a)
        {
            case -1:
                a=logm();//First page
                break;
            case 0:
            {
                a=logo();//Title page
                break;
            }
            case 1:
                ClearBackground(BLACK);
                DrawText(FormatText("%04i", score), 20, 20, 40, GRAY);//Scores are written
                DrawText(FormatText("HI-SCORE: %04i", hscore), 20, 70, 20, LIGHTGRAY);//High score noted
                DrawRectangleRec(r20,RED);//Player's moving area
                DrawRectangleRec(r10,RED);//Player's moving area
                a=1;
                a1=r10.x+r10.width-50;
                if(p.x<=a1)
                {   
                    if(IsKeyDown(KEY_RIGHT))
                    {    
                        fc++;
                        if(fc>=(60/fs))
                        {
                            fc=0;
                            cf++;
                            if(cf>10)
                                cf=0;
                            r.x=(float)cf*(float)run.width/10;
                        }        
                        BeginDrawing();
                        ClearBackground(BLACK);
                        DrawTextureRec(run,r,p,WHITE);//Player moves in right side
                        EndDrawing();
                        p.x=p.x+2.0f;
                    }
                    else
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        DrawTextureRec(idl1,r1,p,WHITE);//If Right Arrow not clicked then player idle sprite loaded
                        EndDrawing();
                    }
                }
                else
                {
                    BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTextureRec(idl1,r1,p,WHITE);
                    DrawRectangle(r10.x+r10.width,w,hw,ht,GREEN);//Ladder drawing
                    if(p.x>=a1)
                    {
                        if(IsKeyDown(KEY_SPACE))//Increases Height of ladder
                        {
                            ht=ht+1.0f;
                            w=w-1.0f;
                        }
                        if(IsKeyReleased(KEY_SPACE))//Stops the increase of size of ladder and ladder falls down
                        {
                            int mtk=hw;
                            hw=ht;
                            ht=mtk;
                            w=w1;
                            a=2;
                            k1=0;
                            fc=0;
                            cf=0;
                            a1=a1+hw;
                        }
                    }
                    EndDrawing();   
                }
                break;
            case 2:
                ClearBackground(BLACK);
                DrawText(FormatText("%04i", score), 20, 20, 40, GRAY);
                DrawText(FormatText("HI-SCORE: %04i", hscore), 20, 70, 20, LIGHTGRAY);
                DrawRectangleRec(r10,RED);
                DrawRectangleRec(r20,RED);
                DrawRectangle(r10.x+r10.width,w,hw,ht,GREEN);
                st=r20.x+r20.width-(r10.x+r10.width);
                if(p.x<=a1)
                {
                    if(IsKeyDown(KEY_RIGHT))
                    {    
                        fc++;
                        if(fc>=(60/fs))
                        {
                            fc=0;
                            cf++;
                            if(cf>10)
                                cf=0;
                            r.x=(float)cf*(float)run.width/10;
                        }        
                        BeginDrawing();
                        ClearBackground(BLACK);
                        DrawTextureRec(run,r,p,WHITE);
                        EndDrawing();
                        p.x=p.x+2.0f;
                    }
                    else
                    {
                        BeginDrawing();
                        ClearBackground(BLACK);
                        DrawTextureRec(idl1,r1,p,WHITE);
                        EndDrawing();
                    }
                }
                else
                {
                    BeginDrawing();
                    ClearBackground(BLACK);
                    DrawTextureRec(idl1,r1,p,WHITE);
                    EndDrawing();
                    if(k1==0)
                    {
                        if(hw>=r20.x-r10.width && hw<=st)
                        {
                            a1=a1+r20.width-50;
                            score++;
                            if(score>hscore)
                                hscore=score;
                            m++;
                            highscores(score);//Every score is noted
                            break;
                        }
                        else
                        {
                            a=4;
                            break;
                        }
                    }
                }
                a=2;    
                break;
           case 4:
                ClearBackground(WHITE);
                BeginDrawing();
                DrawText("Press [Enter] to retry!!",200,200,40,GRAY);
                EndDrawing();
                a=4;
                if(IsKeyPressed(KEY_ENTER))//If retry , then starts game again
                {
                    a=1;
                    ht=0;
                    w=300;
                    w1=w;
                    hw=5;
                    p.x=0;
                    p.y=230;
                    score=0;
                }
                break;   
           case 5: 
                ClearBackground(WHITE);
                BeginDrawing();
                DrawText("You Win !!!",200,200,35,BLUE);
                DrawText(FormatText("%04i", score), 20, 20, 40, GRAY);
                EndDrawing();
                a=5;
                break;
        }
        if(score>=2)        
             a=5;  
        if(score==1 && m==1)
        {
            ht=0;
            w=300;
            w1=w;
            hw=5;
            k1=0;
            r10.x=0;
            r10.y=300;
            r10.width=300;
            r10.height=150;
            r20.x=GetRandomValue(400,600);
            r20.y=300;
            r20.width=GetRandomValue(60,400);;
            r20.height=150;
            p.x=0;
            p.y=230;
            a=1;
        }
        m++;
    }
    highs();//Finally High score is noted
    CloseWindow();
}
int logm()
{
    BeginDrawing();
    Texture2D k=LoadTexture("res/bgm.png");
    DrawTexture(k,0,0,WHITE);
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))//Goes to next window
    {
        UnloadTexture(k);
        return 0;
    }
    EndDrawing();
    return -1;
}
int logo()
{
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangle(400,500,300,500,RAYWHITE);
        DrawText("STICK HUMAN",250,57,25,MAROON);
        Texture2D bill = LoadTexture("res/idle.png");
        DrawTexture(bill,300,110,WHITE);
        circle c;
        c.cx=325;
        c.cy=250;
        c.r=50.0;
        Vector2 m=GetMousePosition();
        Vector2 c1=(Vector2){c.cx,c.cy};
        DrawCircle(c.cx,c.cy,c.r,PINK);
        DrawText("Play",305,240,20,WHITE);
        if(CheckCollisionPointCircle(m,c1,c.r))//Play button
        {
            DrawText("Play",305,240,20,YELLOW);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                ad=false;
                UnloadTexture(bill);
                return 1;
            }
        }
        circle co;
        co.cx=120;
        co.cy=350;
        co.r=40.0;
        c1=(Vector2){co.cx,co.cy};
        DrawCircle(co.cx,co.cy,co.r,PINK);
        DrawText("Mute",90,340,20,WHITE);
        if(CheckCollisionPointCircle(m,c1,co.r))//Mute button
        {
            DrawText("Mute",90,340,20,YELLOW);
            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                i++;
                if(i%2==1)
                    ad=false;       
                UnloadTexture(bill);
            }
        }
        EndDrawing();
        return 0;
}
void highscores(int scores)
{
    FILE *fptr;
    fptr=fopen("score.txt","a+");
    id++;
    fprintf(fptr,"\n %d \t %d",id,scores);
    fclose(fptr);
}
void highs()
{
    FILE *fptr;
    fptr=fopen("hscore.txt","a+");
    fprintf(fptr,"\n %d \t %d",id,hscore);
    fclose(fptr);
}