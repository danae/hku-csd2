package life.nodes;

import life.Node;
import java.util.Random;
import life.Grid;
import life.gui.hexagon.Hex;
import net.beadsproject.beads.data.Buffer;
import net.beadsproject.beads.ugens.Gain;
import net.beadsproject.beads.ugens.WavePlayer;
import processing.core.PGraphics;

public class GeneratorNode extends Node
{
  // Audo components
  public final WavePlayer wavePlayer;
  public final Gain gain;
  
  // Constructor
  public GeneratorNode(Grid grid, Hex position)
  {
    super(grid,position);
    
    Random r = new Random();
    this.wavePlayer = new WavePlayer(this.grid.audioContext,r.nextInt(400) + 400,Buffer.SINE);
    
    this.gain = new Gain(this.grid.audioContext,1,0.2f);
    this.gain.addInput(this.wavePlayer);
    
    this.grid.audioContext.out.addInput(this.gain);
  }
  
  // Draw the unit
  @Override public void draw(PGraphics g)
  {
    g.noStroke();
    g.fill(0,128,255);
    
    this.position.layout(this.grid.layout).draw(g);
  } 
  
  // Change the X value
  @Override public void changeX(double x)
  {
    // Nothing to be done
  }
  
  // Change the Y value
  @Override public void changeY(double y)
  {
    this.wavePlayer.setFrequency((float)y * 10.0f);
  }

  // Handle neighboring nodes
  @Override public void handleNeighbor(Node neighbor)
  {
    // Nothing to be done
  }
}
