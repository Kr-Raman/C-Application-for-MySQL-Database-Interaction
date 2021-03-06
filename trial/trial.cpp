#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;


// just going to input the general details and not the port numbers
struct connection_details
{
    const char* server;
    const char* user;
    const char* password;
    //const char* database;
};
struct connection_details mysqlD;
MYSQL* mysql_connection_setup(struct connection_details mysql_details)
{
    // first of all create a mysql instance and initialize the variables within
    MYSQL* connection = mysql_init(NULL);

    // connect to the database with the details attached.
    if (!mysql_real_connect(connection, mysql_details.server, mysql_details.user, mysql_details.password, NULL, 0, NULL, 0)) {
       // printf("Conection error : %s\n", mysql_error(connection));
        cout << "Connect Error : " << mysql_error(connection)<<endl;
        exit(1);
    }
    else
    {
        cout << "Connection Established" << endl;
    }
    return connection;
}
//---------------------------------------------------------------->>>>> Function to Execute Any Specified query which does not have a predefined function
void mysql_perform_query(MYSQL* connection, const char* sql_query)
{
    MYSQL_RES* res;
    MYSQL_ROW row;
    // send the query to the database
    if (mysql_query(connection, sql_query))
    {
       // printf("MySQL query error : %s\n", mysql_error(connection));
        cout << "Connect Error : " << mysql_error(connection) << endl;
        exit(1);
    }

    res=  mysql_use_result(connection);
    cout << "Mysql Tables in Mysql database " << endl;
    while ((row = mysql_fetch_row(res)) != NULL)
        cout <<"->" << row[0] << endl;

    mysql_free_result(res);
}
//---------------------------------------------------------------->>>>> Function to show all the DATABASES
void mysql_list_database(MYSQL* connection, const char* wild)
{
    MYSQL_RES* res = mysql_list_dbs(connection,wild);
    MYSQL_ROW row;
    // send the query to the database
    if (!res)
    {
        cout << "Connection Error"<<endl;
    }
    

    //res = mysql_use_result(connection);
    cout << "-->MySQL all DATABASES :: " << endl;
    while ((row = mysql_fetch_row(res)) != NULL)
        cout << row[0] << endl;

    mysql_free_result(res);
}
void mysql_select_database(MYSQL* connection,const char* input)
{
    int res = mysql_select_db(connection, input);
    if (res==0)
    {
        //cout << "Error in connecting to the specfied Database " << input << endl;
        cout << "Connected to " << input << "  Database" << endl;
    }
    else
    {
        cout << "Error in connecting to the specfied Database " << input << endl;
        //cout << "Connected to " << input << "Database" << endl;
    }
}

/*
    choose a database
    create new table
    fetch records
    insert record
    update record
    **fetch a particular record according to the given input from the user
    drop a table
    drop a database

    ---------------------------------------------------------

    1-Create restriction ---currentyly hm system ke database ko bhi access kr pa re hai which is not good
    2-Create Hierarchy >>> admin>>department>>Employee types;

    $$$$---REGARDING DISPLAY OF THE CONTENT
    -- CREATE A PROPER LAYOUT
    -- SESSION CREATE KR PAYE TO IT WILL BE BETTER -- session mtlb ki abhi baar baar pura while ke andr ke contnet print ho rha hai acha ni lg rha

    $$$----QUESTIONS
    --- is it possible to create link between two databases
    --- IF YES then what is the use of that HOW can i use it
    --- can i take connection from a remote server
    --- HOW can i Implement DATA STRUCTURES in it... cuz abhi to kuch bhi aisa smjh ni aa rha jaha mai usko use kr pau.

*/



int main()
{
    MYSQL* conn;		// the connection
  //  MYSQL_RES* res;	// the results
   // MYSQL_ROW row;	// the results row (line by line)


    mysqlD.server = "localhost";  // where the mysql database is
    mysqlD.user = "root";		// the root user of mysql	
    mysqlD.password = "0ZfmSg@1"; // the password of the root user in mysql
    //mysqlD.database = "trail";	// the databse to pick

    // connect to the mysql database
    conn = mysql_connection_setup(mysqlD);

    // assign the results return to the MYSQL_RES pointer
    
    while (1)
    {
        int input = 0;
        cout << endl << endl;
        cout << "Enter the Number before the Instruction you want to perform" << endl;
        cout << "1. Show all DaTabase" << endl;
        cout << "2. Connect to a Database" << endl;
        cout << "3. show what's inside the Database" << endl;
        cout << "4. Select a Table" << endl;
        cin >> input;
            switch (input)
            {
                case 1:
                    mysql_list_database(conn, "%");
                    break;
                case 2:
                    cout << "-->Enter the Name of the database to Enter into" << endl;
                    char in[100];
                    cin >> in;
                    mysql_select_database(conn, in);
                    break;
                   
                case 3:
                    //cout << "-->Enter the name of the ";
                    mysql_perform_query(conn, "show tables");
                  
                    break;
            default:
                break;
            }
    }
   

   
   

    /* clean up the database result set */
    
    /* clean up the database link */
    mysql_close(conn);

    return 0;
}
//mysql_list_dbs( )
//mysql_select_db( )