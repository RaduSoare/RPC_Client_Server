/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPC_DB_H_RPCGEN
#define _RPC_DB_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct SensorData {
	int dataId;
	int noValues;
	float values[30];
};
typedef struct SensorData SensorData;

struct SensorDataParam {
	SensorData sensor_data;
	u_long session_key;
};
typedef struct SensorDataParam SensorDataParam;

struct IntegerParam {
	u_long session_key;
	int value;
};
typedef struct IntegerParam IntegerParam;

struct StringParam {
	u_long session_key;
	char *value;
};
typedef struct StringParam StringParam;

struct LoadParam {
	u_long session_key;
	struct {
		u_int clients_data_len;
		SensorData *clients_data_val;
	} clients_data;
};
typedef struct LoadParam LoadParam;

struct StoreResult {
	SensorData clients_data[30];
	int num;
};
typedef struct StoreResult StoreResult;

struct LoginCredentials {
	char *username;
	u_long session_key;
};
typedef struct LoginCredentials LoginCredentials;

struct Stats {
	float min;
	float max;
	float median;
	float mean;
};
typedef struct Stats Stats;

struct AllStatsResp {
	Stats stats[30];
	int count;
};
typedef struct AllStatsResp AllStatsResp;

#define RPC_DB_PROG 0xCAFEBABE
#define RPC_DB_VER 1

#if defined(__STDC__) || defined(__cplusplus)
#define LOGIN 1
extern  LoginCredentials * login_1(char **, CLIENT *);
extern  LoginCredentials * login_1_svc(char **, struct svc_req *);
#define LOGOUT 2
extern  bool_t * logout_1(LoginCredentials *, CLIENT *);
extern  bool_t * logout_1_svc(LoginCredentials *, struct svc_req *);
#define LOAD 3
extern  bool_t * load_1(u_long *, CLIENT *);
extern  bool_t * load_1_svc(u_long *, struct svc_req *);
#define STORE 4
extern  bool_t * store_1(u_long *, CLIENT *);
extern  bool_t * store_1_svc(u_long *, struct svc_req *);
#define ADD 5
extern  bool_t * add_1(SensorDataParam *, CLIENT *);
extern  bool_t * add_1_svc(SensorDataParam *, struct svc_req *);
#define DEL 6
extern  bool_t * del_1(IntegerParam *, CLIENT *);
extern  bool_t * del_1_svc(IntegerParam *, struct svc_req *);
#define UPDATE 7
extern  bool_t * update_1(SensorDataParam *, CLIENT *);
extern  bool_t * update_1_svc(SensorDataParam *, struct svc_req *);
#define READ 8
extern  SensorData * read_1(IntegerParam *, CLIENT *);
extern  SensorData * read_1_svc(IntegerParam *, struct svc_req *);
#define READ_ALL 9
extern  StoreResult * read_all_1(u_long *, CLIENT *);
extern  StoreResult * read_all_1_svc(u_long *, struct svc_req *);
#define GET_STAT 10
extern  Stats * get_stat_1(IntegerParam *, CLIENT *);
extern  Stats * get_stat_1_svc(IntegerParam *, struct svc_req *);
#define GET_STAT_ALL 11
extern  AllStatsResp * get_stat_all_1(void *, CLIENT *);
extern  AllStatsResp * get_stat_all_1_svc(void *, struct svc_req *);
extern int rpc_db_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define LOGIN 1
extern  LoginCredentials * login_1();
extern  LoginCredentials * login_1_svc();
#define LOGOUT 2
extern  bool_t * logout_1();
extern  bool_t * logout_1_svc();
#define LOAD 3
extern  bool_t * load_1();
extern  bool_t * load_1_svc();
#define STORE 4
extern  bool_t * store_1();
extern  bool_t * store_1_svc();
#define ADD 5
extern  bool_t * add_1();
extern  bool_t * add_1_svc();
#define DEL 6
extern  bool_t * del_1();
extern  bool_t * del_1_svc();
#define UPDATE 7
extern  bool_t * update_1();
extern  bool_t * update_1_svc();
#define READ 8
extern  SensorData * read_1();
extern  SensorData * read_1_svc();
#define READ_ALL 9
extern  StoreResult * read_all_1();
extern  StoreResult * read_all_1_svc();
#define GET_STAT 10
extern  Stats * get_stat_1();
extern  Stats * get_stat_1_svc();
#define GET_STAT_ALL 11
extern  AllStatsResp * get_stat_all_1();
extern  AllStatsResp * get_stat_all_1_svc();
extern int rpc_db_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_SensorData (XDR *, SensorData*);
extern  bool_t xdr_SensorDataParam (XDR *, SensorDataParam*);
extern  bool_t xdr_IntegerParam (XDR *, IntegerParam*);
extern  bool_t xdr_StringParam (XDR *, StringParam*);
extern  bool_t xdr_LoadParam (XDR *, LoadParam*);
extern  bool_t xdr_StoreResult (XDR *, StoreResult*);
extern  bool_t xdr_LoginCredentials (XDR *, LoginCredentials*);
extern  bool_t xdr_Stats (XDR *, Stats*);
extern  bool_t xdr_AllStatsResp (XDR *, AllStatsResp*);

#else /* K&R C */
extern bool_t xdr_SensorData ();
extern bool_t xdr_SensorDataParam ();
extern bool_t xdr_IntegerParam ();
extern bool_t xdr_StringParam ();
extern bool_t xdr_LoadParam ();
extern bool_t xdr_StoreResult ();
extern bool_t xdr_LoginCredentials ();
extern bool_t xdr_Stats ();
extern bool_t xdr_AllStatsResp ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_TEST_H_RPCGEN */
