package life.gui;

import java.util.LinkedList;
import java.util.List;
import java.util.ListIterator;
import life.gui.events.component.ComponentBlurEvent;
import life.gui.events.component.ComponentEnterEvent;
import life.gui.events.component.ComponentFocusEvent;
import life.gui.events.component.ComponentLeaveEvent;
import life.gui.events.keyboard.KeyPressEvent;
import life.gui.events.keyboard.KeyReleaseEvent;
import life.gui.events.keyboard.KeyTypeEvent;
import life.gui.events.mouse.Button;
import life.gui.events.mouse.MouseDragEvent;
import life.gui.events.mouse.MouseMoveEvent;
import life.gui.events.mouse.MousePressEvent;
import life.gui.events.mouse.MouseReleaseEvent;
import life.gui.util.Point;
import life.gui.util.Updateable;
import processing.core.PApplet;
import processing.event.KeyEvent;
import processing.event.MouseEvent;

public class GContext extends PApplet
{
  // List containing the components
  private final List<GComponent> components = new LinkedList<>();
  
  // Reference to the mouse pressed position
  private Point mousePressedPosition = null;
  
  // Reference to the hovered and focused components
  private GComponent hoveredComponent = null;
  private GComponent lastHoveredComponent = null;
  
  private GComponent focusedComponent = null;
  private GComponent lastFocusedComponent = null;
  
  // Timer variables
  private long currentLoop, lastLoop;
  
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
  
  // Return the hovered component
  public GComponent getHoveredComponent()
  {
    return this.hoveredComponent;
  }
  
  // Set the hovered component
  void setHoveredComponent(GComponent component)
  {
    if (!this.components.contains(component))
      throw new IllegalArgumentException(String.format("The component %s is not part of this context",component));
    
    this.hoveredComponent = component;
    
    // TODO: Fire events on the old and new object
  }
  
  // Return the focused component
  public GComponent getFocusedComponent()
  {
    return this.focusedComponent;
  }
  
  // Set the focused component
  void setFocusedComponent(GComponent component)
  {
    if (!this.components.contains(component))
      throw new IllegalArgumentException(String.format("The component %s is not part of this context",component));
    
    this.focusedComponent = component;
    
    // TODO: Fire events on the old and new object
  }
  
  // Setup method
  @Override public void setup()
  {
    // Set the last loop
    this.lastLoop = millis();
  }
  
  // Draw method
  @Override public void draw()
  {
    // Set the current loop
    this.currentLoop = millis();
    
    // Draw a white background
    background(255);
    
    // Iterate over the components and draw and update them
    long elapsedTime = this.currentLoop - this.lastLoop;
    for (GComponent component : this.components)
    {
      component.draw(this.g);
      
      if (component instanceof Updateable)
        ((Updateable)component).update(elapsedTime);
    }
    
    // Set the last loop
    this.lastLoop = this.currentLoop;
  }

  // Methods for handling mouse events
  @Override public void mousePressed(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    
    // Set the mouse pressd position
    this.mousePressedPosition = position;
    
    // Get the focused component
    this.focusedComponent = this.getComponentAt(position);
    
    // Fire a focus event if the focused component changed
    if (this.focusedComponent != this.lastFocusedComponent)
    {
      if (this.lastFocusedComponent != null)
        this.lastFocusedComponent.executeEvent(new ComponentBlurEvent(this.lastHoveredComponent));
      
      if (this.focusedComponent != null)
        this.focusedComponent.executeEvent(new ComponentFocusEvent(this.hoveredComponent));
      
      this.lastFocusedComponent = this.focusedComponent;
    }
    
    // Delegate mouse press events to the hovered component
    if (this.hoveredComponent != null)
      this.hoveredComponent.executeEvent(new MousePressEvent(position,Button.of(e.getButton())));
  }
  @Override public void mouseReleased(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    
    // Reset the mouse pressd position
    this.mousePressedPosition = null;
    
    // Delegate mouse release events to the hovered component
    if (this.hoveredComponent != null)
      this.hoveredComponent.executeEvent(new MouseReleaseEvent(position,this.mousePressedPosition,Button.of(e.getButton())));
  }
  @Override public void mouseMoved(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    
    // Get the hovered component
    this.hoveredComponent = this.getComponentAt(position);
    
    // Fire a hover event if the hovered component changed
    if (this.hoveredComponent != this.lastHoveredComponent)
    {
      if (this.lastHoveredComponent != null)
        this.lastHoveredComponent.executeEvent(new ComponentLeaveEvent(this.lastHoveredComponent));
      
      if (this.hoveredComponent != null)
        this.hoveredComponent.executeEvent(new ComponentEnterEvent(this.hoveredComponent));
      
      this.lastHoveredComponent = this.hoveredComponent;
    }
    
    // Delegate mouse move events to the hovered component
    if (this.hoveredComponent != null)
      this.hoveredComponent.executeEvent(new MouseMoveEvent(position));
  }
  @Override public void mouseDragged(MouseEvent e)
  {
    Point position = new Point(e.getX(),e.getY());
    
    // Delegate mouse drag events to the hovered component
    if (this.hoveredComponent != null)
      this.hoveredComponent.executeEvent(new MouseDragEvent(position,this.mousePressedPosition));
  }
  
  // Methods for handling keyboard events
  @Override public void keyPressed(KeyEvent e)
  {
    // Delegate key press events to the focused component
    if (this.focusedComponent != null)
      this.focusedComponent.executeEvent(new KeyPressEvent(e.getKey(),e.getKeyCode()));
  }
  @Override public void keyReleased(KeyEvent e)
  {
    // Delegate key release events to the focused component
    if (this.focusedComponent != null)
      this.focusedComponent.executeEvent(new KeyReleaseEvent(e.getKey(),e.getKeyCode()));
  }
  @Override public void keyTyped(KeyEvent e)
  {
    // Delegate key type events to the focused component
    if (this.focusedComponent != null)
      this.focusedComponent.executeEvent(new KeyTypeEvent(e.getKey(),e.getKeyCode()));
  }
}
