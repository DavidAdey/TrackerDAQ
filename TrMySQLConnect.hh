#include <mysql/mysql.h>
#include <iostream>
#include <fstream>
#include "TrGlobals.hh"

#ifndef TRMYSQLCONNECT_HH
#define TRMYSQLCONNECT_HH

class TrMySQLConnect {

	private:
		MYSQL *connection;	
	public:
		TrMySQLConnect();
		int connect();
		int disconect();
		int query(std::string);
		

};


#endif
