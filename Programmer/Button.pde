import java.util.List;
import java.util.ArrayList;

interface BoolChecker {
  public boolean check();
}

class ButtonDescription {
  Integer x, y, w, h;
  Integer extraSize, textSpacing;
  Integer backgroundColor, borderColor, textColor;
  String text;

  public ButtonDescription() {
    this(false);
  }

  public ButtonDescription(boolean defaultValues) {
    if (defaultValues) {
      x = 0;
      y = 0;
      w = 0;
      h = 0;
      extraSize = 0;
      textSpacing = 0;
      backgroundColor = 0;
      borderColor = 0;
      textColor = 0;
      text = null;
    } else {
      x = null;
      y = null;
      w = null;
      h = null;
      extraSize = null;
      textSpacing = null;
      backgroundColor = null;
      borderColor = null;
      textColor = null;
      text = null;
    }
  }

  public void override(ButtonDescription overrider) {
    if (overrider.x != null)
      x = overrider.x;
    if (overrider.y != null)
      y = overrider.y;
    if (overrider.w != null)
      w = overrider.w;
    if (overrider.h != null)
      h = overrider.h;
      
    if (overrider.extraSize != null)
      extraSize = overrider.extraSize;
      
    if (overrider.textSpacing != null)
      textSpacing = overrider.textSpacing;
      
    if (overrider.backgroundColor != null)
      backgroundColor = overrider.backgroundColor;
      
    if (overrider.borderColor != null)
      borderColor = overrider.borderColor;
      
    if (overrider.textColor != null)
      textColor = overrider.textColor;
      
    if (overrider.text != null)
      text = overrider.text;
  }
}

class ButtonDescriptionBuilder {
  private ButtonDescription desc;
  
  public ButtonDescriptionBuilder() {
    desc = new ButtonDescription();
  }
  
  public ButtonDescriptionBuilder x(int x) {
    desc.x = x;
    return this;
  }
  
  public ButtonDescriptionBuilder y(int y) {
    desc.y = y;
    return this;
  }
  
  public ButtonDescriptionBuilder pos(int x, int y) {
    desc.x = x;
    desc.y = y;
    return this;
  }
  
  public ButtonDescriptionBuilder width(int w) {
    desc.w = w;
    return this;
  }
  
  public ButtonDescriptionBuilder height(int h) {
    desc.h = h;
    return this;
  }
  
  public ButtonDescriptionBuilder size(int w, int h) {
    desc.w = w;
    desc.h = h;
    return this;
  }
  
  public ButtonDescriptionBuilder dimension(int x, int y, int w, int h) {
    desc.x = x;
    desc.y = y;
    desc.w = w;
    desc.h = h;
    return this;
  }
  
  public ButtonDescriptionBuilder extraSize(int v) {
    desc.extraSize = v;
    return this;
  }
  
  public ButtonDescriptionBuilder text(String text) {
    desc.text = text;
    return this;
  }
  
  public ButtonDescriptionBuilder textSpacing(int v) {
    desc.textSpacing = v;
    return this;
  }
  
  public ButtonDescriptionBuilder backgroundColor(int c) {
    desc.backgroundColor = c;
    return this;
  }
  
  public ButtonDescriptionBuilder borderColor(int c) {
    desc.borderColor = c;
    return this;
  }
  
  public ButtonDescriptionBuilder textColor(int c) {
    desc.textColor = c;
    return this;
  }
  
  public ButtonDescription build() {
     return desc; 
  }
}



class Button {
  private List<BoolChecker> checkers;
  private List<ButtonDescription> descriptions;
  private ButtonDescription currentFullDesc;
  private Runnable onClickAction;

  public Button() {
    checkers = new ArrayList();
    descriptions = new ArrayList();
  }

  public Button addDescription(BoolChecker req, ButtonDescription description) {
    checkers.add(req);
    descriptions.add(description);
    return this;
  }
  
  public Button bindOnClick(Runnable action) {
    this.onClickAction = action;
    return this;
  }


  public void update() {
    currentFullDesc = new ButtonDescription(true);

    for (int i = 0; i < checkers.size(); i++) {
      if (checkers.get(i).check()) {
        currentFullDesc.override(descriptions.get(i));
      }
    }
  }

  public void draw() {
    int x = currentFullDesc.x - currentFullDesc.extraSize;
    int y = currentFullDesc.y - currentFullDesc.extraSize;
    int w = currentFullDesc.w + currentFullDesc.extraSize*2;
    int h = currentFullDesc.h + currentFullDesc.extraSize*2;

    fill(currentFullDesc.backgroundColor);
    stroke(currentFullDesc.borderColor);
    rect(x, y, w, h);
    if (currentFullDesc.text != null) {
      int ts = currentFullDesc.textSpacing;
      textAlign(CENTER, CENTER);
      fill(currentFullDesc.textColor);
      text(currentFullDesc.text, x+ts, y+ts, w-ts*2, h-ts*2);
    }
  }

  public boolean isMouseInside() {
    return (currentFullDesc != null) 
          && (mouseX >= currentFullDesc.x && mouseX <= currentFullDesc.x+currentFullDesc.w)
          && (mouseY >= currentFullDesc.y && mouseY <= currentFullDesc.y+currentFullDesc.h);
  }

  public void mousePressed() {
    if (isMouseInside()) {
      onClickAction.run();
    }
  }
}
