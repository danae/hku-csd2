package life.gui.events.mouse;

import life.gui.events.Event;
import life.gui.util.Point;

public abstract class MouseEvent extends Event
{
  // Variables
  private final Point position;
  
  // Constructor
  public MouseEvent(Point position)
  {
    this.position = new Point(position);
  }
  
  // Return the position
  public final Point getPosition()
  {
    return this.position;  
  }
}
