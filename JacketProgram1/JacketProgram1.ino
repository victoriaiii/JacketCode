/*
 * Copyright 2016 William Snow & Victoria Houed. All Rights Reserved.
 */

#include <Adafruit_NeoPixel.h>

#define NPIXELS_C 1
#define NPIXELS_R 66
#define NPIXELS_L 56
#define PIN_C 8
#define PIN_R 9
#define PIN_L 10

#define STARTRAIL 40
#define STARFADE (255/STARTRAIL)
#define STREAMTRAIL 16
#define SPEEDFACTOR 1  // higher number slows down effects

#define FULL   0xffffff

//COLOR ARCHIVE
//BABY, SHADES OF BLUE, PURPLE, BLUISH, GREENS
#define BABYPURPLE 0x4B12AE
#define BABYMAGENTA 0xD416C7
#define BABYBLGRE 0x23BEC3
#define BABYGREEN 0X23C383
#define BABYBLUE1 0x0A0629
#define BABYBLUE2 0x0B0262
#define BABYBLUE3 0x3822F7
#define BABYBLUE4 0x2278F8
#define BABYBLUE5 0x22E3F8
#define BABYBLUE6 0x7DF3FF

//WAY, DARKER PURPLES PINKS 
#define WAYDARKPURPLE 0x562597
#define WAYDARKBLUE 0X252D98
#define WAYDARKMAGENTA 0x802697
#define WAYDARKPINK 0xC029BB

//ULB, MAINLYWHITE WITH RED UNDERTONES
#define ULBWHITE 0xFFFFFF
#define ULBRED 0xD80000
#define ULBYELLOW 0xFFDE00

//NOPROBLEMS, PRIMARY/SECONDARY RBYGOP
#define NPRED 0xFF1100
#define NPBLUE 0x1100FF
#define NPYELLOW 0xEFFF00
#define NPGREEN 0x00FF11
#define NPORANGE 0xFF9100
#define NPPURPLE 0x9100FF

//MIXTAPE
#define MIXMINT 0x00FF80
#define MIXORANGE 0xFF8000
#define MIXPINKS 0xD72A9D

//ALL NIGHT
#define CANDYPINK 0xFF11B0
#define CANDYBLUE 0x099DFF
#define CANDYAPPLE 0x00C92D
#define CANDYYELLOW 0xF7FF00
#define CANDYORANGE 0xFF9100 
#define CANDYPURPLE 0x82459C

#define BLACK 0x000000
//Magnigicent Coloring Book Colors
#define SALMON 0xFE615C
#define DARKBLUE 0x020D3B
#define PEACH 0xFFB99B
#define BABYBLUE 0x93B6EC
//ACID RAP
#define DARKPURPLE 0x3D1050
#define HOTPINK 0xEF5788
#define PURPLEPINK 0xA03054
#define TEAL 0x3C88A2
//10 DAY
#define RED 0xB13130
#define DARKERBLUE 0x0E314D
#define BABYBLUE 0x8FB9D1
#define WHITE 0xFAFBFD
//ALL NIGHT
#define GOLD 0xFFCE47
#define BLUEARROW 0x2067DB
#define PINKARROW 0xE81F87
#define TEALL 0x09DAD7
#define PURPLEARROW 0xAA21E1
#define FOREST 0x324901
#define CRAYONBLUE 0x3CA4FF
#define ORANGE 0xFD7A4C
//BABYBLUE
#define LIGHTPURPLE 0x6D61FF
#define LIGHTBLUE 0x68B6FF
#define BLUE 0x1E22FF
//MIXTAPE
#define MIXBLUE 0x0000E2
#define MIXRED 0xFD0000
#define MIXPURPLE 0x7100B3
#define MIXPINK 0xF10162
//NOPROBLEMS
#define NORED 0xF40000
#define NODEEPRED 0x850001
#define NOLIGHTRED 0xF44846




Adafruit_NeoPixel center = Adafruit_NeoPixel(NPIXELS_C, PIN_C, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left = Adafruit_NeoPixel(NPIXELS_L, PIN_L, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right = Adafruit_NeoPixel(NPIXELS_R, PIN_R, NEO_GRB + NEO_KHZ800);

//------------------THESE ARE ALL OF THE SETUP FUNCTIONS--------------------//

//SETS PLAIN COLORS
void setcenter(uint32_t color)
{
  center.setPixelColor(0, color);
}
void setright(uint8_t start, uint8_t num, uint32_t color)
{
  for (uint8_t i = 0; i != num; i++)
    right.setPixelColor(start+i, color);
}
void setleft(uint8_t start, uint8_t num, uint32_t color)
{
  for (uint8_t i = 0; i != num; i++)
    left.setPixelColor(start+i, color);
}

uint32_t colorwheel(uint8_t wiper)
{
  wiper = 255 - wiper;
  if (wiper < 85) {
    return 255-wiper*3<<16 | wiper*3;
  } else if (wiper < 170) {
    wiper -= 85;
    return wiper*3<<8 | 255-wiper*3;
  } else {
    wiper -= 170;
    return wiper*3<<16 | 255-wiper*3<<8;
  }
}

void rainbowleft(uint8_t pixel, uint8_t n, uint8_t speed, int32_t duration)
{
  uint8_t wait = (256-speed) << SPEEDFACTOR;
  while (duration > 0) {
    for (uint8_t i = 0; i <= 255; i++) {
      setleft(pixel, n, colorwheel(i));
      left.show();
      delay(wait);
      duration -= wait;
    }
  }
}

void rainbowright(uint8_t pixel, uint8_t n, uint8_t speed, int32_t duration)
{
  uint8_t wait = (256-speed) << SPEEDFACTOR;
  while (duration > 0) {
    for (uint8_t i = 0; i <= 255; i++) {
      setright(pixel, n, colorwheel(i));
      right.show();
      delay(wait);
      duration -= wait;
    }
  }
}

void rainbowcenter(uint8_t speed, int32_t duration)
{
  uint8_t wait = (256-speed) << SPEEDFACTOR;
  while (duration > 0) {
    for (uint8_t i = 0; i <= 255; i++) {
      setcenter(colorwheel(i));
      center.show();
      delay(wait);
      duration -= wait;
    }
  }
}

void setwavemiddle(uint32_t color, uint16_t leftpos, uint16_t rightpos)
{
  uint8_t fade, fadestep, cur, width;
  int8_t middle;
  if (leftpos > rightpos)
    middle = -((leftpos - rightpos) >> 1);
  else
    middle = (rightpos - leftpos) >> 1;
  width = (leftpos + rightpos) >> 1;
  fadestep = 255/width;
  fade = 0;
  for (cur = leftpos; cur >= 0; cur--) {
    if (cur > -middle)
      fade += fadestep;
    else if (cur == -middle)
      fade = 255;
    else
      fade -= fadestep;
    if (cur < NPIXELS_L)
      setleft(cur, 1, dim(color, fade));
  }
  setcenter(dim(color, fade));
  for (cur = 0; cur <= rightpos; cur++) {
    if (cur < middle)
      fade += fadestep;
    else if (cur == middle)
      fade = 255;
    else
      fade -= fadestep;
    if (cur < NPIXELS_R)
      setright(cur, 1, dim(color, fade));
  }
  left.show();
  center.show();
  right.show();
}

void setwaveright(uint32_t color, int16_t position, uint16_t width)
{
  int16_t cur;
  uint16_t fade = 0;
  for (cur = position-width; cur <= position; cur++) {
    fade += 255/width;
    if (cur >= 0 && cur < NPIXELS_R)
      setright(cur, 1, dim(color, fade));
  }
  for (fade = 255; cur <= position+width; cur++) {
    fade -= 255/width;
    if (cur >= 0 && cur < NPIXELS_R)
      setright(cur, 1, dim(color, fade));
  }
  right.show();
}

void setwaveleft(uint32_t color, int16_t position, uint16_t width)
{
  int16_t cur;
  uint16_t fade = 0;
  for (cur = position-width; cur <= position; cur++) {
    fade += 255/width;
    if (cur >= 0 && cur < NPIXELS_L)
      setleft(cur, 1, dim(color, fade));
  }
  for (fade = 255; cur <= position+width; cur++) {
    fade -= 255/width;
    if (cur >= 0 && cur < NPIXELS_L)
      setleft(cur, 1, dim(color, fade));
  }
  left.show();
}

// linear interpolation of intensity 0-255
uint32_t dim(uint32_t color, uint8_t intensity) {
  uint32_t r, g, b;
  r = 0xff & (color >> 16);
  g = 0xff & (color >> 8);
  b = 0xff & color;
  r *= intensity;
  r >>= 8;
  g *= intensity;
  g >>= 8;
  b *= intensity;
  b >>= 8;
  return ((r<<16) | (g<<8) | b);
}

//-----------THESE ARE DIFFERENT THINGS THAT THE LIGHTS CAN DO------------//


//SET COLORS FOR LONG TIME
void solid(uint32_t color, uint32_t duration) {
  setcenter(color);
  setleft(0, NPIXELS_L, color);
  setright(0, NPIXELS_R, color);
  center.show();
  left.show();
  right.show();
  delay(duration);
}

void streamer(uint32_t color, uint8_t speed, int32_t duration)
{
  int8_t position;
  uint8_t wait = (256-speed) << SPEEDFACTOR;
  while (duration > 0) {
    // start at right end
    for (position = NPIXELS_R + STREAMTRAIL; position > STREAMTRAIL; position--) {
      setwaveright(color, position, STREAMTRAIL);
      delay(wait);
      duration -= wait;
    }
    // middle right to left
    while (position > -STREAMTRAIL) {
      setwavemiddle(color, position-STREAMTRAIL, position+STREAMTRAIL);
      delay(wait);
      duration -= wait;
      position--;
    }
    // to left end
    while (position > -(NPIXELS_L+STREAMTRAIL)) {
      setwaveleft(color, position, STREAMTRAIL);
      delay(wait);
      duration -= wait;
      position--;
    }
    // left end to middle
    while (position < -STREAMTRAIL) {
      setwaveleft(color, position, STREAMTRAIL);
      delay(wait);
      duration -= wait;
      position++;
    }
    // middle left to right
    while (position < STREAMTRAIL) {
      setwavemiddle(color, position-STREAMTRAIL, position+STREAMTRAIL);
      delay(wait);
      duration -= wait;
      position++;
    }
    // to right end
    while (position < NPIXELS_R+STREAMTRAIL) {
      setwaveright(color, position, STREAMTRAIL);
      delay(wait);
      duration -= wait;
      position++;
    }
  }
}

void star(uint32_t color, uint8_t speed, int32_t duration) {
  // outward/inward stream effect
  // always takes longer than specified duration
  // because it completes the whole cycle
  int8_t lead, tail, cur;
  uint8_t fade;
  uint8_t wait = (256 - speed) << SPEEDFACTOR;
  while (duration > 0) {
    lead = 0;
    tail = lead - STARTRAIL;
    while (lead != 100) {
      cur = lead;
      fade = 255;
      while (cur >= tail) {
        if (cur >= 0 && cur < NPIXELS_L) {
          setleft(cur, 1, dim(color, fade));
          //left.show();
        }
        if (cur >= 0 && cur < NPIXELS_R) {
          setright(cur, 1, dim(color, fade));
          //right.show();
        }
        fade -= STARFADE;
        cur--;
      }
      setcenter(0);
      left.show();
      right.show();
      center.show();
      delay(wait);
      duration -= wait;
      lead++;
      tail++;
    }
  }
}

//FADES ALL COLORS ON
void fadeon(uint32_t color, uint32_t duration) {
  for (uint8_t i = 0; i != 220; i++)
    solid(dim(color, i), duration>>8);
}
//FADES ALL COLORS OFF
void fadeoff(uint32_t color, uint32_t duration) {
for (uint8_t i = 220; i != 0; i--)
    solid(dim(color, i), duration>>8);
}



void setup() 
{
  center.begin();
  left.begin();
  right.begin();
  center.show();
  left.show();
  right.show();
}

void loop() 
{
  uint8_t i, j;

solid(ULBWHITE, 1000);
solid(0, 25000);//make 25 seconds

//BABY, APROXIMATELY 1:30
//0:00-1:30
//SLOW STAR, DIFFERENT PATTERN, THEN THE FASTER STAR
  //SLOW STAR
for (i = 0; i < 2; i++){ //slow star four 9 sec loops = 36 seconds
  star(BABYBLUE1, 250, 500); 
  star(BABYBLUE2, 250, 500);
  star(BABYBLUE3, 250, 500);
  star(BABYBLUE4, 250, 500);
  star(BABYBLUE5, 250, 500);
  star(BABYBLUE4, 250, 500);
  star(BABYBLUE3, 250, 500);
  star(BABYBLUE2, 250, 500);
  star(BABYBLUE1, 250, 500);
  } 
  //FAST STREAMER
for ( i = 0; i < 2; i++){ //streamer-slow-random, four 8sec = 32 sec // one side is dimmer and the left side is bright
  star(BABYPURPLE, 250, 500);
  star(BABYMAGENTA, 250, 500);
  star(BABYGREEN, 250, 500);
  star(BABYMAGENTA, 250, 500);
  star(BABYBLUE3, 250, 500);
  star(BABYMAGENTA, 250, 500);
  star(BABYBLUE2, 250, 500);
  }
 for (i = 0; i < 2 ; i++){ //faster star, four 9sec = 36sec
  star(BABYBLUE1, 250, 500);
  star(BABYBLUE2, 250, 500);
  star(BABYBLUE3, 250, 500);
  star(BABYBLUE4, 250, 500);
  star(BABYBLUE5, 250, 500);
  star(BABYBLUE4, 250, 500);
  star(BABYBLUE3, 250, 500);
  star(BABYBLUE2, 250, 500);
  star(BABYBLUE1, 250, 500);
 }

//WAY
//DARKER PURPLES DARK PINKS AND THE LIKE DARKER COLORS
//FLASH THEN FADE PULSE LIKE THING
//APPROXIMATELY 1:20
//1:30-2:52
 for (i = 0; i < 2 ; i++){ //four 5 seconds flash fade pulsing, 20 seconds
  fadeon(ULBRED, 700);
  fadeoff(ULBRED, 700);
  fadeon(NPORANGE, 700);
  fadeoff(NPORANGE, 700);
  
 }
 for (i = 0; i < 2; i++){ //four 5 seconds flash fade 
  fadeon(WAYDARKMAGENTA, 700);
  fadeoff(WAYDARKMAGENTA,700);
  fadeon(WAYDARKPINK, 700);
  fadeoff(WAYDARKPINK, 700);
 }
 for (i = 0; i < 2; i++){
  fadeon(WAYDARKPURPLE, 700);
  fadeoff(WAYDARKPURPLE, 700);
  fadeon(WAYDARKBLUE, 700);
  fadeoff(WAYDARKBLUE, 700);
  fadeon(WAYDARKMAGENTA, 700);
  fadeoff(WAYDARKMAGENTA,700);
  fadeon(WAYDARKPINK, 700);
  fadeoff(WAYDARKPINK, 700);
 }
 for (i = 0; i < 2 ; i++){ //four 5 seconds flash fade pulsing, 20 seconds
  fadeon(ULBRED, 700);
  fadeoff(ULBRED, 700);
  fadeon(NPORANGE, 700);
  fadeoff(NPORANGE, 700);
 }

//8more seconts
//ULB
//MAINLYWHITE WITH RED UNDERTONES
//APPROX 
//2:53-5:06
  for (i = 0; i<5; i++){
    star(ULBWHITE, 50, 500);
    star(NPRED, 250, 500);  
  }
    fadeon(NPRED, 500);
    fadeoff(NPRED, 500);
  for (i = 0; i<2; i++){
    star(ULBWHITE, 50, 500);
    star(NPRED, 250, 500);  
  }
    fadeon(NPRED, 500);
    fadeoff(NPRED, 500);
 

//NO PROBLEMS
//PRIMARY AND SECONDARY RBYGOP
//SLOW IN FOR THE TALK THING WITH SOLID COLORS AND THEN CRAY FOR THE MIDDLE OF THE SONG 
//AND THEN FADE INTO MIXTAPE

  for (i = 0; i != 250 ; i += 10) {
    setleft((0+i)%50,10,DARKERBLUE);
    setleft((10+i)%50,10,RED);
    setleft((20+i)%50,10,PEACH);
    setleft((30+i)%50,10,SALMON);
    setleft((40+i)%50,10,BLUE);
    setleft((50+i)%50,10,PEACH);//CHANGE FOR LIKE 50-55 ON THAT SIDE MAYBE
    setright((0+i)%50,10,BABYBLUE);
    setright((10+i)%50,10,DARKPURPLE);
    setright((20+i)%50,10,HOTPINK);
    setright((30+i)%50,10,PURPLEPINK);
    setright((40+i)%50,10,TEAL);
    setright((50+i)%50,10,RED);//CHANGE MAYBE
    setcenter(0);//CHANGE MAYBE DEPENDING ON PLACEMENT
    left.show();
    right.show();
    center.show();
    delay(1000);
  }

   for (i = 0; i < 2 ; i++){ 
  star(DARKERBLUE, 250, 500);
  star(RED, 250, 500);
  star(SALMON, 250, 500);
  star(BLUE, 250, 500);
  star(BABYBLUE, 250, 500);
  star(DARKPURPLE, 250, 500);
  star(HOTPINK, 250, 500);
  star(PURPLEPINK, 250, 500);
   star(TEAL, 250, 500);
   }
 for (i = 0; i != 250 ; i += 10) {
  setleft((0+i)%50,10,DARKERBLUE);
  setleft((10+i)%50,10,RED);
  setleft((20+i)%50,10,PEACH);
  setleft((30+i)%50,10,SALMON);
  setleft((40+i)%50,10,BLUE);
  setleft((50+i)%50,10,PEACH);//CHANGE FOR LIKE 50-55 ON THAT SIDE MAYBE
  setright((0+i)%50,10,BABYBLUE);
  setright((10+i)%50,10,DARKPURPLE);
  setright((20+i)%50,10,HOTPINK);
  setright((30+i)%50,10,PURPLEPINK);
  setright((40+i)%50,10,TEAL);
  setright((50+i)%50,10,RED);//CHANGE MAYBE
  setcenter(0);//CHANGE MAYBE DEPENDING ON PLACEMENT
  left.show();
  right.show();
  center.show();
  delay(1000);
  }
 for (i = 0; i < 2 ; i++){ 
  star(DARKERBLUE, 250, 500);
  star(RED, 250, 500);
  star(SALMON, 250, 500);
  star(BLUE, 250, 500);
  star(BABYBLUE, 250, 500);
  star(DARKPURPLE, 250, 500);
  star(HOTPINK, 250, 500);
  star(PURPLEPINK, 250, 500);
  star(TEAL, 250, 500);
 } 
   for (i = 0; i != 250 ; i += 10) {
    setleft((0+i)%50,10,DARKERBLUE);
    setleft((10+i)%50,10,RED);
    setleft((20+i)%50,10,PEACH);
    setleft((30+i)%50,10,SALMON);
    setleft((40+i)%50,10,BLUE);
    setleft((50+i)%50,10,PEACH);//CHANGE FOR LIKE 50-55 ON THAT SIDE MAYBE
    setright((0+i)%50,10,BABYBLUE);
    setright((10+i)%50,10,DARKPURPLE);
    setright((20+i)%50,10,HOTPINK);
    setright((30+i)%50,10,PURPLEPINK);
    setright((40+i)%50,10,TEAL);
    setright((50+i)%50,10,RED);//CHANGE MAYBE
    setcenter(0);//CHANGE MAYBE DEPENDING ON PLACEMENT
    left.show();
    right.show();
    center.show();
    delay(500);
  }

//MIXTAPE
//minty grean ORANGE DIFFERENT PINK YELLOW
//PIXELS LIGHTING UP AT DIFFERENT TIMES, PIXELY LOOKING 

 for (i = 0; i < 2; i++){ 
  star(CANDYPINK, 240, 1000);
  star(CANDYBLUE, 240, 3000);
  star(CANDYAPPLE, 240, 3000);
  star(CANDYYELLOW, 240, 3000);
  star(CANDYORANGE, 240, 3000);
  star(CANDYPURPLE, 240, 3000);
 }
for (i =0; i<20;i++){
  solid(MIXMINT, 50);
  solid(MIXORANGE, 50);
  solid(MIXPINKS,50);
}
 for (i = 0; i < 2; i++){ 
  star(CANDYPINK, 240, 1000);
  star(CANDYBLUE, 240, 3000);
  star(CANDYAPPLE, 240, 3000);
  star(CANDYYELLOW, 240, 3000);
  star(CANDYORANGE, 240, 3000);
  star(CANDYPURPLE, 240, 3000);
 }
 for (i =0; i<20;i++){
  solid(MIXMINT, 50);
  solid(MIXORANGE, 50);
  solid(MIXPINKS,50);
}
 for (i = 0; i < 2; i++){ 
  star(CANDYPINK, 240, 1000);
  star(CANDYBLUE, 240, 3000);
  star(CANDYAPPLE, 240, 3000);
  star(CANDYYELLOW, 240, 3000);
  star(CANDYORANGE, 240, 3000);
  star(CANDYPURPLE, 240, 3000);
 }
 for (i =0; i<10;i++){
  solid(MIXMINT, 500);
  solid(MIXORANGE, 500);
  solid(MIXPINKS,500);
}
//ALL NIGHT CRAZY CANDY COLORS

  for (i = 0; i != 250; i += 10) {
    setleft((0+i)%50,10,NPRED);
    setleft((10+i)%50,10,NPBLUE);
    setleft((20+i)%50,10,NPYELLOW);
    setleft((30+i)%50,10,NPGREEN);
    setleft((40+i)%50,10,NPORANGE);
    setleft((50+i)%50,10,NPPURPLE);//CHANGE FOR LIKE 50-55 ON THAT SIDE MAYBE
    setright((0+i)%50,10,NPBLUE);
    setright((10+i)%50,10,NPYELLOW);
    setright((20+i)%50,10,NPGREEN);
    setright((30+i)%50,10,NPORANGE);
    setright((40+i)%50,10,NPPURPLE);
    setright((50+i)%50,10,NPBLUE);//CHANGE MAYBE
    setcenter(0);//CHANGE MAYBE DEPENDING ON PLACEMENT
    left.show();
    right.show();
    center.show();
    delay(500);
  } 
  for (i =0; i<20;i++){
  solid(MIXMINT, 50);
  solid(MIXORANGE, 50);
  solid(MIXPINKS,50);
  } 
    for (i = 0; i != 250; i += 10) {
    setleft((0+i)%50,10,NPRED);
    setleft((10+i)%50,10,NPBLUE);
    setleft((20+i)%50,10,NPYELLOW);
    setleft((30+i)%50,10,NPGREEN);
    setleft((40+i)%50,10,NPORANGE);
    setleft((50+i)%50,10,NPPURPLE);//CHANGE FOR LIKE 50-55 ON THAT SIDE MAYBE
    setright((0+i)%50,10,NPBLUE);
    setright((10+i)%50,10,NPYELLOW);
    setright((20+i)%50,10,NPGREEN);
    setright((30+i)%50,10,NPORANGE);
    setright((40+i)%50,10,NPPURPLE);
    setright((50+i)%50,10,NPBLUE);//CHANGE MAYBE
    setcenter(0);//CHANGE MAYBE DEPENDING ON PLACEMENT
    left.show();
    right.show();
    center.show();
    delay(500);
  }
 for (i =0; i<20;i++){
  solid(MIXMINT, 50);
  solid(MIXORANGE, 50);
  solid(MIXPINKS,50);
 }
  for (i = 0; i< 40000; i += 10) {
    setleft((0+i)%50,10,NPRED);
    setleft((10+i)%50,10,NPBLUE);
    setleft((20+i)%50,10,NPYELLOW);
    setleft((30+i)%50,10,NPGREEN);
    setleft((40+i)%50,10,NPORANGE);
    setleft((50+i)%50,10,NPPURPLE);//CHANGE FOR LIKE 50-55 ON THAT SIDE MAYBE
    setright((0+i)%50,10,NPBLUE);
    setright((10+i)%50,10,NPYELLOW);
    setright((20+i)%50,10,NPGREEN);
    setright((30+i)%50,10,NPORANGE);
    setright((40+i)%50,10,NPPURPLE);
    setright((50+i)%50,10,NPBLUE);//CHANGE MAYBE
    setcenter(0);//CHANGE MAYBE DEPENDING ON PLACEMENT
    left.show();
    right.show();
    center.show();
    delay(500);
  }
  
   }


