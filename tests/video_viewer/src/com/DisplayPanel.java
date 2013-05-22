package com;

import java.awt.Color;
import java.awt.GridLayout;

import javax.swing.JPanel;

public class DisplayPanel extends JPanel
{
   
    private static final long serialVersionUID = 5303516101772649769L;
    
    private Pixel displayMatrix[][];

    public DisplayPanel() {
        setLayout(new GridLayout(Constants.DISPLAY.height, 
                Constants.DISPLAY.width, 
                Constants.DISPLAY.hgap, 
                Constants.DISPLAY.vgap));
        setSize(Constants.DISPLAY.getSize());
        setPreferredSize(Constants.DISPLAY.getSize());
        
        displayMatrix = new Pixel[Constants.DISPLAY.height][Constants.DISPLAY.width];
        
        for(int r = 0; r < Constants.DISPLAY.height; ++r) {
            for(int c = 0; c < Constants.DISPLAY.width; ++c) {
                Pixel p = new Pixel();
                displayMatrix[r][c] = p;
                add(p);
            }
        }
    }
    
    public Pixel[][] getDisplayMatrix() {
        return displayMatrix;
    }
    
    public void refresh() {
        updateUI();
    }
    
    public void setPixel(int x, int y, int cr, int cg, int cb) {
        Pixel p = displayMatrix[y][x];
        p.setColor(cr, cg, cb);
    }
    
    public void setPixel(int x, int y, Color c) {
        Pixel p = displayMatrix[y][x];
        p.setColor(c);
    }
    
    public void clearDisplay() {
        for(int r = 0; r < Constants.DISPLAY.height; ++r) {
            for(int c = 0; c < Constants.DISPLAY.width; ++c) {
                Pixel p = displayMatrix[r][c];
                p.setColor(255, 255, 255);
            }
        }
    }
    
    public void fillDisplay() {
        for(int r = 0; r < Constants.DISPLAY.height; ++r) {
            for(int c = 0; c < Constants.DISPLAY.width; ++c) {
                Pixel p = displayMatrix[r][c];
                p.setColor(128, 128, 128);
            }
        }
    }
    
    public void showRandomPixels() {
        for(int r = 0; r < Constants.DISPLAY.height; ++r) {
            for(int c = 0; c < Constants.DISPLAY.width; ++c) {
                Pixel p = displayMatrix[r][c];
                int cr = (int)(Math.random() * ((255 - 0) + 1));
                int cg = (int)(Math.random() * ((255 - 0) + 1));
                int cb = (int)(Math.random() * ((255 - 0) + 1));
                p.setColor(cr, cg, cb);
            }
        }
    }
}
