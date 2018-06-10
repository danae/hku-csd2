package life.gui.util;

public class Rect
{
  // Variables
  public final double left, top, right, bottom;
  
  // Constructor
  public Rect(double left, double top, double right, double bottom)
  {
    this.left = left;
    this.top = top;
    this.right = right;
    this.bottom = bottom;
  }
  public Rect(Rect rect)
  {
    this(rect.left,rect.top,rect.right,rect.bottom);
  }
  
  // Return the width
  public double width()
  {
    return this.right - this.left;  
  }
  
  // Return the height
  public double height()
  {
    return this.bottom - this.top;  
  }
  
  // Return the center of this rect
  public Point center()
  {
    return new Point((this.left + this.right) / 2.0,(this.top + this.bottom) / 2.0);  
  }
  
  // Return sif a point is contained in this rect
  public boolean contains(Point point)
  {
    return point.x >= this.left && point.x <= this.right && point.y >= this.top && point.y <= this.bottom;  
  }
  
  // Return the corners of this rect as points
  public Point topLeft()
  {
    return new Point(this.left,this.top);
  }
  public Point topRight()
  {
    return new Point(this.right,this.top);
  }
  public Point bottomLeft()
  {
    return new Point(this.left,this.bottom);
  }
  public Point bottomRight()
  {
    return new Point(this.right,this.bottom);
  }
  
  // Return if this rect is equal to another object
  @Override public boolean equals(Object o)
  {
    if (o == null)
      return false;
    else if (this.getClass() != o.getClass())
      return false;
    
    Rect other = (Rect)o;
    return Double.doubleToLongBits(this.left) == Double.doubleToLongBits(other.left)
      && Double.doubleToLongBits(this.top) == Double.doubleToLongBits(other.top)
      && Double.doubleToLongBits(this.right) == Double.doubleToLongBits(other.right)
      && Double.doubleToLongBits(this.bottom) == Double.doubleToLongBits(other.bottom);
  }
  
  // Return the hash for this rect
  @Override public int hashCode()
  {
    int hash = 7;
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.left) ^ (Double.doubleToLongBits(this.left) >>> 32));
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.top) ^ (Double.doubleToLongBits(this.top) >>> 32));
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.right) ^ (Double.doubleToLongBits(this.right) >>> 32));
    hash = 89 * hash + (int) (Double.doubleToLongBits(this.bottom) ^ (Double.doubleToLongBits(this.bottom) >>> 32));
    return hash;
  }
  
  // Convert to string
  @Override public String toString()
  {
    return String.format("Rect(%f, %f, %f, %f)",this.left,this.top,this.right,this.bottom);
  }
}
