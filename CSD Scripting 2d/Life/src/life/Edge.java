package life;

public class Edge
{
  // The parent grid of the edge
  protected final Life grid;
  
  // Start and end nodes
  private final Node start, end;
  
  // Constructor
  public Edge(Life grid, Node start, Node end)
  {
    this.grid = grid;
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
