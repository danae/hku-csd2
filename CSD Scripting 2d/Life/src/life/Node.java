package life;

import life.gui.hexagon.Hex;
import life.gui.util.Drawable;
import life.gui.util.Point;
import processing.core.PGraphics;

public class Node implements Drawable
{
  // The parent grid of the node
  protected final Life grid;
  
  // The position of the node
  protected Hex position;
  
  // Constructor
  public Node(Life grid, Hex position)
  {
    this.grid = grid;
    this.position = position;
  }
  
  // Get and set the position
  public Hex getPosition()
  {
    return this.position;
  }
  public void setPosition(Hex position)
  {
    this.position = position;
  }
  
  // Draw the node
  @Override public void draw(PGraphics g)
  {
    Point center = this.grid.layout.hexToPixel(this.getPosition());
  } 
  
  // Convert to string
  @Override public String toString()
  {
    return String.format("%s at %s", this.getClass().getSimpleName(), this.position);
  }
}
