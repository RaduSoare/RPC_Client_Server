struct SensorData
{
    int dataId;
    int noValues;
    float* values;
};

struct LoginCredentials
{
    string username<>;
    unsigned long session_key;
};


program RPC_DB_PROG { 
    version RPC_DB_VER{
        LoginCredentials LOGIN(string) = 1;
        void LOGOUT() = 2;
        void LOAD() = 3;
        void STORE() = 4;
        void ADD() = 5;
        void DEL() = 6;
        void UPDATE() = 7;
        void READ() = 8;
        void GET_STAT() = 9;
        void GET_STAT_ALL() = 10;
    } = 1;
} = 0xCAFEBABE;

