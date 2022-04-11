import processing.serial.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

Serial myPort;

void setup() {
   myPort = new Serial(this, "COM9", 9600);
}

void draw() {
  while (myPort.available() > 0) {
    String data = myPort.readString();
    Pattern pattern = Pattern.compile("([A-Z]):(\\d+),(\\d+),(\\d+),(\\d+)");
    Matcher matcher = pattern.matcher(data);
    if (!matcher.find()) {
      print(data);
      return;
    }
    
    String imageGroup = matcher.group(1);
    
    File f = new File(dataPath(imageGroup + "/"));
    int fileCount = f.exists() ? f.list().length : 0;
      
    
    PImage newImage = createImage(2, 2, RGB);
    newImage.loadPixels();
    newImage.pixels[0] = parseInt(matcher.group(2));
    newImage.pixels[1] = parseInt(matcher.group(3));
    newImage.pixels[2] = parseInt(matcher.group(4));
    newImage.pixels[3] = parseInt(matcher.group(5));
    newImage.updatePixels();
    newImage.save(dataPath(imageGroup + "/Test" + fileCount + ".jpeg"));
    print("Created file " + imageGroup + "/Test" + fileCount + ".jpeg\n");
  }
}
