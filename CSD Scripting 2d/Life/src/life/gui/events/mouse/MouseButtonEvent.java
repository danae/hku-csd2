package life.gui.events.mouse;

import life.gui.util.Point;

public abstract class MouseButtonEvent extends MouseEvent
{
  // Variables
  private final Button button;
  
  // Constructor
  public MouseButtonEvent(Point position, Button button)
  {
    super(position);
    this.button = button;
  }
  
  // Return the mouse button
  public final Button getButton()
  {
    return this.button;  
  }
}
