package life;

import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;
import life.gui.GComponent;
import life.gui.GContext;
import life.gui.events.mouse.MouseMoveEvent;
import life.gui.hexagon.Hex;
import life.gui.hexagon.Layout;
import life.gui.hexagon.Orientation;
import life.gui.util.Point;
import life.gui.util.Rect;
import processing.core.PGraphics;

public final class Life extends GComponent
{
  // Lists for storing the nodes and edges between nodes
  private final List<Node> nodes = new LinkedList<>();
  private final List<Edge> edges = new LinkedList<>();
  
  // Layout to use while drawing the hexes
  public final Layout layout;
  
  // Hex at mouse
  private Hex mouseHex;
  
  // Constructor
  public Life(GContext context, Rect bounds)
  {
    super(context,bounds);
    
    // Register event listeners
    this.registerListener(this,MouseMoveEvent.class,this::onMouseMove);
    
    // Create the layout
    this.layout = new Layout(Orientation.POINTY,new Point(25,25),bounds.center());
  }
  
  // Return a list of all nodes
  public List<Node> getNodes()
  {
    return this.nodes;
  }
  
  // Return a node at a particular position
  public Node getNodeAt(Hex position)
  {
    return this.nodes.stream()
      .filter(node -> node.getPosition().equals(position))
      .findFirst()
      .orElse(null);
  }
  
  // Add a node
  public boolean addNode(Node node)
  {
    return this.nodes.add(node);
  }
  
  // Return a list of all edges
  public List<Edge> getEdges()
  {
    return this.edges;
  }
  
  // Return a list of edges that connect to a particular node
  public List<Edge> getEdgesFrom(Node node)
  {
    return this.edges.stream()
      .filter(edge -> edge.getStart().equals(node) || edge.getEnd().equals(node))
      .collect(Collectors.toList());
  }

  // Draw the grid
  @Override public void draw(PGraphics g)
  {
    // Draw the background
    g.background(250);
    
    // Draw a ring around the mouse hex
    if (this.mouseHex != null)
    {
      // Create a ring for all radiuses 0-3
      for (int i = 0; i <= 3; i ++)
      {
        g.noFill();
        g.stroke(0,24 - 6 * i);
        
        // Calculate the ring and draw the hexes in it
        List<Hex> hexes = this.mouseHex.ring(i);
        for (Hex hex : hexes)
          hex.layout(this.layout).draw(g);
      }
    }
    
    // Iterate over the edges and draw them
    for (Edge edge : this.edges)
    {
      // Get the screen positions of the start and end node
      Point startPixel = this.layout.hexToPixel(edge.getStart().getPosition());
      Point endPixel = this.layout.hexToPixel(edge.getEnd().getPosition());
      
      // Draw a line from the start to the end
      g.strokeWeight(10);
      g.stroke(128);
      g.line((float)startPixel.x,(float)startPixel.y,(float)endPixel.x,(float)endPixel.y);
    }
    
    // Iterate over the nodes and draw them
    for (Node node : this.nodes)
    {
      // Draw the node
      node.draw(g);
    }
  }

  // Mouse move event
  public void onMouseMove(MouseMoveEvent e)
  {
    this.mouseHex = this.layout.pixelToHex(e.getPosition());
  }
}
