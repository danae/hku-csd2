package com.dengsn.life.grid;

// GridOrientation class
// Code mostly adapted from https://www.redblobgames.com/grids/hexagons/
public class GridOrientation
{
  // Variables
  public final double f0, f1, f2, f3;
  public final double b0, b1, b2, b3;
  public final double startAngle;
  
  // Constructor
  public GridOrientation(double f0, double f1, double f2, double f3, double b0, double b1, double b2, double b3, double startAngle)
  {
    this.f0 = f0;
    this.f1 = f1;
    this.f2 = f2;
    this.f3 = f3;
    this.b0 = b0;
    this.b1 = b1;
    this.b2 = b2;
    this.b3 = b3;
    this.startAngle = startAngle;
  }
  
  // Constants that define the two orientations:
  // POINTY defines a grid with the pointy side of the hex upwards
  public static final GridOrientation POINTY = new GridOrientation(
    Math.sqrt(3.0), Math.sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
    Math.sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
    0.5);
  // FLAT defines a grid with the flat side of the hex upwards
  public static final GridOrientation FLAT = new GridOrientation(
    3.0 / 2.0, 0.0, Math.sqrt(3.0) / 2.0,  Math.sqrt(3.0),
    2.0 / 3.0, 0.0, -1.0 / 3.0, Math.sqrt(3.0) / 3.0,
    0.0);
}
