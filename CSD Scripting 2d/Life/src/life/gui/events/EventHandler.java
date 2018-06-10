package life.gui.events;

import java.util.List;
import java.util.concurrent.CopyOnWriteArrayList;
import life.gui.GComponent;

public class EventHandler
{
  // List of registered listeners
  private final List<RegisteredListener> listeners = new CopyOnWriteArrayList<>();
  
  // Register a listener
  public final <E extends Event> void registerListener(GComponent observer, Class<E> eventClass, Listener<E> listener)
  {
    this.listeners.add(new RegisteredListener(observer,eventClass,listener));
  }
  
  // Unregister a listener
  public final <E extends Event> void unregisterListener(Listener<E> listener)
  {
    // Iterate over the listeners
    for (RegisteredListener registeredListener : this.listeners)
    {
      // If this is the listener, then remove it
      if (registeredListener.listener.equals(listener))
        this.listeners.remove(registeredListener);
    }
  }
  
  // Execute an event
  public final <E extends Event> void executeEvent(E event)
  {
    // Iterate over the listeners
    for (RegisteredListener registeredListener : this.listeners)
    {
      // If this listener listens for this event
      if (registeredListener.eventClass.isAssignableFrom(event.getClass()))
      {
        // Handle the event
        registeredListener.listener.handle(event);
        
        // If the event is cancelled, then break
        if (event.isCancelled())
          break;
      }
    }
  }
}
