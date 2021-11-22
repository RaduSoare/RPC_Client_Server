/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpc_db.h"
#include <stdio.h>
#include <stdlib.h>
#include <rpc/pmap_clnt.h>
#include <string.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef SIG_PF
#define SIG_PF void(*)(int)
#endif

static void
rpc_db_prog_1(struct svc_req *rqstp, register SVCXPRT *transp)
{
	union {
		char *login_1_arg;
		char *logout_1_arg;
		LoadParam load_1_arg;
		u_long store_1_arg;
		SensorDataParam add_1_arg;
		IntegerParam del_1_arg;
		SensorDataParam update_1_arg;
		IntegerParam read_1_arg;
		u_long read_all_1_arg;
		IntegerParam get_stat_1_arg;
	} argument;
	char *result;
	xdrproc_t _xdr_argument, _xdr_result;
	char *(*local)(char *, struct svc_req *);

	switch (rqstp->rq_proc) {
	case NULLPROC:
		(void) svc_sendreply (transp, (xdrproc_t) xdr_void, (char *)NULL);
		return;

	case LOGIN:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_LoginCredentials;
		local = (char *(*)(char *, struct svc_req *)) login_1_svc;
		break;

	case LOGOUT:
		_xdr_argument = (xdrproc_t) xdr_wrapstring;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) logout_1_svc;
		break;

	case LOAD:
		_xdr_argument = (xdrproc_t) xdr_LoadParam;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) load_1_svc;
		break;

	case STORE:
		_xdr_argument = (xdrproc_t) xdr_u_long;
		_xdr_result = (xdrproc_t) xdr_StoreResult;
		local = (char *(*)(char *, struct svc_req *)) store_1_svc;
		break;

	case ADD:
		_xdr_argument = (xdrproc_t) xdr_SensorDataParam;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) add_1_svc;
		break;

	case DEL:
		_xdr_argument = (xdrproc_t) xdr_IntegerParam;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) del_1_svc;
		break;

	case UPDATE:
		_xdr_argument = (xdrproc_t) xdr_SensorDataParam;
		_xdr_result = (xdrproc_t) xdr_bool;
		local = (char *(*)(char *, struct svc_req *)) update_1_svc;
		break;

	case READ:
		_xdr_argument = (xdrproc_t) xdr_IntegerParam;
		_xdr_result = (xdrproc_t) xdr_SensorData;
		local = (char *(*)(char *, struct svc_req *)) read_1_svc;
		break;

	case READ_ALL:
		_xdr_argument = (xdrproc_t) xdr_u_long;
		_xdr_result = (xdrproc_t) xdr_StoreResult;
		local = (char *(*)(char *, struct svc_req *)) read_all_1_svc;
		break;

	case GET_STAT:
		_xdr_argument = (xdrproc_t) xdr_IntegerParam;
		_xdr_result = (xdrproc_t) xdr_Stats;
		local = (char *(*)(char *, struct svc_req *)) get_stat_1_svc;
		break;

	case GET_STAT_ALL:
		_xdr_argument = (xdrproc_t) xdr_void;
		_xdr_result = (xdrproc_t) xdr_AllStatsResp;
		local = (char *(*)(char *, struct svc_req *)) get_stat_all_1_svc;
		break;

	default:
		svcerr_noproc (transp);
		return;
	}
	memset ((char *)&argument, 0, sizeof (argument));
	if (!svc_getargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		svcerr_decode (transp);
		return;
	}
	result = (*local)((char *)&argument, rqstp);
	if (result != NULL && !svc_sendreply(transp, (xdrproc_t) _xdr_result, result)) {
		svcerr_systemerr (transp);
	}
	if (!svc_freeargs (transp, (xdrproc_t) _xdr_argument, (caddr_t) &argument)) {
		fprintf (stderr, "%s", "unable to free arguments");
		exit (1);
	}
	return;
}

int
main (int argc, char **argv)
{
	register SVCXPRT *transp;

	pmap_unset (RPC_DB_PROG, RPC_DB_VER);

	transp = svcudp_create(RPC_ANYSOCK);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create udp service.");
		exit(1);
	}
	if (!svc_register(transp, RPC_DB_PROG, RPC_DB_VER, rpc_db_prog_1, IPPROTO_UDP)) {
		fprintf (stderr, "%s", "unable to register (RPC_DB_PROG, RPC_DB_VER, udp).");
		exit(1);
	}

	transp = svctcp_create(RPC_ANYSOCK, 0, 0);
	if (transp == NULL) {
		fprintf (stderr, "%s", "cannot create tcp service.");
		exit(1);
	}
	if (!svc_register(transp, RPC_DB_PROG, RPC_DB_VER, rpc_db_prog_1, IPPROTO_TCP)) {
		fprintf (stderr, "%s", "unable to register (RPC_DB_PROG, RPC_DB_VER, tcp).");
		exit(1);
	}

	svc_run ();
	fprintf (stderr, "%s", "svc_run returned");
	exit (1);
	/* NOTREACHED */
}
