package com;

public class BasicVideoPlayer extends AbstractVideoPlayer
{

    public BasicVideoPlayer(DisplayPanel display)
    {
        super(display);
    }

    @Override
    protected void processFrameBuffer()
    {
        for(int r = 0; r < Constants.DISPLAY.height; ++r) {
            int offset = 0;
            for(int c = 0; c < Constants.DISPLAY.width; ++c, offset += 3) {
                int cr = frameBuffer[r][offset+0] & 0xff;
                int cg = frameBuffer[r][offset+1] & 0xff;
                int cb = frameBuffer[r][offset+2] & 0xff;
                displayMatrix[r][c].setColor(cr, cg, cb);
            }
        }
        
        
    }

}
