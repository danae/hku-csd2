package life.gui.hexagon;

import life.gui.util.Drawable;
import life.gui.util.Rect;
import processing.core.PGraphics;

public class HexGrid implements Drawable
{
  // The layout to use
  private final Layout layout;
  
  // The boundaries of the grid
  private final Rect bounds;
  
  // Constructor
  public HexGrid(Layout layout, Rect bounds)
  {
    this.layout = layout;
    this.bounds = bounds;
  }
  
  // Draw the grid
  @Override public void draw(PGraphics g)
  {
    // Get the corners of the screen
    Hex topLeft = this.layout.pixelToHex(this.bounds.topLeft());
    Hex topRight = this.layout.pixelToHex(this.bounds.topRight());
    Hex bottomLeft = this.layout.pixelToHex(this.bounds.bottomLeft());
    Hex bottomRight = this.layout.pixelToHex(this.bounds.bottomRight());
    
    // Draw the hexes
    g.stroke(255,8);
    g.noFill();
    
    for (int q = bottomLeft.q; q < topRight.q; q ++)
    {
      for (int r = topLeft.r; r < bottomRight.r; r ++)
      {
        // Get the hex and its corners
        Hex hex = new Hex(q,r);
        hex.layout(this.layout).draw(g);
      }
    }
  }
}
