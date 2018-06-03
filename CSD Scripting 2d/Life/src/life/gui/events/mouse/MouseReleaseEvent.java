package life.gui.events.mouse;

import life.gui.util.Point;

public class MouseReleaseEvent extends MouseButtonEvent
{
  // Constructor
  public MouseReleaseEvent(Point position, Button button)
  {
    super(position,button);
  }
}
