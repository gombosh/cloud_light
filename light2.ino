int button1 = D6;
int led1 = D2;
int led2 = D1;
int led3 = D0;
int32_t light_state;
int color_num = 1;
char color_num_str[1];



void set_color(int color_num)
{
    sprintf(color_num_str,"%d", color_num);
    switch (color_num) {
        case 0:
            digitalWrite(led1,HIGH);
            digitalWrite(led2,HIGH);
            digitalWrite(led3,HIGH);
            light_state = LOW;
            break;
        case 1:
            digitalWrite(led1,HIGH);
            digitalWrite(led2,LOW);
            digitalWrite(led3,LOW);
            light_state = HIGH;
            break;
        case 2:
            digitalWrite(led1,LOW);
            digitalWrite(led2,HIGH);
            digitalWrite(led3,LOW);
            light_state = HIGH;
            break;
        case 3:
            digitalWrite(led1,HIGH);
            digitalWrite(led2,HIGH);
            digitalWrite(led3,LOW);
            light_state = HIGH;
            break;
        case 4:
            digitalWrite(led1,LOW);
            digitalWrite(led2,LOW);
            digitalWrite(led3,HIGH);
            light_state = HIGH;
            break;
        case 5:
            digitalWrite(led1,HIGH);
            digitalWrite(led2,LOW);
            digitalWrite(led3,HIGH);
            light_state = HIGH;
            break;
        case 6:
            digitalWrite(led1,LOW);
            digitalWrite(led2,HIGH);
            digitalWrite(led3,HIGH);
            light_state = HIGH;
            break;
        case 7:
            digitalWrite(led1,LOW);
            digitalWrite(led2,LOW);
            digitalWrite(led3,LOW);
            light_state = HIGH;
            break;
    }
}

void HandleLightOff(const char *event, const char *data)
{
    //char rxName[64];
    //strcpy(rxName, event);
    //light2_state = digitalRead(led1);
    Particle.publish("yaara_light2_catched_off_1");
    if (light_state == HIGH) {
        set_color(0);
    }
    
}

void HandleLightOn(const char *event, const char *data)
{
    char rxData[1];
    strcpy(rxData, data);
    //light2_state = digitalRead(led1);
    Particle.publish("yaara_light2_catched_on_1");
    Particle.publish(rxData);
    set_color(atoi(rxData));
}

void setup()
{
    // the system thread isn't busy so these synchronous functions execute quickly
    Particle.subscribe("yaara_light_light1_on", HandleLightOn);
    Particle.subscribe("yaara_light_light1_off", HandleLightOff);
    //Particle.publish("light1_state", myvar);
    Particle.publish("yaara_light_power_on_2");
    Particle.connect();    // <-- now connect to the cloud, which ties up the system thread
    pinMode(button1, INPUT_PULLUP);
    pinMode(led1, OUTPUT);    
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
    set_color(0);
}

void loop() {
    if (digitalRead(button1) == LOW) {
        delay(1000);
        if (digitalRead(button1) == LOW) {
            set_color(0);
            Particle.publish("yaara_light_light2_off",color_num_str,PRIVATE);
        } else {
            //light2_state = digitalRead(led1);
            set_color(color_num);
            color_num = (color_num + 1)%8;
            if (color_num == 0) {
                color_num = 1;
            }
            Particle.publish("yaara_light_light2_on",color_num_str,PRIVATE);
        }
        delay(1000);
    }
    delay(500);
}
