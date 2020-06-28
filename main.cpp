#include "mbed.h"
#include "bbcar.h"

RawSerial xbee(D12, D11);
PwmOut pin12(D8), pin13(D9);
DigitalInOut ping(D10);
Serial uart(D1,D0); //tx,rx
Timer t_ping;
Thread thread_ping;
Thread thread_obj;
EventQueue queue_ping;
EventQueue queue_obj;

Ticker servo_ticker;

BBCar car(pin13, pin12, servo_ticker);

float ping_value = 999;
float ping_data[35];

void right() {
    car.servo0.set_speed(38);//34.75
    car.servo1.set_speed(38);//34.75
    wait_ms(1000);
    car.stop();
}

void left() {
    car.servo0.set_speed(-30);//-27
    car.servo1.set_speed(-30);//-27
    wait_ms(1000);
    car.stop();
}

void straight_front() {
    car.servo0.set_speed(35);
    car.servo1.set_speed(-41.2);
}

void straight_back() {
    car.servo0.set_speed(-35);
    car.servo1.set_speed(55.57);
}

void ping_read() {
    ping.output();
    ping = 0; wait_us(200);
    ping = 1; wait_us(5);
    ping = 0; wait_us(5);
    ping.input();
    while(ping.read()==0);
    t_ping.start();
    while(ping.read()==1);
    ping_value = t_ping.read() * 17700.4f;
    t_ping.stop();
    t_ping.reset();
}

void right_10() {
    car.servo0.set_speed(23.5);//34.75
    car.servo1.set_speed(23.5);//34.75
    wait_ms(1000);
    car.stop();
}

void left_20() {
    car.servo0.set_speed(-13);//-27
    car.servo1.set_speed(-13);//-27
    wait_ms(3500);
    car.stop();
}

void obj() {
    for (int i = 0; i < 35; i++) {
        queue_ping.call(ping_read);
        wait_ms(100);
        ping_data[i] = ping_value;
    }
}

int main() {
    car.stop();
    thread_ping.start(callback(&queue_ping, &EventQueue::dispatch_forever));
    thread_obj.start(callback(&queue_obj, &EventQueue::dispatch_forever));
    // 0 left 1 right

    xbee.printf("----------BBcar start.----------\r\n");
    xbee.printf("Go straight front.\r\n");
    straight_front();
    while (true) {
        queue_ping.call(ping_read);
        if (ping_value < 20) {
            car.stop();
            break;
        }
        wait_ms(100);
    }
    wait(1);
    xbee.printf("Turn left.\r\n");
    left();
    wait(1);
    // mission 1
    ping_value = 999;
    xbee.printf("Go straight front.\r\n");
    straight_front();
    while (true) {
        queue_ping.call(ping_read);
        if (ping_value < 15) {
            car.stop();
            break;
        }
        wait_ms(100);
    }
    wait(1);
    xbee.printf("Turn right.\r\n");
    right();
    wait(1);
    xbee.printf("Go straight back.\r\n");
    straight_back();
    wait_ms(1000);
    car.stop();

    char s[21];
    sprintf(s,"image_classification");
    uart.puts(s);

    xbee.printf("Take a picture.\r\n");
    int photo_time = 5;
    while (photo_time > 0) {
        if (uart.readable()) {
                char recv = uart.getc();
                xbee.putc(recv);
                xbee.printf("\r\n");
        }
        photo_time--;
        wait(1);
    }

    xbee.printf("Go straight front.\r\n");
    straight_front();
    wait_ms(1000);
    car.stop();
    wait(1);

    xbee.printf("Turn left.\r\n");
    left();
    wait(1);
    xbee.printf("Go straight back.\r\n");
    straight_back();
    wait_ms(3000);
    car.stop();
    wait(1);
    xbee.printf("Turn left.\r\n");
    left();
    wait(1);
    xbee.printf("Go straight front.\r\n");

    ping_value = 999;
    straight_front();
    while (true) {
        queue_ping.call(ping_read);
        if (ping_value < 20) {
            car.stop();
            break;
        }
        wait_ms(100);
    }

    wait(1);
    xbee.printf("Go straight back.\r\n");
    straight_back();
    wait_ms(2000);
    car.stop();
    wait(1);
    xbee.printf("Turn left.\r\n");
    left();
    wait(1);

    xbee.printf("Go straight front.\r\n");
    straight_front();
    wait_ms(1300);
    car.stop();
    wait(1);
    xbee.printf("Turn right.\r\n");
    right();
    wait(1);
    // mission 2
    ping_value = 999;
    xbee.printf("Go straight front.\r\n");
    straight_front();
    while (true) {
        queue_ping.call(ping_read);
        if (ping_value < 20) {
            car.stop();
            break;
        }
        wait_ms(100);
    }
    wait(1);
    xbee.printf("Turn right.\r\n");
    right();
    wait(1);
    xbee.printf("Go straight front.\r\n");
    straight_front();
    wait_ms(1500);
    car.stop();
    wait(1);
    xbee.printf("Turn right.\r\n");
    right();
    wait(1);
    xbee.printf("Go straight front.\r\n");
    straight_front();
    wait_ms(1000);
    wait(1);
    car.stop();
    wait(1);

    xbee.printf("Distinguish the object.\r\n");
    right_10();
    wait(1);
    queue_obj.call(obj);
    left_20();
    wait(1);
    right_10();
    wait(1);

    xbee.printf("Go straight back.\r\n");
    straight_back();
    wait_ms(1800);
    car.stop();
    wait(1);
    xbee.printf("Turn left.\r\n");
    left();
    wait(1);

    ping_value = 999;
    xbee.printf("Go straight front.\r\n");
    straight_front();
    while (true) {
        queue_ping.call(ping_read);
        if (ping_value < 20) {
            car.stop();
            break;
        }
        wait_ms(100);
    }
    wait(1);
    xbee.printf("Turn right.\r\n");
    right();
    wait(1);
    xbee.printf("Go straight front.\r\n");
    straight_front();
    wait(10);
    car.stop();

    float der[34];
    for (int i = 0; i < 34; i++) {
        der[i] = ping_data[i + 1] = ping_data[i];
    }
    float rank_1 = 0;
    float rank_2 = 0;
    for (int i = 8; i < 17; i++) {
        rank_1 += der[i] / 9;
    }
    for (int i = 17; i < 26; i++) {
        rank_2 += der[i] / 9;
    }
    if (rank_1 < 0 && rank_2 < 0) {
        xbee.printf("This is triangle.\r\n");
    } else if (rank_1 > rank_2) {
        xbee.printf("This is a square without triangle.\r\n");
    } else if (ping_data[26] - ping_data[17] > 8) {
        xbee.printf("This is a perfect triangle.\r\n");
    } else {
        xbee.printf("This is a square.\r\n");
    }
    while (true) {
    }
}