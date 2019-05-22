#include "bbcar_rpc.h"
RPCFunction rpcAngle(&RPC_ServoAngle, "ServoAngle");
RPCFunction rpcStop(&RPC_ServoStop, "ServoStop");
RPCFunction rpcCtrl(&RPC_ServoCtrl, "ServoCtrl");
RPCFunction rpcTurn(&RPC_ServoTurn, "ServoTurn");
RPCFunction rpcSetController(&RPC_SetController, "setController");

extern BBCar car;

void RPC_ServoAngle (Arguments *in, Reply *out)   {
    float angle = in->getArg<float>();
    car.controller(angle);
//    ServoStop(speed);
    return;
}

void RPC_ServoStop (Arguments *in, Reply *out)   {
    car.servoStop();
    return;
}

void RPC_ServoCtrl (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    car.servoCtrl(speed);
    return;
}

void RPC_ServoTurn (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    double turn = in->getArg<double>();
    car.servoTurn(speed,turn);
    return;
}

void RPC_SetController (Arguments *in, Reply *out)   {
    float kp = in->getArg<double>();
    float ki = in->getArg<double>();
    car.setController(kp,ki);
    return;
}