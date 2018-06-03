package life.gui.util;

public class Rect
{
  // Variables
  public final double x1, y1, x2, y2;
  
  // Constructor
  public Rect(double x1, double y1, double x2, double y2)
  {
    this.x1 = x1;
    this.y1 = y1;
    this.x2 = x2;
    this.y2 = y2;
  }
  public Rect(Rect rect)
  {
    this(rect.x1,rect.y1,rect.x2,rect.y2);
  }
  
  // Return the width
  public double width()
  {
    return this.x2 - this.x1;  
  }
  
  // Return the height
  public double height()
  {
    return this.y2 - this.y1;  
  }
  
  // Return the center of this rect
  public Point center()
  {
    return new Point((this.x1 + this.x2) / 2.0,(this.y1 + this.y2) / 2.0);  
  }
  
  // Return sif a point is contained in this rect
  public boolean contains(Point point)
  {
    return point.x >= this.x1 && point.x <= this.x2 && point.y >= this.y1 && point.y <= this.y2;  
  }
  
  // Return the corners of this rect as points
  public Point topLeft()
  {
    return new Point(this.x1,this.y1);
  }
  public Point topRight()
  {
    return new Point(this.x2,this.y1);
  }
  public Point bottomLeft()
  {
    return new Point(this.x1,this.y2);
  }
  public Point bottomRight()
  {
    return new Point(this.x2,this.y2);
  }
  
  // Return if this rect is equal to another object
  @Override public boolean equals(Object o)
  {
    if (o == null)
      return false;
    else if (this.getClass() != o.getClass())
      return false;
    
    Rect other = (Rect)o;
    return Double.doubleToLongBits(this.x1) == Double.doubleToLongBits(other.x1)
      && Double.doubleToLongBits(this.y1) == Double.doubleToLongBits(other.y1)
      && Double.doubleToLongBits(this.x2) == Double.doubleToLongBits(other.x2)
      && Double.doubleToLongBits(this.y2) == Double.doubleToLongBits(other.y2);
  }
  
  // Return the hash for this rect
  @Override public int hashCode()
  {
    int hash = 7;
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.x1) ^ (Double.doubleToLongBits(this.x1) >>> 32));
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.y1) ^ (Double.doubleToLongBits(this.y1) >>> 32));
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.x2) ^ (Double.doubleToLongBits(this.x2) >>> 32));
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.y2) ^ (Double.doubleToLongBits(this.y2) >>> 32));
    return hash;
  }
  
  // Convert to string
  @Override public String toString()
  {
    return String.format("Rect(%f, %f, %f, %f)",this.x1,this.y1,this.x2,this.y2);
  }
}
