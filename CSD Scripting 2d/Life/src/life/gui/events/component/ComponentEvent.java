
package life.gui.events.component;

import life.gui.GComponent;
import life.gui.events.Event;

public abstract class ComponentEvent extends Event
{
  // Variables
  private final GComponent component;
  
  // Constructor
  public ComponentEvent(GComponent component)
  {
    this.component = component;
  }
  
  // Return the component
  public GComponent getComponent()
  {
    return this.component;
  }
}
