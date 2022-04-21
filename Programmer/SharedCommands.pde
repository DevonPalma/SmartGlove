/* Commands fill up one byte. This means I can have 256 different commands
 * In order to not have to define a shit load of them for various hand poses
 * I made a special lil algorithm for creating the byte per command
 *
 *   1bit = 2
 *   2bit = 4
 *   3bit = 8
 *   4bit = 16
 *   5bit = 32
 *   6bit = 64
 *   7bit = 128
 *   8bit = 256
 *
 * As there will be quite a large number of hand poses I decided the bit should be split
 * up as such:
 *
 *   0b1110 0000 = 0xE0 = Main command, giving me 16 main commands
 *   0b0001 1111 = 0x1F = Sub command data, giving me 16 different sub commands / meta data
 */


// === Main Commands ===

enum MainCommand {
  PROGRAM(0x0), // Using a FingerPosition as the sub cmd, tells the particle to save its current pos in corresponding finger
    REQUEST(0x1); // Sends a request packet, see RequestSubCommands for extra data

  public final byte metaData;

  private MainCommand(int data) {
    this.metaData = (byte) data;
  }
  
  public static MainCommand get(byte data) {
    for (MainCommand cmd : MainCommand.values()) {
      if (cmd.metaData == data) {
        return cmd;
      }
    }
    return null;
  }
}

enum FingerPosition {
  P_FIST(0x00), 
    P_PEACE(0x01), 
    P_GUN(0x02), 
    P_ROCK(0x03), 
    P_SPIDER(0x04), 
    P_2P1S(0x05), 
    P_PHONE(0x06), 
    P_OKAY(0x07);
    //F_01000(0x08),
    //F_01001(0x09),
    //F_01010(0x0A),
    //F_01011(0x0B),
    //F_01100(0x0C),
    //F_01101(0x0D),
    //F_01110(0x0E),
    //F_01111(0x0F);
    //F_10000(0x10), 
    //F_10001(0x11), 
    //F_10010(0x12), 
    //F_10011(0x13), 
    //F_10100(0x14), 
    //F_10101(0x15), 
    //F_10110(0x16), 
    //F_10111(0x17),
    //F_11000(0x18),
    //F_11001(0x19),
    //F_11010(0x1A),
    //F_11011(0x1B),
    //F_11100(0x1C),
    //F_11101(0x1D),
    //F_11110(0x1E),
    //F_11111(0x1F);

  public final byte metaData;

  private FingerPosition(int data) {
    this.metaData = (byte) data;
  }
  
  public static FingerPosition get(byte data) {
    for (FingerPosition pos : FingerPosition.values()) {
      if (pos.metaData == data) {
        return pos;
      }
    }
    return null;
  }
}


enum RequestSubCommands {
  BEST(0x00), // Request the best finger position, Expects the provide packet value to be a finger position
  WIPE(0x01);

  public final byte metaData;

  private RequestSubCommands(int data) {
    this.metaData = (byte) data;
  }
  
  public static RequestSubCommands get(byte data) {
    for (RequestSubCommands cmd : RequestSubCommands.values()) {
      if (cmd.metaData == data) {
        return cmd;
      }
    }
    return null;
  }
}


void sendCommand(byte mainCmd, byte dat) {
  myPort.write(mainCmd << 5 | dat);
}
