package life.nodes;

import java.util.LinkedList;
import java.util.List;
import life.Grid;
import life.gui.GComponent;
import life.gui.events.mouse.MouseDragEvent;
import life.gui.hexagon.Hex;
import life.gui.util.Updateable;

public abstract class Node extends GComponent implements Updateable
{
  // The parent grid of the node
  protected final Grid grid;
  
  // The position of the node
  protected Hex position;
  
  // Constructor
  public Node(Grid grid, Hex position)
  {
    super(grid.getContext(),position.layout(grid.layout).bounds());
    
    this.grid = grid;
    this.position = position;
    
    // Register listeners
    this.registerListener(this,MouseDragEvent.class,this::onMouseDrag);
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
  
  // Get neighboring nodes
  public List<Node> neighbors()
  {
    // Create a list to hold the nodes
    List<Node> nodes = new LinkedList<>();
    
    // Iterate over the directions
    for (int i = 0; i < 6; i ++)
    {
      // Get the neighboring node at this position
      Node neighbor = this.grid.getNodeAt(this.getPosition().neighbor(i));
      if (neighbor != null)
        nodes.add(neighbor);
    }
      
    // Return the nodes
    return nodes;
  }
  
  // Change the values based on a 2-dimensional grid
  public abstract void changeX(double x);
  public abstract void changeY(double y);
  
  // Handle neighbouring nodes
  public abstract void handleNeighbor(Node neighbor);
  
  // Update this node
  @Override public void update(long elapsedTime)
  {
    // Handle neighbor relations
    for (Node neighbor : this.neighbors())
      this.handleNeighbor(neighbor);
  }
  
  // Mouse drag event
  public void onMouseDrag(MouseDragEvent e)
  {
    // Set the value of the node, mirror the Y value
    this.changeX(e.getDelta().x);
    this.changeY(e.getDelta().y * -1);
  }
}
