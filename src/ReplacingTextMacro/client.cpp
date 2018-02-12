#include "Classes.h"
#include "ClassList.h"
//#include <iostream>


enum MessageTypeId
{
#define INIT_MESSAGE(ID, NAME)          \
	NAME ,\

	DEFINES_TEMPLATES(INIT_MESSAGE)
#undef INIT_MESSAGE
	MESSAGE_TYPE_COUNT
};


struct ICaller
		{
#define DEFINE_TEMPLATE(ID, NAME)                           \
	virtual int process(NAME const& msg) { return -1; } \

	DEFINES_TEMPLATES(DEFINE_TEMPLATE)
#undef DEFINE_TEMPLATE
};


int main() 
{
	MessageTypeId test;
//	std::cout << test::MESSAGE_TYPE_COUNT <<std::endl;
//	std::cout << test::ABC <<std::endl;

}
