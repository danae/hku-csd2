package com.dengsn.life.graph;

public class Edge
{
  // Start and end nodes
  private final Node start, end;
  
  // Constructor
  public Edge(Node start, Node end)
  {
    this.start = start;
    this.end = end;
  }
  
  // Return the start and end nodes
  public Node getStart()
  {
    return this.start;
  }
  public Node getEnd()
  {
    return this.end;
  }
}
