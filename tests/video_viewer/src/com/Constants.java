package com;

import java.awt.Dimension;

public final class Constants
{
    public static final boolean basicVideoPlayback = false;
    public static final boolean noVideoPlayBack = false;
    
    public static final class INPUT_VIDEO {
        public static final int width = 160;
        public static final int height = 120;
    }

    public static final int frameRateFPS = 25;
    public static final int sliderPadding = 100;

    public static final class WHEEL {
        public static final float defaultRateHz = 0.1f;
        public static final float displacementUpdate = 1.0f; // cm
        public static final float diameter = 64.0f; // cm 
        public static final float displayRadius = 23.5f; // cm
        public static final float centerRadius = 2.75f; // cm
        public static final float cmToPixel = 1.2f; // pixel / cm
        public static final int displayPixels = 28; //(int) (displayRadius * cmToPixel); 
        public static final float displayRadiusInc = 1/cmToPixel;
    }

    public static final class DISPLAY {
        public static final int width = 64;
        public static final int height = 64;
        public static final int hgap = 1;
        public static final int vgap = 1;
        
        public static final int centerX = width/2;
        public static final int centerY = height/2;

        public static final class PIXEL {
            public static final int width = 4;
            public static final int height = 4;
        }

        public static Dimension getSize() {
            return new Dimension(width*(PIXEL.width + hgap), height*(PIXEL.height+vgap));
        }
    }
}
