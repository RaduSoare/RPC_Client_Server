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
    Stats stats[100];
    int count;
};


struct LoadParam
{
    unsigned long session_key;
    SensorData clients_data<>;
};

struct StoreResult
{
    SensorData clients_data[30];
    int num;
};


program RPC_DB_PROG { 
    version RPC_DB_VER{
        LoginCredentials LOGIN(string) = 1;
        bool LOGOUT(string) = 2;
        bool LOAD(LoadParam) = 3;
        StoreResult STORE(unsigned long) = 4;
        bool ADD(SensorDataParam) = 5;
        bool DEL(IntegerParam) = 6;
        bool UPDATE(SensorDataParam) = 7;
        SensorData READ(IntegerParam) = 8;
        StoreResult READ_ALL(unsigned long) = 9;
        Stats GET_STAT(IntegerParam) = 10;
        AllStatsResp GET_STAT_ALL() = 11;
    } = 1;
} = 0xCAFEBABE;

