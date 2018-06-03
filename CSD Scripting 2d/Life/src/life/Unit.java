package life;

import life.Life;
import life.Node;
import life.gui.hexagon.Hex;
import processing.core.PGraphics;

public class Unit extends Node
{
  // Constructor
  public Unit(Life grid, Hex position)
  {
    super(grid,position);
  }
  
  // Draw the unit
  @Override public void draw(PGraphics g)
  {
    g.noStroke();
    g.fill(106,212,0);
    
    this.position.layout(this.grid.layout).draw(g);
  } 
}
