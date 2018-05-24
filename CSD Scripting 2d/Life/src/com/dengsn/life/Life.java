package com.dengsn.life;

import com.dengsn.life.graph.Graph;
import com.dengsn.life.graph.Node;
import com.dengsn.life.grid.Grid;
import com.dengsn.life.grid.GridOrientation;
import com.dengsn.life.grid.Hex;
import com.dengsn.life.grid.Point;
import processing.core.PApplet;
import processing.core.PGraphics;
import processing.event.MouseEvent;

public class Life extends PApplet
{
  // The grid contains the layout
  private Grid grid;
  private PGraphics gridGraphics;
  
  // The graph contains all units and edges
  private Graph graph;
  
  // Variable to hold the hex that the mouse points to
  private Hex mouseHex = null;
  
  // Settings method
  @Override public void settings()
  {
    size(1024,768);
  }
  
  // Setup method
  @Override public void setup()
  {
    this.grid = new Grid(GridOrientation.POINTY, new Point(25,25), new Point(width / 2, height / 2));
    this.graph = new Graph(grid);
    
    // Create the grid graphics and draw the grid on it
    this.gridGraphics = createGraphics(width,height);
    this.gridGraphics.beginDraw();
      this.gridGraphics.background(255);
      this.grid.draw(this.gridGraphics);
    this.gridGraphics.endDraw();
  }
  
  // Draw method
  @Override public void draw()
  {
    // Draw a black background
    background(0);
    
    // Draw the grid
    image(this.gridGraphics,0,0);
    
    // Draw the graph
    this.graph.draw(this.g);
    
    // Draw the mouse hex
    if (mouseHex != null)
    {
      Point mouseHexPixel = this.grid.hexToPixel(mouseHex);
    
      fill(0,16);
      noStroke();

      Point[] corners = this.grid.corners(mouseHex);
        
      beginShape();
      for (Point corner : corners)
        vertex((float)corner.x, (float)corner.y);
      endShape(CLOSE);
    }
    
    /*// Update the selected cell
    int cellX = mouseX / GRID_SIZE;
    int cellY = mouseY / GRID_SIZE;
    mouse = new Position(cellX, cellY);
    
    // Draw the grid around the mouse
    fill(255,16);
    rect(mouse.x * GRID_SIZE + GRID_PADDING, mouse.y * GRID_SIZE + GRID_PADDING, GRID_SIZE - 2 * GRID_PADDING, GRID_SIZE - 2 * GRID_PADDING);
    
    fill(255,8);
    for (Position c : mouse.square(1))
      rect(c.x * GRID_SIZE + GRID_PADDING, c.y * GRID_SIZE + GRID_PADDING, GRID_SIZE - 2 * GRID_PADDING, GRID_SIZE - 2 * GRID_PADDING);

    fill(255,4);
    for (Position c : mouse.square(2))
      rect(c.x * GRID_SIZE + GRID_PADDING, c.y * GRID_SIZE + GRID_PADDING, GRID_SIZE - 2 * GRID_PADDING, GRID_SIZE - 2 * GRID_PADDING);
    
    // Draw the world on the PGraphics instance of the PApplet
    world.draw(g);
    
    // Update the world
    world.update(elapsedTime);*/
  }
  
  // Mouse move event
  @Override public void mouseMoved(MouseEvent e)
  {
    Point pixel = new Point(e.getX(),e.getY());
    mouseHex = this.grid.pixelToHex(pixel);
  }
  
  // Mouse press event
  @Override public void mousePressed(MouseEvent e)
  {
    // Create a new node at the pointed position if not already present
    if (this.graph.getNodeAt(mouseHex) == null)
      this.graph.addNode(new Node(mouseHex));
  }
  
  // Main method
  public static void main(String[] args)
  {
    PApplet.main(Life.class);
  }
}
