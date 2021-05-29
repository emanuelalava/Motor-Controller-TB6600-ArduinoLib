#ifndef StepperController_h
#define StepperController_h

// library interface description
class StepperController
{
public:
    StepperController(int driver_pulse_pin, int driver_dir_pin, float final_step_angle);

    void setRPM(long rpms);

    void runSteps(int n_steps, int dir);

    void runMM(float millimeters, float lead, int dir);

    void waitTime(int seconds);

private:
    void pulse(int dir);

    int pulse_pin;
    int dir_pin;
    float step_angle;
    int pulse_delay;
};

#endif