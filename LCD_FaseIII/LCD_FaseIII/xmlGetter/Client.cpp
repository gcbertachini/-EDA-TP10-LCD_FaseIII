#include "Client.h"


using namespace boost::asio;
Client::Client(string ip, const char * port_)		
{
	this->IOHandler = new io_service();
	this->clientSocket = new ip::tcp::socket(*IOHandler);
	this->clientResolver = new ip::tcp::resolver(*IOHandler);

	ipToConect = ip;
	port = port_;
}

//using namespace boost::asio;
void Client::link()	//Conecto al ip enviado
{

	/*size_t stringLength = ipToConect.length();
	char* messagePointer = new char[stringLength]; //Data sin \n
	ipToConect.copy(messagePointer, stringLength);	//Copio data a arreglo*/

	auto q = ip::tcp::resolver::query(ipToConect.c_str(), this->port);
	this->endpoint = clientResolver->resolve(q);
	cout << "Connecting to Server" << endl;
	try {
		connect(*clientSocket, endpoint);
	}
	catch (const std::exception& error) {
		// Should print the actual error message
		std::cerr << error.what() << std::endl;
	}
	
	clientSocket->non_blocking(true);
	

	cout << "Client trying to connect to " << ipToConect.c_str() << endl;

	//delete[] messagePointer;
}

void Client::sendMessage(string msg)	//Envio mensaje
{
	std::cout << "Trying to send message" << std::endl;
	size_t lenght = 0;
	boost::system::error_code error;
	//En vez de enviar un string envio un arreglo de chars sin el terminador
	size_t stringLength = msg.size();	
	char* messagePointer = new char[stringLength]; //Data sin \n
	msg.copy(messagePointer, stringLength);	//Copio data a arreglo

	lenght = this->clientSocket->write_some(boost::asio::buffer(messagePointer,stringLength), error);

	char dec = 13;
	char*pdec = &dec;
	lenght += this->clientSocket->write_some(boost::asio::buffer(pdec,1), error);
	dec = 10;
	lenght += this->clientSocket->write_some(boost::asio::buffer(pdec,1), error);

	std::cout << "Message sent, lenght =" <<lenght <<"Message"<<msg<<std::endl;

	delete[] messagePointer;
}

/*bool Client::sendMessageTimed(string msg, int ms)
{
	std::cout << "Trying to send message" << std::endl;
	Timer timer;
	timer.start();
	bool timeout = false;

	size_t lenght = 0;
	boost::system::error_code error;

	do {
		lenght = this->clientSocket->write_some(boost::asio::buffer(msg, msg.size()), error);
		timer.stop();
		if (timer.getTime() > ms && lenght == 0)
			timeout = true;
	} while (error && !timeout);

	return !timeout;
}
*/
std::string Client::getInfo() {

	char buffer[1 + 255 + 1];
	size_t lenght = 0;
	boost::system::error_code error;

	do {
		lenght = this->clientSocket->read_some(boost::asio::buffer(buffer), error);
	} while (error);

	buffer[lenght] = 0;
	std::string retValue = buffer;
	std::cout << "Recieved a message" << std::endl;

	return retValue;
}

string Client::getInfoTimed(int ms)	//ESTO HAY QUE REHACER
{
	Timer timer;
	string buffer;
	char hola[1024];
	size_t length = 0;
	boost::system::error_code error;
	timer.start();
	bool timeout = false;
	string last_string = "";
	string aux_string = "";

	try
	{
		while (!timeout)
		{
			do {
				length = this->clientSocket->read_some(boost::asio::buffer(hola, 1024), error);	//leo, lo mato con breaks por que sino se queda esperando
				
				timer.stop();
				if (timer.getTime() < ms) {	//todavia no me pase de tiempo
					timeout = false;
					aux_string = string(hola);
					if (/*last_string !=aux_string*/ length)
					{
						buffer += aux_string;
						//last_string = aux_string;
					}
					else
					{
						break;
					}
				}
				else
				{
					timeout = true;
					break;
				}

			} while ((error.value() == WSAEWOULDBLOCK));
		}
		int erval = error.value();
		if (error == boost::asio::error::eof)
			cout << "Mensaje recibido bien";
		else if (error)
			throw boost::system::system_error(error); // Some other error.
	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return buffer;
}


Client::~Client()
{
	std::cout << "Closing connection" << std::endl;
	this->clientSocket->close();
	delete this->clientResolver;
	delete this->clientSocket;
	delete this->IOHandler;
}
