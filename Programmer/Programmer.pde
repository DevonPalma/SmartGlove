import processing.serial.*;

Serial myPort;

void setup() {
  size(640, 360);
  createPeaceSignButton();
  myPort = new Serial(this, "COM5", 9600);
}



void programPeaceSign() {
   System.out.printf("Sending peace sign program request...");
   myPort.write("PEACE_REQUEST");
}

void draw() {
  background(255);
  peaceSignButton.draw();
  
  while(myPort.available() > 0) {
    String dat = myPort.readString();
    if (dat.equals("PEACE_COMPLETE")) {
       System.out.printf("Peace sign programmed\n"); 
    }
  }
}

void mousePressed() {
   peaceSignButton.mousePressed();
}
