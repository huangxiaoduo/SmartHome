/*
 * ipptvfun.h
 *
 *  Created on: 2012-9-29
 *       Author: jingyu.wang
 */

#ifndef IPPIBFUN_H_
#define IPPIBFUN_H_
#include "ippstruct.h"

int
fnIBSetPowerMode(int id, int mode);

int
fnIBSetColdTemprature(int id, int temp);

int
fnIBSetFreezeTemprature(int id, int temp);

int
fnIBSetVariableTemprature(int id, int temp);

int fnIBGetColdTemprature(int id);

int fnIBGetFreezeTemprature(int id);

int fnIBGetSensorVariableTemprature(int id);

int fnIBGetSensorColdTemprature(int id);

int fnIBGetSensorFreezeTemprature(int id);
int fnIBGetIndoorTemprature(int id);

int fnIBGetVariableTemprature(int id);

int fnIBSetWorkMode(int id, int mode, int onoff);

int fnIBGetWorkMode(int id, int mode);

int fnIBSetHighTimeStart(int id, int hours, int second);
int fnIBSetHighTimeEnd(int id, int hours, int second);
int fnIBSetLowTimeStart(int id, int hours, int second);
int fnIBSetLowTimeEnd(int id, int hours, int second);


int fnIBGetLowTimeStart(int id, int* time);
int fnIBGetLowTimeEnd(int id, int* time);













int fnIBGetDoorStatus(int dev, PIBDoorStatus ret);

int fnIBSetWIFISSID(int dev, char* ssid, int len);

int fnIBSetWIFIPASSWORD(int dev,char* password, int len);

int fnIBSetACTIVECODE(int dev, char* activecode, int len);

#endif /* IPPTVFUN_H_ */
