#include "S-shaped_ac_dec.h"
#include "math.h"

#define SPEED_2_ROUNDS(rads) rads/6.28f   //����λת��Ϊ��Ȧ/�룩
#define INCACCELROUND(j,t)       ( ( (j) * pow( (t) , 3 ) ) / 6.0f )     /* �Ӽ��ٶε�λ����(Ȧ��)  S = 1/6 * J * t^3 */



speed_calc_t m_calc_t;


//�����ٶȵĵ�λΪrad/s(����/��)   �����v0�ǳ��ٶȣ�vt������ٶȣ�time�Ǽ��ٶε�ʱ�䣨s��,S��Ŀ���ܻ���ֵ, -----------------����ʱ���S�ͼӼ���
//void calc_S_speed_data(speed_calc_t *m_calc_t,float v0,float vt,float time,float S)
//{
//	//ֻҪ�����һ�μӼ��ٶε�ʱ��Ϳ��Եõ�����ʱ��
//	//��Ϊ��֪�е���ٶȣ�������Ӽ��ٶ�
//	m_calc_t->Acc_t = time/2.0f;//�Ӽ��ٶε�ʱ��Ϊ���ٶε�ʱ���һ��
//	m_calc_t->Vm = fabs((v0+vt)/2);
//	m_calc_t->Jerk = 2.0f*m_calc_t->Vm/(m_calc_t->Acc_t * m_calc_t->Acc_t); //�Ӽ��ٶ�
//	m_calc_t->S_Acc = 0.166666667f*(m_calc_t->Jerk*pow(m_calc_t->Acc_t,3)) ; //�Ӽ��ٶεĻ�����ֵ
//	m_calc_t->S_sum = 4.0f*m_calc_t->S_Acc; //�Ӽ��ٶȵ���·�̵Ļ���ֵ
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

//    // ����ʱ�����
//     t1 = m_calc_t->Acc_t;          // ���ٽ׶�ʱ��
//     t2 = 2 * m_calc_t->Acc_t;      // �ȼ��ٽ׶ν���ʱ��
//    float S_uniform = m_calc_t->uniform_S; // ���ٶεľ���
//     t3 = t2 + (S_uniform / m_calc_t->Vm); // ���ٽ׶ν���ʱ��
//     t4 = t3 + m_calc_t->Acc_t;     // ���ٽ׶ν���ʱ��
//     t5 = t4 + m_calc_t->Acc_t;     // �ٴμ��ٽ׶ν���ʱ��

//    // �Ӽ��ٽ׶Σ�0 �� t �� t1��
//    if (time_now >= 0 && time_now <= t1) {
//        Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(time_now, 2)) / 2.0f;
//    }
//    // �����ٽ׶Σ�t1 < t �� t2��
//    else if (time_now > t1 && time_now <= t2) {
//        Vnext = m_calc_t->Vm + m_calc_t->Jerk * m_calc_t->Acc_t * (time_now - t1) 
//                 - (m_calc_t->Jerk * pow(time_now - t1, 2)) / 2.0f;
//    }
//    // ���ٽ׶Σ�t2 < t �� t3��
//    else if (time_now > t2 && time_now <= t3) {
//        Vnext = m_calc_t->Vt; // ���ٱ��� Vm
//    }
//    // �Ӽ��ٽ׶Σ�t3 < t �� t4��
//    else if (time_now > t3 && time_now <= t4) {
//        Vnext = m_calc_t->Vt - (m_calc_t->Jerk * pow(time_now - t3, 2)) / 2.0f;
//    }
//    // �����ٽ׶Σ�t4 < t �� t5��
//    else if (time_now > t4 && time_now <= t5) {
////        Vnext = m_calc_t->Vt - (m_calc_t->Jerk * pow(t4 - t3, 2)) / 2.0f - m_calc_t->Jerk * t4 * (time_now - t4) 
////                 + (m_calc_t->Jerk * pow(time_now - t4, 2)) / 2.0f;
//		
//		Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(t5-time_now, 2)) / 2.0f;
//    }
//    // Ĭ�����
//    else {
//        Vnext = 0; // ���߿��Է����������ʵ�ֵ
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
//		float v_ = pow(pow(S/2 ,2)*J,0.33333333333f);//���ﲻ����1/3��Ҫֱ����С�������ʽ����Ȼ������
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

//    // �Ӽ��ٽ׶Σ�0 �� t �� t1��
//    if (time_now >= 0 && time_now <= T1) {
//        Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(time_now, 2)) / 2.0f;
//    }
//    // �����ٽ׶Σ�t1 < t �� t2��
//    else if (time_now > T1 && time_now <= T2) {
//        Vnext = V1 + m_calc_t->Jerk * T1 * (time_now - T1) - m_calc_t->Jerk * pow(time_now - T1, 2) / 2.0f;
//    }
//    // ���ٽ׶Σ�t2 < t �� t3��
//    else if (time_now > T2 && time_now <= T3) {
//        Vnext = V2; // ���ٱ��� Vm
//    }
//    // �Ӽ��ٽ׶Σ�t3 < t �� t4��
//    else if (time_now > T3 && time_now <= T4) {
//        Vnext = V3 - (m_calc_t->Jerk * pow(time_now - T3, 2)) / 2.0f;
//    }
//    // �����ٽ׶Σ�t4 < t �� t5��
//    else if (time_now > T4 && time_now <= T5) {		
//		Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(T5 - time_now, 2)) / 2.0f ;
//    }
//    // Ĭ�����
//    else {
//        Vnext = 0; // ���߿��Է����������ʵ�ֵ
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
	

    // �Ӽ��ٽ׶Σ�0 �� t �� t1��
    if (time_now >= 0 && time_now <= T1) {
        Vnext = m_calc_t->V0 + (m_calc_t->Jerk * pow(time_now, 2)) / 2.0f;
    }
    // �����ٽ׶Σ�t1 < t �� t2��
    else if (time_now > T1 && time_now <= T2) {
        Vnext = V1 + m_calc_t->Jerk * T1 * (time_now - T1) - m_calc_t->Jerk * pow(time_now - T1, 2) / 2.0f;
    }
    // ���ٽ׶Σ�t2 < t �� t3��
    else if (time_now > T2 && time_now <= T3) {
        Vnext = V2; // ���ٱ��� Vm
    }
    // �Ӽ��ٽ׶Σ�t3 < t �� t4��
    else if (time_now > T3 && time_now <= T4) {
        Vnext = V3 - (m_calc_t->Jerk * pow(time_now - T3, 2)) / 2.0f;
    }
    // �����ٽ׶Σ�t4 < t �� t5��
    else if (time_now > T4 && time_now <= T5) {		
		Vnext = m_calc_t->Ve + (m_calc_t->Jerk * pow(T5 - time_now, 2)) / 2.0f ;
    }
    // Ĭ�����
    else {
        Vnext = m_calc_t->Ve; // ���߿��Է����������ʵ�ֵ
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































