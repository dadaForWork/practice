#include <stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <windows.h>
#include <conio.h>

//typedef int bool;
//#define true 1
//#define false 0



#define OFFSETX 1
#define OFFSETY 2
#define GAPX 3
#define GAPY 1
#define INSWITCH 11


#define KEY_SPACE 32
#define KEY_FLAG_UPPER 70
#define KEY_FLAG_LOWER 102
#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80


#define BUMB 10
#define FLAG 11
#define SPACE 12

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
	if( ch!=KEY_SPACE && ch!=KEY_FLAG_UPPER && ch!=KEY_FLAG_LOWER )return true;
	switch(ch){
		case KEY_SPACE:
			//space
			if(map[x/GAPX][y/GAPY]==10){
				//Game Over
				printS('B',x,y);
//				return false;
			}
			return false;
			
		case KEY_FLAG_UPPER:
		case KEY_FLAG_LOWER:
			//flag
			gotoXY(x,y);
			printf("F");
			gotoXY(x,y);
			return false;
	}
}

void gotoXYSys(int x,int y){
	HANDLE hout;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x+OFFSETX,y+OFFSETY};
	SetConsoleCursorPosition(hout, pos);
	
}


//輸入 
int Input(int input,int x,int y){
	switch(input){
		case KEY_UP:
			//up
			if(gotoXY(x,y-GAPY))return INSWITCH-1;
			return INSWITCH;

		case KEY_LEFT:
			//left
			if(gotoXY(x-GAPX,y))return INSWITCH-10;
			return INSWITCH;
			
		case KEY_RIGHT:
			//right
			if(gotoXY(x+GAPX,y))return INSWITCH+10;
			return INSWITCH;
			
		case KEY_DOWN:
			//down
			if(gotoXY(x,y+GAPY))return INSWITCH+1;
			return INSWITCH;
			
		case KEY_SPACE:
			//space
			printS('S',x,y);
			return INSWITCH;
			
		case KEY_FLAG_UPPER:
		case KEY_FLAG_LOWER:
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
		
		
	
		//輸入地圖大小 
		printf("輸入地圖大小(範例:9*9)：");
		scanf("%d*%d",&sizex,&sizey);
		
//		int map[sizex][sizey];
		//calloc: 將內容清0，malloc: 不會清0 
		int **map = (int**)calloc(sizex, sizeof(int*));	
		
		//每一列有 sizey 個行 
		for(i=0;i<sizex;i++){
			map[i] = (int*)calloc(sizey, sizeof(int*)); 
		}
		
		
		//更改狀態使用 map，originMap 在插滿旗子時用來判斷 
		int **originMap = (int**)calloc(sizex, sizeof(int*));	
		
		//每一列有 sizey 個行 
		for(i=0;i<sizex;i++){
			originMap[i] = (int*)calloc(sizey, sizeof(int*)); 
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
			
			map[bumb_x][bumb_y]=BUMB; 
			originMap[bumb_x][bumb_y]=BUMB;
			//計算九宮格內是否有炸彈 炸彈讓附近九宮格加一---------------------------------------------
			for(x=bumb_x-1;x<=bumb_x+1;x++){
				for(y=bumb_y-1;y<=bumb_y+1;y++){
					if(x>=0 && y>=0 && x<sizex && y<sizey && map[x][y]!=10){
						map[x][y]++;
						originMap[x][y]++;
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
	
		
		int ch,x=0,y=0,countFlag=0;
		bool gameover=false;
		gotoXY(x,y);
		
		
		/* 
		 *開始遊戲 
		*/ 
		 
		while(ch = getch()){
			

			if(ch==224)continue;
			
			
			/*
			 *判斷規則 
			*/
			
			int showX=x*GAPX,showY=y*GAPY;
			
			//空白規則: 1.開過的不做事 2.有插旗的不做事 3.沒開過的顯示地圖資訊，判斷是否GAME OVER 4.
			if(ch==KEY_SPACE){
				if(map[x][y]==SPACE || map[x][y]==FLAG){
					continue;
				}
				else{
					if(map[x][y]==BUMB){
						//GAME OVER
						
						break;
					}
					else{
						gotoXY(showX,showY);
						printf("%d",map[x][y]);
						gotoXY(showX,showY);
						
						map[x][y]=SPACE;
						continue;
					}
				}
			}
			
			//插旗規則: 1.插過旗的取消插旗 2.空白的不做事 3.沒開過且沒插旗的插旗 3.旗子數達到炸彈數，判斷是否GAME OVER
			else if(ch==KEY_FLAG_UPPER || ch==KEY_FLAG_LOWER){
				if(map[x][y]==FLAG){
					printS('*',showX,showY);
					map[x][y] = originMap[x][y];
					continue;
				}
				else if(map[x][y]==SPACE){
					continue;
				}
				else{
					printS('F',showX,showY);
					map[x][y] = FLAG;
					countFlag+=1;
					if(countFlag==bumbnum){
						//判斷是否GAME OVER 
						
						system("cls");
						
						for(int i=0;i<sizex;i++){
							for(int j=0;j<sizey;j++){
								
								int showX=i*GAPX,showY=j*GAPY;
								gotoXY(showX,showY);
								
								// 地圖內容 1.數字 2.SPACE 3.FLAG 4.BUMB 
								switch(map[i][j]){
									case FLAG:
										printS('F',showX,showY);
										break;
									case BUMB:
										printS('X',showX,showY);
										gameover=true;
										break; 
									default:
										gotoXY(showX,showY);
										printf("%d",originMap[i][j]);
										gotoXY(showX,showY);
										break;
									
								}
								
								if(!gameover){
									Sleep(100);
								}
								else{
									Sleep(10);
								} 
								
							}
						}
						gotoXYSys(sizex*GAPX,sizey*GAPY);
						system("pause"); 
						
					}
				}
			}
			
			//上下左右規則: 不能超過邊界* 
			else{
				int tem = Input(ch,showX,showY)-INSWITCH;
				x+=tem/10;
				y+=tem%10;
			}
			
			
			
			
			
			if(gameover)break;
			
			

			
			
			
		
			
			
		
		}	
		
		/* 
		 *結束畫面 
		*/ 
		
		system("cls");
		printf("GAME OVER!!\n");
		system("pause");
		
		system("cls");
	}
	 
	 
	
}
