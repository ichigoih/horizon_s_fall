#pragma once


struct Animation {
    int index;
    int frames;
    int speed;
    int frameWidth;
    int frameHeight;

    Animation() {
        index = 0;
        frames = 0;
        speed = 100;
        frameWidth = 64;
        frameHeight = 64;
    }

    Animation(int i, int f, int s, int w, int h) {
        index = i;
        frames = f;
        speed = s;
        frameWidth = w;
        frameHeight = h;
    }
};
