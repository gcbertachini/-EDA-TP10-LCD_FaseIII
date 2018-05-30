#pragma once

#include "LCDHitachi.h"
#include "Timer.h"
#include <string>
#include <windows.h>
#include "Observer.h"
using namespace std;



class FuncionesGenerales: public Observer
{
public:
	FuncionesGenerales(LCDHitachi& lcd_);
	~FuncionesGenerales();
	basicLCD * LCD;
	Timer * Ptimer;

	void marquesina(string str, int row);
	void imprimirPorcentaje(char porcentaje);
	void imprimirFecha(string str);
	void subir_vel();
	void bajar_vel();
	virtual void update();

private:
	const cursorPosition pos1 = { 0, 0 };
	const cursorPosition pos2 = { 1, 0 };
	int j;
	int sleepTimer;
};
