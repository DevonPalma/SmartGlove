

Button peaceSignButton;
Button thumbsUpButton;
Button getBestButton;

// Creates a generic textframe for the static appearance
TextFrame defaultButtonAppearance(int x, int y, String txt) {
  return new TextFrameBuilder(x, y, 100, 50)
            .setBackground(color(255))
            .setBorder(color(0))
            .setText(txt)
            .setTextColor(color(0))
            .build();
}


// Creates a generic textframe for the hover appearance
TextFrame hoverButtonAppearance(int x, int y, String txt) {
  return new TextFrameBuilder(x-5, y-5, 110, 60)
          .setBackground(color(200))
          .setBorder(color(50))
          .setText(txt)
          .setTextColor(color(0))
          .build();
}

// Creates the peace sign program button
void createPeaceSignButton(int x, int y) {
  peaceSignButton = new Button(defaultButtonAppearance(x, y, "Peace Sign"));
 
  peaceSignButton.setClickAction(new Runnable() {
    public void run() {
     programPeaceSign();
    }
  });
  
  peaceSignButton.setHover(hoverButtonAppearance(x, y, "Program peace sign?"));
}

// Creates the thumbs up program button
void createThumbsUpButton(int x, int y) {
   thumbsUpButton = new Button(defaultButtonAppearance(x,y,"Thumbs Up"));
   
   thumbsUpButton.setClickAction(new Runnable() {
     public void run() {
       programThumbsUp();
     }
   });
   
   thumbsUpButton.setHover(hoverButtonAppearance(x,y,"Program Thumbs Up?"));
}

void createGetBestButton(int x, int y) {
  getBestButton = new Button(defaultButtonAppearance(x,y,"Best"));
  
  getBestButton.setClickAction(new Runnable() {
      public void run() {
        requestBest();
      }
  });
}
