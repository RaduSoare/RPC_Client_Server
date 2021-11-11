struct SensorData
{
    int dataId;
    int noValues;
    float values[30];
};

struct LoginCredentials
{
    string username<>;
    unsigned long session_key;
};


program RPC_DB_PROG { 
    version RPC_DB_VER{
        LoginCredentials LOGIN(string) = 1;
        bool LOGOUT(string) = 2;
        bool LOAD() = 3;
        bool STORE() = 4;
        bool ADD(SensorData) = 5;
        bool DEL(int) = 6;
        bool UPDATE(SensorData) = 7;
        bool READ(int) = 8;
        bool GET_STAT(int) = 9;
        bool GET_STAT_ALL() = 10;
    } = 1;
} = 0xCAFEBABE;

