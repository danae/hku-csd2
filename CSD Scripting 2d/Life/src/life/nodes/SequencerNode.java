package life.nodes;

import life.Grid;
import life.gui.events.component.ComponentEnterEvent;
import life.gui.events.mouse.MousePressEvent;
import life.gui.hexagon.Hex;
import life.gui.hexagon.LayoutHex;
import life.gui.util.Point;
import processing.core.PGraphics;

public class SequencerNode extends Node
{
  // Variable to store the sequencer steps
  private boolean[] steps = new boolean[6];
  
  // Constructor
  public SequencerNode(Grid grid, Hex position)
  {
    super(grid,position);
    
    // Register listeners
    this.registerListener(this,ComponentEnterEvent.class,this::onEnter);
    this.registerListener(this,MousePressEvent.class,this::onMousePressed);
  }
  
  // Draw the unit
  @Override public void draw(PGraphics g)
  {
    g.noStroke();
    g.fill(255,128,0);
    
    // Draw the hex
    this.position.layout(this.grid.layout).draw(g);
    
    // Draw the steps
    LayoutHex layoutHex = this.position.layout(this.grid.layout);
    Point center = layoutHex.center();
    Point[] corners = layoutHex.corners();
    
    g.fill(255,64);
    for (int i = 0; i < 6; i ++)
    {
      if (this.steps[i])
      {
        g.beginShape();
          g.vertex((float)center.x,(float)center.y);
          g.vertex((float)corners[i].x,(float)corners[i].y);
          g.vertex((float)corners[(i+1) % 6].x,(float)corners[(i+ 1) % 6].y);
        g.endShape(PGraphics.CLOSE);
      }
    }
  } 
  
  // Update this node
  @Override public void update(long elapsedTime)
  {
    
  }
  
  // Change the X value
  @Override public void changeX(double x)
  {
    // Nothing to be done
  }
  
  // Change the Y value
  @Override public void changeY(double y)
  {
    // Nothing to be done
  }

  // Handle neighboring nodes
  @Override public void handleNeighbor(Node neighbor)
  {
  }
  
  // COmponent enter event
  public void onEnter(ComponentEnterEvent e)
  {
    System.out.println("Entered node at " + this.position.toString());
  }
  
  // Mouse press event
  public void onMousePressed(MousePressEvent e)
  {
    // Get the direction
    int direction = this.grid.layout.pixelToDirection(e.getPosition(),this.position);
    System.out.println("At " + this.position.toString() + ": direction = " + direction);
    
    // Toggle the step at this direction
    this.steps[direction] = !this.steps[direction];
  }
}
