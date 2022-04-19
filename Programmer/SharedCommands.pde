enum Commands {
  UNKNOWN(0xFF),
  
  PROGRAM_PEACE(0x01),
  PROGRAMMED_PEACE(0x11),
  
  PROGRAM_THUMB_UP(0x02),
  PROGRAMMED_THUMB_UP(0x12),
  
  PROGRAM_ROCK_ON(0x03),
  PROGRAMMED_ROCK_ON(0x13),
  
  REQUEST_BEST(0xA0),
  BEST_PEACE(0xA1),
  BEST_THUMB_UP(0xA2),
  BEST_ROCK_ON(0xA3),
  BEST_UNKNOWN(0xB0);
  
  public final int val;
  
  private Commands(int val) {
    this.val = val;
  }
  
  static public Commands getCommand(int val) {
    for (Commands cmd : Commands.values()) {
      if (cmd.val == val) {
        return cmd;
      }
    }
    return UNKNOWN;
  }
}
