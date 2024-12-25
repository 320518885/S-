#include "S-shaped_ac_dec.h"
#include "math.h"

#define SPEED_2_ROUNDS(rads) rads/6.28f   //将单位转换为（圈/秒）
#define INCACCELROUND(j,t)       ( ( (j) * pow( (t) , 3 ) ) / 6.0f )     /* 加加速段的位移量(圈数)  S = 1/6 * J * t^3 */



speed_calc_t m_calc_t;


//传入速度的单位为rad/s(弧度/秒)   传入的v0是初速度，vt是最大速度，time是加速段的时间（s）,S是目标总弧度值, -----------------基于时间的S型加减速
//void calc_S_speed_data(speed_calc_t *m_calc_t,float v0,float vt,float time,float S)
//{
//	//只要计算出一段加加速段的时间就可以得到所有时间
//	//因为已知中点的速度，先求出加加速度
//	m_calc_t->Acc_t = time/2.0f;//加加速段的时间为加速段的时间的一半
//	m_calc_t->Vm = fabs((v0+vt)/2);
//	m_calc_t->Jerk = 2.0f*m_calc_t->Vm/(m_calc_t->Acc_t * m_calc_t->Acc_t); //加加速度
//	m_calc_t->S_Acc = 0.166666667f*(m_calc_t->Jerk*pow(m_calc_t->Acc_t,3)) ; //加加速段的弧度总值
//	m_calc_t->S_sum = 4.0f*m_calc_t->S_Acc; //加减速度的总路程的弧度值
//	m_calc_t->Vt = vt;
//	m_calc_t->V_now=0;
//	m_calc_t->V0=v0;
//	m_calc_t->S_now=0;
//	m_calc_t->delta_t=0.001f;
//	if(m_calc_t->S_sum<S)
//	{
//		m_calc_t->uniform_S = S - m_calc_t->S_sum;
//	}else
//	{
//		m_calc_t->uniform_S = 0;
//	}
//}




//float t1;
//float t2;
//float t3;	
//float t4;
//float t5;

//float calc_speed(speed_calc_t *m_calc_t, float time_now) {
//    float Vnext;

//    // 定义时间界限
//     t1 = m_calc_t->Acc_t;          // 加速阶段时间
//     t2 = 2 * m_calc_t->Acc_t;      // 匀加速阶段结束时间
//    float S_uniform = m_calc_t->uniform_S; // 匀速段的距离
//     t3 = t2 + (S_uniform / m_calc_t->Vm); // 匀速阶段结束时间
//     t4 = t3 + m_calc_t->Acc_t;     // 减速阶段结束时间
//     t5 = t4 + m_calc_t->Acc_t;     // 再次加速阶段结束时间

//    // 加加速阶段（0 ≤ t ≤ t1）
//    if (time_now >= 0 && time_now <= t1) {
//        Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(time_now, 2)) / 2.0f;
//    }
//    // 减加速阶段（t1 < t ≤ t2）
//    else if (time_now > t1 && time_now <= t2) {
//        Vnext = m_calc_t->Vm + m_calc_t->Jerk * m_calc_t->Acc_t * (time_now - t1) 
//                 - (m_calc_t->Jerk * pow(time_now - t1, 2)) / 2.0f;
//    }
//    // 匀速阶段（t2 < t ≤ t3）
//    else if (time_now > t2 && time_now <= t3) {
//        Vnext = m_calc_t->Vt; // 匀速保持 Vm
//    }
//    // 加减速阶段（t3 < t ≤ t4）
//    else if (time_now > t3 && time_now <= t4) {
//        Vnext = m_calc_t->Vt - (m_calc_t->Jerk * pow(time_now - t3, 2)) / 2.0f;
//    }
//    // 减减速阶段（t4 < t ≤ t5）
//    else if (time_now > t4 && time_now <= t5) {
////        Vnext = m_calc_t->Vt - (m_calc_t->Jerk * pow(t4 - t3, 2)) / 2.0f - m_calc_t->Jerk * t4 * (time_now - t4) 
////                 + (m_calc_t->Jerk * pow(time_now - t4, 2)) / 2.0f;
//		
//		Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(t5-time_now, 2)) / 2.0f;
//    }
//    // 默认情况
//    else {
//        Vnext = 0; // 或者可以返回其他合适的值
//    }

//    return Vnext;
//}



//void S_Init(void)
//{
//	calc_S_speed_data(&m_calc_t,0.0f,10.0f,20.0f,100.0f);
//	
//}

//void S_Going(void)
//{
//	m_calc_t.t_sum += m_calc_t.delta_t;
//	m_calc_t.V_now  = calc_speed(&m_calc_t,m_calc_t.t_sum);
//	
//	
//}



















//float t1;
//float t2;
//float t3;	
//float t4;
//float t5;

//float T1,T2,T3,T4,T5;
//float V1,V2,V3,V4,V5;

//void calc_S_speed_data(speed_calc_t *m_calc_t,float vt,float J,float S) //--------------------- vs=ve=0
//{
//	m_calc_t->Jerk = J;
//	m_calc_t->V0 = 0;
//	m_calc_t->delta_t = 0.001;
//	float Sa,Sd;
//	Sa=Sd=vt*sqrt(vt/J);
//	if(Sa + Sd <=S)
//	{
//		t1 = t2 = t4 = t5 = sqrt(vt/J);
//		t3 = (S - Sa - Sd)/vt;
//	}else if(Sa + Sd >S)
//	{
//		float v_ = pow(pow(S/2 ,2)*J,0.33333333333f);//这里不能用1/3，要直接用小数点的形式，不然出问题
//		t1 = t2 = t4 = t5 = sqrt(v_/J);
//		t3 = 0;
//	}
//	
//	T1 = t1;
//	T2 = t1+t2;
//	T3 = t1+t2+t3;
//	T4 = t1+t2+t3+t4;
//	T5 = t1+t2+t3+t4+t5;
//	
//	V1 = m_calc_t->V0 + (m_calc_t->Jerk * pow(T1, 2)) / 2.0f;
//	V2 = V1 + J * T1 * (T2 - T1) - J * pow(T2 - T1, 2) / 2.0f;
//	V3 = V2;
//	V4 = V3 - (J * pow(T4 - T3, 2)) / 2.0f;
//	V5 = m_calc_t->V0 ;
//}




//float calc_speed(speed_calc_t *m_calc_t, float time_now) {
//    float Vnext;
//	

//    // 加加速阶段（0 ≤ t ≤ t1）
//    if (time_now >= 0 && time_now <= T1) {
//        Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(time_now, 2)) / 2.0f;
//    }
//    // 减加速阶段（t1 < t ≤ t2）
//    else if (time_now > T1 && time_now <= T2) {
//        Vnext = V1 + m_calc_t->Jerk * T1 * (time_now - T1) - m_calc_t->Jerk * pow(time_now - T1, 2) / 2.0f;
//    }
//    // 匀速阶段（t2 < t ≤ t3）
//    else if (time_now > T2 && time_now <= T3) {
//        Vnext = V2; // 匀速保持 Vm
//    }
//    // 加减速阶段（t3 < t ≤ t4）
//    else if (time_now > T3 && time_now <= T4) {
//        Vnext = V3 - (m_calc_t->Jerk * pow(time_now - T3, 2)) / 2.0f;
//    }
//    // 减减速阶段（t4 < t ≤ t5）
//    else if (time_now > T4 && time_now <= T5) {		
//		Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(T5 - time_now, 2)) / 2.0f ;
//    }
//    // 默认情况
//    else {
//        Vnext = 0; // 或者可以返回其他合适的值
//    }

//    return Vnext;
//}



//void S_Init(void)
//{
//	calc_S_speed_data(&m_calc_t,100.0f,2.0f,1000.0f);
//	
//}

//void S_Going(void)
//{
//	m_calc_t.t_sum += m_calc_t.delta_t;
//	m_calc_t.V_now  = calc_speed(&m_calc_t,m_calc_t.t_sum);
//	m_calc_t.S_now += m_calc_t.V_now*0.001f;
//	
//}





int Iteration_S(float *vt,float ve,float vs,float S,float J,float *Sa,float *Sd)
{
		float v1 = *vt;
		float v2 = vs>ve?vs:ve;
		int i=0;
		while(i<=9)
		{
			*vt = (v1+v2)/2.0f;
			*Sa=(*vt+vs)*sqrt((*vt - vs)/J);
			*Sd=(*vt+ve)*sqrt((*vt - ve)/J);
			if(S>*Sa+*Sd)v2=*vt;
			else v1=*vt;
			
			if(fabs(S-*Sa-*Sd)<0.000001f){return 1;}
			
			i++;
		}
	return 0;
}



float t1;
float t2;
float t3;	
float t4;
float t5;

float T1,T2,T3,T4,T5;
float V1,V2,V3,V4,V5;
 
void calc_S_speed_data(speed_calc_t *m_calc_t,float vs,float ve,float vt,float J,float S)  // ------------------- vs or ve != 0
{
	m_calc_t->Jerk = J;
	m_calc_t->Ve = ve;
	m_calc_t->V0 = vs;
	m_calc_t->delta_t = 0.001;
	
	float Sa,Sd;
	
	Sa=(vt+vs)*sqrt((vt - vs)/J);
	Sd=(vt+ve)*sqrt((vt - ve)/J);
	if(Sa + Sd <=S)
	{
		t1 = t2 = sqrt((vt - vs)/J);
		t4 = t5 = sqrt((vt - ve)/J);
		t3 = (S - Sa - Sd)/vt;
	}else if(Sa + Sd >S)
	{
		
		Iteration_S(&vt,ve,vs,S,J,&Sa,&Sd);
		
		t1 = t2 = sqrt((vt - vs)/J);
		t4 = t5 = sqrt((vt - ve)/J);
		t3 = 0;
	}
	
	T1 = t1;
	T2 = t1+t2;
	T3 = t1+t2+t3;
	T4 = t1+t2+t3+t4;
	T5 = t1+t2+t3+t4+t5;
	
	V1 = m_calc_t->V0 + (m_calc_t->Jerk * pow(T1, 2)) / 2.0f;
	V2 = V1 + J * T1 * (T2 - T1) - J * pow(T2 - T1, 2) / 2.0f;
	V3 = V2;
	V4 = V3 - (J * pow(T4 - T3, 2)) / 2.0f;
	V5 = m_calc_t->Ve ;
}




float calc_speed(speed_calc_t *m_calc_t, float time_now) {
    float Vnext;
	

    // 加加速阶段（0 ≤ t ≤ t1）
    if (time_now >= 0 && time_now <= T1) {
        Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(time_now, 2)) / 2.0f;
    }
    // 减加速阶段（t1 < t ≤ t2）
    else if (time_now > T1 && time_now <= T2) {
        Vnext = V1 + m_calc_t->Jerk * T1 * (time_now - T1) - m_calc_t->Jerk * pow(time_now - T1, 2) / 2.0f;
    }
    // 匀速阶段（t2 < t ≤ t3）
    else if (time_now > T2 && time_now <= T3) {
        Vnext = V2; // 匀速保持 Vm
    }
    // 加减速阶段（t3 < t ≤ t4）
    else if (time_now > T3 && time_now <= T4) {
        Vnext = V3 - (m_calc_t->Jerk * pow(time_now - T3, 2)) / 2.0f;
    }
    // 减减速阶段（t4 < t ≤ t5）
    else if (time_now > T4 && time_now <= T5) {		
		Vnext = m_calc_t->Ve + (m_calc_t->Jerk * pow(T5 - time_now, 2)) / 2.0f ;
    }
    // 默认情况
    else {
        Vnext = m_calc_t->Ve; // 或者可以返回其他合适的值
    }

    return Vnext;
}



void S_Init(void)
{
	calc_S_speed_data(&m_calc_t,0.0f,5.0f,50.0f,2.0f,100.0f);
	
}

void S_Going(void)
{
	m_calc_t.t_sum += m_calc_t.delta_t;
	m_calc_t.V_now  = calc_speed(&m_calc_t,m_calc_t.t_sum);
	m_calc_t.S_now += m_calc_t.V_now*0.001f;
	
}































