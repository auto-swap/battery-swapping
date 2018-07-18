#include <Servo.h>

Servo actuator_x;
Servo actuator_y;

const int actuator_x_pin = 13;
const int actuator_y_pin = 7;
const int light_sensor_front_pin = A0;
const int light_sensor_back_pin = A1;

const int actuator_max_extension = 2300;
const int actuator_min_extension = 1000;

int light_sensor_front_value;
int light_sensor_back_value;
int car_detected;


void setup(){
    Serial.begin(9600);
    actuator_x.attach(actuator_x_pin);
    actuator_y.attach(actuator_y_pin);
    actuator_x.writeMicroseconds(actuator_min_extension);
    actuator_y.writeMicroseconds(actuator_min_extension);
}

void loop(){
    light_sensor_front_value = analogRead(light_sensor_front_pin);
    light_sensor_back_value = analogRead(light_sensor_back_pin);
    
    if (light_sensor_front_value <= 15 && light_sensor_back_value <= 15) {
        car_detected += 1;
    } else {
        car_detected = 0;
    }
    
    if (car_detected == 6) {
        Serial.print("Car Detected! ");
        Serial.println(car_detected);

        actuator_x.writeMicroseconds(actuator_max_extension);
        delay(6500);
        actuator_y.writeMicroseconds(actuator_max_extension);
        delay(7500);
        actuator_y.writeMicroseconds(actuator_min_extension);
        delay(6500);
        actuator_x.writeMicroseconds(actuator_min_extension);
    }
    
    delay(500);
}
