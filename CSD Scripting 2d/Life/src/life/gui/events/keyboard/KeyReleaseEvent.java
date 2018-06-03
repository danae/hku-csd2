package life.gui.events.keyboard;

public class KeyReleaseEvent extends KeyEvent
{
  // Constructor
  public KeyReleaseEvent(char key, int keyCode)
  {
    super(key,keyCode);
  }
}
