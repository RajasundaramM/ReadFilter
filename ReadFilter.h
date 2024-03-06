#ifndef ReadFilter_h
#define ReadFilter_h

#include<Arduino.h>
#include<Vector.h>


class ReadFilter{
public:
float sto[20],sum;
Vector<float> rdngs; 
int window,count,del;
float mapl, maph,nsigma; 
bool outrej;
ReadFilter(int w=10, float ml=0, float mh=1023,bool outr=false,float n=1 ,int d=100);
float avg(int p);
float mvgavg(int p);
void clr();

private:
float remout(float s, float l);
};

#endif
