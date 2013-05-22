package com;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

public abstract class AbstractVideoPlayer extends Thread
{
    protected DisplayPanel display;
    protected Pixel displayMatrix[][];

    protected byte frameBuffer[][];
    protected byte rawBuffer[];
    protected File rawFile;
    protected boolean isRunning;

    public AbstractVideoPlayer(DisplayPanel display) {
        this.display = display;
        this.displayMatrix = display.getDisplayMatrix();
        this.isRunning = false;

        frameBuffer = new byte[Constants.DISPLAY.height][Constants.DISPLAY.width*3];
        rawBuffer = new byte[Constants.INPUT_VIDEO.width*Constants.INPUT_VIDEO.height*4];
    }

    public boolean startPlayback(String path) {
        rawFile = new File(path);
        if(!rawFile.exists())
            return false;

        isRunning = true;

        this.start();

        return true;
    }

    protected void populateFrameBuffer() {
        int marginX = ((Constants.INPUT_VIDEO.width - Constants.DISPLAY.width) / 2)*4;
        int marginY = ((Constants.INPUT_VIDEO.height - Constants.DISPLAY.height) / 2)*4;
        int rawIdx = marginY * Constants.INPUT_VIDEO.width;
        
        for(int r = 0; r < Constants.DISPLAY.height; ++r) {
            rawIdx += marginX; // skip left margin
            for(int c = 0; c < Constants.DISPLAY.width*3; c += 3) {
                ++rawIdx; // skip blank byte
                frameBuffer[r][c + 0] = rawBuffer[rawIdx++]; // r
                frameBuffer[r][c + 1] = rawBuffer[rawIdx++]; // g
                frameBuffer[r][c + 2] = rawBuffer[rawIdx++]; // b
            }
            rawIdx += marginX; // skip right margin
        }
    }

    protected abstract void processFrameBuffer();




    @Override
    public void run() {
        InputStream inStream = null;

        if(!Constants.noVideoPlayBack) {
            while(true) {
                try {
                    inStream = new FileInputStream(rawFile);
                    //int frameCount = 0;
                    while(inStream.read(rawBuffer) == rawBuffer.length) {
                        populateFrameBuffer();
                        processFrameBuffer();
                        display.refresh();
                        //System.out.println("Frame: " + frameCount++);
                        Thread.sleep(1000/Constants.frameRateFPS);
                    }
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                    isRunning = false;
                }


                try {
                    inStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                    isRunning = false;
                }
            }

        } else {
            while(true) {
                populateFrameBuffer();
                processFrameBuffer();
                display.refresh();
                //System.out.println("Frame: " + frameCount++);
                try
                {
                    Thread.sleep(1000/Constants.frameRateFPS);
                } catch (InterruptedException e)
                {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        }
    }
}
