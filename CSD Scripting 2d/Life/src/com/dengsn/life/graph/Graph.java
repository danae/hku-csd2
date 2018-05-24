package com.dengsn.life.graph;

import com.dengsn.life.grid.Grid;
import com.dengsn.life.grid.Hex;
import com.dengsn.life.grid.Point;
import com.dengsn.life.util.Drawable;
import java.util.LinkedList;
import java.util.List;
import java.util.stream.Collectors;
import processing.core.PGraphics;

// Graph class:
// Contains a list of nodes and edges that connect them.
public class Graph implements Drawable
{
  // Grid instance to draw the graph on
  private final Grid grid;
  
  // List for storing the nodes
  private final List<Node> nodes;
  
  // List for storing the edges between nodes
  private final List<Edge> edges;
  
  // Constructor
  public Graph(Grid grid)
  {
    this.grid = grid;
    
    this.nodes = new LinkedList<>();
    this.edges = new LinkedList<>();
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

  // Draw the graph
  @Override public void draw(PGraphics g)
  {
    // Iterate over the edges and draw them
    for (Edge edge : this.edges)
    {
      // Get the screen positions of the start and end node
      Point startPixel = this.grid.hexToPixel(edge.getStart().getPosition());
      Point endPixel = this.grid.hexToPixel(edge.getEnd().getPosition());
      
      // Draw a line from the start to the end
      g.strokeWeight(10);
      g.stroke(128);
      
      g.line((float)startPixel.x, (float)startPixel.y, (float)endPixel.x, (float)endPixel.y);
    }
    
    // Iterate over the nodes and draw them
    for (Node node : this.nodes)
    {
      // Get the screen position of the node
      Point nodePixel = this.grid.hexToPixel(node.getPosition());
      
      // Translate the screen and draw the node
      g.pushMatrix();
        g.translate((float)nodePixel.x, (float)nodePixel.y);      
        node.draw(g);
      g.popMatrix();
    }
  }
}
