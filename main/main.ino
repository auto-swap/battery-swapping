#include <Servo.h>

Servo actuator_x;
Servo actuator_y;

const int actuator_x_pin = 7;
const int actuator_y_pin = 13;
const int light_sensor_front_pin = A0;
const int light_sensor_back_pin = A1;

const int actuator_max_extension = 2300;
const int actuator_min_extension = 1000;

int car_detected = 0;
int light_sensor_front_value;
int light_sensor_back_value;
int light_sensor_front_initial = 0;
int light_sensor_back_initial = 0;
int light_sensor_front_prev = 0;
int light_sensor_back_prev = 0;
int front_sensor_cut_off;
int back_sensor_cut_off;


void setup(){
    Serial.begin(9600);
    actuator_x.attach(actuator_x_pin);
    actuator_y.attach(actuator_y_pin);
    actuator_x.writeMicroseconds(actuator_min_extension);
    actuator_y.writeMicroseconds(actuator_min_extension);

    while (light_sensor_front_initial == 0 || light_sensor_back_initial == 0){
        light_sensor_front_value = analogRead(light_sensor_front_pin);
        light_sensor_back_value = analogRead(light_sensor_back_pin);

        if (light_sensor_front_prev * 0.90 <= light_sensor_front_value &&
            light_sensor_front_prev * 1.10 >= light_sensor_front_value){
            light_sensor_front_initial = light_sensor_front_value;
        }

        if (light_sensor_back_prev * 0.90 <= light_sensor_back_value &&
            light_sensor_back_prev * 1.10 >= light_sensor_back_value){
            light_sensor_back_initial = light_sensor_back_value;
        }

        light_sensor_front_prev = light_sensor_front_value;
        light_sensor_back_prev = light_sensor_back_value;

        delay(1000);
    }

    front_sensor_cut_off = light_sensor_front_initial*0.1;
    back_sensor_cut_off = light_sensor_back_initial*0.1;
}

void loop(){
  
    light_sensor_front_value = analogRead(light_sensor_front_pin);
    light_sensor_back_value = analogRead(light_sensor_back_pin);

    Serial.print("Front cuttof: ");
    Serial.println(front_sensor_cut_off);

    Serial.print("Back cutoff: ");
    Serial.println(back_sensor_cut_off);
    
    Serial.print("A0: ");
    Serial.println(light_sensor_front_value);

    Serial.print("A1: ");
    Serial.println(light_sensor_back_value);
    
    if (light_sensor_front_value <= front_sensor_cut_off && light_sensor_back_value <= back_sensor_cut_off) {
        car_detected += 1;
    } else {
        car_detected = 0;
    }
    
    if (car_detected == 6) {
        Serial.print("Car Detected! ");

        //battery removal
        actuator_x.writeMicroseconds(1800);
        delay(6500);
        actuator_y.writeMicroseconds(1850);
        delay(7500);
        actuator_y.writeMicroseconds(actuator_min_extension);
        delay(6500);
        actuator_x.writeMicroseconds(actuator_min_extension);
        delay(6500);
        //drop the depleted battery in place
        actuator_y.writeMicroseconds(1850);
        delay(7500);
        actuator_y.writeMicroseconds(actuator_min_extension);
        delay(6500);
        //pick up a fully charged battery
        actuator_x.writeMicroseconds(1300);
        delay(3000);
        actuator_y.writeMicroseconds(1850);
        delay(7500);
        actuator_y.writeMicroseconds(actuator_min_extension);
        delay(7500);
        //insert a new battery
        actuator_x.writeMicroseconds(1800);
        delay(6500);
        actuator_y.writeMicroseconds(1850);
        delay(7500);
        actuator_y.writeMicroseconds(actuator_min_extension);
        delay(6500);
        actuator_x.writeMicroseconds(actuator_min_extension);
        delay(6500);
    }
    
    delay(500);
}