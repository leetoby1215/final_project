#include "bbcar_rpc.h"
RPCFunction rpcAngle(&RPC_ServoAngle, "ServoAngle");
RPCFunction rpcStop(&RPC_ServoStop, "ServoStop");
RPCFunction rpcCtrl(&RPC_ServoCtrl, "ServoCtrl");
RPCFunction rpcTurn(&RPC_ServoTurn, "ServoTurn");
RPCFunction rpcSetController(&RPC_SetController, "setController");
RPCFunction rpcBuzz(&RPC_Buzz, "Buzz");

void RPC_ServoAngle (Arguments *in, Reply *out)   {
    float angle = in->getArg<float>();
    controller(angle);
//    ServoStop(speed);
    return;
}

void RPC_ServoStop (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    ServoStop(speed);
    return;
}

void RPC_ServoCtrl (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    ServoCtrl(speed);
    return;
}

void RPC_ServoTurn (Arguments *in, Reply *out)   {
    static int last_speed = 0;
    int speed = in->getArg<double>();
    double turn = in->getArg<double>();
    ServoTurn(speed,turn);
    return;
}

void RPC_SetController (Arguments *in, Reply *out)   {
    float kp = in->getArg<double>();
    float ki = in->getArg<double>();
    setController(kp,ki);
    return;
}

void RPC_Buzz (Arguments *in, Reply *out)   {
    Buzz();
    return;
}
