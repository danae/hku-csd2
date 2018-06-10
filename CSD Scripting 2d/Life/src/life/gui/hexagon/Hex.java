package life.gui.hexagon;

import java.util.LinkedList;
import java.util.List;

public class Hex
{
  // Code mostly adapted from https://www.redblobgames.com/grids/hexagons/
  
  // Array to hold directions
  public static Hex[] DIRECTIONS = {
    new Hex(1,-1,0), new Hex(1,0,-1), new Hex(0,1,-1),
    new Hex(-1,1,0), new Hex(-1,0,1), new Hex(0,-1,1) 
  };
  
  // Array to hold diagonal directions
  public static Hex[] DIAGONAL_DIRECTIONS = {
    new Hex(2,-1,-1), new Hex(1,1,-2), new Hex(-1,2,-1),
    new Hex(-2,1,1), new Hex(-1,-1,2), new Hex(1,-2,1) 
  };
  
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
  public Hex neighbor(int direction)
  {
    return this.add(DIRECTIONS[direction % 6]);
  }
  
  // Return the diagnoal neighbor in a particular direction
  public Hex diagonalNeighbor(int direction)
  {
    return this.add(DIAGONAL_DIRECTIONS[direction % 6]);
  }
  
  // Return a ring around the hex
  public List<Hex> ring(int radius)
  {
    // Create a new list to store the hexes
    List<Hex> hexes = new LinkedList<>();
    
    // If the radius is 0, add ourself
    if (radius == 0)
      hexes.add(this);
    
    // Otherwise calculate
    else
    {
      Hex hex = this.add(DIRECTIONS[4].scale(radius));
      for (int i = 0; i < 6; i ++)
      {
        for (int j = 0; j < radius; j ++)
        {
          hexes.add(hex);
          hex = hex.neighbor(i);
        }
      }
    }
    
    // Return the hexes
    return hexes;
  }
  
  // Return a hex referring to the origin (0,0)
  public static Hex origin()
  {
    return new Hex(0,0,0);
  }
}
