#include <Arduino.h>
#include <PID_v1.h>

void AlterSimulationConditions();
void SimulateInput();
void DoSerial();

//working variables/initial conditions
double setpoint, input, output;
double kp = 1, ki = 2, kd = 0;
const double outputStart = 50;
const double inputStart = 200;
const double setpointStart = 200;


PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

//parameters used to simulate the process connected to the pid
const int ntheta = 50;
double kpmodel = 1, taup = 50, theta[ntheta];
bool integrating = false;
int tindex = 0;

//time variables
unsigned long evalTime = 0, evalInc = 10,
              serialTime = 0, serialInc = 100;
unsigned long now = 0;

double limitsMin, limitsMax;

void setOutputLimits(double min, double max) {
  limitsMin = min;
  limitsMax = max;
  myPID.SetOutputLimits(min, max);
}

unsigned long fakeMillis() {
  return now;
}

void setup() {
  
  //working variables
  input = inputStart;
  setpoint = setpointStart;
  output = outputStart;
  for (int i = 0; i < ntheta; i++)theta[i] = outputStart;

  //initialize pid
  myPID.SetTimeFunction(fakeMillis);
  setOutputLimits(-250, 250);
  myPID.SetMode(AUTOMATIC);


  //initialize serial comm
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Test Start");

}

void loop() {
  if (now > 60000)
  {
    Serial.println("End Test");
    //block execution to have a clean serial output at the end of the test
    end();
  }

  AlterSimulationConditions();
  SimulateInput();

  bool computed = myPID.Compute();
  if (computed) {
    Serial.print(now);
    Serial.println(" PID computed");
  }
  
  if (now >= serialTime)
  {
    serialTime += serialInc;
    DoSerial();
  }

  evalTime += evalInc;
  now += evalInc;
}

void SimulateInput()
{
  // Serial.print("theta:");
  // for (int i = 0; i < ntheta; ++i) {
  //   Serial.print(i == tindex ? " *" : "  ");
  //   Serial.print(theta[i]);
  // }
  // Serial.println();

  //Create a dead time by using a circular buffer
  theta[tindex] = output;
  tindex++;
  if (tindex >= ntheta)tindex = 0;

  // Compute the input
  if (integrating) input = (kpmodel / taup) * (theta[tindex] - outputStart) + input;
  else input = (kpmodel / taup) * (theta[tindex] - outputStart) + (input - inputStart) * (1 - 1 / taup) + inputStart;
  //add some noise
  //input += ((float)random(-10, 10)) / 100;
  Serial.print(now);
  Serial.print(" theta=(");
  Serial.print(output);
  Serial.print(" => ");
  Serial.print(theta[tindex]);
  Serial.print(") outputStart=");
  Serial.print(outputStart);
  Serial.print("} input=");
  Serial.println(input);
}

void AlterSimulationConditions()
{
  //setpoint stepper
  if (now > 49000) setpoint = 150;
  else if (now > 44000) setpoint = 100;
  else if (now > 38000) setpoint = 500;
  else if (now > 36000) setpoint = 200;
  else if (now > 32000)setpoint = 150;
  else if (now > 20000) setpoint = 200;
  else if (now > 11000) setpoint = 100;
  else if (now > 8000) setpoint = 1000;
  else if (now > 6000) setpoint = 200;
  else if (now > 2000)setpoint = 150;
  /*else if(now>3000)setpoint=50;*/

  //limit changes
  if (now > 45000)setOutputLimits(-100, 100);
  else if (now > 39000)setOutputLimits(0, 200);
  else if (now > 30000)setOutputLimits(-255, 255);
  else if (now > 15000)setOutputLimits(-100, 100);
  else if (now > 9000)setOutputLimits(0, 200);

  //random mode changes
  if (now > 15000) myPID.SetMode(AUTOMATIC);
  else if (now > 10900) myPID.SetMode(MANUAL);
  else if (now > 8500) myPID.SetMode(AUTOMATIC);
  else if (now > 6800) myPID.SetMode(MANUAL);
  else if (now > 4500) myPID.SetMode(AUTOMATIC);
  else if (now > 4000) myPID.SetMode(AUTOMATIC);

  //tunings changes
  if (now > 43000) myPID.SetTunings(3, .15, 0.15);
  else if (now > 39000) myPID.SetTunings(.5, .1, .05);
  else if (now > 30000) myPID.SetTunings(0.1, .05, 0);
  else if (now > 13000) myPID.SetTunings(0.5, 2, 0.15);
  else if (now > 9000) myPID.SetTunings(2, 1, .05);

  //model change: switch the nature of the process connected to the pid
  integrating = (now >= 30000);

}

void DoSerial()
{
  Serial.print(now); Serial.print(" Kp ");
  Serial.print(myPID.GetKp()); Serial.print(" Ki ");
  Serial.print(myPID.GetKi()); Serial.print(" Kd ");
  Serial.print(myPID.GetKd()); Serial.print(" ");
  Serial.print(myPID.GetMode() == AUTOMATIC ? "A" : "M"); Serial.print(" limits (");
  Serial.print(limitsMin); Serial.print(", ");
  Serial.print(limitsMax); Serial.print(") setpoint ");
  Serial.print(setpoint); Serial.print(" input ");
  Serial.print(input); Serial.print(" output ");
  Serial.println(output);
}

