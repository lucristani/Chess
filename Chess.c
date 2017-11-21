/*Chess*/
#include <stdio.h>
#include <string.h>
#define M 16
#define N 8
/* ♔ ♕ ♖ ♗ ♘ ♙ ♚ ♛ ♜ ♝ ♞ ♟ */
typedef struct {						//chess piece 
	char name;
	char img[4];																					
	int xpos;
	int ypos;
	int capt;
	int move[N][N];
}ChessPiece;
struct Player{
	ChessPiece pl[M];
	int checkmate;
	int check;
};
typedef struct {								//chessboard
	ChessPiece Chessboard[N][N];
}chessboard;
int menu(){									//menu function
	int a=0;
	printf("Gamemode?\n 1. Two players\n");
	scanf("%d", &a);
	if(a==1)
		return 1;
	return 0;
}
void printcb(chessboard*a){						//chessboard output visualization
	int i=0, j=0;
	for(i=0; i<N; i++){														
		printf("\n");
		for(j=0; j<N; j++)
			printf(" %s ", a->Chessboard[i][j].img);
	}
}
void InMv(struct Player*a, int l ){			//move inizializer
	int i=0, j=0;
		for(i=0; i<N; i++){		//rows 
			for(j=0; j<N; j++){		//columns
				a->pl[l].move[i][j]=0;
			}
		}
}
void PcsMv(struct Player*a, struct Player*b, int l){			//move for all different pieces
	int i=0, j=0; 
	char k=a->pl[l].name;
	switch(k){
		case('p'):{
			InMv(a,l);
			if(strcmp(a->pl[l].img,"♟")==1){
				for(i=0; i<M; i++){
					if((b->pl[i].xpos==(a->pl[l].xpos+1) || b->pl[i].ypos==(a->pl[l].xpos-1)) && (b->pl[i].ypos==(a->pl[l].ypos+1))){
					a->pl[l].move[b->pl[i].xpos][b->pl[i].ypos]=1;
					}
					if((a->pl[i].xpos==(a->pl[l].xpos+1) || a->pl[i].xpos==(a->pl[l].xpos-1)) && (a->pl[i].ypos==(a->pl[l].ypos+1))){
					a->pl[l].move[a->pl[i].xpos][a->pl[i].ypos]=-1;
					}
					if((b->pl[i].xpos==(a->pl[l].xpos)) && (b->pl[i].ypos==(a->pl[l].ypos+1))){
					a->pl[l].move[b->pl[i].xpos][b->pl[i].ypos]=1;
					}
					if((a->pl[i].xpos==(a->pl[l].xpos)) && (a->pl[i].ypos==(a->pl[l].ypos+1))){
					a->pl[l].move[a->pl[i].xpos][a->pl[i].ypos]=-1;
					}
					else{
						a->pl[l].move[a->pl[l].xpos][a->pl[l].ypos+1]=1;
					}
				}
				if(a->pl[l].ypos==1){
					for(i=0; i<M; i++){
						if(b->pl[i].xpos==(a->pl[l].xpos) && (b->pl[i].ypos==(a->pl[l].ypos+2)))
							a->pl[l].move[(a->pl[l].xpos)][(a->pl[l].ypos)+2]=0;
						else if(a->pl[i].xpos==(a->pl[l].xpos) && (a->pl[i].ypos==(a->pl[l].ypos+2)))
							a->pl[l].move[(a->pl[l].xpos)][(a->pl[l].ypos)+2]=-1;
					}
				}
			}
			else{
				if(strcmp(a->pl[l].img,"♙")==1){
					for(i=0; i<M; i++){
						if((b->pl[i].xpos==(a->pl[l].xpos+1) || b->pl[i].ypos==(a->pl[l].xpos-1)) && (b->pl[i].ypos==(a->pl[l].ypos-1))){
						a->pl[l].move[b->pl[i].xpos][b->pl[i].ypos]=1;
						}
						if((a->pl[i].xpos==(a->pl[l].xpos+1) || a->pl[i].xpos==(a->pl[l].xpos-1)) && (a->pl[i].ypos==(a->pl[l].ypos-1))){
						a->pl[l].move[a->pl[i].xpos][a->pl[i].ypos]=-1;
						}
						if((b->pl[i].xpos==(a->pl[l].xpos)) && (b->pl[i].ypos==(a->pl[l].ypos-1))){
						a->pl[l].move[b->pl[i].xpos][b->pl[i].ypos]=1;
						}
						if((a->pl[i].xpos==(a->pl[l].xpos)) && (a->pl[i].ypos==(a->pl[l].ypos-1))){
						a->pl[l].move[a->pl[i].xpos][a->pl[i].ypos]=-1;
						}
						else{
							a->pl[l].move[a->pl[l].xpos][a->pl[l].ypos-1]=1;
						}	
					}
					if(a->pl[l].ypos==1){
						for(i=0; i<M; i++){
							if(b->pl[i].xpos==(a->pl[l].xpos) && (b->pl[i].ypos==(a->pl[l].ypos-2)))
								a->pl[l].move[(a->pl[l].xpos)][(a->pl[l].ypos)-2]=0;
							else if(a->pl[i].xpos==(a->pl[l].xpos) && (a->pl[i].ypos==(a->pl[l].ypos-2)))
								a->pl[l].move[(a->pl[l].xpos)][(a->pl[l].ypos)-2]=-1;
						}
					}
				}
						}
			break;
		}
		case('r'):{
			InMv(a,l);
			for(i=0; i<N-(a->pl[l].xpos); i++){														//rook start
				for(j=0; j<M; j++){
					if(((a->pl[l].xpos+i)==b->pl[j].xpos) && (a->pl[l].ypos==b->pl[j].ypos)){
						a->pl[l].move[(a->pl[l].xpos+i)][(a->pl[l].ypos)]=1;
						break;
					}
					if(((a->pl[l].xpos+i)==a->pl[j].xpos) && (a->pl[l].ypos==a->pl[j].ypos)){
						a->pl[l].move[(a->pl[l].xpos+i)][(a->pl[l].ypos)]=-1;
						break;
					}
					else{ 
						a->pl[l].move[(a->pl[l].xpos+i)][(a->pl[l].ypos)]=1;
					}
				}
			}
			for(i=0; i<a->pl[l].xpos; i++){
				for(j=0; j<M; j++){
					if(((a->pl[l].xpos-i)==b->pl[j].xpos) && (a->pl[l].ypos==b->pl[j].ypos)){
						a->pl[l].move[(a->pl[l].xpos+i)][(a->pl[l].ypos)]=1;
						break;
					}
					if(((a->pl[l].xpos-i)==a->pl[j].xpos) && (a->pl[l].ypos==a->pl[j].ypos)){
						a->pl[l].move[(a->pl[l].xpos-i)][(a->pl[l].ypos)]=-1;
						break;
					}
					a->pl[l].move[(a->pl[l].xpos-i)][(a->pl[l].ypos)]=1;
				}
			}
			for(i=0; i<a->pl[l].ypos; i++){
				for(j=0; j<M; j++){
					if(((a->pl[l].ypos-i)==b->pl[j].ypos) && (a->pl[l].xpos==b->pl[j].xpos)){
						a->pl[l].move[(a->pl[l].ypos+i)][(a->pl[l].xpos)]=1;
						break;
					}
					if(((a->pl[l].ypos-i)==a->pl[j].ypos) && (a->pl[l].xpos==a->pl[j].xpos)){
						a->pl[l].move[(a->pl[l].ypos-i)][(a->pl[l].xpos)]=-1;
						break;
					}
					a->pl[l].move[(a->pl[l].ypos-i)][(a->pl[l].xpos)]=1;
				}
			}
			for(i=0; i<N-a->pl[l].ypos; i++){
				for(j=0; j<M; j++){
					if(((a->pl[l].ypos+i)==b->pl[j].ypos) && (a->pl[l].xpos==b->pl[j].xpos)){
						a->pl[l].move[(a->pl[l].ypos+i)][(a->pl[l].xpos)]=1;
						break;
					}
					if(((a->pl[l].ypos+i)==a->pl[j].ypos) && (a->pl[l].xpos==a->pl[j].xpos)){
						a->pl[l].move[(a->pl[l].ypos+i)][(a->pl[l].xpos)]=-1;
						break;
					}
					a->pl[l].move[(a->pl[l].ypos+i)][(a->pl[l].xpos)]=1;
				}
			}
			break;	
		}																							//rook end
		case('k'):{													//knights start
			InMv(a,l);
			break;	
			
		}															//knights end
		case('b'):{																					//bishop start 
			InMv(a,l);
			break;	
		}																							//bishop end
		case('q'):{									//queen start
			InMv(a,l);
			break;	
	}											//queen end
		case('K'):{																					//king start
			InMv(a,l);
			for(i=0; i<3; i++){
				for(j=0; j<3; j++){
					if(i==1 && j==1)
						j++;
					else{
						for(k=0;k<M;k++){
							if(a->pl[k].xpos==i && a->pl[k].ypos==j)
								a->pl[l].move[(a->pl[l].xpos)-(i-1)][(a->pl[l].ypos)-(j-1)]=-1;
							else							
								a->pl[l].move[(a->pl[l].xpos)-(i-1)][(a->pl[l].ypos)-(j-1)]=1;
						}
					}
				}
			}
			break;
		}																							//king end
	}
}
void AskMv(int *x, int *y, char *g){						//move asker
	int a, b;
	char c;
	char m;
	printf("\nYour move, Sir. Chess piece x-position\n");
	scanf("%d", &a);
	printf("\nYour move, Sir. Chess piece y-position\n");
	scanf("%d", &b);
	printf("\nYour move, Sir. Chess piece first\n");
	scanf("%c", &m);
	scanf("%c", &c);
	*x=a;
	*y=7-b;
	*g=c;
}
int searchm(struct Player*a, chessboard*c, ChessPiece*d, int x, int y, char m, int *n){		//move verifier: valid or not. if valid move else not
	int i=0, flag=0, l=0;
	for(i=0;i<M;i++){
		if(a->pl[i].move[x][y]==1 && a->pl[i].name==m){
			flag++;
			l=i;			
		}
	}
	if(flag==1){
		c->Chessboard[x][y]=a->pl[l];
		c->Chessboard[a->pl[l].xpos][a->pl[l].ypos]=*d;
		a->pl[i].xpos=x;
		a->pl[i].ypos=y;
		*n=l;
	}
	if(flag>1){
			return -1;
	}
return flag;
}
int checks(int x, int y, struct Player*a){									//check verifier function
	int i=0;
	for(; i<M; i++){		//player's chess pieces
		if(a->pl[i].move[x][y]==1 || (x<0 || x>N) || (y<0 || y>N))
			return 1;
	}
	return 0;
}
int Surrp(int x, int y, struct Player*a){							//surroun verifier function: looks for pieces around a piece
	int i=0, j=0, k=0;
	for(i=0; i<3; i++){				//3 by 3 matrix: rows
		for(j=0; j<3; j++){					//3 by 3 matrix: rows
			if(i==1 && j==1)					//skip central slot
				j++;
			else{
				for(k=0;k<M;k++){
					if((a->pl[k].xpos==x && a->pl[k].ypos==y) && checks(x,y,a))
						return 1;
				}
			}
		}
	}
	return 0;
}
void checkm(struct Player*a,struct Player*b){				//checkmate verifier function
	int i=0, j=0;
		if(a->check==1){
			for(i=0; i<3; i++){			//rows
				for(j=0; j<3; j++){			//columns
					if(i==1 && j==1)
						j++;
					else{
						if((checks(((a->pl[12].xpos)-(i-1)),((a->pl[12].ypos)-(j-1)), b)==1) ||
						Surrp(a->pl[12].xpos, a->pl[12].ypos, a) || (Surrp(a->pl[12].xpos, a->pl[12].ypos, b))){
							a->checkmate=1;
						}
						else
							a->checkmate=0;
					}
				}
			}
					
		}
}											//main match function: game is actually played completly in this function
int matcht(struct Player*a,struct Player*b,chessboard*c, ChessPiece*d){						     																		
	int t=1, x=0, y=0, i=0, n=0, xp=0, yp=0;
	char g=0;
	PcsMv(a, b, 0);
	for(i=0; i<N; i++){														
		printf("\n");
		for(int j=0; j<N; j++)
			printf(" %d ", b->pl[0].move[i][j]);
	}
	while(a->checkmate!=1 && b->checkmate!=1){
		if(t){									//player "b": pl1
			printf("\nPlayer 1:\n");
			for(i=0; i<M; i++)
				PcsMv(a, b, i);
			AskMv(&x,&y,&g);
			if(searchm(b, c, d, x, y, g, &n)==1){
					searchm(b, c, d, x, y, g, &n);
					t=0;
				}
			while(searchm(b, c, d, x, y, g, &n)==-1){			//move not valid: ask again
				printf("\nWhich piece?\n");
				printf("\nx-pos?\n");
				scanf("%d", &xp);
				printf("\ny-pos?\n");
				scanf("%d", &yp);
				for(i=0;i<N; i++){
					if(b->pl[i].xpos==xp && b->pl[i].ypos==yp){			//do a valid move
						c->Chessboard[x][y]=b->pl[i];
						c->Chessboard[b->pl[i].xpos][b->pl[i].ypos]=*d;
						b->pl[i].xpos=x;
						b->pl[i].ypos=y;
						t=0;
					}		
				}
			}
			while(searchm(b, c, d, x, y, g, &n)==0)													//end turn
				AskMv(&x,&y,&g);
			searchm(b, c, d, x, y, g, &n);
			if(checks((a->pl[12].xpos),(a->pl[12].ypos), b)==1)
				printf("\nCheck!\n");
			checkm(a,b);
		}
		else{											//player "w": pl2
			printf("\nPlayer 2:\n");
			for(i=0; i<M; i++)
				PcsMv(b, a, i);
			AskMv(&x,&y,&g);
			if(searchm(a, c, d, x, y, g, &n)==1){
				searchm(a, c, d, x, y, g, &n);
				t=1;
			}
			while(searchm(a, c, d, x, y, g, &n)==-1){			//move not valid: ask again
				printf("\nWhich piece?\n");
				printf("\nx-pos?\n");
				scanf("%d", &xp);
				printf("\ny-pos?\n");
				scanf("%d", &yp);
				for(i=0;i<N; i++){
					if(a->pl[i].xpos==xp && a->pl[i].ypos==yp){		//do a valid move
						c->Chessboard[x][y]=a->pl[i];
						c->Chessboard[a->pl[i].xpos][a->pl[i].ypos]=*d;
						a->pl[i].xpos=x;
						a->pl[i].ypos=y;
						t=1;
					}		
				}
			}
			while(searchm(a, c, d, x, y, g, &n)==0)													//end turn
				AskMv(&x,&y,&g);
			searchm(a, c, d, x, y, g, &n);
			if(checks((b->pl[12].xpos),(b->pl[12].ypos), a)==1)
				printf("\nCheck!\n");
			checkm(b,a);			
		}	
		printcb(c);						//chessboard output
	}
	printf("\nCheckmate!\n");
	return 0;
}
int main(){											//main function: chess pieces inizialization and matcht function call
	int i=0, j=0;
	struct Player pl1, pl2;
	chessboard chessb;
	ChessPiece zero;
	zero.name='0';					    //chess pieces inizialization
	strcpy(zero.img, "0");
	pl1.checkmate=0;
	pl2.checkmate=0;
	for(i=0; i<N; i++){									//pawns														
		pl1.pl[i].capt=0;
		pl2.pl[i].capt=0;
		pl1.pl[i].name='p';
		pl2.pl[i].name='p';
		strcpy(pl1.pl[i].img, "♟");
		strcpy(pl2.pl[i].img, "♙");
	}
	for(i=8; i<M; i+=7){								//rooks
		pl1.pl[i].capt=0;
		pl2.pl[i].capt=0;
		pl1.pl[i].name='r';
		pl2.pl[i].name='r';
		strcpy(pl1.pl[i].img, "♜");
		strcpy(pl2.pl[i].img, "♖");
	}
	for(i=9; i<M; i+=5){								//kinghts
		pl1.pl[i].capt=0;
		pl2.pl[i].capt=0;
		pl1.pl[i].name='k';
		pl2.pl[i].name='k';
		strcpy(pl1.pl[i].img, "♞");
		strcpy(pl2.pl[i].img, "♘");
	}
	for(i=10; i<M; i+=3){								//bishops
		pl1.pl[i].capt=0;
		pl2.pl[i].capt=0;
		pl1.pl[i].name='b';
		pl2.pl[i].name='b';
		strcpy(pl1.pl[i].img, "♝");
		strcpy(pl2.pl[i].img, "♗");
	}
	
	pl1.pl[11].capt=0;									//queens
	pl2.pl[11].capt=0;
	pl1.pl[11].name='q';
	pl2.pl[11].name='q';
	strcpy(pl1.pl[11].img, "♛");
	strcpy(pl2.pl[11].img, "♕");
	
	pl1.pl[12].capt=0;									//kings
	pl2.pl[12].capt=0;
	pl1.pl[12].name='K';
	pl2.pl[12].name='K';
	strcpy(pl1.pl[12].img, "♚");
	strcpy(pl2.pl[12].img, "♔");
																 																								
	for(i=0; i<N; i++){				//pawns
		pl1.pl[i].xpos=i;
	}
	for(i=0; i<N; i++){
		pl1.pl[i].ypos=1;
	}	
	for(i=0; i<N; i++){
		pl2.pl[i].xpos=i;
	}
	for(i=0; i<N; i++){
		pl2.pl[i].ypos=6;
	}
	for(i=8; i<M; i+=7){			//rooks
		pl1.pl[i].xpos=i-8;
	}
	for(i=8; i<M; i+=7){
		pl1.pl[i].ypos=0;
	}
	for(i=8; i<M; i+=7){
		pl2.pl[i].xpos=i-8;
	}
	for(i=8; i<M; i+=7){
		pl2.pl[i].ypos=7;
	}
	for(i=9; i<M; i+=5){			//knights
		pl1.pl[i].xpos=i-8;
	}
	for(i=9; i<M; i+=5){
		pl1.pl[i].ypos=0;
	}
	for(i=9; i<M; i+=5){
		pl2.pl[i].xpos=i-8;
	}
	for(i=9; i<M; i+=5){
		pl2.pl[i].ypos=7;
	}
	for(i=10; i<M; i+=3){			//bishops
		pl1.pl[i].xpos=i-8;
	}
	for(i=10; i<M; i+=3){
		pl1.pl[i].ypos=0;
	}
	for(i=10; i<M; i+=3){
		pl2.pl[i].xpos=i-8;
	}
	for(i=10; i<M; i+=3){
		pl2.pl[i].ypos=7;
	}
	
	pl1.pl[11].xpos=4;				//queens
	pl1.pl[11].ypos=0;
	pl2.pl[11].xpos=4;				
	pl2.pl[11].ypos=7;
	
	pl1.pl[12].xpos=3;				//kings
	pl1.pl[12].ypos=0;
	pl2.pl[12].xpos=3;				
	pl2.pl[12].ypos=7;
	
	for(i=0; i<N; i++){				//chessboard inizializer: chesspiece zero
		for(j=0; j<N; j++){
			chessb.Chessboard[i][j]=zero;
		}
	}
	for(i=0; i<M; i++){								//chessboard inizializer: player 1
		chessb.Chessboard[pl1.pl[i].ypos][pl1.pl[i].xpos]=pl1.pl[i];
	}
	for(i=0; i<M; i++){								//chessboard inizializer: player 2
		chessb.Chessboard[pl2.pl[i].ypos][pl2.pl[i].xpos]=pl2.pl[i];
	}
	printcb(&chessb);
	printf("\n\n");
	if(menu())										//matcht call													
		matcht(&pl1, &pl2, &chessb, &zero);
	return 0;																								
}																						