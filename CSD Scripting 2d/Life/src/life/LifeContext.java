package life;

import life.gui.GContext;
import life.gui.hexagon.Hex;
import life.gui.util.Rect;
import processing.core.PApplet;

public class LifeContext extends GContext
{  
  // The grid with nodes and edges
  private Life grid;
  
  // Settings method
  @Override public void settings()
  {
    size(1024,768);
  }
  
  // Setup method
  @Override public void setup()
  {
    // Create the grid
    this.grid = new Life(this,new Rect(0,0,width,height));
    this.addComponent(this.grid);
    
    this.grid.addNode(new Unit(this.grid,Hex.origin()));
  }
  
  // Main method
  public static void main(String[] args)
  {
    PApplet.main(LifeContext.class);
  }
}
