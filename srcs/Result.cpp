#include "Result.hpp"

Result::Result(T_RESULT* res)
:rowCount(-1),result(res),currentRow((Row*)NULL)
{}

Result::~Result()
{
    Close();
}

int Result::Next()
{
    T_ROW row;

    if(result==(T_RESULT*)NULL)
        throw "Result set closed.";
    row=mysql_fetch_row(result);
    if(!row)
    {
        currentRow=(Row*)NULL;
        return 0;
    }
    else
    {
        currentRow=new Row(result,row);
        return 1;
    }
}

Row* Result::GetCurrentRow()
{
    if(result==(T_RESULT*)NULL)
        throw "Result set closed.";

    return currentRow;
}

void Result::Close()
{
    if(result==(T_RESULT*)NULL)
        return;

    mysql_free_result(result);
    result=(T_RESULT*)NULL;
}

int Result::GetRowCount()
{
    if(result==(T_RESULT*)NULL)
        throw "Result set closed.";

        rowCount=mysql_num_rows(result);
    if(rowCount>-1)
        return rowCount;
    else
    return 0;
}