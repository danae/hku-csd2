package life.gui.events.keyboard;

import life.gui.events.Event;

public class KeyEvent extends Event
{
  // Variables
  private final char key;
  private final int keyCode;
  
  // Constructor
  public KeyEvent(char key, int keyCode)
  {
    this.key = key;
    this.keyCode = keyCode;
  }
  
  // Return the key
  public char getKey()
  {
    return this.key;
  }
  
  // Return the key code
  public int getKeyCode()
  {
    return this.keyCode;
  }
}
