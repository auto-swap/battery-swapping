#include <Servo.h>
Servo actuator_x;
Servo actuator_y;

const int actuator_x_pin = 13;
const int actuator_y_pin = 7;
const int light_sensor_front_pin = A0;
const int light_sensor_back_pin = A0;

int sensor_value;
int car_detected;


void setup(){
    Serial.begin(9600);
    actuator_x.attach(actuator_x_pin);
}

void loop(){
    sensor_value = analogRead(light_sensor_front_pin);
    
    if (sensor_value <= 10) {
        car_detected += 1;
    } else {
        car_detected = 0;
    }
    
    if (car_detected == 6) {
        
    }
    
    Serial.print("Sensor value: ");
    Serial.println(sensorVal);
    
    delay(500);
}