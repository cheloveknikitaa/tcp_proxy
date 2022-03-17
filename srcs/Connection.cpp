#include "Connection.hpp"

Connection::Connection(const char* host,const char* dataBase)
:affectedRows(0)
{
    connection=(MYSQL*)NULL;
    Connect(host,dataBase,(const char*)NULL,(const char*)NULL);
}

Connection::Connection(const char* host,const char* dataBase,
                       const char* userID,const char* password)
:affectedRows(0)
{
    connection=(MYSQL*)NULL;
    Connect(host,dataBase,userID,password);
}

void Connection::Connect(const char* host,const char* dataBase,
                         const char* userID,const char* password)
{
    int state;

    if(IsConnected())
        throw "Connection has been established.";
    mysql_init(&mysql);
    connection=mysql_real_connect(&mysql,host,userID,password,
                                     dataBase,0,NULL,0);
    if(!IsConnected())
        throw GetError();

    if(state<0)
        throw GetError();
}

Connection::~Connection()
{
    if(IsConnected())
        Close();
}

void Connection::Close()
{
    if(!IsConnected())
        return;

    mysql_close(connection);
    connection=(MYSQL*)NULL;
}

Result* Connection::Query(const char* sqlCommand)
{
    T_RESULT* result;
    int state;

    if(!IsConnected())
        throw "DataBase not connected.";

    state=mysql_query(connection,sqlCommand);

    if(state!=0)
        throw GetError();

    result=mysql_store_result(connection);

    //if the result was null,it was an update or an error occurred
    if(result==(T_RESULT*)NULL)
    {
        int fieldCount=mysql_field_count(connection);
        if(fieldCount!=0)
            throw GetError();
        else
            affectedRows=mysql_affected_rows(connection);
        //return NULL for updates
        return (Result*)NULL;
     }
     //return a Result instance for queries
     return new Result(result);
}

int Connection::GetAffectedRows() const
{
    return affectedRows;
}

const char* Connection::GetError()
{
    if(IsConnected())
        return mysql_error(connection);
    else
        return mysql_error(&mysql);
}

int Connection::IsConnected() const
{
    return (connection!=NULL);
}