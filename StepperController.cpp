#include "Arduino.h"
#include "StepperController.h"

StepperController::StepperController(int driver_pulse_pin, int driver_dir_pin, float final_step_angle)
{
    this->pulse_pin = driver_pulse_pin;
    this->dir_pin = driver_dir_pin;
    this->step_angle = final_step_angle;

    this->pulse_delay = 1000;

    pinMode(this->pulse_pin, OUTPUT);
    pinMode(this->dir_pin, OUTPUT);
}

void StepperController::setRPM(long rpms)
{
    this->pulse_delay = int(((float(this->step_angle) * 120.0 * 3.141592) / (float(rpms) * 720.0)) * 1000000.0);
}

void StepperController::pulse(int dir)
{
    digitalWrite(this->dir_pin, dir);
    digitalWrite(this->pulse_pin, HIGH);
    delayMicroseconds(this->pulse_delay);
    digitalWrite(this->pulse_pin, LOW);
    delayMicroseconds(this->pulse_delay);
}

void StepperController::runSteps(int n_steps, int dir)
{
    for (int x = 0; x <= n_steps; x++)
    {
        pulse(dir);
    }
}

void StepperController::runMM(float millimeters, float lead, int dir)
{
    float pulses_float = millimeters * (360.0 / lead) * (1.0 / this->step_angle);
    int pulses = (int)pulses_float;

    runSteps(pulses, dir);
}

void StepperController::waitTime(int seconds)
{
    int miliseconds = seconds * 1000;
    unsigned long startTimer = millis();
    unsigned long currentTime = millis();
    bool isValid = false;

    while (isValid == false)
    {
        if (!(currentTime < startTimer + miliseconds))
        {
            isValid = true;
        }
        currentTime = millis();
    }
}