package life.gui.events.mouse;

import java.util.*;
import processing.core.*;

public enum Button
{
  // Values
  LEFT(PConstants.LEFT),
  RIGHT(PConstants.RIGHT),
  MIDDLE(PConstants.CENTER);
  
  // Variable to hold the Processing button
  private final int processingButton;
  
  // Constructor
  private Button(int processingButton)
  {
    this.processingButton = processingButton;
  }
  
  // Convert from a processing mouse button
  public static Button of(int processingButton)
  {
    return Arrays.stream(Button.values())
      .filter(mouseButton -> mouseButton.processingButton == processingButton)
      .findFirst()
      .orElseThrow(() -> new IllegalArgumentException(String.format("%d is not a valid Processing mouse button constant",processingButton)));
  }
}
