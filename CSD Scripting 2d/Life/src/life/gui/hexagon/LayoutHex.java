package life.gui.hexagon;

import life.gui.util.Drawable;
import life.gui.util.Point;
import life.gui.util.Rect;
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
  public Point[] corners(double scale)
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
  public Point[] corners()
  {
    return this.corners(1.0);
  }
  
  // Return the boundaries of a hex
  public Rect bounds()
  {
    Point[] corners = this.corners();
    double left = corners[0].x, top = corners[0].y, right = corners[0].x, bottom = corners[0].y;
    
    for (int i = 1; i < 6; i ++)
    {
      if (corners[i].x < left)
        left = corners[i].x;
      if (corners[i].y < top)
        top = corners[i].y;
      if (corners[i].x > right)
        right = corners[i].x;
      if (corners[i].y > bottom)
        bottom = corners[i].y;
    }
    
    return new Rect(left,top,right,bottom);
  }

  // Draw this hex
  public void draw(PGraphics g, double scale)
  {
    g.beginShape();
    for (Point corner : this.corners(scale))
      g.vertex((float)corner.x,(float)corner.y);
    g.endShape(PGraphics.CLOSE);
  }
  @Override public void draw(PGraphics g)
  {
    this.draw(g,1.0);
  } 
}
