#include "data_template.h"
#ifdef TEMPLATE_H
#include "data_template.cpp"
#endif

#ifndef COLLECT_H
#define COLLECT_H

float timestamp(struct timeval t_start, struct timeval t_end);

void collect_pression(int i);

void collect_humidity(int i);

void collect_temperature(int i);

void collect_orientation(int i);

void collect_acceleration(int i);

void collect_magnetisme(int i);

void mainFcn(void (*collectFcn)(int i));

#endif
