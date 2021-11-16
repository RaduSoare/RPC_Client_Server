struct SensorData
{
    int dataId;
    int noValues;
    float values[30];
};

struct SensorDataParam
{
    SensorData sensor_data;
    unsigned long session_key;
};

struct IntegerParam
{
    unsigned long session_key;
    int value;
};

struct StringParam 
{
    unsigned long session_key;
    string value<>;
};

struct LoginCredentials
{
    string username<>;
    unsigned long session_key;
};

struct Stats
{
    float min;
    float max;
    float median;
    float mean;
};

struct AllStatsResp
{
    Stats stats<>;
};


program RPC_DB_PROG { 
    version RPC_DB_VER{
        LoginCredentials LOGIN(string) = 1;
        bool LOGOUT(string) = 2;
        bool LOAD(unsigned long) = 3;
        bool STORE(unsigned long) = 4;
        bool ADD(SensorDataParam) = 5;
        bool DEL(IntegerParam) = 6;
        bool UPDATE(SensorDataParam) = 7;
        bool READ(int) = 8;
        bool GET_STAT(int) = 9;
        bool GET_STAT_ALL() = 10;
    } = 1;
} = 0xCAFEBABE;

