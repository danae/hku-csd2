package life;

import java.util.LinkedList;
import java.util.List;
import life.gui.GComponent;
import life.gui.GContext;
import life.gui.events.keyboard.KeyPressEvent;
import life.gui.events.mouse.MouseDragEvent;
import life.gui.events.mouse.MouseMoveEvent;
import life.gui.events.mouse.MousePressEvent;
import life.gui.events.mouse.MouseReleaseEvent;
import life.gui.hexagon.Hex;
import life.gui.hexagon.Layout;
import life.gui.hexagon.Orientation;
import life.gui.util.Point;
import life.gui.util.Rect;
import life.gui.util.Updateable;
import life.nodes.GeneratorNode;
import life.nodes.Node;
import life.nodes.SequencerNode;
import net.beadsproject.beads.core.AudioContext;
import processing.core.PGraphics;

public final class Grid extends GComponent implements Updateable
{
  // Lists for storing the nodes and edges between nodes
  private final List<Node> nodes = new LinkedList<>();
  
  // Layout to use while drawing the hexes
  public final Layout layout;
  
  // The audio context
  public final AudioContext audioContext;
  
  // Hexes referenced by the UI
  private Hex hoveredHex;
  private Hex selectedHex;
  
  // The selected node
  private Node selectedNode;
  
  // The new node mode
  private int mode = 0;
  
  // Constructor
  public Grid(GContext context, Rect bounds)
  {
    super(context,bounds);
    
    // Register event listeners
    this.registerListener(this,MouseMoveEvent.class,this::onMouseMove);
    this.registerListener(this,MousePressEvent.class,this::onMousePress);
    this.registerListener(this,KeyPressEvent.class,this::onKeyPress);
    
    // Create the layout
    this.layout = new Layout(Orientation.POINTY,new Point(25,25),bounds.center());
    
    // Create the audio context
    this.audioContext = new AudioContext();
    this.audioContext.start();
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
  public void addNode(Node node)
  {
    this.nodes.add(node);
  }

  // Draw the grid
  @Override public void draw(PGraphics g)
  {
    // Draw the background
    g.background(250);
    
    // Draw a ring around the mouse hex
    if (this.hoveredHex != null)
    {
      // Create a ring for all radiuses 0-3
      for (int i = 0; i <= 3; i ++)
      {
        g.noFill();
        g.stroke(0,24 - 6 * i);
        
        // Calculate the ring and draw the hexes in it
        List<Hex> hexes = this.hoveredHex.ring(i);
        for (Hex hex : hexes)
          hex.layout(this.layout).draw(g);
      }
    }
    
    // Iterate over the nodes and draw them
    for (Node node : this.nodes)
      node.draw(g);
  }
  
  // Update the grid
  @Override public void update(long elapsedTime)
  {
    // Iterate over the nodes and update them
    for (Node node : this.nodes)
      node.update(elapsedTime);
  }

  // Mouse move event
  public void onMouseMove(MouseMoveEvent e)
  {
    // Set the hovered hex
    this.hoveredHex = this.layout.pixelToHex(e.getPosition());
  }
  
  // Mouse press event
  public void onMousePress(MousePressEvent e)
  {
    // Set the selected hex
    this.selectedHex = this.layout.pixelToHex(e.getPosition());
    
    // Set the selected node if there is any
    this.selectedNode = this.getNodeAt(this.selectedHex);
    
    // Create a new node at the mouse position
    if (this.selectedNode == null)
    {
      if (mode == 0)
        this.addNode(new GeneratorNode(this,this.hoveredHex));
      else if (mode == 1)
        this.addNode(new SequencerNode(this,this.hoveredHex));
    }
  }
  
  // Key press event
  public void onKeyPress(KeyPressEvent e)
  {
    if (e.getKey() == '1')
      this.mode = 0;
    else if (e.getKey() == '2')
      this.mode = 1;
  }
}
