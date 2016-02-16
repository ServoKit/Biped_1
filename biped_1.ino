#include <Servo.h>

// REST values are servo neutral position
// Adjust so that the servo arm is at exactly 90 degress
// to the servo

#define LEG_REST 94
#define FOOT_REST 90 

// Upper servo lifts feet, experiment with values to
// clear feet from ground, too high values and biped will
// topple over

#define LEFT_FOOT_UP 101
#define RIGHT_FOOT_UP 80

// Lower servo moves legs, change values for
// smaller / larger steps

#define LEFT_LEG_FORWARD 84
#define RIGHT_LEG_FORWARD 104

// STEP_DELAY: delay between steps in ms
// MOVE_DELAY: delay between individual servo moves

#define STEP_DELAY 10
#define MOVE_DELAY 4   

Servo leg;  
Servo foot;

void setup() 
{
  leg.attach(9);  
  foot.attach(10);
  legs(LEG_REST);
  feet(FOOT_REST);
  delay(3000);
}

void loop() 
{
  // Walking straight forward
  
  feet(LEFT_FOOT_UP); 
  legs(LEFT_LEG_FORWARD);
  feet(FOOT_REST);  
  feet(RIGHT_FOOT_UP); 
  legs(RIGHT_LEG_FORWARD);
  feet(FOOT_REST);
}

void legs(int move)
{
  int v = leg.read();
  int delayy;
  if(v < move)
  {
    for(int i=0;i<=move-v;i++)
    {
      leg.write(v + i);
      interDelay(i, move - v);
    }
  }
  else
  {
    for(int i=0;i>=move-v;i--)
    {
      leg.write(v + i);
      interDelay(i, move - v);
    }
  }  
  delay(STEP_DELAY);
}

void feet(int move)
{
  int v = foot.read();
  if(v < move)
  {
    for(int i=0;i<=move-v;i++)
    {
      foot.write(v + i);
      interDelay(i, move - v);
    }
  }
  else
  {
    for(int i=0;i>=move-v;i--)
    {
      foot.write(v + i);
      interDelay(i, move - v);      
    }
  }  
  delay(STEP_DELAY);
}

void interDelay(int current, int target)
{
    // Very simple ease in / ease out
    // Experiment with values for smooth movement
    
    int percentage = (int)(((float)current/(float)(target)) * 100.0);
    int wait = MOVE_DELAY;
    if(percentage < 30 || percentage > 70)
      wait = 10 * MOVE_DELAY;
    if(percentage < 10 || percentage > 90)
      wait = 20 * MOVE_DELAY;
    delay(wait);
}
