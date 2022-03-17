#include "Row.hpp"

Row::Row(T_RESULT* res,T_ROW row)
:result(res),fields(row)
{}

Row::~Row()
{
    if(!IsClosed())
        Close();
}

void Row::Close()
{
    if(IsClosed())
        throw "Row closed.";

    fields=(T_ROW)NULL;
    result=(T_RESULT*)NULL;
}

int Row::GetFieldCount()
{
    if(IsClosed())
        throw "Row closed.";

    return mysql_num_fields(result);
}

char* Row::GetField(int field)
{
    if(IsClosed())
        throw "Row closed.";

    if(field<0 || field>GetFieldCount()-1)
        throw "Field index out of bounds.";

    return fields[field];
}

int Row::IsClosed() const
{
    return (fields==(T_ROW)NULL);
}