interface ButtonClick {
  void click(); 
}

class TextFrame {
  protected int x;
  protected int y;
  protected int w;
  protected int h;
  protected int backgroundColor;
  protected int borderColor;
  
  protected String text;
  protected int textColor;
  protected int textSpacing;
  
  public TextFrame(int x, int y, int w, int h) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    textSpacing = 3;
  }
  
  public void setBackground(int col) {
    this.backgroundColor = col;
  }
  
  public void setBorder(int col) {
    this.borderColor = col;
  }
  
  public void setText(String text) {
    this.text = text;
  }
  
  public void setTextColor(int col) {
     this.textColor = col;
  }
  
  public void draw() {
    fill(backgroundColor);
    stroke(borderColor);
    rect(x, y, w, h);
    if (text != null) {
      textAlign(CENTER, CENTER);
      fill(textColor);
      text(text, x + textSpacing, y + textSpacing, w - textSpacing*2, h - textSpacing*2);
    }
  }
}

class TextFrameBuilder {
  private TextFrame frame;
  
  public TextFrameBuilder(int x, int y, int w, int h) {
     frame = new TextFrame(x, y, w, h); 
  }
  
  public TextFrameBuilder setBackground(int col) {
    frame.setBackground(col);
    return this;
  }
  
  public TextFrameBuilder setBorder(int col) {
    frame.setBorder(col);
    return this;
  }
  
  public TextFrameBuilder setText(String text) {
    frame.setText(text);
    return this;
  }
  
  public TextFrameBuilder setTextColor(int col) {
    frame.setTextColor(col);
    return this;
  }
  
  public TextFrame build() {
     return frame; 
  }
}



class Button {
  private TextFrame basicApperance;
  private TextFrame hoverApperance;
  private Runnable clickAction;
  
  public Button(TextFrame defaultApperance) {
    this.basicApperance = defaultApperance;
  }
  
  public void setHover(TextFrame appearance) {
     hoverApperance = appearance;
  }
  
  public void setClickAction(Runnable clickAction) {
    this.clickAction = clickAction;
  }
  
  public boolean isMouseInside() {
    return  (mouseX >= basicApperance.x && mouseX <= basicApperance.x+basicApperance.w 
          && mouseY >= basicApperance.y && mouseY <= basicApperance.y+basicApperance.h);
  }
  
  public void draw() {
    if (isMouseInside() && hoverApperance != null) {
      hoverApperance.draw();
    } else {
      basicApperance.draw();
    }
  }
  
  public void mousePressed() {
    if (isMouseInside() && clickAction != null) {
       clickAction.run(); 
    }
  }
}