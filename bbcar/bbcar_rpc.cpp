#include "bbcar_rpc.h"
RPCFunction rpcAngle(&RPC_angle, "angle");
RPCFunction rpcStop(&RPC_stop, "stop");
RPCFunction rpcCtrl(&RPC_goStraght, "goStraght");
RPCFunction rpcTurn(&RPC_turn, "turn");
RPCFunction rpcSetController(&RPC_setController, "setController");

extern BBCar car;

void RPC_angle (Arguments *in, Reply *out)   {
    float angle = in->getArg<float>();
    car.controller(angle);
//    ServoStop(speed);
    return;
}

void RPC_stop (Arguments *in, Reply *out)   {
    car.servoStop();
    return;
}

void RPC_goStraight (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    car.servoCtrl(speed);
    return;
}

void RPC_turn (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    double turn = in->getArg<double>();
    car.servoTurn(speed,turn);
    return;
}

void RPC_setController (Arguments *in, Reply *out)   {
    float kp = in->getArg<double>();
    float ki = in->getArg<double>();
    car.setController(kp,ki);
    return;
}