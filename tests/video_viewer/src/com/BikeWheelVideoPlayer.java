package com;

import java.awt.Color;
import java.io.File;

public class BikeWheelVideoPlayer extends AbstractVideoPlayer
{
    private static final Color led0Color = Color.red;
    private static final Color led1Color = Color.green;
    private static final Color led2Color = Color.blue;
    private static final Color led3Color = Color.orange;
    
    private static final float PI_OVER_2 = (float)Math.PI / 2.0f;
    private int displayUpdateFreqHz;
    
    
    public BikeWheelVideoPlayer(DisplayPanel display)
    {      
        super(display);
        displayUpdateFreqHz = 1;
    }

    @Override 
    public boolean startPlayback(String path) {
        rawFile = new File(path);
        if(!rawFile.exists())
            return false;
        
        isRunning = true;
        
        super.start();
        new DisplayUpdaterThread().start();
        new WheelSimulatorThread().start();
        
        return true;
    }
    
    
    private void updateDisplay() {
        
        display.fillDisplay();
        
        long tNow = System.currentTimeMillis();
        
        float currentWheelAngle = sensorAngleLookup[sensorCounter] + PI_OVER_2 * (float)(tNow - tSx) / (float)(tSx - tSx_1);
 
        float radiusX = Constants.WHEEL.centerRadius;
        float radiusY = Constants.WHEEL.centerRadius;
        
        for(int p = 0; p < Constants.WHEEL.displayPixels; ++p) {
            
            float offsetX = radiusX * (float)Math.cos(currentWheelAngle) * Constants.WHEEL.cmToPixel;
            float offsetY = radiusY * (float)Math.sin(currentWheelAngle) * Constants.WHEEL.cmToPixel;
            
            float offsetX2 = radiusX * (float)Math.cos(currentWheelAngle - PI_OVER_2) * Constants.WHEEL.cmToPixel;
            float offsetY2 = radiusY * (float)Math.sin(currentWheelAngle - PI_OVER_2) * Constants.WHEEL.cmToPixel;

            
            if(Constants.noVideoPlayBack)
            {
            display.setPixel(
                    Constants.DISPLAY.centerX + (int)offsetX, 
                    Constants.DISPLAY.centerX + (int)offsetY, 
                    led0Color);
            display.setPixel(
                    Constants.DISPLAY.centerX + (int)offsetX2, 
                    Constants.DISPLAY.centerX + (int)offsetY2, 
                    led1Color);
            display.setPixel(
                    Constants.DISPLAY.centerX - (int)offsetX, 
                    Constants.DISPLAY.centerX - (int)offsetY, 
                    led2Color);
            display.setPixel(
                    Constants.DISPLAY.centerX - (int)offsetX2, 
                    Constants.DISPLAY.centerX - (int)offsetY2, 
                    led3Color);
            } else {
                int x, y, cr, xb, cg, cb;
                x = Constants.DISPLAY.centerX + (int)offsetX;
                y = Constants.DISPLAY.centerX + (int)offsetY;
                cr = frameBuffer[y][x+0] & 0xff;
                cg = frameBuffer[y][x+1] & 0xff;
                cb = frameBuffer[y][x+2] & 0xff;

                display.setPixel(x, y, cr, cg, cb);
                
                x = Constants.DISPLAY.centerX + (int)offsetX2;
                y = Constants.DISPLAY.centerX + (int)offsetY2;
                cr = frameBuffer[y][x+0] & 0xff;
                cg = frameBuffer[y][x+1] & 0xff;
                cb = frameBuffer[y][x+2] & 0xff;
                
                display.setPixel(x, y, cr, cg, cb);
                
                x = Constants.DISPLAY.centerX - (int)offsetX;
                y = Constants.DISPLAY.centerX - (int)offsetY;
                cr = frameBuffer[y][x+0] & 0xff;
                cg = frameBuffer[y][x+1] & 0xff;
                cb = frameBuffer[y][x+2] & 0xff;

                display.setPixel(x, y, cr, cg, cb);
                
                x = Constants.DISPLAY.centerX - (int)offsetX2;
                y = Constants.DISPLAY.centerX - (int)offsetY2;
                cr = frameBuffer[y][x+0] & 0xff;
                cg = frameBuffer[y][x+1] & 0xff;
                cb = frameBuffer[y][x+2] & 0xff;

                display.setPixel(x, y, cr, cg, cb);
            }

            radiusX += Constants.WHEEL.displayRadiusInc;
            radiusY += Constants.WHEEL.displayRadiusInc;
        }
        
       
        
    }
    
    
    
    private volatile int sensorCounter = 0;
    private volatile long tSx_1 = 0;
    private volatile long tSx = System.currentTimeMillis();

    
    private float[] sensorAngleLookup = {
            0, // S0
            (float)Math.PI/2.0f, // S1
            (float)Math.PI, // S2
            3.0f*(float)Math.PI/2.0f, // S3
    };
    
    private void hallEffectExternalInterruptISR() {
        sensorCounter = (sensorCounter+1) & 0x03;
        tSx_1 = tSx;
        tSx = System.currentTimeMillis();
     
        float w = PI_OVER_2 * 1000.0f / (float)(tSx - tSx_1);
        displayUpdateFreqHz = 1000;//(int) (Constants.WHEEL.diameter/2.0f * w / Constants.WHEEL.displacementUpdate);
        
        //System.out.printf("w = %f, f = %d\n", w, displayUpdateFreqHz);
    }
    
    
    @Override
    protected void processFrameBuffer(){}
    
    
    
    
    
    
    
    private class DisplayUpdaterThread extends Thread {
        @Override 
        public void run() {
            
            while(isRunning) {
                
                try
                {
                    updateDisplay();
                    Thread.sleep((long)(1000.0f / displayUpdateFreqHz));
                } catch (InterruptedException e)  {}
            }
        }
    }
    
    
    private class WheelSimulatorThread extends Thread {
        @Override 
        public void run() {
            
            while(isRunning) {
                hallEffectExternalInterruptISR();
                try
                {
                    // 1000/4
                    // 4 because we have 4 sensors 90deg apart
                    // 1000 to convert to ms
                    Thread.sleep((long)(250.0f / DynamicParameters.getBikeWheelRateHz()));
                } catch (InterruptedException e)  {}
            }
        }
    }

}
