#ifndef PID_H
#define PID_H
#include <vector>
class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  
  //parameters for twiddle
  double best_err;
  double twiddle_err;
  int n;
  std::vector<double> dparam;
  
  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);
  
  //TODO: Calcuate steering value here, remember the steering value is [-1, 1].
  double CalculateSteering();
  /*
  * Calculate the total PID error.
  */
  void Twiddle(double cte);
};

#endif /* PID_H */
