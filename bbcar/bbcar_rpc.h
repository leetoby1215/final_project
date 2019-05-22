#ifndef BBCAR_RPC_H
#define BBCAR_RPC_H

#include "bbcar.h"
#include "mbed_rpc.h"

void RPC_ServoStop(Arguments *in, Reply *out);
void RPC_ServoCtrl(Arguments *in, Reply *out);
void RPC_ServoTurn(Arguments *in, Reply *out);
void RPC_ServoAngle(Arguments *in, Reply *out);
void RPC_SetController (Arguments *in, Reply *out);

#endif
