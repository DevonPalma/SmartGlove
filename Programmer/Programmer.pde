import processing.serial.*;
import java.util.List;
import java.util.ArrayList;


Serial myPort;
List<CommandButton> myButtons;

void setup() {
  size(640, 360);
  myPort = new Serial(this, "COM5", 9600);
  myButtons = new ArrayList<CommandButton>();

  myButtons.add(new CommandButton(0, 0, Commands.PROGRAM_PEACE));
  myButtons.add(new CommandButton(1, 0, Commands.PROGRAM_THUMB_UP));
  myButtons.add(new CommandButton(2, 0, Commands.PROGRAM_ROCK_ON));
  myButtons.add(new CommandButton(3, 0, Commands.PROGRAM_SPIDER_MAN));
  myButtons.add(new CommandButton(3, 3, Commands.REQUEST_BEST));
}


void draw() {
  background(255);

  // Draw all buttons. If one is hovered, it will be drawn last.
  CommandButton activeButton = null;
  for (int i = 0; i < myButtons.size(); i++) {
    CommandButton iButton = myButtons.get(i);
    if (iButton.isMouseInside()) {
      activeButton = iButton;
    } else {
      iButton.draw();
    }
  }
  if (activeButton != null) {
    activeButton.draw();
  }
  
  
  
  // Check if the port has more than one byte. If so just print the byte.
  if (myPort.available() > 1) {
    String dat = myPort.readString();
    System.out.print("Particle > " + dat);
  } else if (myPort.available() == 1) { // Otherwise treat the single byte as a command
    Commands cmd = Commands.getCommand(myPort.read());
    switch(cmd) {
    case PROGRAMMED_PEACE:
    case PROGRAMMED_THUMB_UP:
    case PROGRAMMED_ROCK_ON:
    case PROGRAMMED_SPIDER_MAN:
      System.out.printf("Programmer > Successfully programmed the %s sign\n", cmd.toString());
      break;
    case BEST_PEACE:
    case BEST_THUMB_UP:
    case BEST_ROCK_ON:
    case BEST_SPIDER_MAN:
      System.out.printf("Programmer > Best value is the %s sign\n", cmd.toString());
      break;
    case BEST_UNKNOWN:
      System.out.printf("Programmer > Unknown best value\n");
      break;
    default:
      // Should never get here
      System.out.printf("Programmer > ERROR: Recieved command %s:'%d', not currently implemented\n", cmd.toString(), cmd.val);
      break;
    }
  }
}

void mousePressed() {
  for (int i = 0; i < myButtons.size(); i++) {
    myButtons.get(i).mousePressed();
  }
}
