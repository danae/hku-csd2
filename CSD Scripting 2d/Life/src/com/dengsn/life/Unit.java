package com.dengsn.life;

import com.dengsn.life.graph.Node;
import com.dengsn.life.grid.Hex;
import processing.core.PGraphics;

public class Unit extends Node
{
  // Constructor
  public Unit(Hex position)
  {
    super(position);
  }
  
  // Draw the unit
  @Override public void draw(PGraphics g)
  {
    g.noStroke();
    g.fill(0,128,255);
    g.rectMode(PGraphics.CENTER);
    g.rect(0,0,20,20);
  } 
}
