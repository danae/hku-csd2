package life.gui.events;

import life.gui.GComponent;

public class RegisteredListener<E extends Event>
{
  // The component that registered the listener
  final GComponent observer;
  
  // The event class that this listener listens to
  final Class<E> eventClass;
  
  // The actual listener
  final Listener<E> listener;
  
  // Constructor
  RegisteredListener(GComponent observer, Class<E> eventClass, Listener<E> listener)
  {
    this.observer = observer;
    this.eventClass = eventClass;
    this.listener = listener;
  }
}
