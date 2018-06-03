package life.gui;

import life.gui.events.EventHandler;
import life.gui.util.Drawable;
import life.gui.util.Rect;

public abstract class GComponent extends EventHandler implements Drawable
{
  // Reference to the context
  protected final GContext context;
  
  // Boundaries of this component
  protected final Rect bounds;
  
  // Constructor
  public GComponent(GContext context, Rect bounds)
  {
    this.context = context;
    this.bounds = bounds;
  }
  
  // Return the context
  public GContext getContext()
  {
    return this.context;
  }
  
  // Return the boundaries
  public Rect getBounds()
  {
    return this.bounds;
  }
}
