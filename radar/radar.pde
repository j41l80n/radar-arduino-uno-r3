import processing.serial.*; // imports library for serial communication
import java.awt.event.KeyEvent; // imports library for reading the data from the serial port
import java.io.IOException;
Serial myPort; // defines Object Serial
// defubes variables
String angle="";
String distance="";
String data="";
String noObject;
float pixsDistance;
int iAngle, iDistance;
int index1=0;
int index2=0;
PFont orcFont;

int altura = 1920;
int largura = 1080;

void setup() {
  size (1248, 700);
  printArray(Serial.list());
  smooth();
  myPort = new Serial(this, "COM3", 9600); // starts the serial communication
  myPort.bufferUntil('.'); // reads the data from the serial port up to the character '.'. So actually it reads this: angle,distance.
}
void draw() {
  fill(98, 245, 31);
  // simulating motion blur and slow fade of the moving line
  noStroke();
  fill(0, 4); 
  rect(0, 0, width, 800); 

  fill(98, 245, 31); // green color
  // calls the functions for drawing the radar
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}

void serialEvent (Serial myPort) { // starts reading data from the Serial Port
  // reads the data from the Serial Port up to the character '.' and puts it into the String variable "data".
  data = myPort.readStringUntil('.');
  data = data.substring(0, data.length()-1);

  index1 = data.indexOf(","); // find the character ',' and puts it into the variable "index1"
  angle= data.substring(0, index1); // read the data from position "0" to position of the variable index1 or thats the value of the angle the Arduino Board sent into the Serial Port
  distance= data.substring(index1+1, data.length()); // read the data from position "index1" to the end of the data pr thats the value of the distance
  // converts the String variables into Integer
  iAngle = int(angle);
  iDistance = int(distance);
}

void drawRadar() {
  pushMatrix();
  translate(960, 650); // moves the starting coordinats to new location
  noFill();
  strokeWeight(2);
  stroke(98, 245, 31);
  
  arc(0, 0, 900, 900, PI, TWO_PI);
  arc(0, 0, 700, 700, PI, TWO_PI);
  arc(0, 0, 500, 500, PI, TWO_PI);
  arc(0, 0, 300, 300, PI, TWO_PI);
  
  //linha horizontal
  line(-480, 0, 480, 0);
  line(0, 0, -480*cos(radians(30)), -480*sin(radians(30)));
  line(0, 0, -480*cos(radians(60)), -480*sin(radians(60)));
  line(0, 0, -480*cos(radians(90)), -480*sin(radians(90)));
  //60
  line(0, 0, -480*cos(radians(120)), -480*sin(radians(120)));
  //30
  line(0, 0, -480*cos(radians(150)), -480*sin(radians(150)));
  line(-480*cos(radians(30)), 0, 480, 0);
  
  popMatrix();
}

//linha vermelha
void drawObject() {
  pushMatrix();
  //linha vermelha
  translate(960, 650); // moves the starting coordinats to new location
  strokeWeight(9);
  stroke(255, 10, 10); // red color
  pixsDistance = iDistance * 22.5; // covers the distance from the sensor from cm to pixels
  // limiting the range to 40 cms
  if (iDistance < 40) {
    // draws the object according to the angle and the distance
    line(pixsDistance*cos(radians(iAngle)), -pixsDistance*sin(radians(iAngle)), 480*cos(radians(iAngle)), -480*sin(radians(iAngle)));
  }
  popMatrix();
}

//linha verde
void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30, 250, 60);
  translate(960, 650); // moves the starting coordinats to new location
  line(0, 0, 480*cos(radians(iAngle)), -480*sin(radians(iAngle))); // draws the line according to the angle
  popMatrix();
}

void drawText() { // draws the texts on the screen
  pushMatrix();
  if (iDistance > 40) {
    noObject = "fora de alcance";
  } else {
    noObject = "no alcance";
  }
  fill(0, 0, 0);
  noStroke();
  rect(0, 1010, width, 600);
  fill(98, 245, 31);
  textSize(15);
  text("10cm", 1120, 640);
  text("20cm", 1220, 640);
  text("30cm", 1320, 640);
  text("40cm", 1420, 640);
  text("objeto: " + noObject, width/2-360, 690);
  text("angulo: " + iAngle +" °", width/2-30, 690);
  text("distancia: " + iDistance, width/2+280, 690);
  
  if (iDistance<40) {
    text("        " + iDistance +" cm", 1400, 1050);
  }
  
  //textos dos angulos
  textSize(15);
  fill(98, 245, 60);
  translate(961+500*cos(radians(30)), 982-1200*sin(radians(30)));
  rotate(-radians(-60));
  text("30°", 0, 0);
  resetMatrix();
  translate(954+500*cos(radians(60)), 984-900*sin(radians(60)));
  rotate(-radians(-30));
  text("60°", 0, 0);
  resetMatrix();
  translate(945+500*cos(radians(90)), 990-850*sin(radians(90)));
  rotate(radians(0));
  text("90°", 0, 0);
  resetMatrix();
  translate(935+500*cos(radians(120)), 1003-900*sin(radians(120)));
  rotate(radians(-30));
  text("120°", 0, 0);
  resetMatrix();
  translate(940+500*cos(radians(150)), 1018-1200*sin(radians(150)));
  rotate(radians(-60));
  text("150°", 0, 0);
  popMatrix();
}
