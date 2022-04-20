import processing.serial.*;
import java.util.List;
import java.util.ArrayList;


Serial myPort;
List<Button> myButtons;

Button testButton;
boolean waitingForResponse;

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


  if (myPort.available() > 1) {
    String dat = myPort.readString();
    System.out.printf("Particle > %s", dat);
  } else {
    byte[] packet = readCommand();
    MainCommand cmd = MainCommand.get(packet[0]);

    switch (cmd) {
    case STATUS: 
      {
        Statuses status = Statuses.get(packet[1]);
        switch(status) {
        case PROGRAM_SUCCESSFUL:
          System.out.printf("Programmer > Successfully programmed cmd\n");
          waitingForResponse = false;
          break;
        case NO_DATA_AVAILABLE:
          break;
        case REQUEST_FAILED:
          System.out.printf("Programmer > Failed to request data\n");
          waitingForResponse = false;
          break;
        default:
          System.out.printf("Programmer > Unknown status %s\n", status.toString());
          break;
        }
        break;
      }
    case BEST_FINGER:
      FingerPosition pos = FingerPosition.get(packet[1]);
      System.out.printf("Best finger pos is %s\n", pos.toString());
      waitingForResponse = false;
      break;
    default:
      System.out.printf("Programmer > Unknown command 0x%X  0x%X\n", packet[0], packet[1]);
    }
  }

  // Check if the port has more than one byte. If so just print the byte.
  //if (myPort.available() > 1) {
  //  String dat = myPort.readString();
  //  System.out.print("Particle > " + dat);
  //} else if (myPort.available() == 1) { // Otherwise treat the single byte as a command
  //  byte[] packet = readCommand();

  //  switch(MainCommand.get(packet[0])) {
  //    case STATUS:
  //      HandSigns sign = HandSigns.getSign(packet[1]);
  //      if (sign != null) {
  //        System.out.printf("Programmer > Programmed sign %s\n", sign.toString().toLowerCase());
  //      } else {
  //        System.out.printf("Programmer > ERROR programmed invalid sign '0x%X%X\n'\n", packet[0], packet[1]);
  //      }
  //      break;
  //    default:
  //      System.out.printf("Programmer > ERROR Recieved command '0x%X%X', not currently implemented\n", packet[0], packet[1]);
  //  }

  //Commands cmd = Commands.getCommand(myPort.read());
  //switch(cmd) {
  //case PROGRAMMED_PEACE:
  //case PROGRAMMED_THUMB_UP:
  //case PROGRAMMED_ROCK_ON:
  //case PROGRAMMED_SPIDER_MAN:
  //  System.out.printf("Programmer > Successfully programmed the %s sign\n", cmd.toString());
  //  break;
  //case BEST_PEACE:
  //case BEST_THUMB_UP:
  //case BEST_ROCK_ON:
  //case BEST_SPIDER_MAN:
  //  System.out.printf("Programmer > Best value is the %s sign\n", cmd.toString());
  //  break;
  //case BEST_UNKNOWN:
  //  System.out.printf("Programmer > Unknown best value\n");
  //  break;
  //default:
  //  // Should never get here
  //  System.out.printf("Programmer > ERROR: Recieved command %s:'%d', not currently implemented\n", cmd.toString(), cmd.val);
  //  break;
  //}
  //  }
}

void mousePressed() {
  for (int i = 0; i < myButtons.size(); i++) {
    myButtons.get(i).mousePressed();
  }
}
