package life.gui.hexagon;

import life.gui.util.Drawable;
import life.gui.util.Point;
import processing.core.PGraphics;

public class LayoutHex implements Drawable
{
  // The hex position used to draw
  private final Hex hex;
  
  // The layout used to draw
  private final Layout layout;
  
  // Constructor
  LayoutHex(Hex hex, Layout layout)
  {
    this.hex = hex;
    this.layout = layout;
  }
  
  // Return the center of the hex in screen coordinates
  public Point center()
  {
    return this.layout.hexToPixel(this.hex);
  }
  
  // Return an array of points containing the corners of a hex in screen coordinates
  public Point[] corners(Hex hex, double scale)
  {
    // Create a new array to store the corner points
    Point[] corners = new Point[6];
    
    // Get the center of the hex
    Point center = this.center();
    
    // Fill the corner points array
    for (int i = 0; i < 6; i ++)
    {
      Point offset = this.layout.cornerOffset(i);
      corners[i] = new Point(center.x + offset.x * scale, center.y + offset.y * scale);
    }
    
    // Return the corner points array
    return corners;
  }
  public Point[] corners(Hex hex)
  {
    return this.corners(hex,1.0);
  }

  // Draw this hex
  public void draw(PGraphics g, double scale)
  {
    g.beginShape();
    for (Point corner : this.corners(this.hex,scale))
      g.vertex((float)corner.x,(float)corner.y);
    g.endShape(PGraphics.CLOSE);
  }
  @Override public void draw(PGraphics g)
  {
    this.draw(g,1.0);
  } 
}
