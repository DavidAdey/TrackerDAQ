#include "TrMySQLConnect.hh"

TrMySQLConnect::TrMySQLConnect() {

	connection = mysql_init(NULL);
	if (!connection) {
		fprintf(stderr,"Connection failed to initialise");
	}
}

/*TrMySQLConnect::~TrMySQLConnect() {
	delete connection;
}*/

int TrMySQLConnect::connect() {
	
    connection = mysql_real_connect(connection,SERVER,USER,PASSWORD,DATABASE,0,NULL,0); 
    if(connection){
	printf("Connection OK\n");
    }
    else{
        printf("Connection failed\n");
    }
	return 0;
}

/*int TrMySQLConnect::query(std::string query) {

	MYSQL_RES result*;
	MYSQL_ROW *row;
	mysql_query(connection, query);
	result = mysql_store_result(connection);

}*/
