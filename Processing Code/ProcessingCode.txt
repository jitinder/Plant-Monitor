/*
   Arduino Project Source Code - Processing IDE
   By: Sidak Pasricha
   Purpose: Takes serial input from the Arduino
            Draws a real-time graph that shows fluctuations in Temperature and Light as obtained from the Arduino
   Application: Intended for maintaining a plant:
                Real time graph can be used to monitor growth conditions with appropriate axis.
                The value of the temperature at the time it is being plotted is shown in the graph
                The condition of the extra lights is shown in the graph: whether they are activated or not
                The graph also has optimal ranges for the Temperature and LDR output in green
*/
import processing.serial.*;

Serial arduinoPort; //The Serial Port for the Arduino
int x1 = 50; //Horizontal Position of Graph 1
int x2 = 550; //Horizontal Position of Graph 2
float inByte1, inByte2 = 0; //Used for mapping the correct values of temperature and light on the graph
float temp, light = 0; //Stores the obtained value of temperature and light respectively
/* Storing the coordinates of the last point plotted to allow smoother creation of graph */
float lastX1 = x1;
float lastX2 = x2;
float lastY1, lastY2 = 0;

void setup() {
  size(1000, 400); //Window size
  background(#FFFFFF);
  drawLayout1();
  drawLayout2();

  //Opens the port the Arduino uses on the PC
  arduinoPort = new Serial(this, Serial.list()[0], 9600);

  //Generates the serialEvent() after the newline character is seen.
  arduinoPort.bufferUntil('\n');

}

void draw() {

  if (inByte1 != 0 && inByte2 != 0) {
    /* Draw line from Temperature Input */
    stroke(#000000);
    line(lastX1, lastY1, x1, 349 - inByte1);
    line(x1, 349 - inByte1, x1, 349 - inByte1);
    lastX1 = x1;
    lastY1 = 349 - inByte1;

    /* Draw line from Light Input */
    stroke(#000000);
    line(lastX2, lastY2, x2, 349 - inByte2);
    line(x2, 349 - inByte2, x2, 349 - inByte2);
    lastX2 = x2;
    lastY2 = 349 - inByte2;

    showTempData(temp); //Handles the Temperature Text
    showLightStatus(light);//Handles the Light Status Text

    // Restarts graphs from start when they reach end of graphing area
    if (x1 >= 450 || x2 >= 950) {
      fill(#FFFFFF);
      rect(0, 0, 1000, 400);
      drawLayout1();
      drawLayout2();
      x1 = 50;
      x2 = 550;
      lastX1 = x1;
      lastX2 = x2;
    }
    x1++;
    x2++;
  }

}

void showTempData(float temp) {
  /* Creating Empty Box for Updating Temperature */
  fill(#FFFFFF);
  stroke(#FFFFFF);
  beginShape();
  vertex(345, 35);
  vertex(345, 55);
  vertex(460, 55);
  vertex(460, 35);
  endShape();

  /* Creating Text to show Temperature value on the graph */
  textSize(10);
  if (temp <= 30 && temp >= 20) {
    fill(#000000); // If in Ideal range, black text
  } else {
    fill(#FF0000); // If not in Ideal range, red text
  }
  text("Temperature: " + temp + " C", 350, 50);
}

void showLightStatus(float light) {
  /* Creating Empty Box for Updating Extra Light Status */
  fill(#FFFFFF);
  stroke(#FFFFFF);
  beginShape();
  vertex(845, 35);
  vertex(845, 55);
  vertex(960, 55);
  vertex(960, 35);
  endShape();

  /* Creating Text to show Light value on the graph */
  textSize(10);
  String status = ""; // Stores current status.
  if (light < 550) {
    fill(#FF0000); // If not in Ideal range, red text
    status = "on";
  } else {
    fill(#000000); // If in Ideal range, black text
    status = "off";
  }
  text("Extra Light: " + status, 850, 50);
}

void serialEvent(Serial arduinoPort) {
  try { //Prevents stopping of graphing incase there is a delay in serial data retrieval
    String inString = arduinoPort.readStringUntil('\n'); //Reads Arduino output and stores in String
    if (inString != null) {
      float values[] = float(split(inString, ",")); //Splits the output into two appropriate indexes for temperature and light
      temp = values[0];
      light = values[1];
      inByte1 = map(values[0], 0, 60, 0, 300); //Stores the appropriate value of distance from the axes based on temperature scale in graph and available pixels
      inByte2 = map(values[1], 0, 1200, 0, 300); //Stores the appropriate value of distance from the axes based on LDR output range in graph and available pixels
    }
  } catch (RuntimeException e) {
    e.printStackTrace();
  }
}

void drawLayout1() {
  /* The Heading Text */
  textSize(18);
  fill(#000000);
  text("Temperature", 205, 25);

  /* The Axes */
  stroke(#000000);
  line(25, 350, 450, 350); //x-axis
  line(50, 50, 50, 375); //y-axis

  /* Creating Ideal Range Box for Temperature */
  fill(#9EFF95);
  stroke(#9EFF95);
  beginShape();
  vertex(51, 200);
  vertex(451, 200);
  vertex(451, 250);
  vertex(51, 250);
  endShape();

  /* Printing y-axis Labels */
  textSize(9);
  fill(#000000);
  stroke(#000000);
  int y = 300;
  for (int i = 1; i <= 6; i++) {
    text("" + i * 10, 25, y + 4);
    line(45, y, 55, y);
    y -= 50;
  }
}

void drawLayout2() {
  /* The Heading Text */
  textSize(18);
  fill(#000000);
  text("Light", 705, 25);

  /* The Axes */
  stroke(#000000);
  line(525, 350, 950, 350); //x-axis
  line(550, 50, 550, 375); //y-axis

  /* Creating Ideal Range Box for Light Dependent Resistor Reading */
  fill(#9EFF95);
  stroke(#9EFF95);
  beginShape();
  vertex(551, 100);
  vertex(951, 100);
  vertex(951, 212.5);
  vertex(551, 212.5);
  endShape();

  /* Printing y-axis Labels */
  textSize(9);
  fill(#000000);
  stroke(#000000);
  int y = 300;
  for (int i = 1; i <= 6; i++) {
    text("" + i * 200, 520, y + 4);
    line(545, y, 555, y);
    y -= 50;
  }
}