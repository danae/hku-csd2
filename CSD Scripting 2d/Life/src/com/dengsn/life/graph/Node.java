package com.dengsn.life.graph;

import com.dengsn.life.grid.Hex;
import com.dengsn.life.util.Drawable;
import processing.core.PGraphics;

// Node class
public class Node implements Drawable
{
  // The position of the node
  private Hex position;
  
  // Constructor
  public Node(Hex position)
  {
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
    g.noStroke();
    g.fill(128);
    g.ellipseMode(PGraphics.CENTER);
    g.ellipse(0,0,15,15);
  } 
}
