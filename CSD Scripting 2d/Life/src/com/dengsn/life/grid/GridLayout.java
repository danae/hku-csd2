package com.dengsn.life.grid;

// GridLayout class
// Code mostly adapted from https://www.redblobgames.com/grids/hexagons/
public class GridLayout
{
  // Variables
  public final GridOrientation orientation;
  public final Point size;
  public final Point origin;
  
  // Constructor
  public GridLayout(GridOrientation orientation, Point size, Point origin)
  {
    this.orientation = orientation;
    this.size = size;
    this.origin = origin;
  }
  
  // Convert a hex coordinate to a screen coordinate
  public Point hexToPixel(Hex hex)
  {
    GridOrientation or = this.orientation;
    
    // Apply the matrix multiplication from the orientation
    double x = (or.f0 * hex.q + or.f1 * hex.r);
    double y = (or.f2 * hex.q + or.f3 * hex.r);
    
    // Return the new point with correct size and origin
    return new Point(x * this.size.x + this.origin.x,y * this.size.y + this.origin.y);
  }
  
  // Convert a screen coordinate to a hex coordinate
  public Hex pixelToHex(Point pixel)
  {
    GridOrientation or = this.orientation;
    
    // Get the point with the size and origin undone
    Point unit = new Point(
      (pixel.x - this.origin.x) / this.size.x,
      (pixel.y - this.origin.y) / this.size.y);
    
    // Apply the reverse matrix multiplication from the orientation
    double q = or.b0 * unit.x + or.b1 * unit.y;
    double r = or.b2 * unit.x + or.b3 * unit.y;
    double s = -q - r;
    
    // Convert these values to the nearest hex
    int qi = (int)(Math.round(q));
    int ri = (int)(Math.round(r));
    int si = (int)(Math.round(s));
    double q_diff = Math.abs(qi - q);
    double r_diff = Math.abs(ri - r);
    double s_diff = Math.abs(si - s);
    
    if (q_diff > r_diff && q_diff > s_diff)
      qi = -ri - si;
    else if (r_diff > s_diff)
      ri = -qi - si;
    else
      si = -qi - ri;
    return new Hex(qi,ri,si);
  }
  
  // Return the corner offset point of a hex
  public Point cornerOffset(int corner)
  {
    double angle = 2.0 * Math.PI * (this.orientation.startAngle + corner) / 6;
    return new Point(this.size.x * Math.cos(angle), this.size.y * Math.sin(angle));
  }
  
  // Return an array of points containing the corners of a hex
  public Point[] corners(Hex hex)
  {
    // Create a new array to store the corner points
    Point[] corners = new Point[6];
    
    // Get the center of the hex
    Point center = this.hexToPixel(hex);
    
    // Fill the corner points array
    for (int i = 0; i < 6; i ++)
    {
      Point cornerOffset = this.cornerOffset(i);
      corners[i] = new Point(center.x + cornerOffset.x, center.y + cornerOffset.y);
    }
    
    // Return the corner points array
    return corners;
  }
}
