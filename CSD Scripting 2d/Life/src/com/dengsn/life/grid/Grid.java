package com.dengsn.life.grid;

import com.dengsn.life.util.Drawable;
import processing.core.PGraphics;

// Grid class:
// Defines the grid of hexes
public class Grid extends GridLayout implements Drawable
{
  // Constructor
  public Grid(GridOrientation orientation, Point size, Point origin)
  {
    super(orientation,size,origin);
  }

  // Draw the grid
  @Override public void draw(PGraphics g)
  {
    // Get the corners of the screen
    Hex topleft = this.pixelToHex(new Point(0,0));
    Hex topright = this.pixelToHex(new Point(g.width,0));
    Hex bottomleft = this.pixelToHex(new Point(0,g.height));
    Hex bottomright = this.pixelToHex(new Point(g.width,g.height));
    
    // Draw the hexes
    g.stroke(0,12);
    
    for (int q = bottomleft.q; q < topright.q; q ++)
    {
      for (int r = topleft.r; r < bottomright.r; r ++)
      {
        // Get the hex and its corners
        Hex hex = new Hex(q,r);
        Point center = this.hexToPixel(hex);
        Point[] corners = this.corners(hex);
        
        // Draw it
        g.noFill();
        g.beginShape();
        for (Point corner : corners)
          g.vertex((float)corner.x, (float)corner.y);
        g.endShape(PGraphics.CLOSE);
      }
    }
  }
}
