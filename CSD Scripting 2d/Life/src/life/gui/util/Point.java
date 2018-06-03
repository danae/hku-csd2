package life.gui.util;

public class Point
{
  // Variables
  public final double x, y;
  
  // Constructor
  public Point(double x, double y)
  {
    this.x = x;
    this.y = y;
  }
  public Point(Point source)
  {
    this(source.x,source.y);
  }
  
  // Return if this point is equal to another object
  @Override public boolean equals(Object o)
  {
    if (o == null)
      return false;
    else if (this.getClass() != o.getClass())
      return false;
    
    Point other = (Point)o;
    return Double.doubleToLongBits(this.x) == Double.doubleToLongBits(other.x)
      && Double.doubleToLongBits(this.y) == Double.doubleToLongBits(other.y);
  }
  
  // Return the hash for this point
  @Override public int hashCode()
  {
    int hash = 7;
    hash = 53 * hash + (int) (Double.doubleToLongBits(this.x) ^ (Double.doubleToLongBits(this.x) >>> 32));
    hash = 53 * hash + (int) (Double.doubleToLongBits(this.y) ^ (Double.doubleToLongBits(this.y) >>> 32));
    return hash;
  }
  
  // Convert to string
  @Override public String toString()
  {
    return String.format("Point(%f, %f)",this.x,this.y);
  }
  
  // Return the magnitude of this point (i.e. the distance to the origin)
  public double magnitude()
  {
    return Math.sqrt(Math.pow(this.x,2) + Math.pow(this.y,2));
  }
  
  // Return the angle of this point (relative to the origin)
  public double angle()
  {
    return Math.atan2(this.y,this.x);
  }
  
  // Add two points
  public Point add(Point other)
  {
    return new Point(this.x + other.x,this.y + other.y);
  }
  public Point add(double x, double y)
  {
    return this.add(new Point(x,y));  
  }
  
  // Suptract two points
  public Point subtract(Point other)
  {
    return new Point(this.x - other.x,this.y - other.y);
  }
  public Point subtract(double x, double y)
  {
    return this.subtract(new Point(x,y));
  }
  
  // Multiply a point with a scalar value
  public Point scale(double scalar)
  {
    return new Point(this.x * scalar, this.y * scalar);
  }
  
  // Rotate a point
  public Point rotate(double angle)
  {
    double newAngle = this.angle() + angle;
    return new Point(this.magnitude() + Math.cos(newAngle),this.magnitude() + Math.sin(newAngle));
  }
  
  // Return a point at the origin
  public static Point origin()
  {
    return new Point(0.0,0.0);
  }
  
  // Return the distance between two points
  public static double distance(Point p1, Point p2)
  {
    return p1.subtract(p2).magnitude();
  }
  
  // Return the angle between two points
  public static double angle(Point p1, Point p2)
  {
    return p1.angle() - p2.angle();
  }
  
  // Calculates the dot product of two points
  public double dotProduct(Point p1, Point p2)
  {
    return p1.x * p2.x + p1.y * p2.y;
  }
}