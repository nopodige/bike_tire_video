package com;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.JComponent;

public class Pixel extends JComponent
{
    private static final long serialVersionUID = 6366738114850213119L;
    
    private Color c;
    
    public Pixel() {
        setSize(Constants.DISPLAY.PIXEL.width, Constants.DISPLAY.PIXEL.height);
        setOpaque(true);
        c = Color.black;
    }
    
    public void setColor(int r, int g, int b) {
        c = new Color(r, g, b);
    }
    
    public void setColor(Color c) {
       this.c = c;
    }
    
    @Override
    public void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        graphics.setColor(this.c);
        graphics.fillRect(0, 0, Constants.DISPLAY.PIXEL.width, Constants.DISPLAY.PIXEL.height);
    }

    public int getR()
    {
        return c.getRed();
    }

    public int getG()
    {
        return c.getGreen();
    }

    public int getB()
    {
        return c.getBlue();
    }
    
    
}
