#include<stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <windows.h>
#include <conio.h>

typedef int bool;
#define true 1
#define false 0


#define OFFSETX 1
#define OFFSETY 2
#define GAPX 3
#define GAPY 1
#define INSWITCH 11

int sizex,sizey;
//將光標指到指定位置 
bool gotoXY(int x,int y){
	if(x>((sizex-1)*GAPX) || y>((sizey-1)*GAPY) || x<0 || y<0 )return false;
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x+OFFSETX,y+OFFSETY};
	SetConsoleCursorPosition(hout, pos);
	
	return true;
}

//印出指定位置
void printS(char ch,int x,int y){
	gotoXY(x,y);
	printf("%c",ch);
	gotoXY(x,y);
}

//判斷規則 
bool checkMap(int** map,int ch,int x,int y){
	if(ch!=32&&ch!=70&&ch!=102)return true;
	switch(ch){
		case 32:
			//space
			if(map[x][y]==10){
				//Game Over
				printS('B',x,y);
//				return false;
			}
			
		case 70:
		case 102:
			//flag
			gotoXY(x,y);
			printf("F");
			gotoXY(x,y);
			return INSWITCH;
	}
}


//輸入 
int Input(int input,int x,int y){
	switch(input){
		case 72:
			//up
			if(gotoXY(x,y-GAPY))return INSWITCH-1;
			return INSWITCH;

		case 75:
			//left
			if(gotoXY(x-GAPX,y))return INSWITCH-10;
			return INSWITCH;
			
		case 77:
			//right
			if(gotoXY(x+GAPX,y))return INSWITCH+10;
			return INSWITCH;
			
		case 80:
			//down
			if(gotoXY(x,y+GAPY))return INSWITCH+1;
			return INSWITCH;
			
		case 32:
			//space
			printS('S',x,y);
			return INSWITCH;
			
		case 70:
		case 102:
			//set flag
			printS('F',x,y);
			return INSWITCH;
			
		default:
			//other
			return INSWITCH;
	}
	
}




int main(){
	int bumbnum,i,j,x,y;
	
	
	while(true){
		/*
		**	選單 
		*/
		
		bool gameover=false;
	
		//輸入地圖大小 
		printf("輸入地圖大小(範例:9*9)：");
		scanf("%d*%d",&sizex,&sizey);
		
//		int map[sizex][sizey];
		//calloc: 將內容清0，malloc: 不會清0 
		int **map = calloc(sizex, sizeof(int*));	
		
		//每一列有 sizey 個行 
		for(i=0;i<sizex;i++){
			map[i] = calloc(sizey, sizeof(int*)); 
		}
		
		
		//輸入炸彈數量
		printf("輸入炸彈數量：");
		scanf("%d",&bumbnum);
		int bumb[bumbnum];
		
		//炸彈數不能超過總格數 若超過則終止程式 
		if(bumbnum>(sizex*sizey)){
			printf("炸彈數量超過總格數，按任意鍵退出程式");
			exit(0);
		} 
		
		//亂數產生炸彈 
		srand( time(NULL) );
		for(i=0;i<bumbnum;i++){
			bumb[i]=rand()%(sizex*sizey)+1;
			//判斷炸彈是否重複 
			for(j=0;j<i;j++){
				if(bumb[i]==bumb[j]) {	
					i--; 
					break;
				}
			}
		}
	
		
		system("cls");
		
		//印出初始地圖 
		for(i=0;i<sizex;i++){
			for(j=0;j<sizey;j++){
				
				//印在指定位置 
				printS('*',i*GAPX,j*GAPY);
	
			}
		}
		
	//	//炸彈位置 
	//	for(i=0;i<bumbnum;i++){
	//		int bumb_x = bumb[i]%sizey;
	//		int bumb_y = bumb[i]/sizey;
	//		
	//		gotoXY(bumb_x*3,bumb_y);
	//		printf("b");
	//		
	//	}
	
		//將炸彈放入地圖內 地圖左上角為0號依序由右下遞增 炸彈數值為10 
		for(i=0;i<bumbnum;i++){
			int bumb_x = bumb[i]%sizey;
			int bumb_y = bumb[i]/sizey;
			
			map[bumb_x][bumb_y]=10; 
			//計算九宮格內是否有炸彈 炸彈讓附近九宮格加一---------------------------------------------
			for(x=bumb_x-1;x<=bumb_x+1;x++){
				for(y=bumb_y-1;y<=bumb_y+1;y++){
					if(x>=0 && y>=0 && x<sizex && y<sizey && map[x][y]!=10){
						map[x][y]++;
					}
					
				}
			}
		}
		
	//	//查看地圖 
	//	for(int i=0;i<sizex;i++){
	//		for(int j=0;j<sizey;j++){
	//			gotoXY(i*GAPX+OFFSETX,j*GAPY+OFFSETY);
	//			if(map[i][j]==10){
	//				printf("B");
	//			}
	//			else{
	//				printf("%d",map[i][j]);
	//			}
	//			
	//		}
	//	}
	
		
		int ch,x=0,y=0;
		gotoXY(x,y);
		
		/* 
		 *開始遊戲 
		*/ 
		 
		while(ch = getch()){
			
//			if(gameover==true)break;

			if(ch==224)continue;
//			printf("%d\n",ch);
			
			if(checkMap(map,ch,x,y)){
				int tem = Input(ch,x,y)-INSWITCH;
				x+=tem/10*GAPX;
				y+=tem%10*GAPY;
			}
			
			

			
			

			
			
			
		
			
			
		
		}	
		
		/* 
		 *結束畫面 
		*/ 
	}
	 
	 
	
}
