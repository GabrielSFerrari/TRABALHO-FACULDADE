#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define TF 12
//Gabriel Da Silva Ferrari
//Bruno Lenardon Balotari
//Giovane José Capeloti
struct TpElemento{
	int cor, x, y, pontos;
	char simbolo;
};

struct TpData{		//Define a data
	int d, m, a;
};

struct TpJog{			//Dados do jogador
	char Nome[30];
	TpData Data;
	int Pontuacao;
};

void LimpaTela(void)
{
	int i,j;	
	for(i=32;i<72;i++)
		for(j=10;j<22;j++)
		{
			gotoxy(i,j);printf(" ");
		}	
}

void LimpaMenu(void)
{
	int i,j;
	for(i=13;i<30;i++)
		for(j=10;j<22;j++)
		{
			gotoxy(i,j);printf(" ");
		}	
}

 void Moldura(int CI, int LI, int CF, int LF, int Frente, int Fundo)	//Faz a moldura e menu do jogo
{
	int a;
	
	textcolor(Frente);
	textbackground(Fundo);
	gotoxy(CI,LI);  printf("%c",201);
	gotoxy(CF,LI);  printf("%c",187);
	gotoxy(CI,LF);  printf("%c",200);
	gotoxy(CF,LF);  printf("%c",188);
	for(a=CI+1; a<CF; a++)
	{
		gotoxy(a,LI);  printf("%c",205);
		gotoxy(a,LF);  printf("%c",205);
	}
	for(a=LI+1; a<LF; a++)
	{
		gotoxy(CI,a);  printf("%c",186);
		gotoxy(CF,a);  printf("%c",186);
	}
	textcolor(12);
	textbackground(0);
}

void FormPrincipal(void) //chama moldura e passa valores de cores
{
	clrscr();
	Moldura(10,5,75,23,15,8);
	Moldura(12,6,73,8,15,0);
	gotoxy(35,7);  printf("# # # JOGO # # #");
	Moldura(12,9,30,22,15,12);
}

void RelJog(TpJog jog[TF], int qtde) //Exibir jogadores
{
	int a, i;
	gotoxy(38,10); printf("   # # # JOGADORES # # #  ");
	if(qtde == 0)
	{
		gotoxy(35,15); printf("Nao ha jogadores!!");
	}
		
	else
	{
		
			for(a=0, i=11; a<qtde; a++, i++)
			{
				gotoxy(35,i);printf("Nome: %s\n", jog[a].Nome);
				i++;
				gotoxy(35,i);printf("Pontuacao: %d\n",  jog[a].Pontuacao);
				i++;
				gotoxy(35,i);printf("Data: %d/ %d/ %d\n", jog[a].Data.d, jog[a].Data.m, jog[a].Data.a);
				i++;
			}
	}

	getch();
}
int gerarelementos(TpElemento tabelem[TF]) //Gera os elementos na tela de jogar
{
	int i;
	for(i = 1; i < TF; i++)
	{
		
		tabelem[i].cor = rand()%14+2; //cria valores aleatorios para cada variavel
		tabelem[i].simbolo = rand()%4+3;
		tabelem[i].x = rand()%39+33;
		tabelem[i].y = rand()%8+11;
		tabelem[i].pontos = (rand()%3+1) * 10;
	}

}

int BuscaNomeJogador(TpJog TabJog[TF],int TL,char NOME[30]) //Busca jogador
{
	int i=0;
	while(i<TL && stricmp(TabJog[i].Nome,NOME)!=0)
		i++;
	if(i<TL)
		return i;
	else
		return -1;
}

void cadjog(TpJog TabJog[TF], int &tl){ //cadastra jogadore
	char auxnome[30];
	int i;
	gotoxy(38,10);printf(" ** Cadastro de Jogadores ** ");
	gotoxy(35,11);printf("Nome: "); fflush(stdin);
	gets(auxnome);
	i=BuscaNomeJogador(TabJog,tl,auxnome);
	while(tl<TF && strcmp(auxnome, "\0") != 0 && i==-1)
	{
		strcpy(TabJog[tl]. Nome, auxnome);
		TabJog[tl].Pontuacao = 0;
		gotoxy(35,12);printf("Data (dd mm aaaa): ");
		scanf("%d %d %d", &TabJog[tl].Data.d, &TabJog[tl].Data.m, &TabJog[tl].Data.a);
		LimpaTela();
		tl++;
		gotoxy(38,10);printf(" ** Cadastro de Jogadores ** ");
		gotoxy(35,11);printf("Nome: "); fflush(stdin);
		gets(auxnome);
		i=BuscaNomeJogador(TabJog,tl,auxnome);			
	}
	if(i!=-1)
	{
		gotoxy(35,12);
		printf("Nome ja cadastrado");
		getche();
	}
}

void Exclusao(TpJog TabJog[TF], int &TL) //Exclui jogador
{
	char AuxNome[30];
	int pos;
	gotoxy(38,10);printf("## Exclusao de Jogadores ##");
	gotoxy(35,11);printf("Nome a Excluir: ");
	fflush(stdin);
	gets(AuxNome);
	while(TL>0 && strcmp(AuxNome,"\0")!=0)
	{
		pos = BuscaNomeJogador(TabJog,TL,AuxNome);
		if(pos==-1)
		{
			gotoxy(35,15);printf("Nome nao encontrado!");
			Sleep(2000);
			LimpaTela();
		}
		else
			{
				gotoxy(38,13);printf("# # # Dados do Jogador # # #");
				gotoxy(35,14);printf("Nome: %s",TabJog[pos].Nome);
				gotoxy(35,15);printf("Data: %d %d %d",TabJog[pos].Data.d, TabJog[pos].Data.m, TabJog[pos].Data.a);
				gotoxy(35,16);printf("Pontuacao: %d",TabJog[pos].Pontuacao);
				gotoxy(35,17);printf("Confirma Exclusao (S/N)? ");
				if (toupper(getch())=='S')
				{
					for( ;pos<TL-1; pos++)
						TabJog[pos] = TabJog[pos+1];
					
					TL--;
					gotoxy(35,20);printf("Jogador Excluido!");
					Sleep(2000);		
					LimpaTela();
				}
			}
		
		gotoxy(38,10);printf("## Exclusao de Jogadores ##");	
		gotoxy(35,11);printf("Nome a Excluir: ");
		fflush(stdin);
		gets(AuxNome);	
	}
}
 
void mostrarElementos(TpElemento tabelem[TF])
{
	int i;
	for(i = 0; i < TF; i++)
	{
		gotoxy(tabelem[i].x, tabelem[i].y);
		textcolor(tabelem[i].cor);
		printf("%c", tabelem[i].simbolo);
		//printf("%c%d%d",tabelem[i].simbolo,tabelem[i].x,tabelem[i].y);
	}
	textcolor(7);
}

int colisao(TpElemento tabelem[TF],int col,int tiro,int TL)
{
	int i=0;	
	while((col!=tabelem[i].x || tiro!=tabelem[i].y) && i<TL)
		i++;
	if(i<TL)
		return i;
	else
		return -1;
}

int RemanejaElementos(int i,int TL,TpElemento tabelem[TF])
{
	for(i=i; i<TL; i++)
	{
		tabelem[i].cor = tabelem[i+1].cor;
		tabelem[i].simbolo = tabelem[i+1].simbolo;
		tabelem[i].x = tabelem[i+1].x;
		tabelem[i].y = tabelem[i+1].y;
		tabelem[i].pontos = tabelem[i+1].pontos;	
	}
}

void jogar(TpJog TabJog[TF],int TL) //inia o jogo
{
	gotoxy(13,10); printf("Esperando...");
	char simbjog = 1, tecla, tiro,AuxNome[30];;
	int col=40,i,pt=0,TLE=TF,pos;
	TpElemento tabelem[TF];
	gotoxy(34,11);
	printf("Digite o nome do jogador a jogar:");
	gotoxy(34,12);
	fflush(stdin);
	gets(AuxNome);
	pos = BuscaNomeJogador(TabJog,TL,AuxNome);
	if(pos==-1)
	{
		gotoxy(34,13);
		printf("Jogador nao encontrado");
		getche();
	}
	else
	{
		LimpaMenu();
		LimpaTela();
		gotoxy(13,10); printf("Jogador-%s",AuxNome);
		gerarelementos(tabelem);
		mostrarElementos(tabelem);
		do
		{
			int v;
			gotoxy(13,11); printf("Pontos:%d",pt);
			gotoxy(27,12); printf(" ");
			gotoxy(13,12); printf("Qtd inimigos:%d",TLE-1);
			gotoxy(13,13); printf("Total Pontos:%d",pt+TabJog[pos].Pontuacao);
			gotoxy(col, 21); printf("%c", simbjog);
			textcolor(WHITE);
			tecla = getch();
			gotoxy(col, 21); printf(" ");
			switch(toupper(tecla))
			{
				case 'A': if (col>32) col--;
						  break;
					
				case 'D': if (col<72) col++;
						  break;
				
				case ' ': for(tiro = 20; tiro >= 10; tiro--)
						  {
								textcolor(15);
								gotoxy(col, tiro);
								printf("|");
								Sleep(80);
								gotoxy(col, tiro);	
								printf(" ");
								i=colisao(tabelem,col,tiro,TLE);	
								if(i!=-1)
								{
									pt+=tabelem[i].pontos;
									RemanejaElementos(i,TLE,tabelem);
									tiro=0;
									TLE--;	
								}
						  }
						  break;
			}
		}while(tecla != 27 && TLE !=1);
		TabJog[pos].Pontuacao+=pt;
		if(TLE==1)
		{
			gotoxy(45,15);
			printf("Voce Ganhou...");
			getche();
		}
		LimpaMenu();
	}
	//gotoxy(28,11); printf(" ");
	
}

void OrdenarJogador(TpJog TabJog[TF],int TL)
{
	int a,b;
	TpJog aux;
	for(a=0;a<TL-1;a++)
		for(b=a+1;b <TL;b++)
			if(stricmp(TabJog[a].Nome,TabJog[b].Nome)>0)
			{
				//Troca
				aux = TabJog[a];
				TabJog[a] = TabJog[b];
				TabJog[b] = aux;
			}
}

void OrdenarRanking(TpJog TabJog[TF],int TL)
{
	int a,b;
	TpJog aux;
	for(a=0;a<TL-1;a++)
		for(b=a+1;b <TL;b++)
			if(TabJog[a].Pontuacao<TabJog[b].Pontuacao)
			{
				//Troca
				aux = TabJog[a];
				TabJog[a] = TabJog[b];
				TabJog[b] = aux;
			}
}

void ConsultaJogadorNome(TpJog TabJog[TF], int TL) //Colsulta status do jogador
{
    char nome[30];
    int pos;
    
    gotoxy(34,10); printf("## Consulta de Jogadores pelo Nome ##");
    gotoxy(35,11); printf("Nome: ");
    fflush(stdin);
    gets(nome);
    pos = BuscaNomeJogador(TabJog, TL, nome);
    if (pos != -1) 
	{
		LimpaTela();
        gotoxy(37,10);printf(" # # # Dados do Jogador # # #");
        gotoxy(35,11);printf("Nome: %s\n", TabJog[pos].Nome);
        gotoxy(35,12);printf("Data: %d/%d/%d\n", TabJog[pos].Data.d, TabJog[pos].Data.m, TabJog[pos].Data.a);
        gotoxy(35,13);printf("Pontuacao: %d\n", TabJog[pos].Pontuacao);
    } else 
	{
		LimpaTela();
		gotoxy(34,10); printf("## Consulta de Jogadores pelo Nome ##");
        gotoxy(35,13); printf("Jogador nao encontrado!");
    }
    getch();
}

void AlterarJogador(TpJog TabJog[TF], int TL) //Altera jogador
{
    char nome[30];
    int pos;
    gotoxy(34,10);printf("## Alteracao de Jogadores pelo Nome ##");
    gotoxy(35,11);printf("Nome: ");
    fflush(stdin);
    gets(nome);
    pos = BuscaNomeJogador(TabJog, TL, nome);
    if (pos != -1) 
	{
		LimpaTela();
        gotoxy(38,10);printf("## Dados do Jogador ##");
        gotoxy(35,11);printf("Nome: %s\n", TabJog[pos].Nome);
        gotoxy(35,12);printf("Data: %d/%d/%d\n", TabJog[pos].Data.d, TabJog[pos].Data.m, TabJog[pos].Data.a);
        gotoxy(35,13);printf("Pontuação: %d\n", TabJog[pos].Pontuacao);

        gotoxy(35,15);printf("Digite os novos dados:");
        gotoxy(36,16);printf("Nome: ");
        fflush(stdin);
        gets(TabJog[pos].Nome);
        gotoxy(36,18);printf("Data (dd mm aaaa): ");
        scanf("%d %d %d", &TabJog[pos].Data.d, &TabJog[pos].Data.m, &TabJog[pos].Data.a);
    } else 
	{
        gotoxy(35,13);printf("Jogador não encontrado.\n");
    }
    getch();
}

void Ranking(TpJog TabJog[TF], int TL) { //Ranking dos jogadores
    int i,a;
    textcolor(YELLOW);
    gotoxy(37,10); printf("# # # Ranking de Jogadores # # #");
    if (TL == 0) {
       gotoxy(35,12); printf("Nenhum jogador cadastrado ainda.");
    } else {
        OrdenarRanking(TabJog, TL);
        for (i=0, a=12; i < TL; i++, a++) {
            gotoxy(35,a); printf("%d. %s - Pontuacao: %d", i + 1, TabJog[i].Nome, TabJog[i].Pontuacao);
        }
    }
    getch();
}

char Menu(void) //Menu
{	
	textcolor(15);
	gotoxy(13,10); printf("### M E N U ###");
	gotoxy(13,11);printf("[A] CadJog");
	gotoxy(13,12);printf("[B] RelJog");
	gotoxy(13,13);printf("[C] ConsultJog");
	gotoxy(13,14);printf("[D] ExcluJog");
	gotoxy(13,15);printf("[E] AltJog");
	gotoxy(13,16);printf("[F] JOGAR");
	gotoxy(13,17);printf("[G] Ranking");
	gotoxy(13,18);printf("[ESC] Sair");
	gotoxy(13,19);printf("OPCAO DESEJADA");
		
	return toupper(getch());
}

int main(void){
	
	FormPrincipal();
	Moldura(31,9,73,22,15,6);
	TpJog jogador[TF];
	int tlj=0;
	char op;
	srand(time(0));
	do
	{
		op = Menu();
		switch(toupper(op))
		{
			case 'A': cadjog(jogador,tlj);
					LimpaTela();

					break;
				
			case 'B': OrdenarJogador(jogador,tlj); 
					RelJog(jogador,tlj);
					LimpaTela();
					break;
						
			case 'C': ConsultaJogadorNome(jogador,tlj);
					LimpaTela();			         
					break;
			
			case'D': Exclusao(jogador,tlj);
					LimpaTela();
				    break;
				         
			case 'E': AlterarJogador(jogador,tlj);
					LimpaTela();
					break;
				
			case 'F':LimpaMenu(); 
					jogar(jogador, tlj);
					LimpaTela();
					break;
					
			case 'G': Ranking(jogador,tlj);
					LimpaTela();
					break;				
		}
	}while(op!=27);
	
	
	return 0;
}
