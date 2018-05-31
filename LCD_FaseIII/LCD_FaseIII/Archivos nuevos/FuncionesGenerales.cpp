#include "FuncionesGenerales.h"


FuncionesGenerales::FuncionesGenerales(LCDHitachi& lcd_)
{
	LCD = &lcd_;
	this->Ptimer = new Timer;
	this->sleepTimer = 150;
}


FuncionesGenerales::~FuncionesGenerales()
{
	delete Ptimer;
}


bool FuncionesGenerales::marquesina(string str, int row)
{
	Ptimer->stop();
	bool aux;

	if (Ptimer->getTime() > sleepTimer)
	{
		string blankSpace("                ");   //Espacio LCD sin nada bien tumbero!!!
		str = blankSpace + str + blankSpace;
		int sizeStr = str.size();

		unsigned char * pdm = (unsigned char *)str.c_str();


		if (j <= (sizeStr - 16))
		{
			if (!row)
				LCD->lcdSetCursorPosition(pos1);
			else
				LCD->lcdSetCursorPosition(pos2);

			for (int i = j; i < (16 + j); i++)
			{
				*LCD << str[i];
			}
			j++;
		}
		if (j <= (sizeStr - 16))
		{
			aux = false;
		}
		else
		{
			aux = true;
			resetCounter();
		}
	}
	Ptimer->start();
	return aux;
}


void FuncionesGenerales::imprimirPorcentaje(char porcentaje)
{
	string blankSpace = "      ";
	string simpleBlank = " ";
	string simbPorcentaje = "%";
	std::string str = blankSpace + to_string(porcentaje) + simpleBlank + simbPorcentaje + blankSpace;

	unsigned char * pdm = (unsigned char *)str.c_str();

	if (LCD->lcdSetCursorPosition(pos2))
	{
		*LCD << pdm;
	}
}


void FuncionesGenerales::imprimirFecha(string str)
{
	unsigned char * pdm = (unsigned char *)str.c_str();

	if (LCD->lcdSetCursorPosition(pos1))
	{
		*LCD << pdm;
	}
}


//void FuncionesGenerales::marquesina(string str, int row)
//{
//	string blankSpace("                ");   //Espacio LCD sin nada bien tumbero!!!
//	str = blankSpace + str + blankSpace;
//	int sizeStr = str.size();
//
//	unsigned char * pdm = (unsigned char *)str.c_str();
//
//	for (int j = 0; j <= (sizeStr - 16); j++)
//	{
//		if (!row)
//			LCD->lcdSetCursorPosition(pos1);
//		else
//			LCD->lcdSetCursorPosition(pos2);
//
//		for (int i = j; i < (16 + j); i++)
//		{
//			*LCD << str[i];
//		}
//	}
//}


void FuncionesGenerales::update() {

	static char percentage = 0;

	imprimirPorcentaje(percentage);
	percentage++;

	if (percentage == 99) {
		LCD->lcdClear();
		percentage = 0;
	}
	
}


void FuncionesGenerales::subir_vel()
{
	if (sleepTimer >= 50)
	{
		sleepTimer -= 50;
	}
}


void FuncionesGenerales::bajar_vel()
{
	if (sleepTimer <= 300)
	{
		sleepTimer += 50;
	}
}

void FuncionesGenerales::resetCounter()
{
	this->j = 0;
}