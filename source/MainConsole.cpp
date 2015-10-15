#include <nds.h>
#include <stdio.h>

void menu(){
	int l,c;
	for(c=10;c<=20;c++){
		iprintf("\x1b[4;%uH-",c);iprintf("\x1b[8;%uH-",c);
		iprintf("\x1b[11;%uH-",c);iprintf("\x1b[15;%uH-",c);
	}
	for(l=5;l<=7;l++){
		iprintf("\x1b[%u;10H|",l);iprintf("\x1b[%u;20H|",l);
	}
	for(l=12;l<=14;l++){
		iprintf("\x1b[%u;10H|",l);iprintf("\x1b[%u;20H|",l);
	}
	iprintf("\x1b[6;12HTACTILE");		//50,24 A6,45
	iprintf("\x1b[13;11HCONTROLES");	//50,5B A6,7D
}
void screen(){		//Fonction affichage entete
	iprintf("\x1b[0;13HINSSET");
	iprintf("\x1b[1;2HPROJET REUTILISATION CONSOLE");
	//iprintf("Hello World\n");
	int i;
	for(i=0;i<32;i++){
		iprintf("\x1b[2;%uH-",i);
		iprintf("\x1b[22;%uH-",i);
	}
	iprintf("\x1b[23;13HRETOUR");
}
void touch(){		//Fonction de test de l'écran tactile
	touchPosition touchXY;
	int l,c;
	for(l=8;l<=10;l++){
			iprintf("\x1b[%u;14H|",l);
			iprintf("\x1b[%u;0H|",l);
		}
	for(c=0;c<=14;c++){
		iprintf("\x1b[7;%uH-",c);
		iprintf("\x1b[11;%uH-",c);
	}
	do{	
		touchRead(&touchXY);
		iprintf("\x1b[18;2Hx=%04X,%04X", touchXY.rawx, touchXY.px);
		iprintf("\x1b[19;2Hy=%04X,%04X", touchXY.rawy, touchXY.py);
		if ((touchXY.px>0x7F)&&(touchXY.px!=0x00)) iprintf("\x1b[10;5H -->");
		if ((touchXY.px<0x7F)&&(touchXY.px!=0x00)) iprintf("\x1b[10;5H <--");
		if ((touchXY.px==0x00)&&(touchXY.py==0x00)) iprintf("\x1b[10;5H    ");
	}while((touchXY.px>=0x00)&&(touchXY.py>=0x00)&&(touchXY.py<0xB4)&&(touchXY.py<0xFF));//B4,BF
}
void input(){		//Fonction de test des touches
	touchPosition touchXY;
	do{
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
		touchRead(&touchXY);
	}while((touchXY.px>=0x00)&&(touchXY.py>=0x00)&&(touchXY.py<0xB4)&&(touchXY.py<0xFF));
}
void clear(){
	int l,c;
	for(l=3;l<=21;l++){
		for(c=0;c<=31;c++){
			iprintf("\x1b[%u;%uH ",l,c);
		}
	}
}

int main(void) {
//Initialisation
	consoleDemoInit();
	screen();
//Programme
	while(1){
		touchPosition touchXY;
		touchRead(&touchXY);
		if((touchXY.px==0x00)&&(touchXY.py==0x00)){
			menu();
		}
		if((touchXY.px>0x50)&&(touchXY.py>0x24)&&(touchXY.px<0xA6)&&(touchXY.py<0x45)){
			clear();
			touch();
			clear();
		}
		if((touchXY.px>0x50)&&(touchXY.py>0x5B)&&(touchXY.px<0xA6)&&(touchXY.py<0x7D)){
			clear();
			input();
			clear();
		}
	}
	return 0;
}
