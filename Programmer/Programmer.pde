import processing.serial.*;
import java.util.List;
import java.util.ArrayList;


Serial myPort;
List<Button> myButtons;

Button testButton;

void setup() {
  size(640, 600);
  myPort = new Serial(this, "COM5", 9600);
  myButtons = new ArrayList();
  waitingForResponse = false;

  int x = 0;
  int y = 0;
  for (FingerPosition pos : FingerPosition.values()) {
    myButtons.add(new EzButton(x, y, MainCommand.PROGRAM, pos));
    x++;
    if (x > 3) {
      x = 0;
      y++;
    }
  }
  myButtons.add(new EzButton(3, y+1, MainCommand.REQUEST, RequestSubCommands.BEST));
  myButtons.add(new EzButton(2, y+1, MainCommand.REQUEST, RequestSubCommands.WIPE));
}


void draw() {
  background(255);

  // Draw all buttons. If one is hovered, it will be drawn last.
  Button activeButton = null;
  for (int i = 0; i < myButtons.size(); i++) {
    Button iButton = myButtons.get(i);
    iButton.update();
    if (iButton.isMouseInside()) {
      activeButton = iButton;
    } else {
      iButton.draw();
    }
  }
  if (activeButton != null) {
    activeButton.draw();
  }


  if (myPort.available() > 0) {
    String dat = myPort.readString();
    System.out.printf("Particle > %s", dat);
  }

}

void mousePressed() {
  for (int i = 0; i < myButtons.size(); i++) {
    myButtons.get(i).mousePressed();
  }
}
