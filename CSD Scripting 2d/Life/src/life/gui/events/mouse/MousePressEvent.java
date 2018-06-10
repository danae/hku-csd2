package life.gui.events.mouse;

import life.gui.util.Point;

public class MousePressEvent extends MouseButtonEvent
{
  // Constructor
  public MousePressEvent(Point position, Button button)
  {
    super(position,button);
  }
}
