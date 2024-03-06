#include "ReadFilter.h"
#include "Arduino.h"
#include "Vector.h"

ReadFilter :: ReadFilter(int w,  float ml, float mh, bool outr, float n, int d){
    //common parameters to get:
    // window? maplow? maphigh? outlier rejection? nsigma?  delay?
    this->window = w;
    this->outrej = outr;
    this->mapl = ml; 
    this->maph = mh;
    this->del = d;
    this->nsigma = n;
    this->count=0;
    this->sum=0;
    this->rdngs.setStorage(this->sto);
    this->rdngs.clear();
}


float ReadFilter :: avg(int p){   
float s=0,v;
this->rdngs.clear();

for(int i=0; i<this->window; i++){
v=analogRead(p);
this->rdngs.push_back(v);
s+=(float)v;
delayMicroseconds(this->del);
}

s/=(float)(this->window);

if(!(this->outrej)){
v = (s/1023)*(this->maph - this->mapl);
return v;}

else{ return this->remout(s,this->window); }

}


float ReadFilter :: mvgavg(int p){ 
delayMicroseconds(this->del);
float v=analogRead(p);

if((this->count)<(this->window)){
this->rdngs.push_back(v);
this->count+=1;
this->sum+=v;
}else{
this->sum-=(this->rdngs[0]);
this->sum+=v;
this->rdngs.remove(0);
this->rdngs.push_back(v);
}

float s = (float)((float)this->sum)/((float)this->count);

if(!(this->outrej)){
return (float)(s/1023)*(this->maph - this->mapl);
}

else{ return this->remout(s,this->count); }

}


float ReadFilter :: remout(float s, float l){
float stddev,ssqd=0,ns=0,nc=0;
    for(int i=0; i<l; i++){ssqd+=sq((float)this->rdngs[i]-s);}
    stddev = sqrt(ssqd/(float)(l));
    for(int i=0; i<l; i++){
        if(abs((float)this->rdngs[i]-s)<=(float)this->nsigma*stddev){ns+=(float)this->rdngs[i];nc+=1;}
    }
    float nm = (float)(ns/nc);
    float v = (nm/1023)*(this->maph - this->mapl);
    return v;
}

void ReadFilter :: clr(){
    this->count=0;
    this->sum=0;
    this->rdngs.clear();
}
