package life.gui.events.mouse;

import life.gui.util.Point;

public class MouseDragEvent extends MouseEvent
{
  // Variables
  private final Point initialPosition;
  
  // Constructor
  public MouseDragEvent(Point position, Point initialPosition)
  {
    super(position);
    
    this.initialPosition = initialPosition;
  }
  
  // Return the initial position (where the mouse was pressed)
  public Point getInitialPosition()
  {
    return this.initialPosition;
  }
  
  // Return the delta distance from the current position to the initial position
  public Point getDelta()
  {
    return this.getPosition().subtract(this.getInitialPosition());
  }
}
