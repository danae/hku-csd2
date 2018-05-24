package com.dengsn.life.grid;

// Point class
public class Point
{
  // Coordinates of the point
  public final double x, y;
  
  // Constructor
  public Point(double x, double y)
  {
    this.x = x;
    this.y = y;
  }

  // Return if this point is equal to another object
  @Override public boolean equals(Object o)
  {
    if (o == null)
      return false;
    else if (this.getClass() != o.getClass())
      return false;
    
    Point other = (Point)o;
    return Double.doubleToLongBits(this.x) == Double.doubleToLongBits(other.x) && Double.doubleToLongBits(this.y) == Double.doubleToLongBits(other.y);
  }
  
  // Generate a hash for this point
  @Override public int hashCode()
  {
    int hash = 7;
    hash = 17 * hash + (int)(Double.doubleToLongBits(this.x) ^ (Double.doubleToLongBits(this.x) >>> 32));
    hash = 17 * hash + (int)(Double.doubleToLongBits(this.y) ^ (Double.doubleToLongBits(this.y) >>> 32));
    return hash;
  }
}
