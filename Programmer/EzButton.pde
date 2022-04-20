class EzButton extends Button {
  
  private final static int START_X = 20;
  private final static int START_Y = 20;
  private final static int START_W = 150;
  private final static int START_H = 50;
  
  private int x, y;
  
  private String defaultLabel;
  private String hoverLabel;
  private byte mainCmd;
  private byte subCmd;
  
  
  private void addDefaultDescription() {
    addDescription(
          new BoolChecker() {
            public boolean check() {
              return true;
            }
          }, 
          new ButtonDescriptionBuilder()
              .dimension(START_X + x * START_W, START_Y + y * START_H, START_W, START_H)
              .textSpacing(5)
              .backgroundColor(color(255))
              .borderColor(color(0))
              .text(defaultLabel)
              .build());
  }
  
  private void addHoverDescription() {
    addDescription(
      new BoolChecker() {
        public boolean check() {
          return isMouseInside();
        }
      },
      new ButtonDescriptionBuilder()
        .extraSize(5)
        .text(hoverLabel)
        .backgroundColor(color(200))
        .borderColor(color(50))
        .build());
  }
  
  private void addWaitingDescription() {
    addDescription(
      new BoolChecker() {
        public boolean check() {
          return waitingForResponse;
        }
      },
      new ButtonDescriptionBuilder()
        .text("Waiting")
        .build());
  }
  
  private void addClickAction() {
    bindOnClick(new Runnable() {
      public void run() {
        System.out.printf("Pressed %s, sending cmd\n", defaultLabel);
        waitingForResponse = true;
        sendCommand(mainCmd, subCmd);
      }
    });
  }
  
  private EzButton(int x, int y, byte cmd, byte pos) {
    this.x = x;
    this.y = y;
    mainCmd = cmd;
    subCmd = pos;
  }
  
  public EzButton(int x, int y, MainCommand cmd, FingerPosition pos) {
    this(x, y, cmd.metaData, pos.metaData);
    String label = cmd.toString().toLowerCase() + " " + pos.toString().toLowerCase();
    defaultLabel = label;
    hoverLabel = "Send\n " + label + "?";
    addDefaultDescription();
    addHoverDescription();
    addClickAction();
    addWaitingDescription();
  }
  
  public EzButton(int x, int y, MainCommand cmd, RequestSubCommands pos) {
    this(x, y, cmd.metaData, pos.metaData);
    defaultLabel = String.format("%s %s", cmd.toString(), pos.toString());
    hoverLabel = String.format("Send\n %s %s?", cmd.toString(), pos.toString());
    addDefaultDescription();
    addHoverDescription();
    addClickAction();
    addWaitingDescription();
  }
  
}
