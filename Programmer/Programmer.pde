import processing.serial.*;

Serial myPort;

void setup() {
  size(640, 360);
  createPeaceSignButton(20, 20);
  createThumbsUpButton(150, 20);
  createGetBestButton(280,20);
  myPort = new Serial(this, "COM5", 9600);
}



void programPeaceSign() {
   System.out.printf("Sending peace sign program request...");
   myPort.write("REQ_PEACE");
}

void programThumbsUp() {
   System.out.printf("Sending peace sign program request...");
   myPort.write("REQ_THUMB_UP");
}

void requestBest() {
  System.out.printf("Requesting best match...");
  myPort.write("REQ_BEST");
}

void draw() {
  background(255);
  peaceSignButton.draw();
  thumbsUpButton.draw();
  getBestButton.draw();
  
  while(myPort.available() > 0) {
    String dat = myPort.readString();
    if (dat.equals("PROG_PEACE")) {
       System.out.printf("Peace sign programmed\n"); 
    } else if (dat.equals("PROG_THUMB_UP")){
      System.out.printf("Thumps up sign programmed\n");
    } else if (dat.equals("BEST_PEACE")) {
      System.out.printf("Best is peace\n");
    } else if (dat.equals("BEST_THUMB_UP")) {
      System.out.printf("Best is thumb up\n");
    } else if (dat.equals("BEST_UNKOWN")) {
      System.out.printf("No best found\n");
    } else {
      System.out.print(dat); 
    }
  }
}

void mousePressed() {
   peaceSignButton.mousePressed();
   thumbsUpButton.mousePressed();
   getBestButton.mousePressed();
}
