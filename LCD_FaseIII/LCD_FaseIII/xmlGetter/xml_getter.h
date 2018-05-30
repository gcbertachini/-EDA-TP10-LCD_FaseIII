#pragma once
#include"Client.h"
#include<string>
using namespace std;
#define PORT "80"
#include "Observable.h"

class xml_getter : public Observable
{
public:
	xml_getter(string webpage);	
	~xml_getter();
	bool getXml(); //Busca el xml en una el sitio
	string returnXml(); //Si esta todo bien devuelve el xml en un string, si no devuelve "Error"
	

private:
	bool isGetOkay();
	void trim();
	Client* client;
	string hostToGet;
	string rssFeed;
	string xmlRecieved;
	string fullSite;
};

