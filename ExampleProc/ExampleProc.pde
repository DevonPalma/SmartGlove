import processing.serial.*;

Serial myPort;

boolean isGreen = true;

void setup() {
  size(640, 480);
  myPort = new Serial(this, "COM5" , 9600);
}

void draw() {
  if (isGreen) {
    background(0, 255, 0);    
  } else {
    background(255, 0, 0); 
  }
  
  if (myPort.available() > 0) {
    String dat = myPort.readString();
    if (dat.contains("Counted up")) {
      isGreen = true;
    } else if (dat.contains("Counted down")) {
      isGreen = false;
    } else {
      System.out.print(dat);
    }
  }
}
