package com;

import java.awt.EventQueue;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;


public class VideoViewerMain
{

    /**
     * @param args
     */
    public static void main(String[] args)
    {
        System.setProperty("java.util.Arrays.useLegacyMergeSort", "true");
        //Use native L&F
        try {
            UIManager.setLookAndFeel (UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException | InstantiationException
                | IllegalAccessException | UnsupportedLookAndFeelException e) {
            e.printStackTrace();
        }
        EventQueue.invokeLater(new Runnable() {
            @Override
            public void run() {
               new VideoViewer();
            }
        });

    }

}
