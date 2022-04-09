#include "data_template.h"
#ifdef TEMPLATE_H
#include "data_template.cpp"
#endif

#ifndef COLLECT_H
#define COLLECT_H

// declare a function to calculate the collecting duration
float timestamp(struct timeval t_start, struct timeval t_end);

// declare functions to collect data from different sensors

void collect_pression(int i);

void collect_humidity(int i);

void collect_temperature(int i);

void collect_orientation(int i);

void collect_acceleration(int i);

void collect_magnetisme(int i);

// declare a function to unify all collecting functions using the function pointer
void mainFcn(void (*collectFcn)(int i));

#endif
