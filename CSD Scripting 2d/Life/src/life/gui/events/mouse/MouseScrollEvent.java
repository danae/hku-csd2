package life.gui.events.mouse;

import life.gui.util.Point;

public class MouseScrollEvent extends MouseMoveEvent
{
  // Variables
  private final double offset;
  
  // Constructor
  public MouseScrollEvent(Point position, double offset)
  {
    super(position);
    this.offset = offset;
  }
  
  // Return the scroll offset
  public final double getOffset()
  {
    return this.offset;  
  }
  
  // Return the direction of the scroll
  public final double getDirection()
  {
    return Math.signum(this.offset);
  }
}
