#include <nds.h>
#include <stdio.h>

void touch(){		//Fonction de test de l'écran tactile
	touchPosition touchXY;
	int j;
	for(j=4;j<=20;j++){
		iprintf("\x1b[%u;12H|",j);
	}
	iprintf("\x1b[12;0H------------");
	iprintf("\x1b[15;0H------------");
	touchRead(&touchXY);
	iprintf("\x1b[13;0Hx=%04X,%04X\n", touchXY.rawx, touchXY.px);
	iprintf("y=%04X,%04X", touchXY.rawy, touchXY.py);
	if ((touchXY.px>0x7F)&&(touchXY.px!=0x00)) iprintf("\x1b[6;14H -->");
	if ((touchXY.px<0x7F)&&(touchXY.px!=0x00)) iprintf("\x1b[6;14H <--");
	if ((touchXY.px==0x00)&&(touchXY.py==0x00)) iprintf("\x1b[6;14H    ");
}
void input(){		//Fonction de test des touches
	scanKeys();
	if(keysHeld() & KEY_A)
		iprintf("\x1b[4;0HAppui A");		//Bouton A
	else if(keysHeld() & KEY_B)
		iprintf("\x1b[5;0HAppui B");		//Bouton B
	else if(keysHeld() & KEY_X)
		iprintf("\x1b[6;0HAppui X");		//Bouton X
	else if(keysHeld() & KEY_Y)
		iprintf("\x1b[7;0HAppui Y");		//Bouton Y
	else if(keysHeld() & KEY_L)
		iprintf("\x1b[8;0HAppui L");		//Bouton L
	else if(keysHeld() & KEY_R)
		iprintf("\x1b[9;0HAppui R");		//Bouton R
	else if(keysHeld() & KEY_START)
		iprintf("\x1b[10;0HAppui START");	//Bouton START
	else if(keysHeld() & KEY_SELECT)
		iprintf("\x1b[11;0HAppui SELECT");	//Bouton SELECT
	else{
		int i;					//Effaçage zone
		for(i=4;i<=11;i++){
			iprintf("\x1b[%u;0H            ",i);
		}
	}
}
void screen(){		//Fonction affichage entete
	iprintf("\x1b[0;13HINSSET\n");
	iprintf("PROJET REUTILISATION CONSOLE\n");
	iprintf("Hello World\n");
	iprintf("--------------------------------");
}

int main(void) {
//Initialisation
	consoleDemoInit();
	screen();

//Programme
	while(1){
		touch();
		input ();
	}
	return 0;
}
