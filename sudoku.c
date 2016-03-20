#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//program is fragmented into functions which were being added as the progress on project continued
char start_up(); //initializes the program. reads config from file; if no file found, creates a new one; prints current control scheme on screen
void new_game();	
void load_game();
void add_new();
void options();
void play_sudoku(int number);

char print_menu(char *header, char *menu[], char length);
char print_sudoku(char *header, char sudoku[9][9]);
char sudoku_solve(char sudoku[][9], char row, char col); //solves passed sudoku chart using backtracking method
void reset_position();	//resets selectx and selecty values, called when opening new menu
char getch();

static unsigned char config[7]={'a','d','w','s','\r','0','7'};	//<,>,^,v,selection,text color,background color
static char file_name[]="data.txt";
static unsigned char selectx=0;		//current menu and chart field selection
static unsigned char selecty=0;

int main(){
	if(!start_up())	return 0;
	unsigned char run_main_menu=1;
	char main_menu_header[]="SUDOKU";
	char *main_menu[5]={"New game", "Load game", "Add new sudoku", "Options", "Exit"};
	while(run_main_menu){
		switch(print_menu(main_menu_header,main_menu,5)){
			case 0:
				reset_position();
				new_game();
				break;
			case 1:
				reset_position();
				load_game();
				break;
			case 2:
				reset_position();
				add_new();
				break;
			case 3:
				reset_position();
				options();
				break;
			case 4:
				reset_position();
				run_main_menu=0;
				break;
			case 5:
				break;
		}
	}
	return 0;
}

char start_up(){
	FILE *f=fopen(file_name,"rb+");
	if(!f){
		printf("Data file not found - creating new file...\n");
		f=fopen(file_name,"wb+");
		getch();		
		fwrite(config,sizeof(char),7,f);
		int i=0;
		char j=0;
		fwrite(&i,sizeof(int),1,f);
		for(i=0;i<81;i++)
		fwrite(&j,sizeof(char),1,f);
	}else{
		fread(config,sizeof(char),7,f);
		char s[]="Color 07";
		s[6]=config[5];
		s[7]=config[6];
		system(s);
	}
	printf(" Current controls:\n\n");
	printf(" Left : %c\n",config[0]);
	printf(" Right : %c\n",config[1]);
	printf(" Up : %c\n",config[2]);
	printf(" Down : %c\n",config[3]);
	if(config[4]==13){
		printf(" Select : Enter\n");
	}else{
		printf(" Select : %c\n",config[4]);
	}
	fclose(f);
	getch();
	return 1;
}

void new_game(){
	char new_game_menu_header[]="NEW SUDOKU";
	char *new_game_menu[3]={"Chose random chart","Chose chart by number","Return to main menu"};
	char run_new_game_menu=1;
	int numb=0;
	FILE *f=fopen(file_name,"rb+");
	fseek(f,sizeof(char)*7,SEEK_SET);
	fread(&numb,sizeof(int),1,f);
	fclose(f);
	if(numb==0){
		printf("Add charts to data first!\n");
		getch();
		run_new_game_menu=0;
	}
	while(run_new_game_menu){
		switch(print_menu(new_game_menu_header,new_game_menu,3)){
			case 0:
				reset_position();
				srand(time(NULL));
				play_sudoku((rand()%numb)+1);
				break;
			case 1:
				reset_position();
				system("cls");
				printf("Number of charts: %d\nEnter chart number, from 1 to %d: ",numb,numb);
				int c=0;
				scanf("%d",&c);
				c--;
				if(c>=0&&c<numb){
					play_sudoku(c);
				}else{
					printf("Wrong number\n");
					getch();
				}
				break;
			case 2:
				reset_position();
				run_new_game_menu=0;
				break;
			case 3:
				break;
		}
	}
}

void load_game(){
	char i,j,c;
	char load_game_header[]="LOADED SUDOKU";
	char *load_game_menu[4]={"Check chart","Return to chart","Save sudoku and quit","Quit sudoku without saving"};
	char sudoku[9][9]={{0}};
	char solved[9][9]={{0}};
	unsigned char run_load_game_sudoku=1;
	unsigned char run_load_game_menu;
	FILE *f=fopen(file_name,"rb+");
	fseek(f,sizeof(char)*7+sizeof(int),SEEK_SET);
	fread(&solved[0][0],sizeof(char),81,f);
	fclose(f);
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(solved[i][j]>10){
				solved[i][j]-=10;
				sudoku[i][j]=solved[i][j];
			}
		}
	}
	while(run_load_game_sudoku){
		switch(print_sudoku(load_game_header,sudoku)){
			case 0:
				reset_position();
				run_load_game_menu=1;
				while(run_load_game_menu){
					switch(print_menu(load_game_header,load_game_menu,4)){
						case 0:
							reset_position();
							c=0;
							for(i=0;i<9;i++){
								for(j=0;j<9;j++){
									if(sudoku[i][j]&&sudoku[i][j]!=solved[i][j]){
										printf("Wrong number in row %d, column %d.\n",i+1,j+1);
											c++;
									}
								}
							}
							if(c==0)
							printf("No wrong numbers.\n");
							getch();
							break;
						case 1:
							reset_position();
							run_load_game_menu=0;
							break;
						case 2:
							reset_position();
							run_load_game_menu=0;
							run_load_game_sudoku=0;
							FILE *f=fopen(file_name,"rb+");
							fseek(f,sizeof(char)*7+sizeof(int),SEEK_SET);
							for(i=0;i<9;i++){
								for(j=0;j<9;j++){
									if(sudoku[i][j]==solved[i][j])
									solved[i][j]+=10;
								}
							}
							fwrite(&solved[0][0],sizeof(char),81,f);
							fclose(f);
							break;
						case 3:
							reset_position();
							run_load_game_menu=0;
							run_load_game_sudoku=0;
							break;
						case 4:
							break;
					}
				}
			case 1:
				break;
		}
	}
}

void add_new(){
	char i,j,c=0;
	char add_new_sudoku_header[]="ADDING NEW SUDOKU";
	char add_new_menu_header[]="NEW SUDOKU OPTIONS";
	char *add_new_menu[5]={"Solve sudoku","Add sudoku to data","Return to sudoku","Erase sudoku","Return to main menu"};
	unsigned char run_add_new_sudoku=1;
	unsigned char run_add_new_menu;
	char sudoku[9][9]={{9,0,5,0,0,0,0,0,8},{4,0,0,5,7,0,1,0,6},{0,2,7,6,0,0,0,4,0},{0,9,6,0,0,3,5,1,2},{7,0,4,0,1,0,3,0,0,},{2,1,0,9,8,0,0,0,4},{0,8,1,0,0,4,0,9,0},{3,0,0,8,0,0,0,5,1},{0,0,2,0,0,7,0,6,0}};
	//char sudoku[9][9]={{0}};
	char solved[9][9]={{0}};
	while(run_add_new_sudoku){
		switch(print_sudoku(add_new_sudoku_header,sudoku)){
			case 0:
				reset_position();
				run_add_new_menu=1;
				while(run_add_new_menu){
					switch(print_menu(add_new_menu_header,add_new_menu,5)){
						case 0:
							reset_position();
							for(i=0;i<9;i++){
								for(j=0;j<9;j++){
									if(sudoku[i][j])
									solved[i][j]=10;
								}
							}
							if(sudoku_solve(sudoku,0,0)){
								run_add_new_menu=0;
								for(i=0;i<9;i++){
									for(j=0;j<9;j++){
										solved[i][j]+=sudoku[i][j];
									}
								}
							} else{
								printf("Solving sudoku failed\nPress any key to continue...\n");
								run_add_new_menu=0;
								getch();
							}
							c=1;
							break;
						case 1:
							reset_position();
							if(!c){
								system("cls");
								printf("To add chart, chose solve option first.\n");
							}else{
								FILE *f=fopen(file_name,"rb+");
								int numb;
								fseek(f,sizeof(char)*7,SEEK_SET);
								fread(&numb,sizeof(int),1,f);
								numb++;
								fseek(f,sizeof(char)*7,SEEK_SET);
								fwrite(&numb,sizeof(int),1,f);
								fseek(f,0L,SEEK_END);
								fwrite(&solved[0][0],sizeof(char),81,f);
								fclose(f);
								printf("Chart has been added to database.\n");
							}										
							getch();
							break;
						case 2:
							reset_position();
							run_add_new_menu=0;
							break;
						case 3:
							for(i=0;i<9;i++){
								for(j=0;j<9;j++){
									sudoku[i][j]=0;
									solved[i][j]=0;
								}
							}
							c=0;
							break;
						case 4:
							reset_position();
							run_add_new_menu=0;
							run_add_new_sudoku=0;
							break;
						case 5:
							break;
					}
				}
			case 1:
				break;
		}
	}
}

void options(){
	char options_menu_header[]="OPTIONS MENU";
	char *options_menu[5]={"Change control scheme", "Change background and text color", "Return to main menu"};
	char options_options_control_menu_header[]="CHANGE CONTROL SCHEME";
	char *options_control_menu[]={"Left","Right","Up","Down","Select","Return to options menu"};
	char run_options_menu=1;
	char run_options_control_menu;
	while(run_options_menu){
		switch(print_menu(options_menu_header,options_menu,3)){
			case 0:
				reset_position();
				run_options_control_menu=1;
				while(run_options_control_menu){
					system("cls");
					printf("\t%s\n\n",options_options_control_menu_header);
					if(selecty==0){printf(" -->");}
					printf("\t%s\t= %c\n",options_control_menu[0],config[0]);
					if(selecty==1){printf(" -->");}
					printf("\t%s\t= %c\n",options_control_menu[1],config[1]);
					if(selecty==2){printf(" -->");}
					printf("\t%s\t= %c\n",options_control_menu[2],config[2]);
					if(selecty==3){printf(" -->");}
					printf("\t%s\t= %c\n",options_control_menu[3],config[3]);
					if(selecty==4){printf(" -->");}
					printf("\t%s\t= ",options_control_menu[4]);
					if(config[4]==13){printf("Enter\n");}
					else{printf("%c\n",config[4]);}
					if(selecty==5){printf(" -->");}
					printf("\t%s\n",options_control_menu[5]);
					char pressed=getch();
					if(pressed==config[2]){
						if(selecty==0){selecty=5;}
						else{selecty--;}
					}
					if(pressed==config[3]){
						if(selecty==5){selecty=0;}
						else{selecty++;}
					}
					if(pressed==config[4]){
						if(selecty>=0&&selecty<=4){
							system("cls");
							printf("Press new key\n");
							config[selecty]=getch();
							FILE *f=fopen(file_name,"rb+");
							fseek(f,sizeof(char)*selecty,SEEK_SET);
							fwrite(&config[selecty],sizeof(char),1,f);
							fclose(f);
							reset_position();
						}else if(selecty==5){
							run_options_control_menu=0;
							reset_position();
						}
					}
				}
				break;
			case 1:
				reset_position();
				system("cls");
				printf("CHANGE COLOR\nColor attributes are specified by TWO hex digits -- the first corresponds to the background; the second to the foreground. Each digit can be any of the folowing values:\n\n\t0 = Black\t\t8 = Gray\n\t1 = Blue\t\t9 = Light Blue\n\t2 = Green\t\tA = Light Green\n\t3 = Aqua\t\tB = Light Aqua\n\t4 = Red\t\t\tC = Light Red\n\t5 = Purple\t\tD = Light Purple\n\t6 = Yellow\t\tE = Light Yellow\n\t7 = White\t\tF = Bright White\n\n If no argument is given, default color scheme is restored\n\n Input color specifiers: ");
				char s[]="Color 07";
				FILE *f=fopen(file_name,"rb+");
				config[5]=getch();s[6]=config[5];printf("%c",config[5]);
				config[6]=getch();s[7]=config[6];printf("%c",config[6]);
				fseek(f,sizeof(char)*5,SEEK_SET);
				fwrite(&config[5],sizeof(char),2,f);
				fclose(f);
				getch();
				system(s);
				break;
			case 2:
				reset_position();
				run_options_menu=0;
				break;
			case 3:
				break;
		}
	}
}

void play_sudoku(int number){
	char i,j,c;
	char play_sudoku_header[20];sprintf(play_sudoku_header,"SUDOKU NR %d",number);
	char *play_sudoku_options_menu[4]={"Check sudoku","Return to sudoku","Save sudoku and quit","Quit sudoku without saving"};
	unsigned char run_play_sudoku=1;
	unsigned char run_play_sudoku_menu;
	char sudoku[9][9];
	char solved[9][9];
	FILE *f=fopen(file_name,"rb+");
	fseek(f,sizeof(char)*7+sizeof(int)+sizeof(char)*81*number,SEEK_SET);
	fread(&solved[0][0],sizeof(char),81,f);
	fclose(f);
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			if(solved[i][j]>10){
				solved[i][j]-=10;
				sudoku[i][j]=solved[i][j];
			}else{
				sudoku[i][j]=0;
			}
		}
	}
	while(run_play_sudoku){
		switch(print_sudoku(play_sudoku_header,sudoku)){
			case 0:
				reset_position();
				run_play_sudoku_menu=1;
				while(run_play_sudoku_menu){
					switch(print_menu(play_sudoku_header,play_sudoku_options_menu,4)){
						case 0:
							reset_position();
							c=0;
							for(i=0;i<9;i++){
								for(j=0;j<9;j++){
									if(sudoku[i][j]&&sudoku[i][j]!=solved[i][j]){
										printf("Wrong number ir row %d, column %d.\n",i+1,j+1);
										c++;
									}
								}
							}
							if(c==0)
							printf("No wrong numbers.\n");
							getch();
							break;
						case 1:
							reset_position();
							run_play_sudoku_menu=0;
							break;
						case 2:
							reset_position();
							run_play_sudoku_menu=0;
							run_play_sudoku=0;
							FILE *f=fopen(file_name,"rb+");
							fseek(f,sizeof(char)*7+sizeof(int),SEEK_SET);
							for(i=0;i<9;i++){
								for(j=0;j<9;j++){
									if(sudoku[i][j]==solved[i][j])
									solved[i][j]+=10;
								}
							}
							fwrite(&solved[0][0],sizeof(char),81,f);
							fclose(f);
							break;
						case 3:
							reset_position();
							run_play_sudoku_menu=0;
							run_play_sudoku=0;
							break;
						case 4:
							break;
					}
				}
			case 1:
				break;
		}
	}
}

char print_menu(char* header, char *menus[], char length){
	system("cls");
	printf("\t%s\n\n",header);
	unsigned char i;
	for(i=0;i<length;i++){
		if(selecty==i){printf(" -->");}
		printf("\t%s\n",menus[i]);
	}
	char pressed=getch();
	if(pressed==config[2]){
		if(selecty==0){selecty=length-1;}
		else{selecty--;}
	}
	if(pressed==config[3]){
		if(selecty==length-1){selecty=0;}
		else{selecty++;}
	}
	if(pressed==config[4]){
		return selecty;
	}
	return length;
}

char print_sudoku(char *header, char sudoku[9][9]){
	system("cls");
	printf("\t   %s\n\n",header);
	unsigned char i,j,r=1;
	printf("\t%c",201);	for(i=0;i<7;i++){printf("%c",205);}	printf("%c",203);	for(i=0;i<7;i++){printf("%c",205);}	printf("%c",203);	for(i=0;i<7;i++){printf("%c",205);}	printf("%c\n",187);
	for(i=0;i<9;i++){
		printf("\t%c       %c       %c       %c\n",186,186,186,186);
		printf("\t%c",186);
		for(j=0;j<9;j++){
			if(selectx==j&&selecty==i){
				if(sudoku[i][j]==0){printf(">_");}
				else{printf(">%d",sudoku[i][j]);}
			} else{
				if(sudoku[i][j]==0){printf(" _");}
				else{printf(" %d",sudoku[i][j]);}
			}
			if(j%3==2) printf(" %c",186);
		}
		printf("\n");
		if(i==2||i==5){
			printf("\t%c       %c       %c       %c\n",186,186,186,186);
			printf("\t%c",204);	for(j=0;j<7;j++){printf("%c",205);}	printf("%c",206);	for(j=0;j<7;j++){printf("%c",205);}	printf("%c",206);	for(j=0;j<7;j++){printf("%c",205);}	printf("%c\n",185);
		}
	}
	printf("\t%c       %c       %c       %c\n",186,186,186,186);
	printf("\t%c",200);	for(i=0;i<7;i++){printf("%c",205);}	printf("%c",202);	for(i=0;i<7;i++){printf("%c",205);}	printf("%c",202);	for(i=0;i<7;i++){printf("%c",205);}	printf("%c\n",188);
	char pressed=getch();
	if(pressed==config[0]){
		if(selectx==0){selectx=8;}
		else{selectx--;}
	}
	if(pressed==config[1]){
		if(selectx==8){selectx=0;}
		else{selectx++;}
	}
	if(pressed==config[2]){
		if(selecty==0){selecty=8;}
		else{selecty--;}
	}
	if(pressed==config[3]){
		if(selecty==8){selecty=0;}
		else{selecty++;}
	}
	if(pressed>=48&&pressed<=57){
		sudoku[selecty][selectx]=pressed-48;
	}
	if(pressed==config[4]){
		r=0;
	}
	return r;
}

char sudoku_solve(char sudoku[][9], char row, char col){
	char i,j,c,v;
	if(row==9){
		return 1;
	}
	if(sudoku[row][col]){
		if(col==8){
			return sudoku_solve(sudoku,row+1,0);
		}
		else if(col<9){
			return sudoku_solve(sudoku,row,col+1);
		} else{
			return 1;
		}
	} else{
		for(v=1;v<10;v++){
			c=1;
			for(i=0;i<9;i++){
				if(sudoku[row][i]==v||sudoku[i][col]==v){
					c=0;
				}
			}
			for(i=0;i<3;i++){
				for(j=0;j<3;j++){
					if(sudoku[row/3*3+i][col/3*3+j]==v){
						c=0;
					}
				}
			}
			if(c){
				sudoku[row][col]=v;
				if(col==8){
					if(sudoku_solve(sudoku,row+1,0)) return 1;
					else sudoku[row][col]=0;
				}else if(col<8){
					if(sudoku_solve(sudoku,row,col+1)) return 1;
					else sudoku[row][col]=0;
				} else{
					return 1;
				}
			}
		}
	}
	return 0;
}

void reset_position(){
	selectx=0;
	selecty=0;
}

char getch(){
	HANDLE hStdin = GetStdHandle (STD_INPUT_HANDLE);
	INPUT_RECORD irInputRecord;
	DWORD dwEventsRead;
	CHAR cChar;

	while(ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */
	if (irInputRecord.EventType == KEY_EVENT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU
	&&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
    {
		cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar;
		ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */
		return cChar;
    }
	return EOF;
}