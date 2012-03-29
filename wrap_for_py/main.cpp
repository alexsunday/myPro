/*
#include "ISO8583.h"
#include <vector>
#include <iostream>
using namespace std;

int main()
{
	ISO8583 a;
	std::vector<ISO8583_DEF> b;
	a.loadConfig("config.xml",b);

	return 0;
}*/




#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
using namespace std;


char *get_stan_path(char *stan)
{
	static char stan_path[6+1],*stan_ptr;

	stan_ptr=stan+8;
	memset(stan_path,0,sizeof(stan_path));
	strncpy(stan_path,stan_ptr,2);
	strncat(stan_path,"/",1);
	stan_ptr+=2;
	strncat(stan_path,stan_ptr,2);
	strncat(stan_path,"/",1);

	return(stan_path);
}

int main()
{
	cout << "123548144211234" << endl;
	cout << get_stan_path("123548144211234") << endl;

	return 0;
}
