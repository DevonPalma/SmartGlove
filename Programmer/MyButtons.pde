

Button peaceSignButton;

void createPeaceSignButton() {
  peaceSignButton = new Button(
        new TextFrameBuilder(20, 20, 100, 50)
            .setBackground(color(255))
            .setBorder(color(0))
            .setText("Peace Sign")
            .setTextColor(color(0))
            .build()
  );
 
  peaceSignButton.setClickAction(new Runnable() {
    public void run() {
     programPeaceSign();
    }
  });
  
  peaceSignButton.setHover( 
      new TextFrameBuilder(15, 15, 110, 60)
          .setBackground(color(200))
          .setBorder(color(50))
          .setText("Program Peace Sign?")
          .setTextColor(color(0))
          .build()
  );
}
