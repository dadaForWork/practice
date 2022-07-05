#include<stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <windows.h>


//將光標指到指定位置 
void gotoXY(int x,int y){
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x,y};
	SetConsoleCursorPosition(hout, pos);
}


int main(){
	int sizex,sizey,bumbnum;
	
	
	while(true){
		/*
		**	選單 
		*/
	
		//輸入地圖大小 
		printf("輸入地圖大小(範例:9*9)：");
		scanf("%d*%d",&sizex,&sizey);
		int map[sizex][sizey];
		
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
				gotoXY(i*3,j);
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
	//			gotoXY(i*3,j);
	//			if(map[i][j]==10){
	//				printf("B");
	//			}
	//			else{
	//				printf("%d",map[i][j]);
	//			}
	//			
	//		}
	//	}
	
		
		
		//開始遊戲 
		while(true){
		
	
			
			
			
		
			
			
		
		}	
		
	}
	 
	 
	
}
