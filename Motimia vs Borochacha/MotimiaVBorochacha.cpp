#include"iGraphics.h"
#include"myheader.h"
#include "bitmap_loader.h"
#include <string>
#define screenHeight 720
#define screenWidth 1280
double mm1X=rand() % 780+250,mm1Y;
double mm2X=rand() % 780+250,mm2Y;
double abX=rand() % 780+250,abY;
double fmmX=rand() % 780+250,fmmY;
double kongkaX=rand() % 780+250,kongkaY;
double jamilX=rand() % 780+250,jamilY;
double inkX=rand() % 780+250,inkY;
double bcX,bcY;
int game = 0;
int point=0, life=10, counter=2;
int time1=5;
int ink=8;
int i=0,j=0,num,count;
int startScreenbg,instructionbg,userinputbg,lastscreenbg, gamebg, creditbg;
int indexNumber=0;
bool musicOn=true;
bool gameState=true;//pause or resume
bool mm1Flag=false,mm2Flag=false,abFlag=false,inkFlag=false,fmmFlag=false,kongkaFlag=false,jamilFlag=false,mm1Catch=false,mm2Catch=false;
char pointstr[15];
char lifestr[10];
char inkstr[10];
char name[100],pointf[10];
FILE *players=fopen("playerdata.txt","a+");
struct player
{
    char name[100];
    int point;
} p[100];
void assignStruct(struct player *p)
{
	players=fopen("playerdata.txt","a+");
    while(fscanf(players,"%s %d",name,&num)!=EOF)
    {
        strcpy(p[i].name,name);
        p[i].point=num;
        i++;
        count++;//counts player
    }
    fclose(players);
}
void sort(struct player *p)
{
    for(i = 0; i <count; i++)
    {
        for (j = 0; j < count; j++)
        {
            if (p[j].point < p[j + 1].point)
            {
                char temp2[10];
                int temp1 = p[j].point;
                strcpy(temp2,p[j].name);
                p[j].point = p[j + 1].point;
                strcpy(p[j].name,p[j + 1].name);
                p[j + 1].point = temp1;
                strcpy(p[j+1].name,temp2);
            }
        }
    }
}
void writeinFile(struct player *p)//writes in highscore file
{
    FILE *f=fopen("highscore.txt","w");
    assignStruct(p);
    sort(p);
    for(i=0; i<5; i++)
    {
        fprintf(f,"%s %d\n",p[i].name,p[i].point);
    }
    fclose(f);
}
void flagChecker()
{
    if(counter%1==0)
        mm1Flag=true;
    if(counter%3==0)
        mm2Flag=true;
    if(counter%5==0)
        abFlag=true;
    if(counter%4==0)
        inkFlag=true;
    if(counter%10==0)
        fmmFlag=true;
    if(counter%13==0)
        kongkaFlag=true;
    if(counter%17==0)
        jamilFlag=true;
	if((mm1X >= bcX-10 && mm1X <= bcX+236)&&(mm1Y >= bcY && mm1Y <= bcY+220))
		mm1Catch=true;
	if((mm2X >= bcX-10 && mm2X <= bcX+236)&&(mm2Y >= bcY && mm2Y <= bcY+220))
		mm2Catch=true;
}
void gameMode()
{
    if(game == 0)
    {
        //start screen
        iShowImage(0,0,screenWidth,screenHeight,startScreenbg);
		iShowBMPAlternativeSkipWhite(580,50,"exit.bmp");
		iShowBMPAlternativeSkipWhite(580,120,"credit.bmp");
		iShowBMPAlternativeSkipWhite(580,190,"leaderboard.bmp");
		iShowBMPAlternativeSkipWhite(580,260,"instruction.bmp");
		iShowBMPAlternativeSkipWhite(580,330,"start.bmp");
		if(musicOn==false)
		iShowBMPAlternativeSkipWhite(20,20,"soundOff.bmp");
		else iShowBMPAlternativeSkipWhite(20,20,"soundOn.bmp");
    }
    if(game == 1)
    {
        //START GAME
        iShowImage(0,0,screenWidth,screenHeight,gamebg);
		if(gameState == false)
		{
		iSetColor(255,255,255);
		iText(590,300,"      Paused",GLUT_BITMAP_HELVETICA_18);
		iText(590,260,"Press r to resume",GLUT_BITMAP_HELVETICA_18);
		}
		if(mm1Catch==false)
			iShowBMPAlternativeSkipWhite(mm1X,mm1Y,"motimia2.bmp");
		else if(mm1Catch==true)
			iShowBMP2(mm1X+12,mm1Y,"motimia.bmp",0);
        if(mm2Catch==false)
			iShowBMPAlternativeSkipWhite(mm2X,mm2Y,"motimia2.bmp");
		else if(mm2Catch==true)
			iShowBMP2(mm2X+12,mm2Y,"motimia.bmp",0);
        iShowBMP2(abX,abY,"anisbhai.bmp",0);
        iShowBMPAlternativeSkipWhite(fmmX,fmmY,"formalmotimia.bmp");
        iShowBMPAlternativeSkipWhite(kongkaX,kongkaY,"kongka.bmp");
        iShowBMPAlternativeSkipWhite(jamilX,jamilY,"jamil.bmp");
        iShowBMPAlternativeSkipWhite(bcX,bcY,"Borochacha_catcher.bmp");
        iSetColor(255,255,255);
        iShowBMPAlternativeSkipWhite(inkX,inkY,"ink.bmp");
        iShowBMP2(1175,640,"motimia.bmp",0);
		if(point>0)
        iText(1195,615,pointstr,GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMPAlternativeSkipWhite(1175,550,"heart.bmp");
		if(life<=10)
        iText(1200,520,lifestr,GLUT_BITMAP_TIMES_ROMAN_24);
		if(ink!=9)
        iShowBMPAlternativeSkipWhite(1190,480,"ink.bmp");
        iText(1200,450,inkstr,GLUT_BITMAP_TIMES_ROMAN_24);
        flagChecker();
    }
    else if(game == 2)
    {
        //INSTRUCTIONS
        iShowImage(0,0,screenWidth,screenHeight,instructionbg);
        iShowBMPAlternativeSkipWhite(30,650,"back.bmp");
    }
    else if(game == 3)
    {
        //High Score
        iSetColor(0,0,255);
        iFilledRectangle(0,0,screenWidth,screenHeight);
        iShowBMPAlternativeSkipWhite(30,650,"back.bmp");
        int ycord=610;
        iSetColor(0,0,0);
        FILE *f= fopen("highscore.txt","r");
        for(i=0; i<4; i++)
        {
            fscanf(f,"%s %d",name,&num);
            iText(590,ycord,name,GLUT_BITMAP_HELVETICA_18);
            _itoa(num,pointf,10);
            iText(650,ycord,pointf,GLUT_BITMAP_HELVETICA_18);
            ycord-=50;
        }
        fclose(f);
    }
    else if(game == 4)
    {
        //Credit
        iSetColor(0,255,0);
        iShowImage(0,0,screenWidth,screenHeight,creditbg);
        iShowBMPAlternativeSkipWhite(30,650,"back.bmp");
    }
    else if(game == 5)
    {
        //Last Screen
        iSetColor(255,255,255);
        iShowImage(0,0,screenWidth,screenHeight,lastscreenbg);
        iText(590,440,"Your score: ",GLUT_BITMAP_HELVETICA_18);
        iSetColor(255,255,255);
        iFilledRectangle(540,350,200,70);
        iFilledRectangle(540,260,200,70);
        iSetColor(0,0,0);
        iText(620,380,pointstr,GLUT_BITMAP_HELVETICA_18);
        iSetColor(0,0,0);
        iText(590,290,"Play Again",GLUT_BITMAP_HELVETICA_18);
    }
    else if(game == 6)
    {
        //user input screen
        if(musicOn==2)
            PlaySound("music\\astekoiramairen.wav",NULL,SND_LOOP|SND_ASYNC);
        iShowImage(0,0,screenWidth,screenHeight,userinputbg);
        iShowBMPAlternativeSkipWhite(30,650,"back.bmp");
        iText(490,470,"Enter your name : ",GLUT_BITMAP_TIMES_ROMAN_24);
        iSetColor(0,0,0);
        iFilledRectangle(490,400,300,50);
        iSetColor(255,255,255);
        iText(500,410,name,GLUT_BITMAP_TIMES_ROMAN_24);
    }
}
void point_manager(int point)
{
    _itoa(point,pointstr,10);
    printf("%s",pointstr);
}
void life_manager(int life)
{
    _itoa(life,lifestr,10);
    printf("%s",lifestr);
}
void ink_manager(int ink)
{
    _itoa(ink,inkstr,10);
    printf("%s",inkstr);
}
void iDraw()
{
    iClear();
	gameMode();
}
void iMouseMove(int mx, int my)
{
}
void iPassiveMouse(int mx, int my)
{
}
void iMouse(int button, int state, int mx, int my)
{
    if(game == 0)
    {
        if((mx>=580 && mx <=700) && my>=330  && my<=390)
        {
            //user name input screen
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                //user name input screen
                game = 6;
                //musicOn=2;
            }
        }
        else if((mx>=580 && mx <=700) && my>=260  && my<=320)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                game = 2;//instruction button
        }
        else if((mx>=580 && mx <=700) && my>=190  && my<=250)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                game = 3;
                writeinFile(p);
                //high score
        }
        else if((mx>=580 && mx <=700) && my>=120  && my<=180)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                game = 4;//credit
        }
		else if((mx>=580 && mx <=700) && my>=50  && my<=110)
		{
			if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
				exit(0);
		}
        else if((mx>=20 && mx <=140) && my>=20  && my<=140)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                //sound on/off
                if(musicOn==true)
				{
                    musicOn=false;
					PlaySound(0,0,0);
				}
                else if(musicOn==false)
				{
                    musicOn=true;
					PlaySound("music\\bgsound.wav",NULL,SND_LOOP|SND_ASYNC);
				}
        }
    }
    if(game == 2||game == 3||game == 4||game == 6)
    {
        if((mx>=30 && mx <=90) && my>=650  && my<=720)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
                game = 0;//back button
        }
    }
    if(game == 5)
    {
        //play again
        if((mx>=520 && mx <=760) && my>=240  && my<=350)
        {
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
            {
                game = 0;
                life=10;
                point=0;
                ink=8;
                mm1Y=720;
                mm2Y=750;
                abY=750;
                inkY=750;
                fmmY=750;
                kongkaY=750;
                jamilY=750;
                mm1Flag=0;
                mm2Flag=0;
                abFlag=0;
                inkFlag=0;
                fmmFlag=0;
                kongkaFlag=0;
                jamilFlag=0;
            }
        }
    }
}
void iKeyboard(unsigned char key)
{
	if(game==1)
	{
    if (key =='p')
    {
		for(i=0;i<8;i++)
        iPauseTimer(i);
        gameState=false;
    }
    if (key =='r')
    {
		for(i=0;i<8;i++)
        iResumeTimer(i);
        gameState=true;
    }
	}
    //user input
    if(key!='\b')
    {
        name[indexNumber] = key;
        indexNumber++;
        name[indexNumber] = '\0';
    }
    else
    {
        if (indexNumber <= 0)
            indexNumber = 0;
        else
            indexNumber--;
        name[indexNumber]='\0';
    }
    if(key =='\r')
    {
        game = 1;
		players=fopen("playerdata.txt","a+");
        fprintf(players,"%s",name);
    }
}
void iSpecialKeyboard(unsigned char key)
{
    if(key == GLUT_KEY_LEFT && bcX > -30)
    {
        if(gameState==true)
            bcX-=10;
    }
    if(key == GLUT_KEY_RIGHT && bcX < 1050)
    {
        if(gameState==1)
            bcX+=10;
    }
}
void mm1()
{
    if(game == 1)
    {
        if(mm1Flag==1)
        {
            if(point>15)
                mm1Y-=4;
            else
                mm1Y-=3;
            if(mm1Y <= 0)
            {
                mm1X=rand() % 780+250;
                mm1Y = 720;
                life--;
                counter++;
                life_manager(life);
                mm1Flag=false;
                printf("life remaining %d\n",life);
              if(life <= 0)
                {
                    game = 5;
					fprintf(players,"%s\n",pointstr);
                    fclose(players);
                }
            }
            else if((mm1X >= bcX-10 && mm1X <= bcX+236)&&(mm1Y >= bcY && mm1Y <= bcY+200))
            {
                mm1X=rand() % 780+250;
                mm1Y = 720;
                point++;
                ink--;
                counter++;
                point_manager(point);
                ink_manager(ink);
                mm1Flag=false;
				mm1Catch=false;
            }
        }
    }
}
void mm2()
{
    if(game == 1)
    {
        if(mm2Flag==1)
        {
            if(point>15)//increase speed
                mm2Y-=3;
            else
                mm2Y-=2;
            if(mm2Y <= 0)
            {
                mm2X=rand() % 780+250;
                mm2Y = 720;
                life--;
                counter++;
                life_manager(life);
                mm2Flag=false;
                printf("life remaining %d\n",life);
                if(life <= 0)
                {
                    game = 5;
                    fprintf(players,"%s\n",pointstr);
                    fclose(players);
                }
            }
            else if((mm2X >= bcX-10 && mm2X <= bcX+236)&&(mm2Y >= bcY && mm2Y <= bcY+200))
            {
                mm2X=rand() % 780+250;
                mm2Y = 720;
                point++;
                ink--;
                counter++;
                point_manager(point);
                ink_manager(ink);
                mm2Flag=false;
                mm2Catch=false;
            }
        }
    }
}
void ab()
{
    //falling anis bhai
    if(game == 1)
    {
        if(abFlag==1)
        {
            if(point>20)
                abY-=3;
            else
                abY-=2;
            if(abY <= 0)
            {
                abX=rand() % 780+250;
                abY = 720;
                counter++;
                abFlag=false;
                if(life <= 0)
                {
                    game = 5;
                    fprintf(players,"%s\n",pointstr);
                    fclose(players);
                }
            }
        }
        else if((abX >= bcX-10 && abX <= bcX+236)&&(abY >= bcY && abY <= bcY+200))
        {
            abX=rand() % 780+250;
            abY = 720;
            point--;
            ink--;
            counter++;
            point_manager(point);
            ink_manager(ink);
            abFlag=false;
            printf("Ink remaining %d\n",ink);
            printf("point %s\n",pointstr);
        }
    }
}
void inkRefill()
{
    if(game == 1)
    {
        if(inkFlag==1)
        {
            if(point>20)
                inkY-=4;
            else
                inkY-=3;
            if(inkY <= 0)
            {
                inkX=rand() % 780+250;
                inkY = 720;
                counter++;
                inkFlag=false;
            }
            else if((inkX >= bcX-10 && inkX <= bcX+236)&&(inkY >= bcY && inkY <= bcY+200))
            {
                inkX=rand() % 780+250;
                inkY = 720;
                ink+=5;
                counter++;
                ink_manager(ink);
                inkFlag = false;
                printf("\nink %d\n",ink);
            }
           if(ink <= 0)
                {
                    game = 5;
					fprintf(players,"%d\n",point);
                    fclose(players);
                }
        }
    }
}
void fmm()
{
    //falling formal motimia
    if(game == 1)
    {
        if(fmmFlag==1)
        {
            fmmY-=3;
            if(fmmY <= 0)
            {
                fmmX=rand() % 780+250;
                fmmY = 720;
                counter++;
                life_manager(life);
                fmmFlag=false;
                printf("life remaining %d\n",life);
                if(life <= 0)
                {
                    game = 5;
					fprintf(players,"%s\n",point);
                    fclose(players);
                }
            }
            else if((fmmX >= bcX-10 && fmmX <= bcX+236)&&(fmmY >= bcY && fmmY <= bcY+200))
            {
                fmmX=rand() % 780+250;
                fmmY = 720;
                point+=5;
                ink--;
                counter++;
                point_manager(point);
                ink_manager(ink);
                fmmFlag=false;
                printf("Ink remaining %d\n",ink);
                printf("point %s\n",pointstr);
            }
        }
    }
}
void kongka()
{
    if(game == 1)
    {
        if(kongkaFlag==1)
        {
            kongkaY-=3;
            if(kongkaY <= 0)
            {
                kongkaX=rand() % 780+250;
                kongkaY = 720;
                counter++;
                life_manager(life);
                kongkaFlag=false;
                printf("life remaining %d\n",life);
                if(life <= 0)
                {
                    game = 5;
					fprintf(players,"%s\n",pointstr);
                    fclose(players);
                }
            }
            else if((kongkaX >= bcX-10 && kongkaX <= bcX+236)&&(kongkaY >= bcY && kongkaY <= bcY+200))
            {
                kongkaX=rand() % 780+250;
                kongkaY = 720;
                point--;
                counter++;
                point_manager(point);
                ink_manager(ink);
                kongkaFlag=false;
                printf("Ink remaining %d\n",ink);
                printf("point %s\n",pointstr);
            }
        }
    }
}
void jamil()
{
    if(game == 1)
    {
        if(jamilFlag==1)
        {
            jamilY-=3;
            if(jamilY <= 0)
            {
                jamilX=rand() % 780+250;
                jamilY = 720;
                counter++;
                jamilFlag=false;
                if(life <= 0)
                {
                    game = 5;
					fprintf(players,"%s\n",pointstr);
                    fclose(players);
                }
            }
        }
        else if((jamilX >= bcX-10 && jamilX <= bcX+236)&&(jamilY >= bcY && jamilY <= bcY+200))
        {
            jamilX=rand() % 780+250;
            jamilY = 720;
            point--;
            counter++;
            point_manager(point);
            ink_manager(ink);
            jamilFlag=false;
            printf("Ink remaining %d\n",ink);
            printf("point %s\n",pointstr);
        }
    }
}
int main()
{
    srand(time(NULL));
    mm1Y=720;
    mm2Y=750;
    abY=750;
    inkY=750;
    fmmY=750;
    kongkaY=750;
    jamilY=750;
    bcX=640;
    bcY=0;
	if(game==0)
	{
		if(musicOn==true)
			PlaySound("music\\bgsound.wav",NULL,SND_LOOP|SND_ASYNC);
	}
	//else if 
    iInitialize(screenWidth,screenHeight, "M o t i m i a   V   B o r o c h a h a");
    startScreenbg=iLoadImage("images\\StartScreenbg.jpg");
    instructionbg=iLoadImage("images\\Instruction.jpg");
    userinputbg=iLoadImage("images\\userinput.jpg");
    lastscreenbg=iLoadImage("images\\LastScreenbg.jpg");
    creditbg=iLoadImage("images\\creditbg.jpg");
    gamebg=iLoadImage("images\\gamebg.jpeg");
    iSetTimer(time1, mm1);
    iSetTimer(time1, mm2);
    iSetTimer(time1, ab);
    iSetTimer(time1, inkRefill);
    iSetTimer(time1, fmm);
    iSetTimer(time1, kongka);
    iSetTimer(time1, jamil);
    iStart();
    return 0;
}