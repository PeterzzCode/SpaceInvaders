/************************************************/
/* CREDITOS:  erkHca CHOSS choss_21@hotmail.com */
/************************************************/
#include <allegro.h>
#include "timer.h"//Una funcion que incrementa una variable timer simula un contador tiempo
#include "timer2.cpp"
#include <cstdlib> //Para numeros aleatorios
#include <stdio.h>//PAra que se pueda usar lo del sonido 
BITMAP *buffer,*Score,*Numeros,*VidasTxt,*VidasNum,*TerminoJuego,*Explosion,*choss,*ImgNivel;//Buffer para la pantalla
BITMAP *EnemigoA,*EnemigoB,*EnemigoC,*EnemigoD,*Escudo,*Player,*Bala,*Bala2;//El escudo se representa con 'E' y el Player con 'N'
SAMPLE *SonidoMov[4],*SonidoDisp,*SonidoChoqEnemigo,*SonidoChoqPlayer,*SonidoChoqBala,*AlertaEnemigo,*SonidoChoqWin,*SonidoBalEnemigoD;//*MusicaMov2,*MusicaMov3,*MusicaMov4;
int numMusicMov = 0;
int numBalasEne = 1;
#define ESCALA 20 //Escala con relacion al mapa
#define MAXFILMAP 26//Numero maximo de filas para el mapa principal se usa e el arreglo char
#define MAXCOLMAP 33//Numero maximo de columnas para el mapa principal se usa en el arreglo char
char dirEnemigos = 'D';//Se usa D= Derecha I = Izquierda mueve las naves enemigas. . . .
int modMueveEne = 80;//Esto es para saber cada cuantos segundos se va a mover el enemigo. . .
bool detenerJuego = false;
//int TotSeg = 0;//Es el contador total del tiempo en segundos
int Velocidad = 100;//Velocidad
int enemigoDispara; //Esto se saca con un ramdom de 1 a 11 porque son once columnas y el numero que caiga es la columna que disparara
int NumImagen = 0;// Para que se anime la imagen de los enemigos. . . 
const int MAX_BALAS = 5;//Numero maximo de baas
const int MAX_BALASENE = 10;
bool fired = false;
int numEnemigos = 55;//Es el numero de enemigos que hay en el mapa
int PuntosTot = 0;
int NumVidas = 5;
int Nivel = 1;
int ColEnemigo = 11;//para calcular random de que enemigo dispara
//A=NaveEnemigo1 B=NaveEnemigo2 C=NaveEnemigo3 D=NaveEnemigo4,N = nave del jugador X= Limites del mapa E= Parde del escudo
char mapa[MAXFILMAP][MAXCOLMAP]={/*C = 30 puntos B = 20 Puntos A = 10 puntos */
  "  S         1            Y    Z ",//0
  "                                ",//1
  "                                ",//2
  "     C C C C C C C C C C C      ",//3
  "                                ",//4
  "     B B B B B B B B B B B      ",//5
  "                                ",//6
  "     B B B B B B B B B B B      ",//7
  "                                ",//8
  "     A A A A A A A A A A A      ",//9
  "                                ",//10
  "     A A A A A A A A A A A      ",//11
  "                                ",//12
  "                                ",//13
  "                                ",//14
  "                                ",//15
  "                                ",//16
  "                                ",//19
  "                                ",//20
  "                                ",//21
  "     EEEE     EEEE     EEEE     ",//22
  "     EEEE     EEEE     EEEE     ",//23
  "    EE  EE   EE  EE   EE  EE    ",//24
  "                                ",//25
  "             N                  ",//26
  " V   W                  c       "//27
};//Se representara con V

struct Puntos 
{
	int x;
	int y;
	int xT;//Variables temporales
	int yT;//Variables temporales
};
Puntos balasPlayer[MAX_BALAS];
Puntos balasEnemigo[MAX_BALASENE];
Puntos jefe;
int RndDispJefe = 10;//Para saber cuando va a disparar el Jefe. . . .
char dirJefe = 'I';
int balaPlayerIndex = 0,balaEnemigoIndex=0;
bool EntraEnemig = true;
Puntos NavePlayer;//SE inicializa en el Main con la posicion del N en el Mapa X = 13 Y=20
void diBujaNivel(int vNivel){
   Nivel = vNivel;
   NavePlayer.x = 13;
   NavePlayer.y = MAXFILMAP -2;
   NavePlayer.xT = NavePlayer.x;
   NavePlayer.yT = NavePlayer.y;
   for(int i=MAXCOLMAP-1; i>=0; i--){
        for (int j=MAXFILMAP -1 ; j>= 0 ; j--) {
              mapa[j][i] = ' ';    
        }//Fin for j
     } 
   //Los que no cambian
   mapa[0][2] = 'S'; 
   mapa[0][12] = '1';
   mapa[0][30] = 'Z';
   mapa[0][26] = 'Y';
   mapa[25][1] = 'V';
   mapa[25][5] = 'W';
   mapa[25][24] = 'c';
   
   mapa[20][5] = 'E';
   mapa[20][6] = 'E';
   mapa[20][7] = 'E';
   mapa[20][8] = 'E';
   mapa[21][5] = 'E';
   mapa[21][6] = 'E';
   mapa[21][7] = 'E';
   mapa[21][8] = 'E';
   mapa[22][4] = 'E';
   mapa[22][5] = 'E';
   mapa[22][8] = 'E';
   mapa[22][9] = 'E';
   
   mapa[20][14] = 'E';
   mapa[20][15] = 'E';
   mapa[20][16] = 'E';
   mapa[20][17] = 'E';
   mapa[21][14] = 'E';
   mapa[21][15] = 'E';
   mapa[21][16] = 'E';
   mapa[21][17] = 'E';
   mapa[22][13] = 'E';
   mapa[22][14] = 'E';
   mapa[22][17] = 'E';
   mapa[22][18] = 'E';
   
   mapa[20][23] = 'E';
   mapa[20][24] = 'E';
   mapa[20][25] = 'E';
   mapa[20][26] = 'E';
   mapa[21][23] = 'E';
   mapa[21][24] = 'E';
   mapa[21][25] = 'E';
   mapa[21][26] = 'E';
   mapa[22][22] = 'E';
   mapa[22][23] = 'E';
   mapa[22][26] = 'E';
   mapa[22][27] = 'E';
   
   
   if (Nivel == 1){
         mapa[3][5] = 'C'; 
         mapa[3][9] = 'C';
         mapa[3][13] = 'C';
         mapa[3][17] = 'C';
         mapa[3][21] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][9] = 'B';
         mapa[5][13] = 'B';
         mapa[5][17] = 'B';
         mapa[5][21] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][9] = 'B';
         mapa[7][13] = 'B';
         mapa[7][17] = 'B';
         mapa[7][21] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][9] = 'A';
         mapa[9][13] = 'A';
         mapa[9][17] = 'A';
         mapa[9][21] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][9] = 'A';
         mapa[11][13] = 'A';
         mapa[11][17] = 'A';
         mapa[11][21] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 30;
         ColEnemigo = 6;    
         modMueveEne = 150;
   }else if (Nivel == 2){
         mapa[3][5] = 'C';
         mapa[3][9] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][21] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][9] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][21] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][9] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][21] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][9] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][21] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][9] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][21] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 35;
         ColEnemigo = 7;    
         modMueveEne = 140;}
      else if(Nivel == 3){
         mapa[3][5] = 'C';
         mapa[3][9] = 'C';
         mapa[3][11] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][19] = 'C';
         mapa[3][21] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][9] = 'B';
         mapa[5][11] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][19] = 'B';
         mapa[5][21] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][9] = 'B';
         mapa[7][11] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][19] = 'B';
         mapa[7][21] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][9] = 'A';
         mapa[9][11] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][19] = 'A';
         mapa[9][21] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][9] = 'A';
         mapa[11][11] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][19] = 'A';
         mapa[11][21] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 45;
         ColEnemigo = 9;    
         modMueveEne = 130;}
     else if (Nivel == 4){
         mapa[3][5] = 'C';
         mapa[3][7] = 'C';
         mapa[3][9] = 'C';
         mapa[3][11] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][19] = 'C';
         mapa[3][21] = 'C';
         mapa[3][23] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][7] = 'B';
         mapa[5][9] = 'B';
         mapa[5][11] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][19] = 'B';
         mapa[5][21] = 'B';
         mapa[5][23] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][7] = 'B';
         mapa[7][9] = 'B';
         mapa[7][11] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][19] = 'B';
         mapa[7][21] = 'B';
         mapa[7][23] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][7] = 'A';
         mapa[9][9] = 'A';
         mapa[9][11] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][19] = 'A';
         mapa[9][21] = 'A';
         mapa[9][23] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][7] = 'A';
         mapa[11][9] = 'A';
         mapa[11][11] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][19] = 'A';
         mapa[11][21] = 'A';
         mapa[11][23] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 55;
         ColEnemigo = 11;    
         modMueveEne = 120;}
   else if (Nivel == 5){
         mapa[3][5] = 'C';
         mapa[3][9] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][21] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][9] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][21] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][9] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][21] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][9] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][21] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][9] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][21] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 35;
         ColEnemigo = 7;    
         modMueveEne = 110;
         numBalasEne = 2;
         }
      else if(Nivel == 6){
         mapa[3][5] = 'C';
         mapa[3][9] = 'C';
         mapa[3][11] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][19] = 'C';
         mapa[3][21] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][9] = 'B';
         mapa[5][11] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][19] = 'B';
         mapa[5][21] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][9] = 'B';
         mapa[7][11] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][19] = 'B';
         mapa[7][21] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][9] = 'A';
         mapa[9][11] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][19] = 'A';
         mapa[9][21] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][9] = 'A';
         mapa[11][11] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][19] = 'A';
         mapa[11][21] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 45;
         ColEnemigo = 9;    
         modMueveEne = 100;
         numBalasEne = 2;}
     else if(Nivel == 7){
         mapa[3][5] = 'C';
         mapa[3][9] = 'C';
         mapa[3][11] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][19] = 'C';
         mapa[3][21] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][9] = 'B';
         mapa[5][11] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][19] = 'B';
         mapa[5][21] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][9] = 'B';
         mapa[7][11] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][19] = 'B';
         mapa[7][21] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][9] = 'A';
         mapa[9][11] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][19] = 'A';
         mapa[9][21] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][9] = 'A';
         mapa[11][11] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][19] = 'A';
         mapa[11][21] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 45;
         ColEnemigo = 9;    
         modMueveEne = 95;
         numBalasEne = 3;}
     else if (Nivel == 8){
         mapa[3][5] = 'C';
         mapa[3][7] = 'C';
         mapa[3][9] = 'C';
         mapa[3][11] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][19] = 'C';
         mapa[3][21] = 'C';
         mapa[3][23] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][7] = 'B';
         mapa[5][9] = 'B';
         mapa[5][11] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][19] = 'B';
         mapa[5][21] = 'B';
         mapa[5][23] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][7] = 'B';
         mapa[7][9] = 'B';
         mapa[7][11] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][19] = 'B';
         mapa[7][21] = 'B';
         mapa[7][23] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][7] = 'A';
         mapa[9][9] = 'A';
         mapa[9][11] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][19] = 'A';
         mapa[9][21] = 'A';
         mapa[9][23] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][7] = 'A';
         mapa[11][9] = 'A';
         mapa[11][11] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][19] = 'A';
         mapa[11][21] = 'A';
         mapa[11][23] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 55;
         ColEnemigo = 11;    
         modMueveEne = 110;
         numBalasEne = 2;}
    else if (Nivel == 9){
         mapa[3][5] = 'C';
         mapa[3][7] = 'C';
         mapa[3][9] = 'C';
         mapa[3][11] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][19] = 'C';
         mapa[3][21] = 'C';
         mapa[3][23] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][7] = 'B';
         mapa[5][9] = 'B';
         mapa[5][11] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][19] = 'B';
         mapa[5][21] = 'B';
         mapa[5][23] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][7] = 'B';
         mapa[7][9] = 'B';
         mapa[7][11] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][19] = 'B';
         mapa[7][21] = 'B';
         mapa[7][23] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][7] = 'A';
         mapa[9][9] = 'A';
         mapa[9][11] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][19] = 'A';
         mapa[9][21] = 'A';
         mapa[9][23] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][7] = 'A';
         mapa[11][9] = 'A';
         mapa[11][11] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][19] = 'A';
         mapa[11][21] = 'A';
         mapa[11][23] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 55;
         ColEnemigo = 11;    
         modMueveEne = 100;
         numBalasEne = 3;}
   else{
        mapa[3][5] = 'C';
         mapa[3][7] = 'C';
         mapa[3][9] = 'C';
         mapa[3][11] = 'C';
         mapa[3][13] = 'C';
         mapa[3][15] = 'C';
         mapa[3][17] = 'C';
         mapa[3][19] = 'C';
         mapa[3][21] = 'C';
         mapa[3][23] = 'C';
         mapa[3][25] = 'C';
   
         mapa[5][5] = 'B';
         mapa[5][7] = 'B';
         mapa[5][9] = 'B';
         mapa[5][11] = 'B';
         mapa[5][13] = 'B';
         mapa[5][15] = 'B';
         mapa[5][17] = 'B';
         mapa[5][19] = 'B';
         mapa[5][21] = 'B';
         mapa[5][23] = 'B';
         mapa[5][25] = 'B';
         mapa[7][5] = 'B';
         mapa[7][7] = 'B';
         mapa[7][9] = 'B';
         mapa[7][11] = 'B';
         mapa[7][13] = 'B';
         mapa[7][15] = 'B';
         mapa[7][17] = 'B';
         mapa[7][19] = 'B';
         mapa[7][21] = 'B';
         mapa[7][23] = 'B';
         mapa[7][25] = 'B';
   
         mapa[9][5] = 'A';
         mapa[9][7] = 'A';
         mapa[9][9] = 'A';
         mapa[9][11] = 'A';
         mapa[9][13] = 'A';
         mapa[9][15] = 'A';
         mapa[9][17] = 'A';
         mapa[9][19] = 'A';
         mapa[9][21] = 'A';
         mapa[9][23] = 'A';
         mapa[9][25] = 'A';
         mapa[11][5] = 'A';
         mapa[11][7] = 'A';
         mapa[11][9] = 'A';
         mapa[11][11] = 'A';
         mapa[11][13] = 'A';
         mapa[11][15] = 'A';
         mapa[11][17] = 'A';
         mapa[11][19] = 'A';
         mapa[11][21] = 'A';
         mapa[11][23] = 'A';
         mapa[11][25] = 'A';
         numEnemigos = 55;
         ColEnemigo = 11;    
         modMueveEne -= 5;
         if (modMueveEne < 70){
             numBalasEne = 4;}
         else if (modMueveEne < 80){
             numBalasEne = 4;}
         else if (modMueveEne < 90){
             numBalasEne = 3;
         }else{
             numBalasEne = 2;
         }
         
   }
   
     
}
void SonidoEnemigo(){
     play_sample(SonidoMov[numMusicMov],100,128,1000,0); //// 100 = volumen   128 = sonido balanceado   0 = sin bucle
     numMusicMov++;
     if (numMusicMov >=4)numMusicMov = 0;
}

void CambiaDireccion(){
     int i,j,jMayor = -1;
     for(i=MAXCOLMAP-1; i>=0; i--){
        for (j=MAXFILMAP -1 ; j>= 0 ; j--) {
           if (mapa[j][i] == 'A' || mapa[j][i] == 'B' || mapa[j][i] == 'C'){
              //if (i < MAXCOLMAP-1){//Para detectar el limite y iniciar hacia abajo
              mapa[j+1][i] = mapa[j][i];
              mapa[j][i] = ' ';
              if(j+1 > jMayor) jMayor = j+1;
           }      
        }//Fin for j
     }  //Fin for i
     if(dirEnemigos =='D') dirEnemigos = 'I';
     else if(dirEnemigos =='I') dirEnemigos = 'D';
     SonidoEnemigo();
     modMueveEne -=10;
     if (jMayor >= MAXCOLMAP -9){
                NumVidas--;
               detenerJuego = true;
               diBujaNivel(Nivel);
     }
     
}
void addBala(Puntos balas[],int &balaIndex,const int MAX_balas,int x,int y)
{			
	if(balaIndex < MAX_balas)
	{
				balas[balaIndex].x=x;
				balas[balaIndex].y=y-1;
				balaIndex++;			
	}
}
void MueveEnemigoD(){
     if (timer2>= 100){
        if(dirJefe == 'I') dirJefe = 'D';
        else if(dirJefe == 'D') dirJefe = 'I';
        timer2 = 0;
        if(dirJefe == 'I') jefe.x = MAXCOLMAP-2;
        else if(dirJefe == 'D') jefe.x = 0;
        EntraEnemig = true;
        RndDispJefe = (rand()%(MAXCOLMAP-2));   
     }
   if(jefe.x >= 0 && jefe.x < MAXCOLMAP-1){
       if(EntraEnemig){
             timer2 = 0;
             play_sample(AlertaEnemigo,100,128,1000,1);
       }
       EntraEnemig = false;
       jefe.xT = jefe.x;
       jefe.yT = jefe.y;
       if(dirJefe == 'I') jefe.x= MAXCOLMAP-2 -timer2;
       else if(dirJefe == 'D') jefe.x=timer2;
       if (RndDispJefe == jefe.x){
             RndDispJefe =-2;//Evita que vuelva a entrar a esta Comparacion
             play_sample(SonidoBalEnemigoD,100,128,1000,0);
             addBala(balasEnemigo,balaEnemigoIndex,MAX_BALASENE,jefe.x,jefe.y);
       }
       
       mapa[jefe.yT][jefe.xT] = ' ';
       mapa[jefe.y][jefe.x] = 'D';
       if(dirJefe == 'I' && jefe.x == 0) stop_sample(AlertaEnemigo);
       if(dirJefe == 'D' && jefe.x == MAXCOLMAP-2) stop_sample(AlertaEnemigo);
   }else EntraEnemig = true;
}
void MueveEnemigo(){
     int i,j;
if(timer>=modMueveEne &&  detenerJuego == false )
	  { 
         NumImagen ++;
         timer = 0;
         if (NumImagen > 1) NumImagen =0;
         if (dirEnemigos == 'D'){             
	        for(i=MAXCOLMAP-1; i>=0; i--){/*Recorre de derecha izquierda arriba abajo    <-  /|\ /|\ . . .  <- /|\ /|\*/
               for (j=MAXFILMAP -1 ; j>= 0 ; j--) {
                  if (mapa[j][i] == 'A' || mapa[j][i] == 'B' || mapa[j][i] == 'C'){
                     if (i < MAXCOLMAP-2){//Para detectar el limite y iniciar hacia abajo
                     mapa[j][i+1] = mapa[j][i];
                     mapa[j][i] = ' ';}
                     else{
                          CambiaDireccion();
                          return;}
                   }//End if
                }//Fin for j
             }  //Fin for i
         }else if (dirEnemigos =='I'){
            for(i=0; i<MAXCOLMAP; i++){/*Recorre de izquierda derecha arriba abajo    ->  /|\ /|\ . . .  <- /|\ /|\*/
               for (j=MAXFILMAP -1 ; j>= 0 ; j--) {
                  if (mapa[j][i] == 'A' || mapa[j][i] == 'B' || mapa[j][i] == 'C'){
                     if (i > 0){//Para detectar el limite y iniciar hacia abajo
                     mapa[j][i-1] = mapa[j][i];
                     mapa[j][i] = ' ';}
                     else{
                          CambiaDireccion();
                          return;}
                   }//End if
                }//Fin for j
             }  //Fin for i  
         }//Fin de DirEnemigos
         
         /*SONIDO*/
         SonidoEnemigo();
         
         /******************************/
         /*DETECTAR QUE ENEMIGO DISPARA*/
         /******************************/
         int NumBalTmp = 0;
     while(NumBalTmp < numBalasEne){
         NumBalTmp++;
         if(numEnemigos < 10) ColEnemigo = 4;
         enemigoDispara = (rand()%ColEnemigo);   
         int ctEn = 0;//para comparar con el numero de arriba
         for(i=0; i<MAXCOLMAP; i++){/*Recorre de izquierda derecha arriba abajo    -> /|\ /|\ . . .  -> /|\ /|\*/
               for (j=MAXFILMAP -1 ; j>= 0 ; j--) {
                  if (mapa[j][i] == 'A' || mapa[j][i] == 'B' || mapa[j][i] == 'C'){
                     ctEn++;
                     if (ctEn == enemigoDispara){
                         addBala(balasEnemigo,balaEnemigoIndex,MAX_BALASENE,i,j);
                         break;
                     }
                     break;
                   }//End if
                }//Fin for j
         }  //Fin for i 
         }//Fin While     
      }
}
void Disparo(){
     //Para el disparo del PLAYER
   for(int i = 0; i < balaPlayerIndex; i++)
   {
      balasPlayer[i].y--;			
      if(balasPlayer[i].y < 0)
      {
         balaPlayerIndex--;
         balasPlayer[i].y=balasPlayer[balaPlayerIndex].y;
         balasPlayer[i].x=balasPlayer[balaPlayerIndex].x;
      }else if(mapa[balasPlayer[i].y][balasPlayer[i].x] == 'A' || mapa[balasPlayer[i].y][balasPlayer[i].x] == 'B' || mapa[balasPlayer[i].y][balasPlayer[i].x] == 'C' || mapa[balasPlayer[i].y][balasPlayer[i].x] == 'D' || mapa[balasPlayer[i].y][balasPlayer[i].x] == 'E'){
           if(mapa[balasPlayer[i].y][balasPlayer[i].x] == 'A') {PuntosTot+=10;numEnemigos --;}
           else if(mapa[balasPlayer[i].y][balasPlayer[i].x] == 'B'){ PuntosTot+=20;numEnemigos --;}
           else if(mapa[balasPlayer[i].y][balasPlayer[i].x] == 'C') {PuntosTot+=30;numEnemigos --;}
           else if(mapa[balasPlayer[i].y][balasPlayer[i].x] == 'D') {
                jefe.x = -1; 
                PuntosTot+=100;
                stop_sample(AlertaEnemigo);
           }
           draw_sprite(buffer,Explosion,balasPlayer[i].x*20,balasPlayer[i].y*20);
           /*SONIDO*/
           if(mapa[balasPlayer[i].y][balasPlayer[i].x] == 'D') play_sample(SonidoChoqWin,100,128,1000,0); 
           else if(mapa[balasPlayer[i].y][balasPlayer[i].x] != 'E') play_sample(SonidoChoqEnemigo,100,128,1000,0); 
          // else play_sample(SonidoChoqEscudo,100,128,1000,0); //// 100 = volumen   128 = sonido balanceado   0 = sin bucle
           balaPlayerIndex--;
           mapa[balasPlayer[i].y][balasPlayer[i].x] = ' ';
		   balasPlayer[i].y=balasPlayer[balaPlayerIndex].y;
           balasPlayer[i].x=balasPlayer[balaPlayerIndex].x;
      }else{/*VERIFICA CHOQUE CON BALA*/
           for(int k = 0; k < balaEnemigoIndex; k++){
               if(balasEnemigo[k].y == balasPlayer[i].y &&  balasEnemigo[k].x ==  balasPlayer[i].x){
                     draw_sprite(buffer,Explosion,balasEnemigo[k].x*20,balasEnemigo[k].y*20);
                     balaPlayerIndex--;
                     balasPlayer[i].y=balasPlayer[balaPlayerIndex].y;
                     balasPlayer[i].x=balasPlayer[balaPlayerIndex].x;
                     balaEnemigoIndex--;
                     balasEnemigo[k].y=balasEnemigo[balaEnemigoIndex].y;
                     balasEnemigo[k].x=balasEnemigo[balaEnemigoIndex].x;
                     play_sample(SonidoChoqBala,100,128,1000,0); //// 100 = volumen   128 = sonido balanceado   0 = sin bucle
                     break;
               }
           }
      }		
   } 
   //Para el disparo de los ENEMIGOS
   for(int i = 0; i < balaEnemigoIndex; i++)
   {
      balasEnemigo[i].y++;			
      if(balasEnemigo[i].y>MAXFILMAP-1)
      {
         balaEnemigoIndex--;
         balasEnemigo[i].y=balasEnemigo[balaEnemigoIndex].y;
         balasEnemigo[i].x=balasEnemigo[balaEnemigoIndex].x;
      }else if(mapa[balasEnemigo[i].y][balasEnemigo[i].x] == 'E'){
         mapa[balasEnemigo[i].y][balasEnemigo[i].x] = ' ';
         balaEnemigoIndex--;
		 balasEnemigo[i].y=balasEnemigo[balaEnemigoIndex].y;
         balasEnemigo[i].x=balasEnemigo[balaEnemigoIndex].x;
         //play_sample(SonidoChoqEscudo,100,128,1000,0);
      }else if(mapa[balasEnemigo[i].y][balasEnemigo[i].x] == 'N'){/*LE DAN A PLAYER*/
         mapa[balasEnemigo[i].y][balasEnemigo[i].x] == ' ';
         balaEnemigoIndex--;
		 balasEnemigo[i].y=balasEnemigo[balaEnemigoIndex].y;
         balasEnemigo[i].x=balasEnemigo[balaEnemigoIndex].x;
            rest(100);
            timer = 0;
            detenerJuego = true;
            NumVidas --;
            play_sample(SonidoChoqPlayer,100,128,1000,0); //// 100 = volumen   128 = sonido balanceado   0 = sin bucle
      }else{/*Verifica choque con bala*/
         for(int k = 0; k < balaPlayerIndex; k++){
             if(balasEnemigo[i].y == balasPlayer[k].y &&  balasEnemigo[i].x ==  balasPlayer[k].x){
                     draw_sprite(buffer,Explosion,balasEnemigo[i].x*20,balasEnemigo[i].y*20);
                     balaPlayerIndex--;
                     balasPlayer[k].y=balasPlayer[balaPlayerIndex].y;
                     balasPlayer[k].x=balasPlayer[balaPlayerIndex].x;
                     balaEnemigoIndex--;
                     balasEnemigo[i].y=balasEnemigo[balaEnemigoIndex].y;
                     balasEnemigo[i].x=balasEnemigo[balaEnemigoIndex].x;
                     play_sample(SonidoChoqBala,100,128,1000,0); //// 100 = volumen   128 = sonido balanceado   0 = sin bucle
                     break;
               }
         }
      }
   }  
   if(key[KEY_SPACE])
   {				
      if(!fired)	//false							
      {					
	     addBala(balasPlayer,balaPlayerIndex,MAX_BALAS,NavePlayer.x,NavePlayer.y);
	     play_sample(SonidoDisp,100,128,1000,0); //// 100 = volumen   128 = sonido balanceado   0 = sin bucle
	     fired = true;
	   }
	}
	if(!key[KEY_SPACE])
	{
		fired = false;
	}
	for(int i = 0; i < balaPlayerIndex; i++)
		{			
			draw_sprite(buffer,Bala2,balasPlayer[i].x*20+6,balasPlayer[i].y*20);
		}
	for(int i = 0; i < balaEnemigoIndex; i++)
   {
         draw_sprite(buffer,Bala,balasEnemigo[i].x*20+6,balasEnemigo[i].y*20);
   }
}
void MuevePlayer(){
      //mapa[MAXFILMAP][MAXCOLMAP]
     NavePlayer.xT = NavePlayer.x;
     NavePlayer.yT = NavePlayer.y;
    if(key[KEY_LEFT])
	{ 
       if (NavePlayer.x > 0) NavePlayer.x--;
        
	}
	if(key[KEY_RIGHT])
	{    
       if (NavePlayer.x < 31) NavePlayer.x++;
	}
	mapa[NavePlayer.yT][NavePlayer.xT] = ' ';
	mapa[NavePlayer.y][NavePlayer.x] = 'N';
}
void DibujaMapa(){
   int i, j;
   //textprintf(buffer,font,10,10,makecol16(255,255,255),"Puntos: %i",PuntosTot);   
   //textprintf(buffer,font,10,30,makecol16(255,255,255),"Contador: , timer: %i,timer2 %i DirEnemigo %c, Columna Disp: %i, Num Enemigos: %i",timer,timer2,dirEnemigos,enemigoDispara,numEnemigos);   
    for(i=0; i<MAXCOLMAP; i++)
    for (j=0; j<MAXFILMAP; j++) {
      if (mapa[j][i] == 'C')/*imagen 20x40*/
        //draw_sprite(buffer,EnemigoC, i * 20,j * 20);
        blit(EnemigoC, buffer,0,NumImagen*20,i * 20,j * 20,20,20);
      if (mapa[j][i] == 'B')/*Imagen 24X40*/
        //draw_sprite(buffer,EnemigoB, i * 20,j * 20);
        blit(EnemigoB, buffer,0,20-NumImagen*20,i * 20-2,j * 20,24,20);
      if (mapa[j][i] == 'A')/*25X40*/
        //draw_sprite(buffer,EnemigoA, i * 20,j * 20);
        //rectfill( buffer, i * 20, j * 20, (i + 1) * 20, (j + 1) * 20, makecol( 0, 255, 255));
        blit(EnemigoA, buffer,0,NumImagen*20,i * 20-2,j * 20,25,20);
      if (mapa[j][i] == 'E')
       draw_sprite(buffer,Escudo, i * 20,j * 20);
      if (mapa[j][i] == 'D')
       draw_sprite(buffer,EnemigoD, i * 20,j * 20);
        //rectfill( buffer, i * 20, j * 20, (i + 1) * 20, (j + 1) * 20, makecol( 255, 255, 255));
      if (mapa[j][i] == 'N')
        if (detenerJuego == false) draw_sprite(buffer,Player, i * 20,j * 20);
        else draw_sprite(buffer,Explosion,i*20,j*20);
        //rectfill( buffer, i * 20, j * 20, (i + 1) * 20, (j + 1) * 20, makecol( 255, 0, 255));
      if (mapa[j][i] == 'S')//Para el Score
        draw_sprite(buffer,Score, i * 20,j * 20);
      if (mapa[j][i] == 'V')//Para el VIDAS
        draw_sprite(buffer,VidasTxt, i * 20,j * 20);
      if (mapa[j][i] == 'W')//Para Imagenes cont imagenes de vidas
        blit(VidasNum, buffer,NumVidas *20,0,i * 20,j * 20,NumVidas*20,20);
      if (mapa[j][i] == 'c')//Para el VIDAS
        draw_sprite(buffer,choss, i * 20,j * 20-7);
      if (mapa[j][i] == 'Y')//Para el VIDAS
        draw_sprite(buffer,ImgNivel, i * 20,j * 20);
      if (mapa[j][i] == 'Z'){
            int TempNi,Ctn=0;
            TempNi = Nivel;
            int Digito;
            while (TempNi > 0){
              Digito = TempNi % 10;
              blit(Numeros, buffer,Digito*20,0,(i-Ctn) * 20,j * 20,20,20);
              TempNi /= 10;
              Ctn++;
            }
      }
      if (mapa[j][i] == '1'){//Para poner los puntos
            int TempPt,Ctn=0;
            TempPt = PuntosTot;
            int Digito;
            while (TempPt > 0){
              Digito = TempPt % 10;
              blit(Numeros, buffer,Digito*20,0,(i-Ctn) * 20,j * 20,20,20);
              TempPt /= 10;
              Ctn++;
            }
       } 
    }     
}
int main() 
{
    allegro_init();
	install_keyboard();
	install_timer();
	set_color_depth(16);//MAXFILMAP
	//MAXFILMAP 28
//#define MAXCOLMAP 33
	//buffer = create_bitmap(640,480);
	buffer = create_bitmap(640,(MAXFILMAP) *20);
	set_gfx_mode(GFX_SAFE,640,(MAXFILMAP) *20,0,0);
	acquire_screen();
	clear_bitmap(buffer);
	srand(time(NULL));
	EnemigoA = load_bitmap("EnemigoA.bmp",NULL);
	EnemigoB = load_bitmap("EnemigoB.bmp",NULL);
	EnemigoC = load_bitmap("EnemigoC.bmp",NULL);
	EnemigoD = load_bitmap("EnemigoD.bmp",NULL);
	Escudo = load_bitmap("Escudo.bmp",NULL);
	Player = load_bitmap("Tanque.bmp",NULL);
	Bala= load_bitmap("Bala.bmp",NULL);
	Bala2 = load_bitmap("Bala2.bmp",NULL);
	Score = load_bitmap("Puntos.bmp",NULL);
	Numeros = load_bitmap("Numeros.bmp",NULL);
	VidasTxt = load_bitmap("Vidastxt.bmp",NULL);
	VidasNum = load_bitmap("Vidasnum.bmp",NULL);
	TerminoJuego = load_bitmap("Termino.bmp",NULL);
	Explosion = load_bitmap("Explocion.bmp",NULL);
	choss = load_bitmap("choss.bmp",NULL);
	ImgNivel = load_bitmap("Nivel.bmp",NULL);
    blit(buffer,screen,0,0,0,0,640,(MAXFILMAP) * 20);
    
	release_screen();
	NavePlayer.x = 13;
    NavePlayer.y = MAXFILMAP -2;
    NavePlayer.xT = NavePlayer.x;
    NavePlayer.yT = NavePlayer.y;
    jefe.x = -1;
    jefe.y = 1;
    jefe.xT = jefe.x;
    jefe.yT = jefe.y;
    int sn;
    sn = install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL); 
    if (sn != 0 ) { printf("\nError con el driver de sonido");  return 1;  }
    timer2 = 0;
    LOCK_VARIABLE(timer);
    LOCK_VARIABLE(timer2);
	LOCK_FUNCTION(incrementTimer);
	LOCK_FUNCTION(incrementTimer2);
	install_int_ex(incrementTimer,BPS_TO_TIMER(Velocidad)); 
	install_int_ex(incrementTimer2,BPS_TO_TIMER(5));
	//remove_int_ex(incrementTimer());
	SonidoMov[0] = load_wav("Sonidos\\MovEne1.wav");
	SonidoMov[1] = load_wav("Sonidos\\MovEne2.wav");
	SonidoMov[2]= load_wav("Sonidos\\MovEne3.wav");
	SonidoMov[3] = load_wav("Sonidos\\MovEne4.wav");
	SonidoDisp = load_wav("Sonidos\\0.wav");
	SonidoChoqEnemigo = load_wav("Sonidos\\ChoqueEne1.wav");
	SonidoChoqPlayer = load_wav("Sonidos\\ChoquePlay.wav");
	SonidoChoqBala = load_wav("Sonidos\\ChoqueBala.wav");
	SonidoChoqWin = load_wav("Sonidos\\ChoqueWin.wav");
	AlertaEnemigo = load_wav("Sonidos\\AlertaEnemigo.wav");
	SonidoBalEnemigoD = load_wav("Sonidos\\BalaEnemigoD.wav");
    if (!SonidoMov[0]) {    printf("Error leyendo  el fichero de sonido\n"); return 2; }
    if (!SonidoMov[1]) {    printf("Error leyendo  el fichero de sonido\n"); return 2; }
    if (!SonidoMov[2]) {    printf("Error leyendo  el fichero de sonido\n"); return 2; }
    if (!SonidoMov[3]) {    printf("Error leyendo  el fichero de sonido\n"); return 2; }
    //play_sample(SonidoMov[0],100,128,1000,0); //// 100 = volumen   128 = sonido balanceado   0 = sin bucle
    //stop_sample(sonido);//system("PAUSE");
    diBujaNivel(1);
	while( !key[KEY_ESC]){
        acquire_screen();
	    clear_bitmap(buffer);
	    if(numEnemigos<= 0) detenerJuego = true;
		if(detenerJuego) {
           timer = 0;
           if(numEnemigos <= 0){
                textprintf(buffer,font,10,90,makecol16(255,255,255),"FELICIDADES PAsaste al siguiente Nivel ESPACIO o DERECHA o Izquierda o ENTER para continuar"); 
           }else if(NumVidas > 0){
                textprintf(buffer,font,10,90,makecol16(255,255,255),"Te dieron!!!!! preciona ESPACIO o DERECHA o Izquierda o ENTER para continuar"); 
           }else {draw_sprite(buffer,TerminoJuego, 100, 100);}
           
           if(key[KEY_ENTER] || key[KEY_SPACE] || key[KEY_LEFT] || key[KEY_RIGHT])
     	   {  
              detenerJuego = false;
              if(NumVidas <= 0) {break;}
              if(numEnemigos <= 0) diBujaNivel(Nivel+1);
           } 
           
        }
           DibujaMapa();
           MueveEnemigo();
           if (detenerJuego == false)MuevePlayer();
           if (detenerJuego == false)Disparo();
            if (detenerJuego == false)MueveEnemigoD();
           blit(buffer,screen,0,0,0,0,640,(MAXFILMAP) * 20);
           release_screen();
	       rest(50);
    }   
    remove_int(incrementTimer);//PAraque se pueda cerrar. . .
    remove_int(incrementTimer2);//PAraque se pueda cerrar. . .
    destroy_bitmap(buffer);
    destroy_bitmap(EnemigoA);
    destroy_bitmap(EnemigoB);
	destroy_bitmap(EnemigoC);
	destroy_bitmap(Escudo);
	destroy_bitmap(Player);
	destroy_bitmap(Bala);
	destroy_bitmap(Bala2);
	destroy_bitmap(Score);
	destroy_bitmap(Numeros);
	destroy_bitmap(VidasTxt);
	destroy_bitmap(VidasNum);
	destroy_bitmap(TerminoJuego);
	destroy_bitmap(Explosion);
	destroy_bitmap(choss);
	destroy_bitmap(EnemigoD);
	destroy_bitmap(ImgNivel);
    allegro_exit();  
    return 0;
}
END_OF_MAIN();
