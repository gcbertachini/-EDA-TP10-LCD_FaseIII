#include "xml_getter.h"



xml_getter::xml_getter(string webpage)
{
	size_t firstBackslash = webpage.find_first_of('/');
	this->hostToGet = webpage.substr(0, firstBackslash);	// agarro la primera pare
	this->rssFeed = webpage.substr(firstBackslash);	//agarro la segunda parte
	this->fullSite = webpage;
	this->client = NULL;
}

bool xml_getter::getXml()
{
	this->client = new Client(hostToGet, PORT);
	if ((this->client))
	{
		client->link();
		string msj1 = "GET " + rssFeed + " HTTP/1.1";	//Creo los mensajes para enviar
	//	msj1.push_back(13);
	//	msj1.push_back(10);
		string msj2 = "Host: " + hostToGet;	//Creo mensajes para enviar
	///	msj2.push_back(13);
	//	msj2.push_back(10);
		string msj3 = "";
	//	msj3.push_back(13);
	//	msj3.push_back(10);
		//Aca habria que pasar los mensajes a arrays sin el terminador por las dudas
		//Uso strings por que para contcatenar es mas facil y lindo
		client->sendMessage(msj1);	//Envio los mensajes
		client->sendMessage(msj2);
		client->sendMessage(msj3);
		xmlRecieved = client->getInfoTimed(5000);	//recibo el mensaje espero max 20 segundos
		return true;
	}
	else
	{
		return false;
	}
}

string xml_getter::returnXml()
{
	if (isGetOkay())
		trim();
	else
		xmlRecieved = "Error";
	return xmlRecieved;	//Podria hacer isGetOkay y Trim privadas y usarlas aca, queda mas encapsulado y mas lindo
}

bool xml_getter::isGetOkay()
{
	size_t pos_found = xmlRecieved.find("HTTP/1.1 200 OK");	//Me fijo si aparece ese string en el xml que recibo
	if (pos_found == string::npos)	//No lo encuentra 
	{
		return false;
	}
	else
		// (PODRIA AGREGAR CONDICIONAL POSICION (deberia ser 0) TAMBIEN)
	{	
		return true;//lo encontro
	}
}

void xml_getter::trim()	//Recorto la primera informacion que no me sirve
{
	size_t pos_found2 = xmlRecieved.find_first_of("<?");	//Encuentro la posicion del primer header
	xmlRecieved = xmlRecieved.substr(pos_found2);	//Trimeo esa parte que no me sirve.
}


xml_getter::~xml_getter()
{
	delete client;
}
