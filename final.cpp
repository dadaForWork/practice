#include<stdio.h>
#include <stdlib.h> 
#include <time.h>
#include <windows.h>


//�N���Ы�����w��m 
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
		**	��� 
		*/
	
		//��J�a�Ϥj�p 
		printf("��J�a�Ϥj�p(�d��:9*9)�G");
		scanf("%d*%d",&sizex,&sizey);
		int map[sizex][sizey];
		
		//��J���u�ƶq
		printf("��J���u�ƶq�G");
		scanf("%d",&bumbnum);
		int bumb[bumbnum];
		
		//���u�Ƥ���W�L�`��� �Y�W�L�h�פ�{�� 
		if(bumbnum>(sizex*sizey)){
			printf("���u�ƶq�W�L�`��ơA�����N��h�X�{��");
			exit(0);
		} 
		
		//�üƲ��ͬ��u 
		srand( time(NULL) );
		for(int i=0;i<bumbnum;i++){
			bumb[i]=rand()%(sizex*sizey)+1;
			//�P�_���u�O�_���� 
			for(int j=0;j<i;j++){
				if(bumb[i]==bumb[j]) {	
					i--; 
					break;
				}
			}
		}
	
		
		system("cls");
		
		//�L�X��l�a�� 
		for(int i=0;i<sizex;i++){
			for(int j=0;j<sizey;j++){
				//�a�ϲM0 
				map[i][j]=0;
				
				//�L�b���w��m 
				gotoXY(i*3,j);
				printf("*");
			}
		}
		
	//	//���u��m 
	//	for(int i=0;i<bumbnum;i++){
	//		int bumb_x = bumb[i]%sizey;
	//		int bumb_y = bumb[i]/sizey;
	//		
	//		gotoXY(bumb_x*3,bumb_y);
	//		printf("b");
	//		
	//	}
	
		//�N���u��J�a�Ϥ� �a�ϥ��W����0���̧ǥѥk�U���W ���u�ƭȬ�10 
		for(int i=0;i<bumbnum;i++){
			int bumb_x = bumb[i]%sizey;
			int bumb_y = bumb[i]/sizey;
			
			map[bumb_x][bumb_y]=10; 
			//�p��E�c�椺�O�_�����u ���u������E�c��[�@---------------------------------------------
			for(int x=bumb_x-1;x<=bumb_x+1;x++){
				for(int y=bumb_y-1;y<=bumb_y+1;y++){
					if(x>=0 && y>=0 && x<sizex && y<sizey && map[x][y]!=10){
						map[x][y]++;
					}
					
				}
			}
		}
		
	//	//�d�ݦa�� 
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
	
		
		
		//�}�l�C�� 
		while(true){
		
	
			
			
			
		
			
			
		
		}	
		
	}
	 
	 
	
}
