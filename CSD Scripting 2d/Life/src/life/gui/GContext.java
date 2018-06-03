package life.gui;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import life.gui.events.keyboard.KeyPressEvent;
import life.gui.events.keyboard.KeyReleaseEvent;
import life.gui.events.keyboard.KeyTypeEvent;
import life.gui.events.mouse.Button;
import life.gui.events.mouse.MouseDragEvent;
import life.gui.events.mouse.MouseMoveEvent;
import life.gui.events.mouse.MousePressEvent;
import life.gui.events.mouse.MouseReleaseEvent;
import life.gui.util.Point;
import processing.core.PApplet;
import processing.event.KeyEvent;
import processing.event.MouseEvent;

public class GContext extends PApplet
{
  // List containing the components
  private final List<GComponent> components = new LinkedList<>();
  
  // Reference to the hovered and focused components
  private GComponent hoveredComponent = null;
  private GComponent focusedComponent = null;
  
  // Return a list of all components
  public List<GComponent> getComponents()
  {
    return this.components;
  }
  
  // Return the topmost component at a position
  private GComponent getComponentAt(Point point)
  {
    // Create a reverse list iterator
    ListIterator<GComponent> it = this.components.listIterator(this.components.size());
    while (it.hasPrevious())
    {
      GComponent component = it.previous();
      
      // If this component is a the specified position, then return it
      if (component.getBounds().contains(point))
        return component;
    }
    
    // Nothing found, so return null
    return null;
  }
  
  // Add a component
  public void addComponent(GComponent component)
  {
    this.components.add(component);
  }
  
  // Draw method
  @Override public void draw()
  {
    // Draw a white background
    background(0);
    
    // Iterate over the components and draw them
    for (GComponent component : this.components)
      component.draw(this.g);
  }

  // Methods for handling mouse events
  @Override public void mousePressed(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    if (this.hoveredComponent != null)
      this.hoveredComponent.executeEvent(new MousePressEvent(position,Button.of(e.getButton())));
  }
  @Override public void mouseReleased(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    if (this.hoveredComponent != null)
      this.hoveredComponent.executeEvent(new MouseReleaseEvent(position,Button.of(e.getButton())));
  }
  @Override public void mouseMoved(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    
    // Change the hovered component
    this.hoveredComponent = this.getComponentAt(position);
    
    if (this.hoveredComponent != null)
      this.hoveredComponent.executeEvent(new MouseMoveEvent(position));
  }
  @Override public void mouseDragged(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    if (this.hoveredComponent != null)
    {
      this.hoveredComponent.executeEvent(new MouseMoveEvent(position));
      this.hoveredComponent.executeEvent(new MouseDragEvent(position));
    }
  }
  
  // Methods for handling keyboard events
  @Override public void keyPressed(KeyEvent e)
  {
    if (this.focusedComponent != null)
      this.focusedComponent.executeEvent(new KeyPressEvent(e.getKey(),e.getKeyCode()));
  }
  @Override public void keyReleased(KeyEvent e)
  {
    if (this.focusedComponent != null)
      this.focusedComponent.executeEvent(new KeyReleaseEvent(e.getKey(),e.getKeyCode()));
  }
  @Override public void keyTyped(KeyEvent e)
  {
    if (this.focusedComponent != null)
      this.focusedComponent.executeEvent(new KeyTypeEvent(e.getKey(),e.getKeyCode()));
  }
}
