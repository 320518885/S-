#ifndef __S_SHAPED_AC_DEC_H
#define __S_SHAPED_AC_DEC_H

#include "main.h"
typedef struct {
	float S_sum;
	float Jerk;
	float S_Acc;
	float Vm;//中点速度
	float uniform_S;
	float Vt;//最大速度
	float Acc_t;//加加速度的时间
	float t_sum;
	float V_now;
	float V0;
	float Ve;
	float S_now;
	float delta_t;
} speed_calc_t;


//float calc_speed(speed_calc_t *m_calc_t, float time_now);
//void calc_S_speed_data(speed_calc_t *m_calc_t,float v0,float vt,float time,float S);
//void S_Init(void);
//void S_Going(void);

//void calc_S_speed_data(speed_calc_t *m_calc_t,float vt,float J,float S);
//float calc_speed(speed_calc_t *m_calc_t, float time_now);
//void S_Init(void);
//void S_Going(void);
int Iteration_S(float *vt,float ve,float vs,float S,float J,float *Sa,float *Sd);
void calc_S_speed_data(speed_calc_t *m_calc_t,float v0,float vs,float vt,float J,float S);
float calc_speed(speed_calc_t *m_calc_t, float time_now);
void S_Init(void);
void S_Going(void);

extern speed_calc_t m_calc_t;

#endif
