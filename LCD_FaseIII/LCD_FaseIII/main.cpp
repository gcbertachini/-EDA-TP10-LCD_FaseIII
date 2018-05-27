#include <stdio.h>
#include "expat.h"
#include "Feed.h"

void start_tag(void *userData, const XML_Char *name, const XML_Char **atts);
void end_tag(void *userData, const XML_Char *name);
void char_data(void *userData, const XML_Char *s, int len);

typedef struct {

} my_user_data_t;

int main(void)
{
	FILE * my_file = NULL;
	
	XML_Parser parser;
	XML_Status status;
	my_user_data_t user_data;
	
	parser = XML_ParserCreate(NULL);			//despues llamar a XML_ParserFree();
	XML_SetElementHandler(parser, start_tag, end_tag);		//Sets handlers for start and end tags.
	XML_SetCharacterDataHandler(parser, char_data);			//Sets handler for text.
	XML_SetUserData(parser, &user_data);
	Feed feed;
	char * buffer = NULL;
	my_file = fopen("ejemplo.xml", "rb");			
	if (my_file != NULL) {

		int file_size = getSize(my_file);

		buffer = (char *) malloc(file_size * sizeof(char));
		if (buffer != NULL) {
			fread(buffer, sizeof(char), file_size, my_file);
			XML_Parse(parser, buffer, file_size, true);
		}

	}

	XML_ParserFree(parser);
	free(buffer);
	fclose(my_file);

	return;
}

void start_tag(void *userData, const XML_Char *name, const XML_Char **atts) {

}
void end_tag(void *userData, const XML_Char *name) {

}
void char_data(void *userData, const XML_Char *s, int len) {			//NOT zero terminated. You have to use the length argument to deal with the end of the string. 

}