import processing.video.*;
import processing.serial.*;

int CAP_WIDTH = 640;
int CAP_HEIGHT = 360;
int GRAIN_SIZE = 60;

Capture cam;

color[] c_m = new color[(CAP_WIDTH / GRAIN_SIZE) * (CAP_HEIGHT / GRAIN_SIZE)];
color[] last_c_m = new color[(CAP_WIDTH / GRAIN_SIZE) * (CAP_HEIGHT / GRAIN_SIZE)];

Serial sport;

void setup() {
  
  println(c_m.length);
  
  size(640, 360);
  background(0);
  stroke(255);
  String[] cameras = Capture.list();
    
  if (cameras.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    //println("Available cameras:");
    //for (int i = 0; i < cameras.length; i++) {
    //  println(cameras[i]);
    //}
    
    // The camera can be initialized directly using an 
    // element from the array returned by list():
    cam = new Capture(this, CAP_WIDTH, CAP_HEIGHT, cameras[3]);
    cam.start();     
  }
  
  printArray(Serial.list());
  
  sport = new Serial(this, Serial.list()[4], 9600);

}

void draw() {
  if (cam.available() == true) {
    cam.read();
  }
 
  PImage new_im = cam;
  
  arrayCopy(c_m, last_c_m);
  
  for(int x = 0; x < CAP_WIDTH / GRAIN_SIZE; x ++){
    for(int y = 0; y < CAP_HEIGHT / GRAIN_SIZE; y ++){
       c_m[y * (CAP_WIDTH / GRAIN_SIZE) + x] = new_im.get(x * GRAIN_SIZE,y * GRAIN_SIZE);
    }
  }
  delay(1);
  
  fill_all(c_m, last_c_m);
}
void fill_all(color input[], color last_input[]){
  int counter = 0;
  sport.write("-1");
  println("RESETING");
  for(int x = 0; x < CAP_WIDTH / GRAIN_SIZE; x ++){
    for(int y = 0; y < CAP_HEIGHT / GRAIN_SIZE; y ++){
       float delta = brightness(last_input[y * (CAP_WIDTH / GRAIN_SIZE) + x]) - brightness(input[y * (CAP_WIDTH / GRAIN_SIZE) + x]);
       delta = abs(delta);
       println(Integer.toString(int(filter(delta, 255))));
       counter++;
       sport.write(Integer.toString(int(filter(delta, 0))));
       sport.write(Integer.toString(int(filter(delta, 127))));
       sport.write(Integer.toString(int(filter(delta, 255))));
       //sport.write(Integer.toString(255));

       stroke(255);
       fill(filter(delta, 255), filter(delta, 127), filter(delta, 0));
       rect(x * GRAIN_SIZE, y * GRAIN_SIZE, GRAIN_SIZE, GRAIN_SIZE);
    }
  }
}

float filter(float input, float cutoff){
  float spread = 127.0;
  float e = 2.7;
  float exp = -1.0 * pow(((1.0/spread) * (input - cutoff)),2.0);
  //return input;
  return input * pow(e,exp);
}
