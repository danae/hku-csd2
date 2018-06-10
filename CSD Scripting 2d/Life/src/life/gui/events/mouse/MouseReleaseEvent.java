package life.gui.events.mouse;

import life.gui.util.Point;

public class MouseReleaseEvent extends MouseButtonEvent
{
  // Variables
  private final Point initialPosition;
  
  // Constructor
  public MouseReleaseEvent(Point position, Point initialPosition, Button button)
  {
    super(position,button);
    
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
