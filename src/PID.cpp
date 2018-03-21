#include "PID.h"
#include <limits>
#include<numeric>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
  PID::Kp=Kp;
  PID::Ki=Ki;
  PID::Kd=Kd;
  p_error=0;
  d_error=0;
  i_error=0;
  
  
  best_err = std::numeric_limits<double>::max();
  twiddle_err=0;
  n=1;
  dparam={1.0,1.0,1.0};

}

void PID::UpdateError(double cte) {
  d_error=cte-p_error;
  p_error=cte;
  i_error += cte;
}

double PID::CalculateSteering(){
  double steering=-Kp*p_error-Ki*i_error-Kd*d_error;
  if (steering>1.0) steering=1;
  if (steering<-1.0) steering=-1;
  return steering;
}

/*void PID::Twiddle(double cte) {
  vector<double>param{Kp,Kd,Ki};//the order to tune
  //vector<double>dparam={1.0,1.0,1.0};
  double tolerance=0.2;
  
  if(n==1) p_error=cte;
  //UpdateError(cte);
  d_error=cte-p_error;
  p_error=cte;
  i_error += cte;
  //double sum=accumulate(dparam.begin() , dparam.end() , 0.0);
  while(accumulate(dparam.begin() , dparam.end() , 0.0)>tolerance && n>300){
    for(unsigned int i=0;i<3;i++){
      param[i] += dparam[i];
      //if(n>300) twiddle_err +=p_error*p_error;
      twiddle_err +=p_error*p_error;
      if(twiddle_err<best_err){
        best_err =twiddle_err;
        dparam[i] *=1.1;
        cout << "condition 1"<<endl;
      }
      else{
        param[i] -= 2*dparam[i];
        twiddle_err=p_error*p_error;
        if(twiddle_err<best_err){
          best_err =twiddle_err;
          dparam[i] *=1.1;
          cout << "condition 2"<<endl;
        }
        else{
          param[i] += dparam[i];
          dparam[i] *=0.9;
          cout << "condition 3"<<endl;
        }
      }
    }
    //twiddle_err=0;
    
  }
  
  n++;
  Kp=param[0];
  Kd=param[1];
  Ki=param[2];
  //cout << "NEW:   KP " << PID::Kp << ", Ki: " << PID::Ki << ", Kd: " << PID::Kd << endl;
  //cout << "NEW:   KP " << Kp << ", Ki: " << Ki << ", Kd: " << Kd << endl;
  //cout <<"best err " <<best_err<<" twiddle err "<<twiddle_err<<" p_err "<<p_error<<endl;
}*/

