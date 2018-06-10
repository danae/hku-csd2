package life.gui.events;

public interface Listener<E extends Event>
{
  // Handle an event
  public void handle(E event);
}
