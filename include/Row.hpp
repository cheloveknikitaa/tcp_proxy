#pragma once

#include <sys/types.h>
#include <malloc.h>
#define HAS_MYSQL 1

#include </usr/include/mysql/mysql.h>
#define T_RESULT MYSQL_RES
#define T_ROW    MYSQL_ROW

class Row
{
    public:
        Row(T_RESULT* ,T_ROW);
        ~Row();
        
        char* GetField(int index);
        int GetFieldCount();
        int IsClosed() const;
        void Close();

     private:
        T_RESULT* result;
        T_ROW fields;
};

#endif // ROW_H