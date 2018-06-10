package life;

import life.gui.GContext;
import life.gui.util.Rect;
import processing.core.PApplet;
import processing.core.PFont;

public class GridContext extends GContext
{  
  // The grid with nodes and edges
  private Grid grid;
  
  // Settings method
  @Override public void settings()
  {
    size(1024,768);
  }
  
  // Setup method
  @Override public void setup()
  {
    // Create the grid
    this.grid = new Grid(this,new Rect(0,0,width,height));
    this.grid.focus();
    
    // Create the font
    PFont font = this.createFont("Verdana",14);
    g.textFont(font);
  }
  
  // Main method
  public static void main(String[] args)
  {
    PApplet.main(GridContext.class);
  }
}
