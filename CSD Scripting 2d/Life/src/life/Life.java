package life;

import life.gui.GContext;
import processing.core.PApplet;

public class Life extends GContext
{  
  // Settings method
  @Override public void settings()
  {
    size(1024,768);
  }
  
  // Setup method
  @Override public void setup()
  {
  }
  
  // Main method
  public static void main(String[] args)
  {
    PApplet.main(Life.class);
  }
}
