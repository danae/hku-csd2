package life.gui.hexagon;

public class Hex
{
  // Code mostly adapted from https://www.redblobgames.com/grids/hexagons/
  
  // Enum to hold directions
  public enum Direction
  {
    NORTHEAST (new Hex(1,0,-1)),
    EAST (new Hex(1,-1,0)),
    SOUTHEAST (new Hex(0,1,-1)),
    SOUTHWEST (new Hex(-1,0,1)),
    WEST (new Hex(-1,1,0)),
    NORTHWEST (new Hex(0,1,-1));
    
    // Variable to store the relative hex
    private final Hex hex;
    
    // Constructor
    private Direction(Hex hex)
    {
      this.hex = hex;
    }
  }
  
  // Coordinates of the hex
  public final int q, r, s;
  
  // Constructor
  public Hex(int q, int r, int s)
  {
    if (q + r + s != 0)
      throw new IllegalArgumentException(String.format("Invalid hex coordinate: (%d, %d, %d)",q,r,s));
    
    this.q = q;
    this.r = r;
    this.s = s;
  }
  public Hex(int q, int r)
  {
    this(q, r, -q - r);
  }
  
  // Return a hex for drawing using a layout
  public LayoutHex layout(Layout layout)
  {
    return new LayoutHex(this,layout);
  }
  
  // Return if this hex is equal to another object
  @Override public boolean equals(Object o)
  {
    if (o == null)
      return false;
    else if (this.getClass() != o.getClass())
      return false;
    
    Hex other = (Hex)o;
    return this.q == other.q && this.r == other.r && this.s == other.s;
  }
  
  // Return a hash for this hex
  @Override public int hashCode()
  {
    int hash = 7;
    hash = 73 * hash + this.q;
    hash = 73 * hash + this.r;
    hash = 73 * hash + this.s;
    return hash;
  }
  
  // Convert this hex to a string
  @Override public String toString()
  {
    return String.format("Hex(%d, %d)", this.q, this.r);
  }
    
  // Add two hexes: add their respective coordinates
  public Hex add(Hex other)
  {
    return new Hex(this.q + other.q,this.r + other.r,this.s + other.s);
  }
  
  // Subtract two hexes
  public Hex subtract(Hex other)
  {
    return new Hex(this.q - other.q,this.r - other.r,this.s - other.s);
  }
  
  // Scale a hex: multiply its coordinates with a scalar
  public Hex scale(int scalar)
  {
    return new Hex(this.q * scalar,this.r * scalar,this.s * scalar);
  }
  
  // Return the length of this hex, i.e. the distance to the origin
  public int length()
  {
    return (Math.abs(this.q) + Math.abs(this.r) + Math.abs(this.s)) / 2;
  }
  
  // Return the distance to another hex
  public int distanceTo(Hex other)
  {
    return this.subtract(other).length();
  }
  
  // Return the neighboring hex in a particular direction
  public Hex neighbor(Direction d)
  {
    return this.add(d.hex);
  }
  
  // Return a hex referring to the origin (0,0)
  public static Hex origin()
  {
    return new Hex(0,0,0);
  }
}
