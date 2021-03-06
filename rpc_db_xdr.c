/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "rpc_db.h"

bool_t
xdr_SensorData (XDR *xdrs, SensorData *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_int (xdrs, &objp->dataId))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->noValues))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->values, 30,
		sizeof (float), (xdrproc_t) xdr_float))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_LoginCredentials (XDR *xdrs, LoginCredentials *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->username, ~0))
		 return FALSE;
	 if (!xdr_u_long (xdrs, &objp->session_key))
		 return FALSE;
	return TRUE;
}
