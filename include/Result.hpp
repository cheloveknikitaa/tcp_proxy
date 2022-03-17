#pragma once

#include <sys/time.h>
#include </usr/include/mysql/mysql.h>
#include "Row.hpp"

class Result
{
    public:
        Result(T_RESULT* );
        ~Result();

        void Close();
        Row* GetCurrentRow();
        int GetRowCount();
        int Next();

     private:
        int rowCount;
        T_RESULT* result;
        Row* currentRow;
};
