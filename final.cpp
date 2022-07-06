#include<stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <windows.h>
#include <conio.h>


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

bool checkMap(int** map,int ch){
	if(ch!=32&&ch!=70&&ch!=102)return true;
}

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
			gotoXY(x,y);
			printf("S");
			return INSWITCH;
			
		case 70:
		case 102:
			//set flag
			gotoXY(x,y);
			printf("F");
			return INSWITCH;
			
		default:
			//other
			return INSWITCH;
	}
	
}


int main(){
	int bumbnum;
	
	
	while(true){
		/*
		**	選單 
		*/
	
		//輸入地圖大小 
		printf("輸入地圖大小(範例:9*9)：");
		scanf("%d*%d",&sizex,&sizey);
		
		int map[sizex][sizey];
//		int 
//		int** map2 = (int*)
		
		
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
		for(int i=0;i<bumbnum;i++){
			bumb[i]=rand()%(sizex*sizey)+1;
			//判斷炸彈是否重複 
			for(int j=0;j<i;j++){
				if(bumb[i]==bumb[j]) {	
					i--; 
					break;
				}
			}
		}
	
		
		system("cls");
		
		//印出初始地圖 
		for(int i=0;i<sizex;i++){
			for(int j=0;j<sizey;j++){
				//地圖清0 
				map[i][j]=0;
				
				//印在指定位置 
				gotoXY(i*GAPX,j*GAPY);
				printf("*");
			}
		}
		
	//	//炸彈位置 
	//	for(int i=0;i<bumbnum;i++){
	//		int bumb_x = bumb[i]%sizey;
	//		int bumb_y = bumb[i]/sizey;
	//		
	//		gotoXY(bumb_x*3,bumb_y);
	//		printf("b");
	//		
	//	}
	
		//將炸彈放入地圖內 地圖左上角為0號依序由右下遞增 炸彈數值為10 
		for(int i=0;i<bumbnum;i++){
			int bumb_x = bumb[i]%sizey;
			int bumb_y = bumb[i]/sizey;
			
			map[bumb_x][bumb_y]=10; 
			//計算九宮格內是否有炸彈 炸彈讓附近九宮格加一---------------------------------------------
			for(int x=bumb_x-1;x<=bumb_x+1;x++){
				for(int y=bumb_y-1;y<=bumb_y+1;y++){
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
		//開始遊戲 
		while(ch = getch()){

			if(ch==224)continue;
//			printf("%d\n",ch);
			
//			if(checkMap(map,ch)){
				int tem = Input(ch,x,y)-INSWITCH;
				x+=tem/10*GAPX;
				y+=tem%10*GAPY;
//			}
			
			

			
			

			
			
			
		
			
			
		
		}	
		
	}
	 
	 
	
}
