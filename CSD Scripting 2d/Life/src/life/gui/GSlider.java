package life.gui;

import life.gui.events.mouse.MouseDragEvent;
import life.gui.events.mouse.MouseEvent;
import life.gui.events.mouse.MousePressEvent;
import life.gui.util.Rect;
import processing.core.PGraphics;

public class GSlider extends GComponent
{
  // Variables
  private final String name;
  private int value;
  private final int min, max;
  
  // Constructor
  public GSlider(GContext context, Rect bounds, String name, int min, int max, int initialValue)
  {
    super(context,bounds);
    
    this.name = name;
    this.min = min;
    this.max = max;
    this.value = initialValue;
    
    this.registerListener(this,MousePressEvent.class,this::onMouseDrag);
    this.registerListener(this,MouseDragEvent.class,this::onMouseDrag);
  }
  
  // Convert a value to a rect
  private Rect valueToRect(int value)
  {
    double fraction = (double)(value - this.min) / (double)(this.max - this.min);
    double right = this.bounds.left + fraction * this.bounds.width();
    
    return new Rect(this.bounds.left,this.bounds.top,right,this.bounds.bottom);
  }
  
  // Convert a rect coordinate to a value
  private int rectToValue(double x)
  {
    double fraction = (x - this.bounds.left) / this.bounds.width();
    return (int)(this.min + fraction * (this.max - this.min));
  }
 
  // Draw the slider
  @Override public void draw(PGraphics g)
  {
    // Draw rect
    g.fill(0,128);
    g.rectMode(PGraphics.CORNERS);
    g.rect((float)this.bounds.left,(float)this.bounds.top,(float)this.bounds.right,(float)this.bounds.bottom);
    
    // Draw value
    Rect valueRect = this.valueToRect(this.value);
    
    g.fill(0);
    g.rectMode(PGraphics.CORNERS);
    g.rect((float)valueRect.left,(float)valueRect.top,(float)valueRect.right,(float)valueRect.bottom);
    
    // Draw text
    g.fill(255);
    g.text(String.format("%s: %d",this.name,this.value),(float)this.bounds.left + 8,(float)this.bounds.bottom - 8);
  }
  
  // Mouse drag event
  public void onMouseDrag(MouseEvent e)
  {
    this.value = this.rectToValue(e.getPosition().x);
    if (this.value < this.min)
      this.value = this.min;
    if (this.value > this.max)
      this.value = this.max;
  }
}
