package life.gui.events;

public abstract class Event
{
  // Functional implementation left for subclasses
  
  // Variables
  boolean cancelled = false;
  
  // Return if this event is cancelled
  public boolean isCancelled()
  {
    return this.cancelled;
  }
  
  // Set if this event is cancelled
  public void setCancelled(boolean cancelled)
  {
    this.cancelled = cancelled;
  }
}
